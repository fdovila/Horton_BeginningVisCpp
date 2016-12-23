//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Card.h"
#include <algorithm>
#include <ctime>

using namespace MemoryTest;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()  : card1Up(nullptr), card2Up(nullptr), pairCount(0)
{
	InitializeComponent();

	srand(static_cast<unsigned int>(time(nullptr)));

	// Brushes for card colors
	steelBrush = ref new SolidColorBrush(Windows::UI::Colors::SteelBlue);
	azureBrush = ref new SolidColorBrush(Windows::UI::Colors::Azure);

	// cardCount is number of rows x number of columns in cardGrid
	cardCount = cardGrid->ColumnDefinitions->Size*cardGrid->RowDefinitions->Size;
	pairsFound = ref new Platform::Collections::Vector<Card^>(cardCount);

	// Initialize type names for card elements
	typeCircle = Ellipse::typeid->FullName;
	typeSquare = Rectangle::typeid->FullName;
	typeTriangle = Polygon::typeid->FullName;

	// Create arrays that will store element handles for the cards
	// Each type is in a separate array and will be stored in sequence
	circles = ref new Array<Ellipse^>(cardCount);
	triangles = ref new Array<Polygon^>(cardCount);
	squares = ref new Array<Rectangle^>(cardCount);
	cardBacks = ref new Array<TextBlock^>(cardCount);
	grids = ref new Array<Grid^>(cardCount);

	InitializeCardPack();
	SetUpUIState();
	InitializeGame();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void MemoryTest::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Scale all card shapes so they squarely fit their grid cells.

	// Iterate over all children of the cardGrid grid.
	for (unsigned int i = 0; i < cardGrid->Children->Size; ++i)
	{
		// Get the small grid in each cell.
    Grid^ grid = safe_cast<Grid^>(cardGrid->Children->GetAt(i));

    // Get the small grid inside the small grid.
    Grid^ childGrid = safe_cast<Grid^>(grid->Children->GetAt(0));

    // Calculate the scaling factor to keep everything square.
    auto scale = grid->ActualHeight / childGrid->ActualHeight * 0.7;

    // Apply scaling factor.
    auto scaleTransform = ref new ScaleTransform();
    scaleTransform->ScaleX = scale;
    scaleTransform->ScaleY = scale;
    childGrid->RenderTransformOrigin = Point(0.5, 0.5);
    childGrid->RenderTransform = scaleTransform;
  }
}


void MemoryTest::MainPage::Shape_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  // With this event there is always at least one card up but could be two.
  // If only one card is up, the handle is in card1Up
  Shape^ shape = safe_cast<Shape^>(sender);
  if(card1Up != nullptr && card2Up != nullptr)
  {  // Two cards up so turn over both cards
    card1Up->shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed;  
    card1Up->back->Visibility = Windows::UI::Xaml::Visibility::Visible;       
    card2Up->shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed;   
    card2Up->back->Visibility = Windows::UI::Xaml::Visibility::Visible;

    // Enable events for all card backs and background grids
    for(size_t i = 0 ; i < cardBacks->Length ; ++i)
    {
      if(IsFound(cardBacks[i]))
        continue;

      cardBacks[i]->IsTapEnabled = true;
      grids[i]->IsHitTestVisible = true;
    }
    card1Up = card2Up = nullptr;  // Reset both handles to cards up
  }
  else
  {  // only one card up and it was clicked so turn over the card
    card1Up->shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed; 
    card1Up->back->Visibility = Windows::UI::Xaml::Visibility::Visible;
    card1Up = nullptr;
  }
}


void MemoryTest::MainPage::Cardback_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{ // There may be 0 or 1 cards already turn over
  // If there is 1, the card handle will be in Card1Up
  TextBlock^ cardBack = safe_cast<TextBlock^>(sender);                 // Always a card back handle
  cardBack->Visibility = Windows::UI::Xaml::Visibility::Collapsed;     // Hide the back

  // Find the card for the back so the shape can be made visible
  Card^ theCard(nullptr);
  for(auto card : cardPack)
  {
    if(cardBack == card->back)
    { // We have found the card so show the front
      card->shape->Visibility = Windows::UI::Xaml::Visibility::Visible;
      theCard = card;
      break;
    }
  }
  if(card1Up == nullptr)
  {
    card1Up = theCard;
  }
  else
  {
    card2Up = theCard;
    if(card1Up->type == card2Up->type && card1Up->color == card2Up->color)
    { // We have a pair!
      pairsFound->Append(card1Up);
      pairsFound->Append(card2Up);
      DisableCardUp(card1Up);
      DisableCardUp(card2Up);
      card1Up = card2Up = nullptr;
      if(++pairCount == cardCount/2)
        GameOver();
    }
    else
    { // Two cards up but no pair so we now want a Tapped event on either
      // Disable Tapped event for card backs and PointerEntered 
      // and PointerExited events for other cards
      for(size_t i = 0 ; i < cardBacks->Length ; ++i)
      {
        if(cardBacks[i] == card1Up->back || cardBacks[i] == card2Up->back)
          continue;

        cardBacks[i]->IsTapEnabled = false;
        grids[i]->IsHitTestVisible = false;
      }
    }
  } 
}


void MemoryTest::MainPage::Card_Entered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	safe_cast<Grid^>(sender)->Background = steelBrush;
}


void MemoryTest::MainPage::Card_Exited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	safe_cast<Grid^>(sender)->Background = azureBrush;
}

// Initialize the pack of cards so it contains 12 different pairs
void MainPage::InitializeCardPack()
{
  // Create arrays of the shape types and colors
  Array<String^>^ shapeTypes = {typeCircle, typeSquare, typeTriangle};
  Array<SolidColorBrush^>^ colors = {
                             ref new SolidColorBrush(Windows::UI::Colors::Red),
                             ref new SolidColorBrush(Windows::UI::Colors::Green),
                             ref new SolidColorBrush(Windows::UI::Colors::Blue),
                             ref new SolidColorBrush(Windows::UI::Colors::Yellow)
                                    };

  // Initialize the card pack
  cardPack = ref new Array<Card^>(cardCount);
  size_t packIndex(0);                                                 // Index to cardPack array
  Card^ card;
  for(auto color : colors)
  {
    for(auto shapeType : shapeTypes)
    {
      card = ref new Card();                                           // Create a card...
      card->type = shapeType;                                          // with the current type...
      card->color = color;                                             // ... and color
      card->shape = nullptr;                                           // we will find the shape...
      card->back = nullptr;                                            // ...and back later.
      cardPack[packIndex++] = card;                                    // Store the card in the pack...
      cardPack[packIndex++] = ref new Card(card);                      // ...and a copy.
    }
  }
}

// Sets up the initial state of the UI and stores elements in grid cell order 
void MainPage::SetUpUIState()
{
  // Handle to the collection of grids in cardGrid
  auto elements = cardGrid->Children;                   
  
  UIElement^ element;                                                  // Handle to a collection element
  Grid^ grid;
  UIElementCollection^ shapes;                                         // Handle to collection of shapes in a child-grid
  UIElement^ shape;                                                    // Handle to a shape in  a child-grid

  int row(0);                                                          // Child-grid grid row location
  int column(0);                                                       // Child-grid grid column location
  int index(0);                                                        // Index to shape arrays
  unsigned int rowLength(cardGrid->ColumnDefinitions->Size);           // Length of a grid row

  // Iterate over the child elements to cardGrid and store 
  // the Grid^ handles in the grids array in sequence
  for(size_t i = 0 ; i < elements->Size ; ++i)
  {
    element = elements->GetAt(i);                                       // Get next grid child...
    String^ elementType = element->GetType()->FullName;                 // ...and get its type
    if(Grid::typeid->FullName == elementType)                           // Make sure it's a Grid
    {
      grid = safe_cast<Grid^>(element);					                        // Get the child grid of the grid
      row = cardGrid->GetRow(grid);                                     // Get the grid row 
      column = cardGrid->GetColumn(grid);                               // and column location. 
      index = row*rowLength + column;                                   // Array index for row/column
      grids[index] = grid;                                              // Save the grid - it's background
	  // A grid in each cell contains another grid as child.
	  // We know that's always the case so cast to type Grid:
	  grid = safe_cast<Grid^>(grid->Children->GetAt(0));

      shapes = grid->Children;                                           // Get the child shapes
      // Iterate over the child elements to the current Grid and store
      // the shape element handles in the array for their type in sequence
      for(size_t j = 0 ; j < shapes->Size ; ++j)
      {
        element = shapes->GetAt(j);                                     // Get child shape handle
        elementType = element->GetType()->FullName;                     // and its type

        // Store a circle in circles array & do the same for the other elements
        // Only card backs will be visible - all other shapes collapsed.
        if(typeCircle == elementType)
        {
          circles[index] = safe_cast<Ellipse^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if(typeSquare == elementType)
        {
          squares[index] = safe_cast<Rectangle^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if(typeTriangle == elementType)
        {
         triangles[index] = safe_cast<Polygon^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if(TextBlock::typeid->FullName == elementType)
        {
          cardBacks[index] = safe_cast<TextBlock^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Visible;
        }
      }
    }
  }
}

// Shuffle the cards and deal
void MainPage::InitializeGame()
{
  card1Up = card2Up = nullptr;                                         // No cards up
  pairCount = 0;                                                       // No pairs found
  pairsFound->Clear();                                                 // Clear pairs record

  // Null the handles to UI elements
  for(auto card : cardPack)
  {
    card->shape = nullptr;
    card->back = nullptr;
  }

  ShuffleCards();                                                      // Shuffle cardPack

  // Set the shapes in the Grid elements to represent the cards dealt
  for(size_t i = 0 ; i < cardCount ; ++i)
  {
    cardPack[i]->back = cardBacks[i];

    if(cardPack[i]->type == typeCircle)
    {
      circles[i]->Fill = cardPack[i]->color;
      cardPack[i]->shape = circles[i];
    } 
    else if(cardPack[i]->type == typeSquare)
    {
      squares[i]->Fill = cardPack[i]->color;
      cardPack[i]->shape = squares[i];
    }
    else if(cardPack[i]->type == typeTriangle)
    {
      triangles[i]->Fill = cardPack[i]->color;
      cardPack[i]->shape = triangles[i];
    }
    cardPack[i]->shape->IsTapEnabled = true;

    // Set up UI to show card backs & enable events
    cardBacks[i]->Visibility = Windows::UI::Xaml::Visibility::Visible;
    cardBacks[i]->IsTapEnabled = true;

    // Ensure background grids are hit test visible & fully opaque
    grids[i]->IsHitTestVisible = true;
    grids[i]->Opacity = 1;

    // Ensure all shapes are invisible & opaque
    circles[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    squares[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    triangles[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    circles[i]->Opacity = 1;
    squares[i]->Opacity = 1;
    triangles[i]->Opacity = 1;
  }
}

void MainPage::ShuffleCards()
{
	std::random_shuffle(begin(cardPack), end(cardPack));
}

void MainPage::GameOver()
{
  HideMessages();                                                      // Hide any other messages
  winMessage->Opacity = 1.0;                                           // Show the win message
}

void MainPage::DisableCardUp(Card^ card)
{
  card->shape->IsTapEnabled = false;                                   // Disable Tapped event...
  card->shape->Opacity = 0.5;

  // Get the parent Grid for shape
  auto grid = safe_cast<Grid^>(card->shape->Parent);
  grid = safe_cast<Grid^>(grid->Parent);
 
  grid->IsHitTestVisible = false;                                      // Disable hit test
  grid->Background = azureBrush;                                       // Make sure of color
  grid->Opacity = 0.5;
}

bool MainPage::IsFound(TextBlock^ back)
{
  for(auto cardFound : pairsFound)
  {
    if(cardFound && cardFound->back == back) return true;
  }
  return false;
}

// Hide all messages in message area
void MainPage::HideMessages()
{
  auto messageCollection = messageArea->Children;
  for(size_t i = 0 ; i < messageCollection->Size ; ++i)
  {
    safe_cast<FrameworkElement^>(messageCollection->GetAt(i))->Opacity = 0;
  }
}

void MemoryTest::MainPage::Start_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  HideMessages();                                        // Clear the message area
  InitializeGame();                                      // Reset the game
}


void MemoryTest::MainPage::Show_How_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  HideMessages();                                     // Clear the message area
  playButtonTurn->Begin();                            // Start the animation
  playMessage->Opacity = 1;                           // Show the instructions
}
