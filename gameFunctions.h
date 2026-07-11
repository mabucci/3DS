#pragma once

 /*****
 this .h file and its' .cpp file will hold the game functions class, this class will hold all the members and methods that 
 will do the work of the game
 *****/

#include "gameData.h"

class GameFunctions
{
private:
  char quit{ 'z' }; // At points during game play the Player will have the option to quit the game by pressing the ‘esc’ key that will load char value 27 into ‘quite’ and ‘quite’ will be tested to see if game should be terminated. 
  // Game..............................
  bool _bGameBumpedBack{ false };  // was the GAME bumped back by the GOAL
  short _iaGamesBumpBackCard[2]{ {-1}, {-1} }; // Use to print out the card used to calculate the GAME’s bump back distance 
  int _iaGamesCards[nsGF::MAX_NUMBER_OF_GAME_CARDS][2]{ { 0 },{ 0 } }; // Holds Game's dealt cards 
  int _iGamesCardsTotalValue{ 0 };
  int _iaGamesCurrentPosition[3]{ 57, 27, 57 };  // hold's Game's curent position   
  bool _bGameKickedOut{ false };  // was the GAME kicked out of the GOAL 
  short _iaGamesLastPosition[3]{ {0}, {0}, {0} };
  int _iaGamesLongestXYZPath[3]{ 0, 0, 0 };   // OODA loop GAME need to find it longest path that it can move in the GOAL from its present position
  int _iGamesLongestPathTotal{ 0 };
  int _iaGamesRequestedMove[3]{ 0, 0, 0 }; // hold's Game's requested position 
  bool _baGamesPossessionState[2]{ {false}, {false} };  // hold's Game's possession state of the Goal: false|false no possession true|false first stage possession true|true second state possession
  short _iaGamesTrumpCard[2]{ {-1}, {-1} }; // Game’s current card pick   the card the Game wants to play
  short _iaGamesLastTrumpCard[2]{ -1, -1 }; // Game's last card pick (if any) the card the GAME played on the last action phase.
  short _iGamesTrumpCardValue{ 0 };
  int _iGamesTrumpCardMovementValue{ -1 };
  int _iGamesTotalDeltaFromGoal{ 0 };  // The difference in total ‘game space units’ from the GAME’s current position and the GOAL closes boundary.  The total of  X, Y, and Z  'game space units'
  int _iGamesTotalDeltaFromGoalsPerimeter{ 0 };   // The difference in total ‘game space units’ from the GAME’s current position and the GOAL closes boundary.  The total of  X, Y, and Z  'game space units'
  int _iaGamesXYZDeltaFromGoalsPerimeter[3]{ 0, 0, 0 };  //  GAME’s distance from GOAL closes X, Y, Z perimeters.  X, Y, and Z values.   Negative means above, Positive means below.

  // gameSpace members.................
  short _iaCardsLeftInGame{ nsGF::NUMBER_OF_CARDS_IN_DECK };  // When this value goes to zero (the last two cards are played) the match is ended 
  int _iaCardsShuffled[nsGF::NUMBER_OF_CARDS_IN_DECK][2]{ { 0 },{ 0 } };
  short _iaGameSpaceDimentions[nsGF::NUMBER_OF_DIMENSIONS]{ {nsGF::GAME_SPACE_LENGTH}, {nsGF::GAME_SPACE_WIDTH}, {nsGF::GAME_SPACE_HIGHT} };
  int _iaUniverse[3]{ {nsGF::GAME_SPACE_LENGTH}, {nsGF::GAME_SPACE_WIDTH}, {nsGF::GAME_SPACE_HIGHT} };  // size of the universe   
  std::string  _sWhoLostLastHand{ '\0' };  // who throws down first PLAYER or GAME
  bool _bWhoTDFirst{ false };

  // Goal.............................. 
  int _iGoalsBumpRange{ 3 };  // The distances in ‘game space units’ from GOAL’s perimeter outward.    If an ICON is within that distances, before or after the ICON’s throw-down move,  the ICON is moved (bumped) from that XYZ position to a new random XYZ position equal to the ICON’s highest card value plus two ‘game space units’  qed in one dimension;   GOAL’s upper X perimeter is at n, and BumpRange is b,  then if the GOAL moves to a position, or an ICON moves to a position where ICON’s position is in the range of (n, n+b] then the ICON’s position will be changed to that ICON’s highest card value plus two,  a random distances from GOAL’s perimeter. 
  int _iaGoalsBumpRangePerimeter[3][2]{ {0,0}, {0,0}, {0,0} }; // Bump perimeter is initialized in default constructor. 
  int _iaGoalsCurrentCenter[3]{ 50, 20, 50 };         // hold's Goal's center curent location
  int _iaGoalsCurrentPerimeter[3][2]{ {45, 55},{15, 25},{45, 55} }; // Xlow->Xhigh, Ylow->Yhigh, Zlow->Zhigh.
  bool _bGoalInContention{ false }; // If both PLAYER and GAME are in the GOAL’s perimeter at the same time   this will trip special movement logic in GAME’s movement code 
  int _iaGoalsLastPerimeter[3][2]{ {0, 0}, {0, 0}, {0, 0} }; // For cleaning up display. 
  int _iaGoalsLenghtWidthHeight[3]{ 11, 11, 11 }; // hold's Goal's size
  bool _baGoalsPossessionState[2]{ {false}, {false} };  // hold's how the Goal is possessed: false|false no possession true|false first stage possession true|true second state possession                        
  int _iaGoalsRequestedMove[3]{ 0, 0, 0 };           // hold's Goal's next movement request

  // Player............................ 
  bool _bPlayerBB{ false }; // player bumped back
  int _iaplayersBumpBackCard[2]{ {-1}, {-1} }; // will print the card out with the bump back note                                                                                                        
  int _iaPlayersCards[nsGF::MPC][2]{ {0},{0} }; // Holds Player's dealt cards 
  int _iPlayersCardsValue{ 0 };  // Total value of all player’s cards remaining to be played 
  int _iaPlayersCurrentPosition[3]{ 43, 20, 50 }; // holds player's curent position 

  int _iPlayersHighestCardValue{ 0 }; // Highest card value held or Players
  bool _bPlayerKO{ false }; // player kicked out
  int _iaPlayersLastPosition[3]{ 0, 0, 0 };  
  int _iaPlayersLongestXYZPath[3]{ 0,0,0 };  // OODA GAME needs to know PLAYER’s longest path inside the GOAL from PLAYER's present position  
  int _iPlayersLongestPathTotal{ 0 };
  bool _baPlayersPossessionState[2]{ {false}, {false} }; // hold's Player's possession state of the Goal: false|false no possession true|false first stage possession true|true second state possession
  int _iaPlayersRequestedMove[3][2]{ {0, 1}, {0, 1}, {0, 1} }; // this is Player’s requested new position  The [n, m]  n == to requested position to move to   when that requested position is tested if it is found to be out of bounds on any axis   that axis request will be modified to keep the Player’s token in bounds and m == will be set to 0 to show that modification has taken place
  int _iPlayersTCi{ -1 }; /* used to remove last cards played */
  int _iPlayersTotalDeltaFromGoalsPerimeter{ 0 };  // The difference in total ‘game space units’ from the PLAYER’s current position and the GOAL closes boundary.  The total of  X, Y, and Z  'game space units'
  int _iaPlayersTrumpCard[2]{ {-1}, {-1} }; // player’s current card pick   the card the player wants to play
  int _iPlayersTrumpCardValue{ -1 };
  int _iaPlayersXYZDeltaFromGoalsPerimeter[3]{ 0, 0, 0 };  // The difference in ‘game space units’ from the PLAYER’s current position and the GOAL closes boundary.   X, Y, and Z values.   Negative means above, Positive means below.

  // It does not matter to the Goal operation what possesses it, only it state of possession.  
  // State 0. The Goal is not possessed, and will move and change shape randomly at the start of each game turn.
  // State 1. A token has moved into the goal space, this will block the Goal from moving or changing shape.
  // State 2. A token has gained control of the Goal the Goal is now free to randomly change shape, but it moves under the 
  // control of the token that has control of it.

protected:

public:
  GameFunctions() 
  {
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      _iaGoalsBumpRangePerimeter[i][0] = _iaGoalsCurrentPerimeter[i][0]-_iGoalsBumpRange;
      _iaGoalsBumpRangePerimeter[i][1] = _iaGoalsCurrentPerimeter[i][1]+_iGoalsBumpRange;
    }
  };  // default constructor
  ~GameFunctions() {}; // default destructor
  int setUpWindow();   // makes window full screen, and cls it
  void setFontSize(int a = 15, int = 15);  // sets font size    

  // Quit's----------------------------------------------------------------------------------------
  char get_Quit() { return quit; }
  void set_Quit(char c) { quit = c; }


  // Game methods PLAYER, GAME, and game-space ------------------------------------------------------  
  void shuffleDeck();
  void dealCards();
  void orderCards();
  void displayCards();
  char pickPlayersCard();
  void pickGamesCard();  // Separate file for this GameFunctions class method  see file pickGamesCard.cpp 
  void placement(int row, int col);   // place cursor for cout/print
  void placeIcon(int[], HANDLE);      // for screen mode output color size ...
  std::string randomWhoLostLastHand();
  void whoLostLastHand(bool&);                    
  bool calculateIfBumpPossible();
  int swapOutCards(int&);
  void clearInputFieldsWarnings(int);
  void testSetGoalPossession(std::string);
  void goalPossessionThrowDownCalculations();  // When PLAYER and GAME are both in the GOAL perimeter then no mater who has what possession state a throw down is mandated, winner gets full possession and loser gets ejected their highest card value plus two ‘game space units’
  void testIfAnyIconBumped();

  // get and set METHODS --------------------------------------------------------------------------------


  // Game's----------------------------------------------------------------------------------------
  bool get_bGameBumpedBack() { return _bGameBumpedBack; }  // was the GAME bumped back by the GOAL
  void set_bGameBumpedBack(bool b) { _bGameBumpedBack = b; }

  int get_iGamesCardValueAtij(int i, int j) { return _iaGamesCards[i][j]; }

  int get_iaGamesCurrentPosition(int i) { return _iaGamesCurrentPosition[i]; }
  void set_iaGamesCurrentPosition(int i, int value) { _iaGamesCurrentPosition[i] = value; }

  bool get_bGameKickedOut() { return _bGameKickedOut; };  // was the GAME kicked out of the GOAL
  void set_bGameKickedOut(bool b) { _bGameKickedOut = b; };  // was the GAME kicked out of the GOAL

  int get_iaGamesRequestedMove(int i) { return _iaGamesRequestedMove[i]; }
  void set_iaGamesRequestedMove(int i, int value) { _iaGamesRequestedMove[i] = value; }

  int get_iaGamesLastPosition(short i) { return _iaGamesLastPosition[i]; }
  void set_iaGamesLastPosition(short i, short value) { _iaGamesLastPosition[i] = value; }

  int get_iaGamesLastTrumpCard(int i) { return _iaGamesLastTrumpCard[i]; }
  void set_iaGamesLastTrumpCard(int i, int value) { _iaGamesLastTrumpCard[i] = value; }

  int get_iaGamesLongestXYZPath(int i) { return _iaGamesLongestXYZPath[i]; }
  void set_iaGamesLongestXYZPath(int i, int value) { _iaGamesLongestXYZPath[i] = value; }

  int get_iGamesLongestPathTotal(int i) {return _iGamesLongestPathTotal;}
  void set_iGamesLongestPathTotal(int i, int value) { _iGamesLongestPathTotal = value; }

  bool get_baGamesPossessionState(int i) { return _baGamesPossessionState[i]; }
  void set_baGamesPossessionState(int i, bool b) { _baGamesPossessionState[i] = b; }

  int get_iaGamesTrumpCard(int i) { return _iaGamesTrumpCard[i]; }
  void set_iaGamesTrumpCard(int i, int value) { _iaGamesTrumpCard[i] = value; }

  int get_iGamesTrumpCardMovementValue() { return _iGamesTrumpCardMovementValue; }
  void set_iGamesTrumpCardMovementValue(int value) { _iGamesTrumpCardMovementValue = value; }

  int get_iGamesTotalDeltaFromGoal() { return _iGamesTotalDeltaFromGoal; }
  void set_iGamesTotalDeltaFromGoal(int value) { _iGamesTotalDeltaFromGoal = value; }

  int get_iGamesTotalDeltaFromGoalsPerimeter() { return _iGamesTotalDeltaFromGoalsPerimeter; }
  void set_iGamesTotalDeltaFromGoalsPerimeter(int value) { _iGamesTotalDeltaFromGoalsPerimeter = value; }

  int get_iaGamesXYZDeltaFromGoalsPerimeter(int i) { return _iaGamesXYZDeltaFromGoalsPerimeter[i]; }
  void set_iaGamesXYZDeltaFromGoalsPerimeter(int i, int value) { _iaGamesXYZDeltaFromGoalsPerimeter[i] = value; }

 
  
 // void placeIcon(int[], HANDLE);


  // Goal's----------------------------------------------------------------------------------------

  bool get_bGoalInContention() { return _bGoalInContention; }
  void set_bGoalInContention(bool b) { _bGoalInContention = b; }

  int get_iGoalsBumpRange(){ return _iGoalsBumpRange; }
  void set_iGoalsBumpRange(int value){ _iGoalsBumpRange = value; }

  int get_iaGoalsBumpRangePerimeter(int i, int j) { return _iaGoalsBumpRangePerimeter[i][j]; }
  int set_iaGoalsBumpRangePerimeter(int i, int j, int value) { _iaGoalsBumpRangePerimeter[i][j] = value; }

  int get_iaGoalsCurrentCenter(int i) { return _iaGoalsCurrentCenter[i]; }
  void set_iaGoalsCurrentCenter(int i, int value) { _iaGoalsCurrentCenter[i] = value; }

  int get_iaGoalsCurrentPerimeter(int i, int j) { return _iaGoalsCurrentPerimeter[i][j]; }
  void set_iaGoalsCurrentPerimeter(int i, int j, int value) { _iaGoalsCurrentPerimeter[i][j] = value; }

  int get_iaGoalsLastPerimeter(int i, int j) { return _iaGoalsLastPerimeter[i][j]; }
  void set_iaGoalsLastPerimeter(int i, int j, int value) { _iaGoalsLastPerimeter[i][j] = value; }

  int get_iaGoalsLenghtWidthHeight(int i) { return _iaGoalsLenghtWidthHeight[i]; }
  void set_iaGoalsLenghtWidthHeight(int i, int value) { _iaGoalsLenghtWidthHeight[i] = value; }

  bool get_baGoalsPossessionState(int i) { return _baGoalsPossessionState[i]; }
  void set_baGoalsPossessionState(int i, bool b) { _baGoalsPossessionState[i] = b; }

  int get_iaGoalsRequestedMove(int i) { return _iaGoalsRequestedMove[i]; }
  void set_iaGoalsRequestedMove(int i, int value) { _iaGoalsRequestedMove[i] = value; }

  // Test of Goal should move to a new random position and or change it size if the Goal is to be moved it will be kept in bounds 
  // If the Goal's requested new location will put any of the Goal's axis lenght, width or height out of the Universe’s bounds then the movement 
  // request will be modified to keep the Goal in bounds 
  bool testIfGoalShouldMoveOrResize();

  // Player's--------------------------------------------------------------------------------------

  bool playersXyzInput(); // test Player's input for legitimate enters and 'esc' to quite and 
  bool testPlayersMovementRequestInBounds(); // if any of the Player's requested axis movement will put them out of Universe bounds then the movement request will be modified to keep the Players token in bounds 

  // Player's get and set ......

  int get_iPlayersCardValueAtij(int i, int j) { return _iaPlayersCards[i][j]; }

  int get_iaPlayersCurrentPosition(int i) { return  _iaPlayersCurrentPosition[i]; }
  void set_iaPlayersCurrentPosition(int i, int value) { _iaPlayersCurrentPosition[i] = value; }
 
  int get_iaPlayersRequestedMove(int i, int j) { return  _iaPlayersRequestedMove[i][j]; }
  void set_iaPlayersRequestedMove(int i, int j, int value) { _iaPlayersRequestedMove[i][j] = value; }

  bool get_baPlayersPossessionState(int i) { return _baPlayersPossessionState[i]; }
  void set_baPlayersPossessionState(int i, bool b) { _baPlayersPossessionState[i] = b; }
 
  int get_iaPlayersTrumpCard(int i) { return _iaPlayersTrumpCard[i]; }
  void set_iaPlayersTrumpCard(int i, int value) { _iaPlayersTrumpCard[i] = value; }

  int get_iaPlayersCards(int i, int j) { return _iaPlayersCards[i][j]; }  // i,0 == value | i,1 == suit
  void set_iaPlayersCards(int i, int j, int value) { _iaPlayersCards[i][j] = value; }

  int get_iaPlayersLastPosition(short i) { return _iaPlayersLastPosition[i]; }
  void set_iaPlayersLastPosition(short i, short value) { _iaPlayersLastPosition[i] = value; }

  int get_iaPlayersLongestXYZPath(int i) { return _iaPlayersLongestXYZPath[i];}  // OODA GAME needs to know PLAYER’s longest path inside the GOAL from PLAYER's present position  
  void set_iPlayersLongestXYZPath(int i, int value) { _iaPlayersLongestXYZPath[i] = value;}

  int get_iPlayersLongestPathTotal(int i) { return _iPlayersLongestPathTotal; }
  void set_iPlayersLongestPathTotal(int value) { _iPlayersLongestPathTotal = value; }

  int get_iPlayersTCi() { return _iPlayersTCi; }   // player’s trump card index number   the trump card’s index in the Player’s card array
  void set_iPlayersTCi(int value) { _iPlayersTCi = value; }

  int get_iPlayersTrumpCardValue() { return _iPlayersTrumpCardValue; }
  void set_iPlayersTrumpCardValue(int value) { _iPlayersTrumpCardValue = value; }

  int get_iPlayersTotalDeltaFromGoalsPerimeter(int i) { return _iPlayersTotalDeltaFromGoalsPerimeter; }
  void set_iPlayersTotalDeltaFromGoalsPerimeter(int i, int value) { _iPlayersTotalDeltaFromGoalsPerimeter = value; }

  int get_iaPlayersXYZDeltaFromGoalsPerimeter(int i) { return _iaPlayersXYZDeltaFromGoalsPerimeter[i]; }
  void set_iaPlayersXYZDeltaFromGoalsPerimeter(int i, int value) { _iaPlayersXYZDeltaFromGoalsPerimeter[i] = value; }

  // Game Space ------------------------------------------------------------------------------------
  int get_iaGameSpaceDimentions(int i) { return _iaGameSpaceDimentions[i]; }
  void set_iaGameSpaceDimentions(int i, int value) { _iaGameSpaceDimentions[i] = value; }
  // 
  bool get_bWhoTDF(){ return _bWhoTDFirst; }; // who throws down first  false == player, ture == GAME
  void set_bWhoTDF(bool b) { _bWhoTDFirst = b; }

  std::string get_sWhoLostLastHand(){ return _sWhoLostLastHand; };  // "PLAYER" or "GAME"
  void set_sWhoLostLastHand(std::string s){ _sWhoLostLastHand = s; }
 
  // Goal's----------------------------------------------------------------------------------------
 
};


