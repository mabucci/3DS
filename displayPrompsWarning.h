#pragma once
// Attempt to centralize cout and print prompts and warnings and data display 

#include"gameData.h"            // gameData holds C++ include files, and constants needed for game operations\
                                 greeting and Instructions holds namespaces with greetingInstruction string 
#include"gameFunctions.h"      // GameFunctions holds gamesFunctions class that will hold all the member and\
                                 methods that work the game
#include"gameSpace.h"          // Will build and display the field(game space) and print headers for Player, Game, and Goal data.\
                                 Current position, card picked so on

namespace nsSPM
{
  enum DC{ DISPLAY_GREETINGS = 100, PLAYERS_DATA_DISPLAY, GAMES_DATA_DISPLAY, GOALS_DATA_DISPLAY, CLEAR_PLAYERS_XYZ_INPUT, PLAYERS_XYZ_POSITION_DELTAS, \
  GOAL_IN_CONTENTION, CLEAR_GOAL_IN_CONTENTION};
  enum DG{ PLAYERS_ICON_DISPLAY = 200, GAMES_ICON_DISPLAY, GOALS_ICON_DISPLAY };
}  // DC == display codes


class DisplayPrompsWarning : public GameSpace {
private:
protected:
public:
  // constructor destructor
  DisplayPrompsWarning() {};
  ~DisplayPrompsWarning() {};

  // print methodes in a switch statement ++++++++++++++++++++++++++++++++++++++++

  void printMain(int, GameSpace);
  void printGameFuntions(int);
  void printPickPlayersCard(int);
  void clearPlayersXYZinput(); // Clear PLAYER’S X, Y, and Z input feels
};
