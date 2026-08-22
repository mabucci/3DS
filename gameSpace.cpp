#include "gameSpace.h"


//********************************************************************************************************************
//***** START  void buildGameSpace();
// Will build and display the field(game space) and print headers for Player, Game, and Goal data.
// Current position, card picked so on
// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
void GameSpace::buildGameSpace()
{
  // Microsoft Code Page 65001 is the Windows identifier for the UTF-8 character encoding. 
  // It allows Windows applications, particularly legacy ones and the console (CMD), to interpret and display Unicode characters.
  SetConsoleOutputCP(65001);

  // Side borders of ‘game space’
  for (int i{ 0 }; i < nsGF::GAME_SPACE_WIDTH; ++i)
  {    
    placement(nsGF::FIELD_COL_ZERO_OFF_SET - 2, i + nsGF::FIELD_ROW_ZERO_OFF_SET+1);    
    std::cout << RESET; // "\033[0m"; // reset to default forground background collor
    std::print("{:>2}", i);
    std::cout << YELLOW_ON_BLUE; // "\033[33;2;44;2m"; // all cout down to   "std::cout << "\033[0m";" will be  Yellow on Blue 
    placement(nsGF::FIELD_COL_ZERO_OFF_SET, i + nsGF::FIELD_ROW_ZERO_OFF_SET + 1);
    std::print("║");
    for (int j{ 0 }; j < nsGF::GAME_SPACE_LENGTH; ++j) // 'game space' gets blue backgroun and a dot in every game space unit 
      std::cout << ".";
    placement(nsGF::FIELD_COL_ZERO_OFF_SET + nsGF::GAME_SPACE_LENGTH+1, i + nsGF::FIELD_ROW_ZERO_OFF_SET + 1);
    std::cout << "║";
    std::cout << RESET; // "\033[0m"; // reset to default forground background collor
    std::print("{:>2}", i);
  }// END of for

  // Top border of ‘game space’
  std::cout << YELLOW_ON_BLUE; // "\033[33;2;44;2m"; // all cout down to   "std::cout << "\033[0m";" will be  Yellow on Blue 
  placement(nsGF::FIELD_COL_ZERO_OFF_SET , nsGF::FIELD_ROW_ZERO_OFF_SET);
  std::print("╔");
//  placement(nsGF::FIELD_COL_ZERO_OFF_SET + 1, nsGF::START_ROW);
  for (int i{ 0 }; i < nsGF::GAME_SPACE_LENGTH ; ++i)
  {
    std::cout << "═";
  }
  std::print("╗");

  // Bottom border of ‘game space’
  placement(nsGF::FIELD_COL_ZERO_OFF_SET , nsGF::GAME_SPACE_WIDTH + 3);
  std::print("╚");
  for (int i{ 0 }; i < nsGF::GAME_SPACE_LENGTH ; ++i)
  {
    std::cout << "═";
  }
  std::print("╝");
  std::cout << RESET; // "\033[0m"; // reset to default forground background collor 

  //  Now top and bottom hash marks and column values 0, 5, 10, 15 . . . 
  for (int k{ 0 }; k < nsGF::GAME_SPACE_LENGTH; ++k)
  {
    if (k % 5 == 0)
    {
      placement(nsGF::FIELD_COL_ZERO_OFF_SET + 1 + k, nsGF::FIELD_ROW_ZERO_OFF_SET - 1);
      std::print("v{}", k);
    }
  }
  for (int k{ 0 }; k < nsGF::GAME_SPACE_LENGTH; ++k)
  {
    if (k % 5 == 0)
    {
      placement(nsGF::FIELD_COL_ZERO_OFF_SET + 1 + k, nsGF::GAME_SPACE_WIDTH + 4);
      std::print("^{}", k);
    }
  }

  // Player's last card played header
  placement(nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_ROW);
  std::cout << "Player's last card \nselected," << std::endl;
  /* if (get_iaPlayersTrumpCard(0) != -1)
     std::cout << nsGF::cardNames[get_iaPlayersTrumpCard(0)] << " of " << nsGF::cardSuits[get_iaPlayersTrumpCard(1)];
   else
     std::cout << "None selected yet.";  */
     // Player's current position display headers 
  for (int i = 0; i < nsGF::NOD; ++i)
  {
    placement(nsGF::PLAYERS_POSITION_HEADER_COLUMN, i + nsGF::PLAYERS_POSITION_HEADER_ROW);
    std::cout << nsGF::_saPlayersCurrentPositionProms[i];
  }

  // Player’s GOAL possession state
  placement(nsGF::PLAYERS_GOAL_POSSESSION_STATE_HEADER_COLUMN, nsGF::PLAYERS_GOAL_POSSESSION_STATE_HEADER_ROW);
  std::cout << "Player's GOAL\npossession state,";
  std::cout << "\nState one: ";
  std::cout << "\nState two: ";

  // Game's last card played header
  placement(nsGF::GAMES_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::GAMES_LAST_CARD_PLAYED_HEADER_ROW);
  std::cout << "Game's last card";
  placement(nsGF::GAMES_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::GAMES_LAST_CARD_PLAYED_HEADER_ROW + 1);
  std::cout << "selected,";

  // Game's current position display headers 
  for (int i = 0; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
  {
    placement(nsGF::GAMES_POSITION_HEADER_COLUMN, i + nsGF::GAMES_POSITION_HEADER_ROW);
    std::cout << nsGF::_saGamesCurrentPositionProms[i];
  }
  int i{ 0 };
  // Games’s GOAL possession state headers
  for (std::string s : nsGF::_saGoalsPossessionStateHeaders)
  {   
    placement(nsGF::GAMES_GOAL_POSSESSION_STATE_HEADER_COLUMN, nsGF::GAMES_GOAL_POSSESSION_STATE_HEADER_ROW + i);
    std::print("{}", s);
    ++i;
  }
  
 // Goal's position and size dimension data value headers
  placement(nsGF::GOALS_CENTER_POSITION_HEADER_COLUMN, nsGF::GOALS_CENTER_POSITION_HEADER_ROW);
  std::print("{}  {}", nsGF::_sGoalsPositionDataHeaders, nsGF::_sGoalsDimensionalDataHeaders);
  placement(nsGF::GOALS_LENTH_WIDTH_HIEGHT_HEADER_COLUMN, nsGF::GOALS_LENTH_WIDTH_HIEGHT_HEADER_ROW );
  std::print("{}", nsGF::_sGoalsLengthWidthHeightDataHeaders);

  // The default character set(code page) for the Microsoft DOS console, specifically for U.S.English and many other western 
  // regions, is Code Page 437 (CP437), often referred to as "OEM-US" or PC - ASCII. 
  SetConsoleOutputCP(437);
}
//***** END void buildGameSpace() ENDS ********************************************************************************
//*********************************************************************************************************************




//*********************************************************************************************************************
//***** START testIfAnyIconBumped STARTS ****************************************************************************** 
// if any icon is in the bump range (GOAL_BUMP_BACK_RANGE) of the GOAL then bump that icon to a new location that is a distance 
// equal to that icon’s highest card value plus two game space units
// the direction of the bump is to be a right angle to the GOAL’s perimeter on which the bump occurred
// if there is not enough room between the GOAL’s perimeter and the edge of the game-space to accommodate that bump, 
// them bump the icon from the opposite GOAL perimeter on the same axis
void GameSpace::testIfAnyIconBumped()
{
  bool _LbPlaerBump{ false }; // does the PLAYER get bumped
  bool _LbGameBump{ false }; //does the GAME get bumped
  bool _LbPlayerInGoal{ false }; // is the PLAYER in the GOAL
  bool _LbGameInGoal{ false };   // is the GAME in the GOAL

  int _LiaGame[3];  // GAME's position
  int _LiaPlayer[3];// PLAYER's position
  int _LiaGoal[3];  // GOAL's position ( center of GOAL)
  int _LiaGoalP[3][2]; // GOAL's perimeter [n][0] low perimeter on 'n' axis, [n][1] high perimeter on 'n' axis
  int _LiAxis;  // axis to be bumped along X,Y,orZ (0,1, or 2)
  int _LiDirection; // direction to be bumped on 0 down, 1 up
  int _LiBumpCardValue; // icon to be bumped highest card value 
  
// load position data for current move
  for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
  {
    _LiaGame[i] = get_iaGamesCurrentPosition(i);
    _LiaPlayer[i] = get_iaPlayersCurrentPosition(i);
    _LiaGoal[i] = get_iaGoalsCurrentPositon(i);
    _LiaGoalP[i][0] = get_iaGoalsCurrentPerimeter(i, 0);
    _LiaGoalP[i][1] = get_iaGoalsCurrentPerimeter(i, 1);
  }


// test if PLAYER or GAME will be bumped
// simply test if ICON is in the GOAL's bump range usually 2 or 3 game-space units
// remember the ICON must be in that range of all three axis of the GOAL
  for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
  { 
    if ( (_LiaGame[i] < _LiaGoalP[i][0] && _LiaGame[i] >= _LiaGoalP[i][0] - nsGF::GOAL_BUMP_BACK_RANGE )
           || _LiaGame[i] > _LiaGoalP[i][1] && _LiaGame[i] <= _LiaGoalP[i][1] + nsGF::GOAL_BUMP_BACK_RANGE ) )
      _LbGameBump = true;
    else _LbGameBump = false;
     if ( (_LiaPlayer[i] < _LiaGoalP[i][0] && _LiaPlayer[i] >= _LiaGoalP[i][0] - nsGF::GOAL_BUMP_BACK_RANGE )
           || _LiaPlayer[i] > _LiaGoalP[i][1] && _LiaPlayer[i] <= _LiaGoalP[i][1] + nsGF::GOAL_BUMP_BACK_RANGE ) )
      _LbPlayerBump = true;
    else _LbPlayerBump = false;
  }
  
  // if _LbPlayerBump  and or _LbGameBump is true here then that ICON is to be bumped away from the GOAL
   if(_LbGameBump)
  {
   _LiAxis = randomNumberGenerator(0, nsGF::NUMBER_OF_DIMENSIONS );  // A general Random Number Generator method   takes two arguments that make the [inclusive range] 
   _LiDirection  = randomNumberGenerator(0, 1);
   // get value of ICON to be bumped highest card value
   _LiBumpCardValue = get_Games_Highest_Card_Value();  
   // test if enough room to bump in direction _LiDirection on axis _LiAxis    
   // if there is not enough room to bump from the GOAL perimeter to the game-space boundary then flip to the opposite perimeter 
   // if bump is of the GOAL high X perimeter but the distance between that perimeter and the game-space boundary is less that the bump range
   // then flip the bump to be off GOAL low X perimeter 
    
  }
  
}

//***** END testIfAnyIconBumped ENDS ********************************************************************************** 
//*********************************************************************************************************************



//*********************************************************************************************************************
//***** START testGoalContentionWinner STARTS *************************************************************************
// Three possible outcomes;  GAME wins, GAME’s trump card is greater than PLAYER’s trump card and GAME has the XYZ path 
// length to accommodate that theoretical move, PLAYER wins, PLAYER’s trump card is greater than GAME’s trump card and 
// PLAYER has the XYZ path length to accommodate that theoretical move.    There can be no DRAW as if both trump cards 
// have the same movement value then the SUIT decides the winder.   Qed:  Three of Hearts == 7 movement points, 
// Four of Diamonds == 7 movement points, but Hearts bets Diamonds, so Three of Hearts winds. 
void GameSpace::testGoalContentionWinner()
{
  // Player winds, Game gets kicked out   
  if( (get_iaPlayersTrumpCard(0) + get_iaPlayersTrumpCard(1)) > (get_iaGamesTrumpCard(0) + get_iaGamesTrumpCard(1) )
    || (get_iaPlayersTrumpCard(0) + get_iaPlayersTrumpCard(1)) == (get_iaGamesTrumpCard(0) + get_iaGamesTrumpCard(1)
      && get_iaPlayersTrumpCard(1) > get_iaGamesTrumpCard(1)) ) // If value tie then suit decides 
  {
    int _LiKickDistance = get_iGamesCardValueAtij(0,0) + 1 + get_iGamesCardValueAtij(0,1) + 1 + nsGF::GOAL_BUMP_BACK_RANGE;
    int _LiAxis = randomNumberGenerator(0, 2);      
    int _LiDirection = randomNumberGenerator(0, 1);  // 0 == negative direction 
    
  
    int _LiGoalsSide = get_iaGoalsCurrentPerimeter(_LiAxis, _LiDirection); // This will give the low or high side boundary of the GOAL 

    _LiDirection == 0  ?  _LiDirection = -1 : _LiDirection = +1;
    for(int i{0}; i<3; ++i)
      set_iaGamesLastPosition(i, get_iaGamesCurrentPosition(i));  // Need old position so ICON can be over written 
    set_iaGamesCurrentPosition(_LiAxis, (_LiKickDistance * _LiDirection ) + _LiGoalsSide );  // New kicked out to position
    testCorrectKickOutPosition("GOAL");  // Test and or correct the new kicked out to position, if kicked out position is out of game space then clip that position to keep the ICON in bounds  
    set_baGamesPossessionState(0,false);  set_baGamesPossessionState(1, false);  // Out side of GOAL possession state is false, false

  }else  if ((get_iaPlayersTrumpCard(0) + get_iaPlayersTrumpCard(1)) < (get_iaGamesTrumpCard(0) + get_iaGamesTrumpCard(1))
    || (get_iaPlayersTrumpCard(0) + get_iaPlayersTrumpCard(1)) == (get_iaGamesTrumpCard(0) + get_iaGamesTrumpCard(1)
      && get_iaPlayersTrumpCard(1) < get_iaGamesTrumpCard(1)))  // If value tie then suit decides 
  {
    int _LiKickDistance = get_iPlayersCardValueAtij(0, 0) + 1 + get_iPlayersCardValueAtij(0, 1) + 1 + nsGF::GOAL_BUMP_BACK_RANGE;
    int _LiAxis = randomNumberGenerator(0, 2);
    int _LiDirection = randomNumberGenerator(0, 1);

    int _LiGoalsSide = get_iaGoalsCurrentPerimeter(_LiAxis, _LiDirection);

    _LiDirection == 0 ? _LiDirection = -1 : _LiDirection = +1;
    for (int i{ 0 }; i < 3; ++i)
      set_iaPlayersLastPosition(i, get_iaPlayersCurrentPosition(i));
    set_iaPlayersCurrentPosition(_LiAxis, (_LiKickDistance * _LiDirection) + _LiGoalsSide);
    testCorrectKickOutPosition("PLAYER");  // Test and or correct the new kicked out to position, if kicked out position is out of game space then clip that position to keep the ICON in bounds  
    set_baPlayersPossessionState(0, false);   set_baPlayersPossessionState(1, false);
  }

}
//***** END testGoalContentionWinner ENDS *****************************************************************************
//*********************************************************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++ START testCorrectKickOutPosition STARTS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void GameSpace::testCorrectKickOutPosition(std::string icon)
{
  if(icon == "PLAYER")
  {
    for (int i{ 0 }; i < 3; ++i)
    {
      if (get_iaPlayersCurrentPosition(i) < 0) set_iaPlayersCurrentPosition(i, 0);
      else if (get_iaPlayersCurrentPosition(i) > get_iaGameSpaceDimentions(i)) set_iaPlayersCurrentPosition(i, get_iaGameSpaceDimentions(i) - 1);
    }
  }
  else if (icon == "GAME")
  {
    for (int i{ 0 }; i < 3; ++i)
    {
      if (get_iaGamesCurrentPosition(i) < 0) set_iaGamesCurrentPosition(i, 0);
      else if (get_iaGamesCurrentPosition(i) > get_iaGameSpaceDimentions(i)) set_iaGamesCurrentPosition(i, get_iaGameSpaceDimentions(i) - 1);
    }
  }
}
//----- END testCorrectKickOutPosition ENDS ---------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++ START randomNumberGenerator STARTS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// A general Random Number Generator method   takes two arguments that make the [inclusive range] 
int GameSpace::randomNumberGenerator(int a, int b)
{
  // random number generator seeding
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed); // Mersenne Twister engine

  //  Define the desired distributions (e.g., uniform integer distribution between [m, n] inclusive m<=x<=n)  
  std::uniform_int_distribution<int> random(a, b);
  return random(gen);

}
//----- END randomNumberGenerator ENDS --------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
