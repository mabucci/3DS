#include "displayPrompsWarning.h"


void DisplayPrompsWarning::printMain(int i, GameSpace& gS)
{
  switch (i) {
  case nsSPM::DC::DISPLAY_GREETINGS://+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    system("cls");      // clear the newly created window 
    std::print("{}", nsGF::greetingString); // print greeting and instructions to game play
    gS.placement(0, 0);  // move to top of greeting
    break;
  } //-----------------------------------------------------------------------------------------------------------------

  case nsSPM::DC::PLAYERS_DATA_DISPLAY://++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    gS.placement(nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_ROW + 2);
    if (gS.get_iaPlayersTrumpCard(0) != -1)
    {
      std::cout << "                    ";
      gS.placement(nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::PLAYERS_LAST_CARD_PLAYED_HEADER_ROW + 2);
      std::cout << GREEN << nsGF::cardNames[gS.get_iaPlayersTrumpCard(0)] << RESET << " of " << GREEN << nsGF::cardSuits[gS.get_iaPlayersTrumpCard(1)] << RESET;
    }
    else
    {
      std::cout << GREEN;
      std::cout << "None selected yet.";
      std::cout << RESET;
    }
    // Display Player's current position data displayed  Headers displayed by gameSpace.cpp
    gS.placement(nsGF::PLAYERS_POSITION_DATA_COLUMN, nsGF::PLAYERS_POSITION_DATA_ROW);
    for (int i = 0; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      gS.placement(nsGF::PLAYERS_POSITION_DATA_COLUMN, i + nsGF::PLAYERS_POSITION_DATA_ROW);

      if (gS.get_iaPlayersCurrentPosition(i) < gS.get_iaGoalsCurrentPerimeter(i, 0))
        std::cout << RED;
      else if (gS.get_iaPlayersCurrentPosition(i) >= gS.get_iaGoalsCurrentPerimeter(i, 0) && gS.get_iaPlayersCurrentPosition(i) <= gS.get_iaGoalsCurrentPerimeter(i, 1))
        std::cout << GREEN;
      else  if (gS.get_iaPlayersCurrentPosition(i) > gS.get_iaGoalsCurrentPerimeter(i, 1))
        std::cout << YELLOW;
      std::print( "{:>3}",  gS.get_iaPlayersCurrentPosition(i));
      std::cout << RESET;
    }

    // Display Play’s GOAL possession states.     Headers displayed by gameSpace.cpp
    for (int i{ 0 }; i < 2; ++i)
    {
      gS.placement(nsGF::PLAYERS_GOAL_POSSESSION_STATE_DATA_COLUMN, nsGF::PLAYERS_GOAL_POSSESSION_STATE_DATA_ROW + i);
      std::cout << GREEN;
      std::print("      ");
      gS.placement(nsGF::PLAYERS_GOAL_POSSESSION_STATE_DATA_COLUMN, nsGF::PLAYERS_GOAL_POSSESSION_STATE_DATA_ROW + i);
      std::print("{}", gS.get_baPlayersPossessionState(i));
      std::cout << RESET;
    }
    break;
  }//------------------------------------------------------------------------------------------------------------------

  case nsSPM::DC::GAMES_DATA_DISPLAY://++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    //Display  Game’s current data, headers displayed be gameSpace.cpp
    gS.placement(nsGF::GAMES_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::GAMES_LAST_CARD_PLAYED_HEADER_ROW + 2);
    if (gS.get_iaGamesTrumpCard(0) != -1)
    {
      std::cout << "                   ";
      gS.placement(nsGF::GAMES_LAST_CARD_PLAYED_HEADER_COLUMN, nsGF::GAMES_LAST_CARD_PLAYED_HEADER_ROW + 2);
      std::cout << BLUE << nsGF::cardNames[gS.get_iaGamesTrumpCard(0)] << RESET << " of " << BLUE << nsGF::cardSuits[gS.get_iaGamesTrumpCard(1)] << RESET;
    }
    else
    {
      std::cout << BLUE;
      std::cout << "None selected yet.";
      std::cout << RESET;
    }

    for (int i = 0; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      gS.placement(nsGF::GAMES_POSITION_DATA_COLUMN, i + nsGF::GAMES_POSITION_DATA_ROW);
      // std::cout << gS.get_iaGamesCurrentPosition(i);
      std::cout << BLUE;
      std::print("      ");
      gS.placement(nsGF::GAMES_POSITION_DATA_COLUMN, i + nsGF::GAMES_POSITION_DATA_ROW);
      if (gS.get_iaGamesCurrentPosition(i) < gS.get_iaGoalsCurrentPerimeter(i, 0))
        std::cout << RED;
      else if (gS.get_iaGamesCurrentPosition(i) >= gS.get_iaGoalsCurrentPerimeter(i, 0) && gS.get_iaGamesCurrentPosition(i) <= gS.get_iaGoalsCurrentPerimeter(i, 1))
        std::cout << GREEN;
      else  if (gS.get_iaGamesCurrentPosition(i) > gS.get_iaGoalsCurrentPerimeter(i, 1))
        std::cout << YELLOW;
      std::print("{:>3}", gS.get_iaGamesCurrentPosition(i));
      std::cout << RESET;
    }

    // Display Game’s GOAL possession states.     Headers displayed by gameSpace.cpp
    for (int i{ 0 }; i < 2; ++i)
    {
      gS.placement(nsGF::GAMES_GOAL_POSSESSION_STATE_DATA_COLUMN, nsGF::GAMES_GOAL_POSSESSION_STATE_DATA_ROW + i);
      std::cout << BLUE;
      std::print("      ");
      gS.placement(nsGF::GAMES_GOAL_POSSESSION_STATE_DATA_COLUMN, nsGF::GAMES_GOAL_POSSESSION_STATE_DATA_ROW + i);
      std::print("{}", gS.get_baGamesPossessionState(i));
      std::cout << RESET;
    }
    break;
  }//------------------------------------------------------------------------------------------------------------------

  case nsSPM::DC::GOALS_DATA_DISPLAY://++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    // Display GOAL’s position data Headers displayed by gameSpace.cpp    
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      gS.placement(nsGF::GOALS_CENTER_POSITION_DATA_COLUMN + (i * 7), nsGF::GOALS_CENTER_POSITION_DATA_ROW);
      std::cout << YELLOW;
      std::print("{:>3}", gS.get_iaGoalsCurrentCenter(i));
      std::cout << RESET;
    }

    // Display  GOAL's  dimensions       Headers displayed by gameSpace.cpp
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      int _iSpacer{ 0 };
      std::cout << YELLOW;
      gS.placement(nsGF::GOALS_DIMENSIONS_DATA_COLUMN + (i * 16), nsGF::GOALS_DIMENSIONS_DATA_ROW);
      std::print("{:>3}", gS.get_iaGoalsCurrentPerimeter(i, 0));
      gS.placement(nsGF::GOALS_DIMENSIONS_DATA_COLUMN + (i * 16 + 9), nsGF::GOALS_DIMENSIONS_DATA_ROW);
      std::print("{:>3}", gS.get_iaGoalsCurrentPerimeter(i, 1));
      if (i == 2) ++_iSpacer;
      gS.placement(nsGF::GOALS_LENTH_WIDTH_HIEGHT_DATA_COLUMN + (i * 10 + _iSpacer), nsGF::GOALS_LENTH_WIDTH_HIEGHT_DATA_ROW);
      std::print("{:>3}", gS.get_iaGoalsLenghtWidthHeight(i));
      std::cout << RESET;
    }
    break;
  }//------------------------------------------------------------------------------------------------------------------

   // Set cursor position for ‘cout’, or ‘print’
  case nsSPM::DC::CLEAR_PLAYERS_XYZ_INPUT: //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    for (int i{ 0 }; i < 4; ++i)
    {
      gS.placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW + i);
      std::print("                         ");
    };
    break;
  };//--------------------------------------------------------------------------------------------------------------------
  
   // 
  case nsSPM::DC::PLAYERS_XYZ_POSITION_DELTAS: //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    int _LiaTestBefore[3][2]{ {0,99}, {0,99}, {0, 99} };
    int _LiaTestAfter[3][2]{ {0,99}, {0,99}, {0, 99} };
    gS.placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW);
    for (int i = 0; i < nsGF::NOD; ++i)
    {
      _LiaTestBefore[i][0] = gS.get_iaPlayersRequestedMove(i, 0);     _LiaTestBefore[i][1] = gS.get_iaPlayersRequestedMove(i, 1);

      gS.placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW + i); // Set cursor position for ‘cout’, or ‘print’

      if (gS.get_iaPlayersRequestedMove(i, 1) == 1)
        std::cout << nsGF::_saMoveMentRequestResultsAccepted[i] << GREEN << gS.get_iaPlayersRequestedMove(i, 0) << RESET << '\n';
      else
        std::cout << RED << nsGF::_saMoveMentRequestModified[i] << RESET << gS.get_iaPlayersRequestedMove(i, 0) << RESET << '\n';
    };
    for (int i = 0; i < nsGF::NOD; ++i)
    {

      gS.set_iaPlayersRequestedMove(i, 1, 1);  // reset to (i, 1, 1==TRUE) for next test round
      // adjust current Player’s position with Player’s approved/modified movement request  
      _LiaTestAfter[i][0] = gS.get_iaPlayersRequestedMove(i, 0);     _LiaTestAfter[i][1] = gS.get_iaPlayersRequestedMove(i, 1);
    };
    break;
  }//----------------------------------------------------------------------------------------------------------------------

  // 
  case nsSPM::DC::GOAL_IN_CONTENTION : //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    gS.placement(nsGF::GOAL_IN_CONTENTION_HEADER_COLUMN, nsGF::GOAL_IN_CONTENTION_HEADER_ROW);
    std::cout << RED << "Goal in contention, pick card for top trups with GAME:"<<RESET;
    break;
  }//----------------------------------------------------------------------------------------------------------------------

  // 
  case nsSPM::DC::CLEAR_GOAL_IN_CONTENTION: //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    gS.placement(nsGF::GOAL_IN_CONTENTION_HEADER_COLUMN, nsGF::GOAL_IN_CONTENTION_HEADER_ROW);
    std::cout << RESET << "                                                      " << RESET;
    break;
  }//----------------------------------------------------------------------------------------------------------------------


  // Display the PLAYER's location on the 'game space' display 
  case nsSPM::DG::PLAYERS_ICON_DISPLAY : //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {

    placement(nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaPlayersLastPosition(0), nsGF::ICON_ROW_START_OFF_SET + gS.get_iaPlayersLastPosition(1));
    std::cout << YELLOW_ON_BLUE;
    std::print(".");
    if ((gS.get_iaGoalsCurrentPerimeter(0, 0) == gS.get_iaPlayersLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(1, 0) <= gS.get_iaPlayersLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(1, 1)) || \
         (gS.get_iaGoalsCurrentPerimeter(0, 1) == gS.get_iaPlayersLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(1, 0) <= gS.get_iaPlayersLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(1, 1) || \
           (gS.get_iaGoalsCurrentPerimeter(1, 0) == gS.get_iaPlayersLastPosition(1) && gS.get_iaGoalsCurrentPerimeter(0, 0) <= gS.get_iaPlayersLastPosition(0) <= gS.get_iaGoalsCurrentPerimeter(0, 1)) || \
             (gS.get_iaGoalsCurrentPerimeter(1, 1) == gS.get_iaPlayersLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(0, 0) <= gS.get_iaPlayersLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(0, 1))))
              printMain(nsSPM::DG::GOALS_ICON_DISPLAY, gS); // Display the GOAL perimeter

    std::cout << RESET;
    placement(nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaPlayersCurrentPosition(0), nsGF::ICON_ROW_START_OFF_SET + gS.get_iaPlayersCurrentPosition(1));
    std::print("P");
    break;
  } //--------------------------------------------------------------------------------------------------------------------
   // Display the PLAYER's location on the 'game space' display 
  case nsSPM::DG::GAMES_ICON_DISPLAY: //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    placement(nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGamesLastPosition(0), nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGamesLastPosition(1));
    std::cout << YELLOW_ON_BLUE;
    std::print(".");
    if( (gS.get_iaGoalsCurrentPerimeter(0,0) == gS.get_iaGamesLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(1, 0) <= gS.get_iaGamesLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(1, 1)) ||\
         (gS.get_iaGoalsCurrentPerimeter(0, 1) == gS.get_iaGamesLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(1, 0) <= gS.get_iaGamesLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(1,1) ||\
           (gS.get_iaGoalsCurrentPerimeter(1, 0) == gS.get_iaGamesLastPosition(1) && gS.get_iaGoalsCurrentPerimeter(0, 0) <= gS.get_iaGamesLastPosition(0) <= gS.get_iaGoalsCurrentPerimeter(0, 1)) || \
             (gS.get_iaGoalsCurrentPerimeter(1, 1) == gS.get_iaGamesLastPosition(0) && gS.get_iaGoalsCurrentPerimeter(0, 0) <= gS.get_iaGamesLastPosition(1) <= gS.get_iaGoalsCurrentPerimeter(0, 1) ) ) )
               printMain(nsSPM::DG::GOALS_ICON_DISPLAY, gS); // Display the GOAL perimeter

    std::cout << RESET;
    placement(nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGamesCurrentPosition(0), nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGamesCurrentPosition(1));
    std::print("G");
    break;
  }// end  case on nsSPM::DG::GAMES_ICON_DISPLAY:----------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------

  //Display the GOAL's perimeter
  case nsSPM::GOALS_ICON_DISPLAY:  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    // Cover up last GOAL perimeter icon display with ‘game space’ background 
    // // 'i' starts with Xlow + ‘game space’ off set  (0, 1) == Ylow and will stay constant as top of last GOAL perimeter is covored over
    for (int i{ nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsLastPerimeter(0,0) }; i <= nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsLastPerimeter(0, 1); ++i)
    {                                                                                       // need the '<=' to fill in the lower right hand corner of GOAL's perimeter
      placement(i, nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsLastPerimeter(1, 0));   
      std::cout << YELLOW_ON_BLUE;
      std::print(".");
      // (1, 1) is Yhigh this will stay constant as the bottom of the GOAL's last perimeter is covered over 
      placement(i, nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsLastPerimeter(1, 1));
      std::cout << YELLOW_ON_BLUE;
      std::print(".");
    }
    // same idea as above but do it for the sides                                      // need the '<=' to fill in the lower right hand corner of GOAL's perimeter
    for (int i{ nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsLastPerimeter(1, 0) }; i <= nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsLastPerimeter(1, 1); ++i)
    {
      placement( nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsLastPerimeter(0, 0), i);
      std::cout << YELLOW_ON_BLUE;
      std::print(".");

      placement( nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsLastPerimeter(0, 1), i);
      std::cout << YELLOW_ON_BLUE;
      std::print(".");
    }                                                       
                                               // (0, 0) to  (0, 1)  (1, 0) to (1, 1)
    // Now draw new GOAL perimeter                 Xlow  to  Xhigh    Ylow  to Yhigh)        // need the '<=' to fill in the lower right hand corner of GOAL's perimeter
    for (int i{ nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(0,0) }; i <= nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(0, 1); ++i)
    {                                          
      placement(i, nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(1, 0));
     if (gS.get_baGamesPossessionState(0) && gS.get_baPlayersPossessionState(0))
       std::cout << RED; 
     else std::cout<<GREEN;
      std::cout << static_cast<char>(219);  // block char
      // (1, 1) is Yhigh this will stay constant as the bottom of the GOAL's last perimeter is coveLIME over 
      placement(i, nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(1, 1));
      if (gS.get_baGamesPossessionState(0) && gS.get_baPlayersPossessionState(0))
        std::cout << RED;
      else std::cout << GREEN;
      std::cout << static_cast<char>(219);  // block char
    }
    // same idea as above but do it for the sides                                     // need the '<=' to fill in the lower right hand corner of GOAL's perimeter
    for (int i{ nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(1, 0) }; i <= nsGF::ICON_ROW_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(1, 1); ++i)
    {
      placement( nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(0, 0), i );
      if (gS.get_baGamesPossessionState(0) && gS.get_baPlayersPossessionState(0))
        std::cout << RED;
      else std::cout << GREEN;
      std::cout << static_cast<char>(219);

      placement( nsGF::ICON_COLUMNE_START_OFF_SET + gS.get_iaGoalsCurrentPerimeter(0, 1), i);
      if (gS.get_baGamesPossessionState(0) && gS.get_baPlayersPossessionState(0))
        std::cout << RED;
      else std::cout << GREEN;

      std::cout << static_cast<char>(219);
    }  // end of case on  nsSPM::GOALS_ICON_DISPLAY: ------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------

    std::cout << RESET;
    break;
  }

  default:
    std::println("At default");
    break;
  }


}