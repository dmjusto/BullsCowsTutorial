//
//  fBullsCowsGame.hpp
//  BullsCows
//
//  Created by Dylan Fairbanks on 12/26/18.
//  Copyright © 2018 Dylan Fairbanks. All rights reserved.
//

/*The Game Logic*/

#pragma once
#ifndef fBullsCowsGame_hpp
#define fBullsCowsGame_hpp

#include <stdio.h>
#include <string>
using FString = std::string;
using int32 = int;

#endif /* fBullsCowsGame_hpp */

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Ok,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    Invalid_Status,
};


class FBullCowGame
{
public:
    FBullCowGame();//constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHWordLength() const;
    bool IsGameWon() const;
    
    void Reset();
    EGuessStatus CheckGuessValidity(FString) const;
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 myCurrentTry;
    FString myHiddenWord;
    bool bGameWon;
    
    bool Is_Isogram(FString) const;
    bool IsLowercase(FString) const;
};
