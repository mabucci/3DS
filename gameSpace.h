#pragma once
#include "gameFunctions.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameFunctions class begins
class GameSpace : public GameFunctions {
  // private members ----------------------------------
private:
  // protected members --------------------------------
protected:
  // public members and methods -----------------------
public:
  // constructor / destructor 
  GameSpace() {};
  ~GameSpace() {};  

  void buildGameSpace();
  void upDateGoalsPositioinAndDimensions();
  void testIfAnyIconBumped();
  void testGoalContentionWinner(); // Test for the winner of GOAL contention   Set winner as stage two possession, and eject loser   
  int randomNumberGenerator(int, int);  // A general Random Number Generator method   takes two arguments that make the [inclusive range] 
  void testCorrectKickOutPosition(std::string);  // Test and or correct the new kicked out to position, if kicked out position is out of game space then clip that position to keep the ICON in bounds  
};
