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
};
