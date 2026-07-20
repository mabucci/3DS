/*****
 This is attempt to make Top Trumps into a three dimensional game.
 X and Y will have numeric location displayed as well as an abstract visual references, 
 with Z having a numeric value displayed only.
 *****/

#include "gameData.h"         // gameData holds C++ include files, and constants needed for game operations\
                              //   greeting and Instructions holds namespaces with greetingInstruction string 
#include "gameSpace.h"        // GameFunctions holds gamesFunctions class that will hold all the member and\
                              //   methods that work the game
#include "displayPrompsWarning.h" // Attempt to centralize cout and print prompts and warnings and data display 

 //void setFontSize(int, int);   // To set the font size of the dos console   is set further down 

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle   need this for curser placement    font size window size and so on 

int main()
{
  
  bool _bContinue{ true }; // if Goal size is 1, 1, 1 match is over    this local Boolean keeps the game loop, just a while loop cycling 
  char _cQuit{ '\0' };  // if player wants to quit '27' == ESC     hit the ESC key anywhere except X, Y, and Z position input prompts and game exits
  bool _bFirstPlay{ true }; // This will have a random pick for how has to throw-down first.
  GameSpace gS;   // Game Space inherits from Game Function class created   these two classes hold most of the game's methods, additional classes may be added
  DisplayPrompsWarning dPW; // Switch Print class will handle screen out put prompts warnings data  mostly

  gS.setFontSize();  // also GameFunction class method will set font size.
  gS.setUpWindow();   // call to GamedPWace class GameSpace, which inherits from the GameFunction class, the method will maximize window size.

 dPW.printMain(nsSPM::DC::DISPLAY_GREETINGS, gS);  // Switch Print class will handle screen out put prompts warnings data  mostly

  // if player wants to;  move up and down through greeting just roll mouse wheel, play, or quit 

  while (1)
  {
    gS.set_Quit(_getch());
    if ((int)gS.get_Quit() == nsGF::ESC) /* 27 == esc key code */
    {
      system("cls");   // the cls is here to clear the screen on exit
      return 0; // Exit game.
    }
    else if ((int)gS.get_Quit() == nsGF::ENTER)
      break;  // Play game.     
  }// end while(1)

  system("cls");      // clear the newly created window   for gamedPWace display

  
  gS.shuffleDeck();
  gS.dealCards();
  gS.orderCards();
  gS.displayCards();
  gS.buildGameSpace();
  gS.whoLostLastHand(_bFirstPlay);  // this is only for the first match it will randomly pick who throws-down first

  // If GOAL is not possessed then its’ chance of moving or changing shape is 1 in 10 
  // so display now before game loop starts
  // Calls to printMain have gS class called by reference, if data corruption becomes a problem may go to call by value even with all the overhead 
 dPW.printMain(nsSPM::DC::GOALS_DATA_DISPLAY, gS); 

  // start of game loop ........................................................................................
  while(1)  // Loop is broken by PLAY pressing ‘esc’ key at certain prompts 
  { 
   
    // Now test if the Goal is in possession, if it is not then then test if it will make random move and or size change.  
    /*********************************************************************************************************************************************
  if (_bContinue = gS.testIfGoalShouldMoveOrResize())    
   dPW.printMain(nsSPM::DC::GOALS_DATA_DISPLAY, gS);
 *****************************************************************************************************************************************************/

    // If a player’s (GAME or PLAYER) move put them in side the GOAL, or that move keeps them in the GOAL update their possession state.
    gS.testSetGoalPossession("GAME");
    gS.testSetGoalPossession("PLAYER");


    // Display Player's last card played data cout two rows down from header 
    // Headers are displayed by gameSpace.cpp
   
   dPW.printMain(nsSPM::DC::PLAYERS_DATA_DISPLAY, gS); // Switch Print class will handle screen out put prompts warnings data MOSTLY!
   dPW.printMain(nsSPM::DC::GAMES_DATA_DISPLAY, gS);
   dPW.printMain(nsSPM::DC::GOALS_DATA_DISPLAY, gS);
   
   dPW.printMain(nsSPM::DG::GOALS_ICON_DISPLAY, gS); // Display the GOAL perimeter
   dPW.printMain(nsSPM::DG::PLAYERS_ICON_DISPLAY, gS); // Display the PLAYER's location on the 'game space' display
   dPW.printMain(nsSPM::DG::GAMES_ICON_DISPLAY, gS); // Display the PLAYER's location on the 'game space' display
   



    // if both PLAYER and GAME have first or second possession of GOAL throw-down will be tripped 
    // Movement code for GAME when GOAL is in contention.

/*******************************************************************************************************************
If(test if GOAL is in contention)
If true, enter.
GAME's, PLAYER's longest XYZ path and total XYZ path have already be calculated.
1. Find who lost last throw-down(hand).
2. If GAME lost last throw-down then find out if GAME's total X, and or Y, and or Z potential movement(s) to keep GAME inside of 
GOAL’s perimeter are (is) greater than PLAYER's, and if GAME has a card with a movement value that is just greater that PLAYER'S XYZ potential 
movement that would keep PLAYER inside of GOAL’s perimeter, that card may be picked to win the throw-down.
3. Throw-down that card.If you have to pick first this is the best way to secure 1st, 2ed possession.
4. If GAME won last throw-down then PLAYER must throw-down first.  If PLAYER throws-down a card and moves out of the GOAL, then throw-down 
card with a low movement value and move to and X, Y, Z position in the GOAL’s perimeter. This will be default will give GAME 1st, and 2ed 
state possession.
ELSE  if PLAYER throws-down a card and uses its movement value to keep inside the GOAL’s perimeter check for a card value that is just greater 
than that of the PLAYER's, but with a value that will let GAME stay inside of the GOAL when executing its XYZ move.
5. If GAME does not have a card with a low enough movement value to keep it in GOAL’s perimeter then move out of the GOAL to a 
position out side of the GOAL’s range.   PLAYER will have ps1 and ps2, it may bump or run, GAME will have to wait on this move.  
**********************************************************************************************************************/
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++     
    if (gS.get_baGamesPossessionState(0) && gS.get_baPlayersPossessionState(0))
    {
     dPW.printMain(nsSPM::DC::GOAL_IN_CONTENTION, gS);
      // Calculations needed by GAME to decide to contest or relinquish the GOAL   only needed if GOAL is in contention 
      gS.goalPossessionThrowDownCalculations(); // 
      gS.set_bGoalInContention(true);
      gS.pickGamesCard();  // Have GAME pick its top trump card first else a lot of work will be needed for GAME to see PLAYER’s highest card.   
                           // If PLAYER picks first, and picks it top value card, that card is -1, -1, out
                           // but the card stack is not re - ordered, so GAME logic will see zero as PLAYER’s top card value.
      _cQuit = gS.pickPlayersCard();
      // check for "quit" when returning from any method that has player input always check for "ESC" to exit game
      if (_cQuit == nsGF::ESC)
        return 0;
    
      gS.testGoalContentionWinner();
      gS.set_bGoalInContention(false);
     dPW.printMain(nsSPM::DC::CLEAR_GOAL_IN_CONTENTION, gS);
    }
//---------------------------------------------------------------------------------------------------------------------

    // Whomever lost the last must pick and throw-down a card first, and enter there X, Y, and Z movement request.   
    // The card will be shown to the other player before that player (the winner of the last hand) has to pick their card to throw-down.   
    // The other player’s X, Y, and Z movement request will not be shown.
    // The card will be shown to the PLAYER, but not the movement requests. 
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++       
    else if ( gS.get_sWhoLostLastHand() == "PLAYER")
    {
      // The player will now pick a card to throw-down, That card will be removed from the Player’s 
      //stack of playable cards and it’s movement points will be save in the Player’s movement points bank
      _cQuit = gS.pickPlayersCard();
      // check for "quit" when returning from any method that has player input always check for "ESC" to exit game
      if (_cQuit == nsGF::ESC)
        return 0;

      // At this point the Player has picked has picked a legitimate card as their next card to play, now ask for their X,Y, 
     // and Z axis movement values and test and or correct them as needed

     dPW.printMain(nsSPM::DC::CLEAR_PLAYERS_XYZ_INPUT, gS);
     dPW.placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW);
    

      _bContinue = gS.playersXyzInput();
      if (_bContinue == true)
        return 0; // player wants to exit game


      // Test player’s movement request, if any axis movement will put the player’s token out of the
      // playing field that movement request will be clipped to keep the player in bounds  
      gS.testPlayersMovementRequestInBounds();      

      // If a player’s (GAME or PLAYER) move put them in side the GOAL, or that move keeps them in the GOAL update their possession state.
   //   gS.testSetGoalPossession("PLAYER");
     dPW.printMain(nsSPM::DC::CLEAR_GOAL_IN_CONTENTION, gS);
     dPW.printMain(nsSPM::DC::CLEAR_PLAYERS_XYZ_INPUT, gS);
     dPW.printMain(nsSPM::DC::PLAYERS_XYZ_POSITION_DELTAS, gS);

      // If a player’s (GAME or PLAYER) move put them in side the GOAL, or that move keeps them in the GOAL update their possession state.
       //  gS.testSetGoalPossession("PLAYER");

      // Now the GAME will see the PLAYER’s card pick and use that data to formulate it card pick and movement.
      // Pick GAME's card instructions go here       
      gS.pickGamesCard();            
    } // END 'if' on PLAYER lost last hand...
    //-----------------------------------------------------------------------------------------------------------------
    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else  if (gS.get_sWhoLostLastHand() == "GAME") 
    {
      // GAME has lost last hand and must pick a card to throw-down and formulate it movement request.
      // Pick GAME's card instructions go here....................................................................................
      gS.pickGamesCard();
   
      gS.orderCards();   // Looking at GAME’s card stack you can tell if GAME picked first as it stack will be one less than PLAYER’s
      gS.displayCards();
      gS.testSetGoalPossession("GAME");
     dPW.printMain(nsSPM::DC::GAMES_DATA_DISPLAY, gS);  // Only need this in GAME pick first as PLAYER needs to see GAME’s movement data
     dPW.printMain(nsSPM::DG::GAMES_ICON_DISPLAY, gS); // Display the PLAYER's location on the 'game space' display
     dPW.printMain(nsSPM::DG::PLAYERS_ICON_DISPLAY, gS); // Display the PLAYER's location on the 'game space' display
      _cQuit = gS.pickPlayersCard();
   
      // check for "quit" when returning from any method that has player input always check for "ESC" to exit game
      if (_cQuit == nsGF::ESC)
        return 0;

      // At this point the Player has picked has picked a legitimate card as their next card to play, now ask for their X,Y, 
      // and Z axis movement values and test and or correct them as needed
   
      _bContinue = gS.playersXyzInput();
      if (_bContinue == true)
        return 0; // player wants to exit game

      // Test player’s movement request, if any axis movement will put the player’s token out of the
      // playing field that movement request will be clipped to keep the player in bounds  
      gS.testPlayersMovementRequestInBounds();
     dPW.printMain(nsSPM::DC::CLEAR_PLAYERS_XYZ_INPUT, gS);
     dPW.placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW);
     dPW.printMain(nsSPM::DC::PLAYERS_XYZ_POSITION_DELTAS, gS);
     dPW.printMain(nsSPM::DC::CLEAR_GOAL_IN_CONTENTION, gS);
    } // END 'if' on GAME lost last hand...     
 
    gS.whoLostLastHand(_bFirstPlay);  // With the first throw-down played call by reference ‘_bFirstPlay’  has been set to ‘false‘ and the winner loser can be set for next throw-down.
    gS.orderCards();
    gS.displayCards();
    gS.testIfAnyIconBumped();
 
   } // end of game loop .............................................................................
//---------------------------------------------------------------------------------------------------------------------

 return 0;
}


//inline void setFontSize(int a, int b)
//{
//  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//  PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
//  lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
//  GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
//  lpConsoleCurrentFontEx->dwFontSize.X = a;
//  lpConsoleCurrentFontEx->dwFontSize.Y = b;
//  SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
//}
