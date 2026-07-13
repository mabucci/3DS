#include "gameFunctions.h"

/**************************************************************************************
Now the hard part comes.  Want to make the game play a good game that is pick the right cards
that will put it in the goal range and keep it there.
***************************************************************************************/


void GameFunctions::pickGamesCard()
{

  // _L* prefix indicates local variable
  // _L* prefix indicates local variable
  int _LiPlayersHigestCardValue{ _iaPlayersCards[0][0]+1+_iaPlayersCards[0][1]+1};
  int _LiPlayersHighestValueIndex{ 26 }; // Position 26 is set to -1, -1 at start. 
  int _LiPlayersTotalPathLenght{ -1 };
  int _LiPlayerTrumpCardValue{ 0 };

  int _LiGamesHighestCardValue{ _iaGamesCards[0][0]+1+_iaGamesCards[0][1]+1};
  int _LiGamesHighestValueIndex{ 26 }; // Position 26 is set to -1, -1 at start.  
  int _LiGamesLowestValueIndex{ -1 }; // To hold the index of GAME's lowest value card
  int _LiaGamePotXYZmoveInsideGOAL[3][2]{ {0, 0}, {0, 0}, {0, 0} };  // Games potential XYZ movement inside GOAL perimeter.  [axis][low/high] 
  double _LdGamesPercnetsOfXYZDeltaToGoalsPerimeter[3]{ {0}, {0}, {0} }; // Holds percent of GAME’s card value to be used in X, Y, and Z movements.
  int _LiGamesTCV{ 0 }; // Game total card value.
  int _LiGMMinGoal{ 0 };   // Games max movement in GOAL X+Y+Z.
  bool _LbGamesTrumpCardFound{ false };        
  int _LiGamesTrumpCardValue{ 0 };
  int _LiaGamesXYZMovement[3]{ 0, 0, 0 };  // Movement values inside or out side of GOAL perimeter.
  int _LiGamesTotalPathLenght{ -1 };
  bool _LbNGMG{ true };  // Negative GAME Movement in GOAL If this is set to ‘true’ then GAME does not have a card with a movement 
                          // value low enough to keep GAME in the GOAL perimeter
  int i{ -1 };  //Needed for call by reference to 'swapOutCards'    
  int _LiGoalsTotalPathLenght{ -1 };

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

     // Fine distance to GOAL for both PLAYER and GAME.
     // If distance is negitive then P or G is above the upper goal range
     // If *Possession[0] == TRUE, then PLAYER or GAME is in the goal range and their delta should be set to zero

      // The GAME needs to know both its’ and the PLAYER’s Delta from the GOAL. 
      // The difference in ‘game space units’ from the PLAYER’s current position and the GOAL closes boundary.   
      // X, Y, and Z values.   Negative means PLAYER is above GOAL, Positive means PLAYER is below GOAL. 
      // Total delta is alway positive.
      // PLAYER threw down first, GAME knows PLAYER’s;  card value,  current position, delta values,  and GOAL possession states.    

  _iPlayersTotalDeltaFromGoalsPerimeter = _iGamesTotalDeltaFromGoalsPerimeter = 0;

  for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
  {
    if (_iaPlayersCurrentPosition[i] <= _iaGoalsCurrentPerimeter[i][0])
      _iaPlayersXYZDeltaFromGoalsPerimeter[i] = _iaGoalsCurrentPerimeter[i][0] - _iaPlayersCurrentPosition[i];
    else _iaPlayersXYZDeltaFromGoalsPerimeter[i] = _iaGoalsCurrentPerimeter[i][1] - _iaPlayersCurrentPosition[i];
    _iPlayersTotalDeltaFromGoalsPerimeter += abs(_iaPlayersXYZDeltaFromGoalsPerimeter[i]);

    if (_iaGamesCurrentPosition[i] <= _iaGoalsCurrentPerimeter[i][0])
      _iaGamesXYZDeltaFromGoalsPerimeter[i] = _iaGoalsCurrentPerimeter[i][0] - _iaGamesCurrentPosition[i];
    else _iaGamesXYZDeltaFromGoalsPerimeter[i] = _iaGoalsCurrentPerimeter[i][1] - _iaGamesCurrentPosition[i];
    _iGamesTotalDeltaFromGoalsPerimeter += abs(_iaGamesXYZDeltaFromGoalsPerimeter[i]);
  }

  // There is always the possibility that the GAME will NOT have a card with a low enough movement value that once the GAME is in the 
  // GOAL it can not stay in the GOAL as it tries to obtain second stage possession.
  // Here test what the maximum movement in the GOAL is, and then if GAME has a card with a movement value that is equal to or less than that value.
  for (int i : _iaGoalsLenghtWidthHeight)
  {
    _LiGoalsTotalPathLenght += i;
  }
  _LiGoalsTotalPathLenght -= nsGF::NUMBER_OF_DIMENSIONS; // Subtract number of dimension.   Remember movement is NOT counted inclusively, you do not count the ‘game space unit’ you start on.
 

  for (int i{ nsGF::MAX_NUMBER_OF_GAME_CARDS - 2 }; i >= 0; --i)  // Work up from the bottom of GAME’s card list.
  {
    if (_iaGamesCards[i][0] == -1) 
      continue;
    if ((_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1) <= _LiGoalsTotalPathLenght)
    {
      _LbNGMG = false; // GAME has at lest one card that’s movement value is equal to or less than the total path possible inside the GOAL
      break;
    }
  }

  // Start of if/else change  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  // If the GOAL is in contention then no movement is to be made.   GAME must OODA available game data for an action solution.  
  // Available data, GAME’s;  current position in GOAL, longest XYZ paths in GOAL, total path length in GOAL, cards available to play.   
  // Available data, on PLAYER;  current position in GOAL, longest XYZ paths in GOAL, total path length in GOAL, cards available to play. 
  // To win the CONTENTION the GAME must pick a card that has a higher value than the PLAYER's but the value of that card must not 
  // exceed the possible movement that the GAME could make in the GOAL using any or all of the X, Y, and Z axis.
  // Qed: if GAME is in possession of the GOAL and is in the center of the GOAL and the GOAL is
  // 7 by 9 by 5, then the GAME’s max movement is 9.         
  // 
  // If the PLAYER has a possible XYZ path in the GOAL that is greater than the GAME’s possible XYZ path, and a card with that value 
  // that the PLAYER can throw-down then the GAME will loss the CONTENTION, be ejected, and the PLAYER will get second stage possession. 
  // If both GAME and PLAYER have identical paths length and play cards with same value then it’s a “PUSH”.   
  //  On a 'PUSH' the card with the higher suit wins. 
  //
  // The logic below must OODA if…
  // 1. The GAME can take / keep stage two possession of the GOAL.
  // 2. The GAME can NOT take / keep stage two possession of the GOAL.
  //    If it can not then D decision if to make a “PUSH” throw-down or abandon the GOAL with intentional low value throw-down card.
  //

/*****
Compare GAME's maximum in GOAL travel distance to PLAYER's maximum in GOAL travel distance.

If PLAYER's in GOAL travel distance is greater than GAME's in GOAL travel distance look at PLAYERS cards for a card with that travel distance value.
If PLAYER has a card with that value, then GAME will lose the GOAL throw-down.
Have GAME analyze its cards, create a value distribution table and pick the card for the REQUIRED throw-down that is among the most common value.   
GAME must preserve its card value spectrum.
Qed:   If GAME has;  Jack of Spades, Ten of Clubs, Nine of Diamonds, and Eight of Harts, the movement value of those four cards is each twelve, so
look for clusters of cards with the same movement value and put them in a table.     Find the clusters with the most cards in them, 
(maximum will be four) then find the cluster in that group that has the median movement value of all the clusters in that group, and out of that 
cluster pick the lowest suite value holding
card for the throw-down.     That is GAME sacrifice card. 
 
If PLAYER's maximum in GOAL travel distance is less that of GAME's maximum in GOAL travel distance check GAME's card list. If GAME has a card
with a value that is greater than PLAYER's in GOAL maximum travel distance then play that card.    Use the same group and cluster analysts as 
above to find the most abundant card with that value. 

If PLAYER's and GAME's maximum in GOAL travel distance is equal then check PLAYER's card's for the cards that match that value, and GAME's 
cards for cards that match that value.   In a 'PUSH' on card value the card with the higher suit wins.   If the maximum in GOAL travel 
distance is seven 'game space units' then the cards that have that value are the;  Three of Harts, the Four of Diamonds, the Five of Clubs, 
and the Six of Spades.   If all of these cards are in play between GAME and PLAYER, then which ever has the Three of Harts will win the throw-down.   
If GAME does not have the card with the highest suit value then use group and cluster analysts to pick a sacrifice card and give up the contention.

Both winner and loser of contention lose their throw-down card, if winner;  do not move in the GOAL, and get second stage possession.   
If loser, they are ejected in a random direction from GOAL's perimeter a distance of their highest card value plus two 'game space units.
*****/

  if (_bGoalInContention)
  {
    // Test PLAYER’s top card value against GAME’s top card value if GAME’s is greater play that card.  
    // If values are equal test suit, highest suit wins with cards played have equal value.
    // Qed: Three of Hearts, beats Four of Diamonds.  Both have a movement value of seven ‘game space units’,
    // but Hearts bets Diamonds
    // 
    // Start with the most obvious contention scenario;  both ICONs have Longest Path Values greater than their top valued card.
    if (_iPlayersLongestPathTotal >= _LiPlayersHigestCardValue && _iGamesLongestPathTotal >= _LiGamesHighestCardValue)
    {
      if (_LiPlayersHigestCardValue > _LiGamesHighestCardValue)
      {  //  If you get here then GAME can not beat PLAYER in contention over GOAL so find lest valuable GAME card and play that and by that give up the GOAL
        for (int i{ nsGF::MAX_NUMBER_OF_GAME_CARDS - 2 }; i >= 0; --i)
        {
          if (_iaGamesCards[i][0] == -1) // Work up from the bottom of GAME’s card list.
            continue;
          if (_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1 > 0) 
          {  // If that card is found select it as GAME trump card.
            _LiGamesLowestValueIndex = i;
            i = swapOutCards(i);  //  GameFunctions method (in this file) that will load GAME’s trump card, and replace trump card with -1,-1 in GAME’s card list       
            _iGamesTrumpCardMovementValue = _iaGamesTrumpCard[0] + 1 + _iaGamesTrumpCard[1] + 1;
            _LbGamesTrumpCardFound = true;  // _L* prefix indicates local variable.
            break; // break out of for loop
          }
        }

      }

    }

  }// end of 'if (_bGoalInContention)----------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------

// If the GOAL’s total path length, (the maximum movement that can be made while staying in the GOAL’s perimeter) is less than the GAME’s 
// lowest card value stay close to the GOAL but out side its bump range.  GAME can move in and out of the GOAL as needed to keep this distance.
// If PLAYER is close to GOAL, (with in a distance that one of PLAYER card’s movement value can make) the fallowing OODA needs to be preformed.
// GAME can not ‘Contest’ GOAL possession at this time it does not have a card with a low enough movement value to both top trump PLAYER and 
// make a path in the GOAL that fits GOAL’s perimeter dimensions.  Remember GOAL's size/position change is always close at hand.
// So, have GAME stay close to GOAL and wait for a size change that will let GAME ‘Contest’ the GOAL.

// If GAME has second stage possession of the GOAL it does not have to move in the GOAL the GOAL will move with GAME.

  else if (_LbNGMG  && _baGamesPossessionState[0] == false && _baGamesPossessionState[1] == false )    // Start of if/else change 
  {
    // Now want to stay close to GOAL but stay out of its’ bump range.
    for (int i{ nsGF::MAX_NUMBER_OF_GAME_CARDS - 2 }; i >= 0; --i)
    {
      if (_iaGamesCards[i][0] == -1) // Work up from the bottom of GAME’s card list.
        continue;

      // Work up through GAME’s cards list looking for a card with a value that can move GAME close to GOAL but stay out of its bump range.
      if ((_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1) > _iGamesTotalDeltaFromGoalsPerimeter - (_iGoalsBumpRange+1) )   
      {  // If that card is found select it as GAME trump card.
        _LiGamesHighestValueIndex = i;
        i = swapOutCards(i);  //  GameFunctions method (in this file) that will load GAME’s trump card, and replace trump card with -1,-1 in GAME’s card list       
        _iGamesTrumpCardMovementValue = _iaGamesTrumpCard[0] + 1 + _iaGamesTrumpCard[1] + 1;
        _LbGamesTrumpCardFound = true;  // _L* prefix indicates local variable.
        break; // break out of for loop
      }
      // If GOAL is farther away than GAME highest card value. 
      if ((_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1) < _iGamesTotalDeltaFromGoalsPerimeter - (_iGoalsBumpRange+1) && i == 0)
      {  // If that card is found select it as GAME trump card.      
        _LiGamesHighestValueIndex = i;
        i = swapOutCards(i);  //  GameFunctions method (in this file) that will load GAME’s trump card, and replace trump card in GAME's card stack with -1,-1 in GAME’s card list
        _iGamesTrumpCardMovementValue = _iaGamesTrumpCard[0] + 1 + _iaGamesTrumpCard[1] + 1;
        _LbGamesTrumpCardFound = true;  // _L* prefix indicates local variable.
        break; // break out of for loop
      }
    }
    //  Now move towards the GAOL while staying out of its’ bump range. 
    if (_LbGamesTrumpCardFound)
      for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
      {
        _iaGamesLastPosition[i] = _iaGamesCurrentPosition[i]; // Needed to clean up ‘game space’ display 
        _LdGamesPercnetsOfXYZDeltaToGoalsPerimeter[i] = static_cast<double>(_iaGamesXYZDeltaFromGoalsPerimeter[i]) / static_cast<double>(_iGamesTotalDeltaFromGoalsPerimeter);
        _iaGamesRequestedMove[i] = std::round(_LdGamesPercnetsOfXYZDeltaToGoalsPerimeter[i] * _iGamesTrumpCardMovementValue);
        _iaGamesCurrentPosition[i] =  _iaGamesCurrentPosition[i] += _iaGamesRequestedMove[i];
      }

  } // END of if(_LbNGMG....

  // If you get past here then the GOAL is navigable by GAME

  // Total possession of the GOAL take two turns(two throw downs).First P or G must jump into the GOAL range, 
  // this makes their possession TRUE FALES, for the next turn P or G must move, but must move only within 
  // the GOAL range.QED;  ___G____[____]_____ possession state FALSE FALSE, 
  // next move ____[_G_____]______ possession state TRUE FALSE.
  // Now the next throw down(next turn) is to be played, G must play a card, but to take total possession 
  // of the GOAL G must play a card that has a movement value that will keep G in the GOAL range.
  // Next throw down __[__G__]__ possession state TRUE TRUE.Now G has total possession of the GOAL and 
  // the GOAL will move with G.  


 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// START of "If PLAYER and GAME not in possession of GOAL" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  else if (_baGamesPossessionState[0] == false && _baGamesPossessionState[1] == false) // May need to know PLAYER's possession state later  && _baPlayersPossessionState[0] == false && _baPlayersPossessionState[0] == false)
  {
    // Look for a GAME card that will move the GAME closer to GOAL or into the GOAL     
    for (int i{ nsGF::MAX_NUMBER_OF_GAME_CARDS - 2 }; i >= 0; --i)
    {
      if (_iaGamesCards[i][0] == -1) // Work up from the bottom of GAME’s card list.
        continue;

      // Work up through GAME’s cards list looking for a card with a value that can move GAME into the GOAL.
      if ((_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1) >= _iGamesTotalDeltaFromGoalsPerimeter)    // _L* prefix indicates local variable
      {  // If that card is found select it as GAME trump card.
        _LiGamesHighestValueIndex = i;
        i = swapOutCards(i);  //  GameFunctions method (in this file) that will load GAME’s trump card, and replace trump card with -1,-1 in GAME’s card list       
        _iGamesTrumpCardMovementValue = _iaGamesTrumpCard[0] + 1 + _iaGamesTrumpCard[1] + 1;
        _LbGamesTrumpCardFound = true;  // _L* prefix indicates local variable.
        break; // break out of for loop
      }
      // Need to find a card that will put the GAME in the GOAL's perimeter, not pass through it and land out side the GOAL’s opposite side.  
      if ((_iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1) <= _iGamesTotalDeltaFromGoalsPerimeter && i == 0)
      {  // If that card is found select it as GAME trump card.      
        _LiGamesHighestValueIndex = i;
        i = swapOutCards(i);  //  GameFunctions method (in this file) that will load GAME’s trump card, and replace trump card in GAME's card stack with -1,-1 in GAME’s card list
        _iGamesTrumpCardMovementValue = _iaGamesTrumpCard[0] + 1 + _iaGamesTrumpCard[1] + 1;
        _LbGamesTrumpCardFound = true;  // _L* prefix indicates local variable.
        break; // break out of for loop
      }
    } // END OF 'for' on MAX_NUMBER_OF_GAME_CARDS ---------------------------------------------------------------------  


         // The GAME is farther away from the GOAL’s perimeter than its’ highest card value can move it into that perimeter.  
         // The shortest distance between two points is a straight line, so to move the GAME along as close to a straight line as 
         // possible to the nearest part of the GOAL’s perimeter use this…
         // GOAL’s delta X, Y, Z individually divided by _iGamesTotalDeltaFromGoal.From this you will get three values(1, 0], 
         // Now those values are the percentage values that deltas’ make up the distance to the GOAL’s perimeter.Now you have the 
         // GAME’s top card value that is to be played, so multiply dX by dX’s percent value, and that will give you the X movement 
         // value you need, do the same for Y, and Z’s movement value.Use ‘static_cast<double>’ or you will get 0%, 0%, 0%, 
         // and that should move you in(more or less) a straight line to the GOAL’s perimeter.

    if (_LbGamesTrumpCardFound)
      for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
      {
        _iaGamesLastPosition[i] = _iaGamesCurrentPosition[i]; // Needed to clean up ‘game space’ display 
        _LdGamesPercnetsOfXYZDeltaToGoalsPerimeter[i] = static_cast<double>(_iaGamesXYZDeltaFromGoalsPerimeter[i]) / static_cast<double>(_iGamesTotalDeltaFromGoalsPerimeter);
        _iaGamesRequestedMove[i] = std::round(_LdGamesPercnetsOfXYZDeltaToGoalsPerimeter[i] * _iGamesTrumpCardMovementValue);
        set_iaGamesCurrentPosition(i, _iaGamesCurrentPosition[i] += _iaGamesRequestedMove[i]);
      }
    //  _iaGamesRequestedMove[i] = static_cast<double>_iaGamesTrumpCard

  } // END of "If P and G NOT in possession of GOAL"  -----------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------------------------

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // START of "If G in possession of GOAL" TURE FALSE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  else  if (_baGamesPossessionState[0] == true && _baGamesPossessionState[1] == false && _bGoalInContention == false) // May need to know PLAYER's possession state later && _baPlayersPossessionState[0] == false && _baPlayersPossessionState[0] == false)
  {
    // GAME is in goal BUT only has firststage possession.

    for (int i{ 0 }, j{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      _iaGamesLastPosition[i] = _iaGamesCurrentPosition[i];  // Needed to clean up ‘game space’ display 
      _LiaGamePotXYZmoveInsideGOAL[i][j] = _iaGoalsCurrentPerimeter[i][j] - _iaGamesCurrentPosition[i]; // [i][0] [-n, 0] Decreasing X, Y, and Z.
      ++j;
      _LiaGamePotXYZmoveInsideGOAL[i][j] = _iaGoalsCurrentPerimeter[i][j] - _iaGamesCurrentPosition[i]; // [i][1] [0, +n] Increasing X, Y, and Z.
      --j;
      if (std::abs(_LiaGamePotXYZmoveInsideGOAL[i][j]) >= _LiaGamePotXYZmoveInsideGOAL[i][j + 1])
        _LiaGamesXYZMovement[i] = _LiaGamePotXYZmoveInsideGOAL[i][j];
      else  _LiaGamesXYZMovement[i] = _LiaGamePotXYZmoveInsideGOAL[i][j + 1];// Movement values inside or out side of GOAL perimeter.)
      _LiGMMinGoal += std::abs(_LiaGamesXYZMovement[i]);  // Sum up total movement available.  Games max movement in GOAL X+Y+Z.
    }
    // Now find the X, Y, and Z axis directions that have the longest distance that are available to GAME.

    // Now to obtain stage two possession the GAME needs to thrown-down a card and move along any combinations of axis a total of 
    // ‘game space units’ matching the value of that card, while staying inside the GOAL’s perimeter.   
    // Find the lowest card value that will do that, but do not use the lowest card value as a very low card value may be needed in the future.   

    // Work from the top of the card stack down in card value this will find the lowest card value that will work, while leaving cards with lower values if 
    // they are needed later.   Remember the GOAL can shrink down to some combination of 1, 1, 3, for its’ axis lengths, 
    // (when all axis are 1 ‘gsu’ in length the match is ended. 
    for (int i{ 0 }; i <= nsGF::MAX_NUMBER_OF_GAME_CARDS; ++i)
    {
      if (_iaGamesCards[i][0] == -1)
      {  // If you get here than there is no card value low enough to formulate a move along the three axis that will keep the GAME in GOAL’s perimeter.
        _LbNGMG = true;  // Negative GAME Movement in GOAL
        break;
      }

      _LiGamesTCV = _iaGamesCards[i][0] + 1 + _iaGamesCards[i][1] + 1;

      if (_LiGamesTCV <= std::abs(_LiGMMinGoal))    // Games max movement in GOAL X+Y+Z.
      {
        i = swapOutCards(i);

        for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
        {
          if (_LiGamesTCV - std::abs(_LiaGamesXYZMovement[i]) > 0)
          {
            _iaGamesCurrentPosition[i] += _LiaGamesXYZMovement[i];
            _LiGamesTCV -= std::abs(_LiaGamesXYZMovement[i]);
          }
          else
          {
            if (_LiaGamesXYZMovement[i] > 0)
              _iaGamesCurrentPosition[i] += _LiGamesTCV;
            else if (_LiaGamesXYZMovement[i] <= 0)
              _iaGamesCurrentPosition[i] -= _LiGamesTCV;
            _LiGamesTCV -= std::abs(_LiaGamesXYZMovement[i]);

            if (_LiGamesTCV <= 0)
              break;
          }
        }

        _LbGamesTrumpCardFound = true;
        break; // break out of for loop
      }
    } // END of 'for' on nsGF::MAX_NUMBER_OF_GAME_CARDS...

  } // END of "If GAME in possession of GAOL" TRUE FALSE --------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------------------------


/*****************************************************************************************************************************************
WORKING UP TO THIS POINT++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  else  if (_baGamesPossessionState[0] == true && _baGamesPossessionState[1] == true && _bGoalInContention == false)
  {

    }



    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  
    // START of "If GAME in possession of GOAL" TURE TRUE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      else // G has possession of the goal  TRUE TRUE **************************************************************
        if (gamesGoalPossession[0] == true && gamesGoalPossession[1] == true)
        {
          for (int i{ MGC - 2 }; i >= 0; --i)
          {
            if (gamesCards[i][0] == -1)
              continue;
            if (_iLgamesTCV < gamesCards[i][0] + 1 + gamesCards[i][1] + 1)
            {
              _iLgamesTCV = gamesCards[i][0] + 1 + gamesCards[i][1] + 1;
              _iLgamesHVCI = i;
            }
          }// END for loop...   

         // If P throws down first calculate P new position. 
          if (!whoTDF) // START false player throws down first
          {
            // If the ‘if’ statement condition is meat them the game may be able to bump the player away.
            // In this ‘if’ the player has throw trump card first and and the players final position can be found.
            if (playersPosition < goalRange[0] && (playersPosition + _iLplayersTCV) >= goalRange[0] &&
              (playersPosition + _iLplayersTCV) <= goalRange[1])
            {
              // call calculatIfBumpPossible 
              if (_bLbumpPossitle = calculateIfBumpPossible()) // test of game can bump player away.
              {
              }
              swapOutCards(_iLgamesHVCI);
              _bLgamesTCFound = true;
            }
            else
              if (playersPosition > goalRange[1] && (playersPosition - _iLplayersTCV) >= goalRange[0] &&
                (playersPosition - _iLplayersTCV) <= goalRange[1])
              {
                if (_bLbumpPossitle = calculateIfBumpPossible())  // test of game can bump player away.
                {
                }
                swapOutCards(_iLgamesHVCI);
                negativeGame = true;  // player is to right of, game so game will move to the left
                _bLgamesTCFound = true;
              }
              else  // P does not have a card that will move it into the goalRange
              {
                if (playersPosition < goalRange[0])
                {
                  swapOutCards(_iLgamesHVCI);
                  _bLgamesTCFound = true;
                }
                else
                {
                  swapOutCards(_iLgamesHVCI);
                  negativeGame = true;
                  _bLgamesTCFound = true;
                }
              }
          }// END false player throws down first 
          else // GAME must throw down first, GAME lost last hand
          { // move away from P
            if (playersPosition < goalRange[0])
            {
              swapOutCards(_iLgamesHVCI);
              _bLgamesTCFound = true;
            }
            else
            {
              swapOutCards(_iLgamesHVCI);
              negativeGame = true;
              _bLgamesTCFound = true;
            }
          }
        }
    // END of "If GAME in possession of GAOL" TRUE TRUE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
     
    
    
  

  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  // START of "if P in possession of GOAL" TRUE FALSE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  else // else to top if... 
    if (playersGoalPossession[0] == true && playersGoalPossession[1] == false)
    {
      // Look for GAME card that will A. move GAME into goal range, B. move GAME closer to goal     
      for (int i{ MGC - 2 }; i >= 0; --i)
      {
        if (gamesCards[i][0] == -1)
          continue;

        // fined highest card value, will be used if GOAL out of range of all cards
        if ((gamesCards[i][0] + 1 + gamesCards[i][1] + 1) >= _iLgamesTCV)
        {
          _iLgamesTCV = (gamesCards[i][0] + 1 + gamesCards[i][1] + 1);
          _iLgamesHVCI = i;
        }

        if (abs(_iLgamesGRdelta) < gamesCards[i][0] + 1 + gamesCards[i][1] + 1)
        {
          i = swapOutCards(i);
          if (_iLgamesGRdelta < 0)
            negativeGame = true;
          _bLgamesTCFound = true;
          break; // break out of for loop
        }
        else
          if (i == 0)
          {
            i = swapOutCards(_iLgamesHVCI);
            if (_iLgamesGRdelta < 0)
              negativeGame = true;
            _bLgamesTCFound = true;
          }
      }
    }
  // END of "If P in possession of GOAL" TRUE FALSE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  // START of "if P in possession of GOAL" TRUE TRUE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  
    else
      if (playersGoalPossession[0] == true && playersGoalPossession[1] == true)
      {
        for (int i{ MGC - 2 }; i >= 0; --i)
        {
          if (gamesCards[i][0] == -1)
            continue;

          // fined highest card value, will be used if GOAL out of range of all cards
          if ((gamesCards[i][0] + 1 + gamesCards[i][1] + 1) >= _iLgamesTCV)
          {
            _iLgamesTCV = (gamesCards[i][0] + 1 + gamesCards[i][1] + 1);
            _iLgamesHVCI = i;
          }

          if (abs(_iLgamesGRdelta) < gamesCards[i][0] + 1 + gamesCards[i][1] + 1)
          {
            i = swapOutCards(i);
            if (_iLgamesGRdelta < 0)
              negativeGame = true;
            _bLgamesTCFound = true;
            break; // break out of for loop
          }
          else
            if (i == 0)
            {
              i = swapOutCards(_iLgamesHVCI);
              if (_iLgamesGRdelta < 0)
                negativeGame = true;
              _bLgamesTCFound = true;
            }
        }
      }

  // END of "If P in possession of GOAL" TRUE TRUE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



 
  if (gamesTrumpCard[0] != -1)
  {
    cout << "\nGame's card pick is:   ";
    if (negativeGame) cout << '-';
    cout << cardNames[gamesTrumpCard[0]] << " of " << cardSuits[gamesTrumpCard[1]] << '.';
  }
  else
    cout << "\nNO GAME trump card found!";
  return;

 END OF WORKING UP TO THIS POINT--------------------------------------------------------------------------------------------------
 ********************************************************************************************************************************/
   
  return;
}
//**** END pickGamesCard ENDS ****************************************************************************************************
//********************************************************************************************************************************

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START calculatIfBumpPossible / calculatIfBumpPossible STRTS */   
/* If an ICON lands within the bump range of the GOAL that ICON is to be 'bumped' away from the GOAL's perimeter
in the opposite direction, from the GOAL's perimeter, along the axis that is perpendicular to the GOAL's perimeter.    
Both GAME and PLAYER, will be tested here and bumped away if one or both meet the bump conditions.    
*/
bool GameFunctions::calculateIfBumpPossible()
{
      
  return false;    
}
   
   
/* END calculatIfBumpPossible / calculatIfBumpPossible ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START swapOutCards  | swapOutCards STARTS */
int GameFunctions::swapOutCards(int& x)   // removes picked card from game's cards
{
  _iaGamesLastTrumpCard[0] = _iaGamesTrumpCard[0];
  _iaGamesLastTrumpCard[1] = _iaGamesTrumpCard[1];
  _iaGamesTrumpCard[0] = _iaGamesCards[x][0];
  _iaGamesTrumpCard[1] = _iaGamesCards[x][1];
  _iaGamesCards[x][0] = -1; _iaGamesCards[x][1] = -1; // removes picked card from game's cards
  return -1;  // will set for loop counter to -1 and end loop
}
/* END swapOutCards | swapOutCards ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

