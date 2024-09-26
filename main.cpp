#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

enum class Suits
{
    CLUBS = 1,
    DIAMONDS,
    HEARTS,
    SPADES,
};

enum class CardNames
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

struct Card
{
    CardNames name;
    Suits suit;
    int value;

    void PrintCard()
    {
        PrintValue();
        std::cout << " of ";
        PrintSuit();
        std::cout << std::endl;
    }

    void PrintValue()
    {
        if (name == CardNames::JACK)
        {
            std::cout << 10;
        }
        else if (name == CardNames::QUEEN)
        {
            std::cout << 10;
        }
        else if (name == CardNames::KING)
        {
            std::cout << 10;
        }
        else
        {
            std::cout << (int)value;
        }
    }

    void PrintSuit()
    {
        if (suit == Suits::CLUBS)
        {
            std::cout << "clubs";
        }
        else if (suit == Suits::SPADES)
        {
            std::cout << "spades";
        }
        else if (suit == Suits::HEARTS)
        {
            std::cout << "hearts";
        }
        else if (suit == Suits::DIAMONDS)
        {
            std::cout << "diamonds";
        }
    }
};

struct Deck
{
    Card arrCards[52];
    int indexCount = 0;

    void PrintAll()
    {
        for (int i = 0; i < 52; ++i)
        {
            arrCards[i].PrintCard();
        }
    }

    void ShuffleDeck()
    {
        int r;
        for (int i = 0; i < 52; i++)
        {
            r = rand() % 52;
            Card temp = arrCards[i];
            arrCards[i] = arrCards[r];
            arrCards[r] = temp;
        }
    }

    Card DealCard()
    {
        if (indexCount == 51)
        {
            ShuffleDeck();
            indexCount = 0;
        }
        return arrCards[indexCount++];
    }

    void SetupCards()
    {
        int index = 0;
        for (int i = (int)Suits::CLUBS; i <= (int)Suits::SPADES; i++)
        {
            for (int k = (int)CardNames::ACE; k <= (int)CardNames::KING; k++)
            {
                Card c;
                c.suit = (Suits)i;
                c.name = (CardNames)k;

                if (c.name == CardNames::JACK)
                {
                    c.value = 10;
                }
                else if (c.name == CardNames::QUEEN)
                {
                    c.value = 10;
                }
                else if (c.name == CardNames::KING)
                {
                    c.value = 10;
                }
                else
                {
                    c.value = (int)c.name;
                }

                arrCards[index] = c;
                index++;
            }
        }
    }
};

class Player
{
private:
    std::vector<Card> hand;

public:
    int total = 0;
    int aces = 0;

    void Hit(Card card)
    {
        hand.push_back(card);
    }

    int HandTotal()
    {
        total = 0;
        aces = 0;

        for (Card &card : hand)
        {
            if (card.name == CardNames::ACE)
            {
                aces++;
                total += 11;
            }
            else
            {
                total += card.value;
            }
        }
        while (total > 21 && aces > 0)
        {
            total -= 10;
            aces--;
        }
        return total;
    }

    void PrintHand()
    {
        for (Card &card : hand)
        {
            card.PrintCard();
        }
        std::cout << "Total value: " << HandTotal() << std::endl;
    }
};

class Game
{
public:
    void play()
    {
        Deck deck;
        Player player;
        Player dealer;
        char choice;

        deck.SetupCards();
        deck.ShuffleDeck();

        dealer.Hit(deck.DealCard());
        player.Hit(deck.DealCard());
        player.Hit(deck.DealCard());

        std::cout << "Player's Hand: " << std::endl;
        player.PrintHand();

        std::cout << "Dealer's Hand: " << std::endl;
        dealer.PrintHand();

        dealer.Hit(deck.DealCard());

        while (player.HandTotal() < 21)
        {
            std::cout << "Do you want to HIT or STAND? (h/s)";
            std::cin >> choice;
            if (choice == 'h')
            {
                player.Hit(deck.DealCard());
                std::cout << "Player's Hand: " << std::endl;
                player.PrintHand();
            }
            else
            {
                break;
            }
        }

        if (player.HandTotal() > 21)
        {
            std::cout << "Player busts! Dealer wins." << std::endl;
            return;
        }

        std::cout << "Dealer's Hand: " << std::endl;
        dealer.PrintHand();

        while (dealer.HandTotal() < 17)
        {
            dealer.Hit(deck.DealCard());
            std::cout << "Dealer's Hand: " << std::endl;
            dealer.PrintHand();
        }
        if (dealer.HandTotal() > 21)
        {
            std::cout << "Dealer Busts! Player wins." << std::endl;
        }
        else if (dealer.HandTotal() > player.HandTotal())
        {
            std::cout << "Dealer has a higher hand! Dealer wins." << std::endl;
        }
        else if (player.HandTotal() > dealer.HandTotal())
        {
            std::cout << "Player has a higher hand! Player wins." << std::endl;
        }
        else
        {
            std::cout << "Push!" << std::endl;
        }
    }
};

int main()
{
    srand(time(0));

    std::cout << "Type 'Help' for rules on how to play, Type 'Start' to start playing!" << std::endl;
    std::string play;
    std::cin >> play;

    if (play == "help" || play == "Help")
    {
        std::cout << "The goal of Blackjack is to have a hand value that is closer to 21 than the dealer's hand without exceeding 21. Number cards (2-10) are worth their face value. Face cards (Jack, Queen, King) are each worth 10 points. Aces can be worth either 1 point or 11 points, whichever is more favorable for your hand." << std::endl;
        std::cout << "Type 'Start' to start playing!" << std::endl;
        std::cin >> play;
        if (play == "Start" || play == "start")
        {
            Game game;
            game.play();
        }
    }
    else if (play == "Start" || play == "start")
    {
        Game game;
        game.play();
    }
    return 0;
}
