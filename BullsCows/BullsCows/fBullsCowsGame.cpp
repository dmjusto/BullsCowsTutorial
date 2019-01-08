//
//  fBullsCowsGame.cpp
//  BullsCows
//
//  Created by Dylan Fairbanks on 12/26/18.
//  Copyright © 2018 Dylan Fairbanks. All rights reserved.
//


#include "fBullsCowsGame.hpp"
#include <map>
#define TMap std::map
using FString = std::string;
using int32 = int;

int32 FBullCowGame::GetCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::GetHWordLength() const { return int(myHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }


int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> wordLengthToMaxTries {{3,4},{4,7},{5,10},{6,15},{7,20}};
    return wordLengthToMaxTries[int32(myHiddenWord.length())];
    
}

FBullCowGame::FBullCowGame()//constructor
{
    FBullCowGame::Reset();
}

void FBullCowGame::Reset()
{
    const FString hiddenWord = "planet";
    myHiddenWord = hiddenWord;
    FBullCowGame::myCurrentTry = 1;
    FBullCowGame::bGameWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
    if(!Is_Isogram(guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if(!IsLowercase(guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if(guess.length() != GetHWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
        return EGuessStatus::Ok;
}

//receives a VAlID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess( FString guess)
{
    myCurrentTry++;
    FBullCowCount bullCowCount;
    int32 hWordLength = int(myHiddenWord.length());
    for(int32 i = 0; i < hWordLength; i++)
    {
        for(int32 j = 0; j < hWordLength; j++)
        {
            if(guess[i] == myHiddenWord[j])
            {
                if(i == j)
                {
                    bullCowCount.Bulls++;
                }
                else
                {
                    bullCowCount.Cows++;
                }
            }
            else
                ;
        }
        if(bullCowCount.Bulls == hWordLength)
        {
            bGameWon = true;
        }
        else
        {
            bGameWon = false;
        }
    }
    return bullCowCount;
}

bool FBullCowGame::Is_Isogram(FString guess) const
{
    if(guess.length() <= 1) {return true;}
    TMap <char, bool> letterSeen;
    for(auto letter : guess)
    {
        letter = tolower(letter);//to handle mixed case guesses
        if(letterSeen[letter])
        {
            return false;
        }
        else
        {
            letterSeen[letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString guess) const
{
    for(auto letter : guess)
    {
        if(!islower(letter))
        {
            return false;
        }
        
    }
    return true;
}
