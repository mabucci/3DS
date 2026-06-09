#include "gameSpace.h"

//********************************************************************************************************************
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


//*********************************************************************************************************************
//*********************************************************************************************************************
//***** START testIfAnyIconBumped STARTS ****************************************************************************** 
void GameSpace::testIfAnyIconBumped()
{
  int i{ -1 };
  ++i;
}

//***** END testIfAnyIconBumped ENDS ********************************************************************************** 
//*********************************************************************************************************************
//*********************************************************************************************************************