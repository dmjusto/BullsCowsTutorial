/*This is the console executable and acts as
 the 'view' in the MVC pattern
 */

#include <iostream>
#include <string>
#include "fBullsCowsGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlay();


FBullCowGame BCGame;//instantiate a new game

int main()
{
    do {
        PrintIntro();
        PlayGame();
    } while (AskToPlay() == true);
    
    return 0;
}

void PlayGame()
{
    BCGame.Reset();
    int32 maxTries = BCGame.GetMaxTries();
    std::cout << "number of turns: " << maxTries << "\n\n";
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries)
    {
        FText Guess = GetValidGuess();
        
        //submit valid guess to game
        FBullCowCount bullCowCount = BCGame.SubmitValidGuess(Guess);
        //print number of bulls and cows
//        std::cout << "Your guess was " << Guess << "\n";
        std::cout << "Number of Bulls: " << bullCowCount.Bulls << " ";
        std::cout << "Number of Cows: " << bullCowCount.Cows << std::endl << std::endl;
    }
    PrintGameSummary();
    return;
}

void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHWordLength() << " letter isogram I'm thinking of?\n";
    
    return;
}

//loop continually until player gives a valid guess
FText GetValidGuess()
{
    EGuessStatus guessStatus = EGuessStatus::Invalid_Status;
    FText PlayerGuess = "";
    do
    {
        int32 currentTry = BCGame.GetCurrentTry();
        std::cout <<"Try " <<currentTry <<" of " << BCGame.GetMaxTries() <<"; Enter your Guess: ";
        getline(std::cin, PlayerGuess);
        
        guessStatus = BCGame.CheckGuessValidity(PlayerGuess);
        switch(guessStatus)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "\nPlease enter a " << BCGame.GetHWordLength() << " letter isogram\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "\nPlease use all lowercase letters\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "\nPlease enter a proper isogram(no repeated letters)\n";
                break;
            default:
                break;
        }
    }while (guessStatus != EGuessStatus::Ok);//keep looping until we get valid input
    
    return PlayerGuess;
}



bool AskToPlay()
{
    std::cout << "Would you like to play again? (y/n): ";
    FText response = "";
    getline(std::cin, response);
    std::cout << std::endl;
    return response[0] == 'y' || response[0] == 'Y';
}

void PrintGameSummary()
{
    if(BCGame.IsGameWon())
    {
        std::cout << "Well Done!!!\n";
    }
    else
    {
        std::cout << "Better luck next time.\n";
    }
    return;
}
