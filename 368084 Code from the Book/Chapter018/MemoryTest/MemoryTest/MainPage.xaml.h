//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <string>
#include "Card.h"

namespace MemoryTest
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void test(std::wstring str);
		property Platform::String^ type; 

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Shape_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void Cardback_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void Card_Entered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Card_Exited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

		size_t cardCount;                                                    // The number of cards
		Platform::Array<Windows::UI::Xaml::Controls::Grid^>^ grids;
		Platform::Array<Windows::UI::Xaml::Shapes::Ellipse^>^ circles; 
		Platform::Array<Windows::UI::Xaml::Shapes::Rectangle^>^ squares;
		Platform::Array<Windows::UI::Xaml::Shapes::Polygon^>^ triangles;
		Platform::Array<Windows::UI::Xaml::Controls::TextBlock^>^ cardBacks;
		Platform::Array<Card^>^ cardPack;                                  // The pack of cards

		// Type names for card elements
		Platform::String^ typeCircle;
		Platform::String^ typeSquare;
		Platform::String^ typeTriangle;

		// Game functions
		void InitializeCardPack();                                         // Initializes cardPack to hold two of each card
		void SetUpUIState();                                               // Initializes the child elements of cardGrid
		void InitializeGame();                                             // Sets up a game with a shuffled cardPack
		void ShuffleCards();                                               // Shuffle the cards
		void GameOver();
		void DisableCardUp(Card^ card);
		bool IsFound(Windows::UI::Xaml::Controls::TextBlock^ back);
		void HideMessages();

		// Game records
		Card^  card1Up;                                                    // 1st card turned up
		Card^  card2Up;                                                    // 2nd card turned up
		int pairCount;                                                     // Number of pairs found
		Platform::Collections::Vector<Card^>^ pairsFound;                  // Pairs found in the game

		Windows::UI::Xaml::Media::SolidColorBrush^ steelBrush;             // Card highlight color
		Windows::UI::Xaml::Media::SolidColorBrush^ azureBrush;             // Card normal color

		void Start_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void Show_How_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
	};
}
