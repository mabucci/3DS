/*****
this .cpp file and its' .h file will hold the game functions class, this class will hold all the members and methods that
will do the work of the game
*****/

#include"gameData.h"
#include"gameFunctions.h"

//**********************************************************************************************
//***** Game Functions Methods *****************************************************************/
 
 //**********************************************************************************************/
//**********************************************************************************************
//***** START getTestInput METHOD **************************************************************

/***********************************************************************************************
Now must test players input to make sure it fits game play requirements
1. player must pick card to play.
2. player must enter how much of that cards value is to be spent on x, y, and z, movement
3. movement can be positive or negative;  for positive movement a positive hole number is 
entered at the axis prompt, if no movement is wanted on that axis then a zero is entered
if negative movement is wanted then the ‘-’ minus sigh is entered before the hold number valued  
if a minus sigh is entered before a zero then the enter is treated as a zero
there are three axis of movement if a player enters all of there cards values on the first x axis 
then the y and z axis will default to zero   if that is done for x and y axis then z will default to zero
Examples:
player pick 8 of diamonds   the 8 of diamond has a suit value of 3 and a face value of 8
giving it a total movement value of 11
so input x = 5  y = -2 z =4 is legitimate entry the sum of the absolute values of the entries match 
the card value being plaid
but input x = 1  y = 2  z = -1 is not legitimate as the absolute values of the entries do not match 
the card value being plaid
illegitimate value entry will cause the player to be prompted for a new movement axis entry values
if the player inters x = 8  y = 3 then z will default to 0
if the player inters x = 11 then y and z will default to 0
changing the axis values once entered   if the play is at the z axis value entry and desire they do 
not like the x or y then simply entering a value that will make the x,y, and z values greater than 
the card value will trip a reenter all values method.
************************************************************************************************/


//*******************************************************************************
//*******************************************************************************
// 
// place cursor at row, col values **********************************************
void GameFunctions::placement(int col, int row)
{
  // std::cout << "\033[" << row << ";" << col << "H";  
  COORD coord;
  coord.X = col;
  coord.Y = row;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//*******************************************************************************
//*******************************************************************************


/***************************************************************************************************** 
who ever lost the last hand (last throw-down) has to pick a card to throw down first this is a big advantage
QED:  if the Game lost the last hand (had thrown-down a card with value less than the Player’s card value) then on the next throw	-down 
the Game will have pick a card to play and show that card to the Player before any thing else happens;  before, the Player picks a card 
to throw down, or the Goal moves or changes shape
1. Game throws-down FIVE of CLUBS == total value of 7 movement points, Player throws-down FOUR of HARTS == total value of 8 movement 
points.
2. The game lost the last hand, even if it got control of the Goal, and must pick and show the next card it will play.
3. The Game picks SEVEN of DIAMONDS, the SEVEN of DIAMONDS is shown as the Game’s card it is playing.
4. Now the Player has a big advantage, the does not know how the Game is going to use it’s 10 movement points it got by throwing-down 
the SEVEN of DIAMONDS, but the Player knows the game has those 10 movement points.
5. If the Player loses the next hand (the next throw-down) then the Player will have to throw-down a card before the Game does.
Again;  who ever lost last throw-down has to pick a card to throw-down first in the throw-down, that player then enters it X, Y, and Z 
movement request, but only the card being throw-down is shown not the X, Y, and Z movement request.  
Now the winner last throw-down will pick a card to play and enter the wanted X, Y, and Z, movement request.     
Then the “game space” will resolve any gains, losses, and conflicts.
******************************************************************************************************/

/*****************************************************************************************************/
/***** START whoLostLastThrowDown STARTS *************************************************************/
void GameFunctions::whoLostLastHand(bool& b) /* determines who won trump player == TRUE, game == FALSE  */
{
  if (b)
  {
    b = false;  // First play need random coin flip PLAYER/GAME.
    _sWhoLostLastHand =  randomWhoLostLastHand();
    return;
  }
  // use past trump card values to fine loser of last throw-down
  if (_iaGamesTrumpCard[0] > _iaPlayersTrumpCard[0])
    _sWhoLostLastHand = "PLAYER"; /* game's card number trumps palyer's suit */
  else
    if (_iaGamesTrumpCard[0] < _iaPlayersTrumpCard[0])
      _sWhoLostLastHand = "GAME"; /* player's card number trumps game's suit */
    else if (_iaGamesTrumpCard[0] == _iaPlayersTrumpCard[0])  // if card numbers ==
      if (_iaGamesTrumpCard[1] > _iaPlayersTrumpCard[1])/* then evaluate by suit */
        _sWhoLostLastHand = "PLAYER";   /* game's card value trumps player's */
      else
        _sWhoLostLastHand = "GAME"; /* player's card value trumps game's */
}
/* END whoWonTrump | whoWonTrump ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START GameFunctions method whoThrowsDownFirst | GameFunctions method whoThrowsDownFirst STARTS */
// this is only for the first match it will randomly pick how throws-down first
std::string GameFunctions::randomWhoLostLastHand()
{
  /* initialize random seed: */
  //srand((unsigned)time(NULL)); done in main()

  int i = rand() % 2;
  if (i == 0) // game throws down first
  {
    return  "PLAYER";
  }
  else
  {
    return  "GAME";  // player throws down first
  }
}
/* END GameFunctions method whoThrowsDownFirst | GameFunctions method whoThrowsDownFirst ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/



//*******************************************************************************
//*******************************************************************************
// BEGIN placeIcon placeIcon BEGINS *********************************************
void GameFunctions::placeIcon(int iPosition[], HANDLE hConsole)
{
  placement(iPosition[0], iPosition[1]);
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
  std::cout << char(35);
  // Reset to default colors (e.g., standard white on black)
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
  // std::cout << "This is default colored text" << std::endl;  
}// END placeIcon placeIcon ENDS *************************************************
//*******************************************************************************
//*******************************************************************************

  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START pickPlayersCard  | pickPlayersCard STARTS */
char GameFunctions::pickPlayersCard()
{
  char pc{ NULL }; /* player's card player picks to try to trump */
  int i{ 26 }; /* for indexing arrays   if pc is not valid input A...Z or a...z indexing 26 == -1, -1*/
  bool repick{ false };  // needed if player picks a card that has already been played 
  //  cout << endl;
    //cout << "Pick a card to trump or the ESC key to quite:";
  placement(nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN, nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_ROW);
  std::cout << "                     " << std::endl;
  std::cout << "                       ";
  placement(nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN, nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_ROW);
  std::cout << "Player pick\nnext card: ";
  pc = _getch(); /* _getch and _getwch functions read a single character from the console with OUT echo, _getche and _getwche are with echo */
  if ((int)pc == 27) // 27 decc is 'esc' key value
    return pc;

  do
  {
    repick = false;

    if ((int)pc >= 97 && (int)pc <= 122)
      i = (int)pc - 97;  /* sets 'i' up to be in index array range [0 25] */
    else
      if ((int)pc >= 65 && (int)pc <= 90)
        i = (int)pc - 65;
    if (get_iaPlayersCards(i, 0) == -1 || get_iaPlayersCards(i, 1) == -1)  //   if pc is not valid input A...Z or a...z indexing 26 == -1, -1*/
    {
      placement(nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN, nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_ROW);
      std::cout << RED << "Bad input try again." << RESET;  
      std::cout << "\nPlayer pick next card: ";
    
      pc = _getch(); /* _getch and _getwch functions read a single character from the console with OUT echo, _getche and _getwche are with echo */
      if ((int)pc == 27) // 27 decc is 'esc' key value
        return pc;

      repick = true;
      continue;  // The continue will jump execution to the ‘while’ assessment
    }

    set_iPlayersTCi(i);  // player’s trump card index number   the trump card’s index in the Player’s card array

    // to get here the card picked by the player is legitimate and can be moved in the Player’s Trump Card 
    _iaPlayersTrumpCard[0] = _iaPlayersCards[i][0]; 
    _iaPlayersTrumpCard[1] = _iaPlayersCards[i][1];
    // now the picked card must be removed from the cards the player has left
    _iaPlayersCards[i][0] = -1;
    _iaPlayersCards[i][1] = -1;

    // Display picked card
    placement(nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN, nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_ROW);
    std::cout << "                    ";
    std::cout << "\n                       ";
    placement(nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN, nsGF::PLAYER_PICK_NEXT_CARD_PROMPT_ROW);
    std::cout << "New Picked Card:\n";
    std::cout << GREEN << nsGF::cardNames[_iaPlayersTrumpCard[0]] << RESET << " of " << GREEN << std::setw(nsGF::DWS) << nsGF::cardSuits[_iaPlayersTrumpCard[1]] << RESET;   
  } while (repick && (int)pc != nsGF::ESC);

  // Set PLAYER’s Trump Card Value needed for GAME to pick its strategy.
  _iPlayersTrumpCardValue = _iaPlayersTrumpCard[0] + 1 + _iaPlayersTrumpCard[1] + 1;
  return pc;
}
/* END pickPlayersCard | pickPlayersCard ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START GameFunctions method displayCards  | GameFunctions method displayCards STARTS */
void GameFunctions::displayCards()
{

  int j{ 1 };   // for row length

  // START display game's cards *******************************************************
  placement(nsGF::FIELD_COL_ZERO_OFF_SET + nsGF::GAME_SPACE_LENGTH + nsGF::GAMES_CARDS_OFF_SET, nsGF::HEADER_CARDS_Y_DISPLAY_OFF_SET);

  std::cout << "Game's Cards." << std::endl;

  for (int i{ 0 }; i < nsGF::MGC; ++i)
  {
    placement(nsGF::FIELD_COL_ZERO_OFF_SET + nsGF::GAME_SPACE_LENGTH + nsGF::GAMES_CARDS_OFF_SET, i + nsGF::CARDS_Y_DISPLAY_OFF_SET);
    if (_iaGamesCards[i][0] == -1 || _iaGamesCards[i][1] == -1)
    {
      std::cout << "                    ";
      continue;
    }
    std::cout << nsGF::cardTitles[i] << "->";
    // cout << setw(DW) << _iaGamesCards[i][0] << "," << setw(DW) << _iaGamesCards[i][1];
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << std::setw(nsGF::DWC) << nsGF::cardNames[_iaGamesCards[i][0]] << " of " << std::setw(nsGF::DWS) << nsGF::cardSuits[_iaGamesCards[i][1]];
    //if ((j % nsGF::NCR) == 0) // for row length
    //  std::cout << std::endl;
    //else
    //  if (_iaGamesCards[i + 1][0] != -1 && i < nsGF::MPC - 1) std::cout << " | ";
    //++j;
  }

  // END display game's cards *********************************************************

  // START display player's cards *****************************************************

  placement(nsGF::CARDS_X_DISPLY_OFF_SET, nsGF::HEADER_CARDS_Y_DISPLAY_OFF_SET);  // move cursor to point on screen that data is wanted to be displayed at   
  std::cout << "Player's Cards." << std::endl;
  for (int i{ 0 }; i < nsGF::MAX_NUMBER_OF_PLAYERS_CARDS; ++i)
  {
    placement(nsGF::CARDS_X_DISPLY_OFF_SET, i + nsGF::CARDS_Y_DISPLAY_OFF_SET);  // move cursor to point on screen that data is wanted to be displayed at  
    if (_iaPlayersCards[i][0] == -1 || _iaPlayersCards[i][1] == -1)
    {
      std::cout << "                    ";
      continue;
    }
    std::cout << nsGF::cardTitles[i] << "->";
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << std::setw(nsGF::DWC) << nsGF::cardNames[_iaPlayersCards[i][0]] << " of " << std::setw(nsGF::DWS) << nsGF::cardSuits[_iaPlayersCards[i][1]];    
  }
   // END display player's cards ******************************************************
  return;
}
/* END GameFunctions method displayCards | GameFunctions method displayCards ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START GameFunctions method orderCards | GameFunctions method orderCards STARTS */
void GameFunctions::orderCards() /* To load the _iaGamesCards array in descending order of value  */
{
/******************************************************************************************************
When cardValue is used the cards are in a descending order of value Kings, Queens, … Eights, Sevens…, 
but they are not ordered by suit yet, so there can be four Queens like this:
Queen of Clubs
Queen of Diamonds
Queen of Spades
Queen of Hearts
followed by the Jack of Hearts
The Queens are a sub-group of all the cards Player or Game has been dealt.   
Now to order this sub-group by suit cardValue will be assigned Queen and will be used to test the next 
card to be ordered buy suit, if the value of that next card does not match cardValue then a ‘break’ is tripped 
to get out of the suit ordering ‘for’ loop.   The nested ‘for’ loops will make four passes max through every 
sub-group and cardValue will ‘break’ that nest of ‘for’ loops early if there is less than four members of a suit in a sub-group.
*******************************************************************************************************/
  int temp[1][2]{ 0, 0 };
  int cardVal{ 0 };  // cardVal  will keep the ordering in the suit   

  // GC and PC == 27, 0 - 25 hold card values, 26 == -1, -1 to stop run over.
  // GC - 2, PC - 2 in 'for' loops for i < so i + 1 will not sort 27th member the - 1, -1 over run stop value.

   // start of game cards ordering ****************************************************

   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   // * this code orders cards by card value decending card suit  K-H  K-D  K-C  K-S  Q-H  Q-D .......

    // order card value +++++++++++++++++++++++++++++++++++++  
  for (int j{ 0 }; j < nsGF::MAX_NUMBER_OF_GAME_CARDS - 2; ++j)
    for (int i{ 0 }; i < nsGF::MAX_NUMBER_OF_GAME_CARDS - 2; ++i)
    {
      if (_iaGamesCards[i + 1][0] > _iaGamesCards[i][0])
      {
        temp[0][0] = _iaGamesCards[i][0];
        temp[0][1] = _iaGamesCards[i][1];
        _iaGamesCards[i][0] = _iaGamesCards[i + 1][0];
        _iaGamesCards[i][1] = _iaGamesCards[i + 1][1];
        _iaGamesCards[i + 1][0] = temp[0][0];
        _iaGamesCards[i + 1][1] = temp[0][1];
      }
    }
  // order card value -----------------------------------

  // order card suit ++++++++++++++++++++++++++++++++++++
  for (int i{ 0 }; i <= nsGF::MAX_NUMBER_OF_GAME_CARDS; ++i)
  {
    cardVal = _iaGamesCards[i][0];   // cardVal  will keep the ordering in the suit   
    for (int j{ 0 }; j <= 3; ++j)
    {
      for (int k{ 0 }; k <= 3; ++k)
      {
        if (cardVal != _iaGamesCards[i + k + 1][0]) break;  // once 'k' has moved to next card value you break out of the suit ordering
        if (_iaGamesCards[i + k + 1][1] > _iaGamesCards[i + k][1])  // j is will cycle and k is set back to 0 to order the suit again. 
        { 
          // this is to stop over wright of other memory  
          if (i >= nsGF::MAX_NUMBER_OF_GAME_CARDS - 1) break;
          // when j == 3,  i will increment cardVal is reset 
          temp[0][0] = _iaGamesCards[i + k][0];
          temp[0][1] = _iaGamesCards[i + k][1];
          _iaGamesCards[i + k][0] = _iaGamesCards[i + k + 1][0];
          _iaGamesCards[i + k][1] = _iaGamesCards[i + k + 1][1];
          _iaGamesCards[i + k + 1][0] = temp[0][0];
          _iaGamesCards[i + k + 1][1] = temp[0][1];
        }
      }
    }
    // start of player's cards ordering ****************************************************

       //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       // * this code orders cards by card value decending card suit  K-H  K-D  K-C  K-S  Q-H  Q-D .......

        // order card value +++++++++++++++++++++++++++++++++++++  
    for (int j{ 0 }; j < nsGF::MAX_NUMBER_OF_PLAYERS_CARDS - 2; ++j)
      for (int i{ 0 }; i < nsGF::MAX_NUMBER_OF_PLAYERS_CARDS - 2; ++i)
      {
        if (_iaPlayersCards[i + 1][0] > _iaPlayersCards[i][0])
        {
          temp[0][0] = _iaPlayersCards[i][0];
          temp[0][1] = _iaPlayersCards[i][1];
          _iaPlayersCards[i][0] = _iaPlayersCards[i + 1][0];
          _iaPlayersCards[i][1] = _iaPlayersCards[i + 1][1];
          _iaPlayersCards[i + 1][0] = temp[0][0];
          _iaPlayersCards[i + 1][1] = temp[0][1];
        }
      }
    // order card value -----------------------------------

    // order card suit ++++++++++++++++++++++++++++++++++++
    for (int i{ 0 }; i <= nsGF::MAX_NUMBER_OF_PLAYERS_CARDS; ++i)
    {
      cardVal = _iaPlayersCards[i][0];   // cardVal  will keep the ordering in the suit   
      for (int j{ 0 }; j <= 3; ++j)
      {
        for (int k{ 0 }; k <= 3; ++k)
        {
          if (cardVal != _iaPlayersCards[i + k + 1][0]) break;  // once 'k' has moved to next card value you break out of the suit ordering
          if (_iaPlayersCards[i + k + 1][1] > _iaPlayersCards[i + k][1])  // j is will cycle and k is set back to 0 to order the suit again. 
          { 
            // this is to stop over wright of other memory  
            if (i >= nsGF::MAX_NUMBER_OF_PLAYERS_CARDS - 1) break;
            // when j == 3,  i will increment cardVal is reset 
            temp[0][0] = _iaPlayersCards[i + k][0];
            temp[0][1] = _iaPlayersCards[i + k][1];
            _iaPlayersCards[i + k][0] = _iaPlayersCards[i + k + 1][0];
            _iaPlayersCards[i + k][1] = _iaPlayersCards[i + k + 1][1];
            _iaPlayersCards[i + k + 1][0] = temp[0][0];
            _iaPlayersCards[i + k + 1][1] = temp[0][1];
          }
        }
      }
    } // end of  for (int i{ 0 }; i <= nsGF::MGC; ++i)
  }  
 }
  /* END GameFunctions method orderCards | GameFunctions method orderCards ENDS */
  /*-----------------------------------------------------------------------------------*/
  /*-----------------------------------------------------------------------------------*/


  // order card sute ------------------------------------
 //--------------------------------------------------------------------------------------------------



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START GameFunctions method dealCards | GameFunctions method dealCards STARTS */
void GameFunctions::dealCards()
{
  for (int i{ 0 }; i < nsGF::MPC - 1; ++i)  /* On initial deal game gets 26 cards, player get 26 */
  {
    _iaGamesCards[i][0] = _iaCardsShuffled[i][0];
    _iaGamesCards[i][1] = _iaCardsShuffled[i][1];

    _iaPlayersCards[i][0] = _iaCardsShuffled[i + nsGF::MPC - 1][0];  // i+PC This will deal the shuffeld cards from iaCardsShuffled[25] to [51]
    _iaPlayersCards[i][1] = _iaCardsShuffled[i + nsGF::MPC - 1][1];  // to playersCards[0] to [25]   
  }

  _iaGamesCards[nsGF::MGC - 1][0] = -1; _iaGamesCards[nsGF::MGC - 1][1] = -1; // load -1 at end of array to stop [GC+1] run over
  _iaPlayersCards[nsGF::MPC - 1][0] = -1;   _iaPlayersCards[nsGF::MPC - 1][1] = -1;  // when sorting or picking cards
  return;
}
/* END GameFunctions method dealCards | GameFunctions method dealCards ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* START GameFunctions method shuffleDeck | GameFunctions method shuffleDeck STARTS */
void GameFunctions::shuffleDeck()
{
  int iCardNumber{ 1 };
  int iCardSuit{ 1 };
  bool full{ false };

  /* to test for and not except duplicate cards */
  char iTestForDoubleCard[nsGF::NCD][nsGF::NCS]{ 'N' };

  /* used to increas the cardsShuffled array */
  int k{ 0 };

  for (int i{ 0 }; i < nsGF::NUMBER_OF_CARDS_IN_A_SUIT; ++i)
    for (int j{ 0 }; j < nsGF::NUMBER_OF_SUITS; ++j)
      iTestForDoubleCard[i][j] = 'N';

  /* initialize random seed: */
  srand((unsigned)time(NULL));

  do
  {
    /* generate random number between [0 , 12]: for card value*/
    iCardNumber = rand() % nsGF::NCS;
    /* generate random number between [0 , 3]: for card suit*/
    iCardSuit = rand() % nsGF::NS;

    if (iTestForDoubleCard[iCardNumber][iCardSuit] == 'N')
    {

      _iaCardsShuffled[k][0] = iCardNumber;  /* cardsDealt[CARD NUMBER][SUIT]  */
      _iaCardsShuffled[k][1] = iCardSuit;  /* cardsDealt[CARD NUMBER][SUIT]  */

      iTestForDoubleCard[iCardNumber][iCardSuit] = 'Y';
      ++k; // needed for cardsShuffled index value
    }
    for (int i{ 0 }; i < nsGF::NCS; ++i)
      for (int j{ 0 }; j < nsGF::NS; ++j)
        if (iTestForDoubleCard[i][j] == ('N'))  // if you get an 'N' then that card had not been added to the shuffled deck
        {
          full = false;
          i = nsGF::NCS;
          break;
        }
        else
        {
          full = true; // the 52 cards are randomized in cardsFhuffled array with no duplicates
        }

  } while (full != true);
  return;
};
/* END GameFunctions method shuffleDeck | Gamefunctions method shuffleDeck ENDS */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/


//*************************************************************************************************
//*************************************************************************************************
//***** START playersXyzInput METHOD
bool GameFunctions::playersXyzInput()
{
std::string _sInput{ '\0' }; // player's input is read in as a string of chars, so it can be tested to see if it is int only no one, 1.1 ....
//char _cC{ '\0' }; // used for cin to get player's char entered to continue
char _cQuit{ '\0' };
int _iTotalXYZ{ 0 }; //  holds |abs| of user's x,y, and z axis movement values will be tested to see if player is over/under card value
int _iIndex{ 0 };  // to keep tract of position in range-based for loop
int _iaXyz[3]{ {0}, {0}, {0} }; // local to hold and test player's input  if input good then will be moved to _iaPlayersXyz[3]
short cardValue{ 0 };  // substitute for player's card value
bool _bBadInput{ false };

  // This is the adjusted card value of the Player’s picked card to play remember all indexes start at 0 so Ace of Spades 
  // in the index will have [0](0) and [1](0) but in the game it’s value is two movement points as card value Ace == 1 and 
  // suit value Spades == 1. 
  cardValue = get_iaPlayersTrumpCard(0) + 1 + get_iaPlayersTrumpCard(1) + 1;

  clearInputFieldsWarnings(86);  // 86 stops method from clearing Warning fields that are blank 
  for (int i = 0; i < 3; ++i)  // to get player's movement requests
  { 
    placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW+i);
    std::cout << nsGF::_saEntryProms[i];  // x,y,z axis movement entre prompt   
    std::cin >> _sInput; // in put is taken as a string
   
    // range-based for loop to test player's input for x,y, and z axis movement
    for (unsigned char _cC : _sInput)  // Iterate through the string character by character
      if (std::isdigit(_cC) || (_iIndex == 0 && (_cC == '+' || _cC == '-')))
      {
        ++_iIndex;  // '-' and '+' must precede int value 
         continue;  // if first character is int, '+'', or '-' input is good so continue testing
      }
      else
      {	// if bad character is detected give warning and prompt to reenter or ESC to quit
        placement(nsGF::BAD_INPUT_WARNING_COLUMN, nsGF::BAD_INPUT_WARNING_ROW);
        std::cout << BOLDRED;// "\033[1m\033[31m"; // forground bold red
        std::cout << nsGF::_saEntryErrorProms[1];        
        std::cout << RESET; // "\033[0m"; // reset to default forground background collor
        _cQuit = (_getch());
        if ((int)_cQuit == nsGF::ESC)  /* 27 == esc key code */
          return true;  // return 'true' player wants to quite
        _bBadInput = true; // Enter any-other key and PLAYER wants to continue 
        break; // break out of the 'for' on _sIndex
      }

    if (_bBadInput)
    {
      _bBadInput = false;
      // clear input fields and warnings  
      clearInputFieldsWarnings(1);
      i = -1;  // setting 'i' to -1 will force for loop reset to 0 
      continue; // well send execution back to for loop on 'i'==-1 and 'for' will increment 'i' to 0
    }
    _iaXyz[i] = std::stoi(_sInput);  // to get to here input is good so save
    _iTotalXYZ += abs(_iaXyz[i]);    // add abs of input to test if player is under or over card value
    _iIndex = 0; // reset the index used to find possition in range-based for loop testting the input string 

    if (_iTotalXYZ > cardValue)  // if over card value ERROR and prompt player to continue or quit with ESC
    {
      placement(nsGF::BAD_INPUT_WARNING_COLUMN, nsGF::BAD_INPUT_WARNING_ROW);
      std::cout << BOLDRED; // "\033[1m\033[31m"; // forground bold red
      std::cout << nsGF::_saEntryErrorProms[i + 2];
      std::cout << RESET; // "\033[0m"; // reset to default forground background collor
      _cQuit=(_getch());
      if((int)_cQuit == nsGF::ESC)  /* 27 == esc key code */
      return true;  // return 'true' player wants to quite
    
      _bBadInput = true;
    }
    if (_bBadInput)
    {
      _bBadInput = false;
      _iTotalXYZ = 0;
      // clear input fields and warnings
      clearInputFieldsWarnings(i+2);
      i = -1;     // setting 'i' to -1 will force for loop reset to 0 
      continue;   // well send execution back to for loop on 'i' and increment 'i' to 0
    }

    if (_iTotalXYZ < cardValue && i == 2) // if under card value ERROR
    {
      placement(nsGF::BAD_INPUT_WARNING_COLUMN, nsGF::BAD_INPUT_WARNING_ROW);
      std::cout << BOLDRED; // "\033[1m\033[31m"; // forground bold red
      std::cout << nsGF::_saEntryErrorProms[i + 3];
      std::cout << RESET; // "\033[0m"; // reset to default forground background collor
      _cQuit = (_getch());
      if ((int)_cQuit == nsGF::ESC)  /* 27 == esc key code */
        return true;  // return 'true' player wants to quite
      _bBadInput = true;
    }
    if (_bBadInput)
    {
      _bBadInput = false;
      _iTotalXYZ = 0;
      // clear input fields warnings
      clearInputFieldsWarnings(i+3);
      i = -1;     // setting 'i' to -1 will force for loop reset to 0 
      continue;   // well send execution back to for loop on 'i' and increment 'i' to 0
    }

    if (_iTotalXYZ == cardValue) // if x or x+y == card value process movement  x == card value or x+y == card value so y+z == 0 or z == 0
    {
      if (_iaXyz[1] == 0 || _iaXyz[2] == 0)
        i = 3;
    }
    //-------------------------------------------------------------------------------------------------------------------------
  } // END OF FOR loop on playersXyz load

  // good numbers entered load them into _iaPlayersXyz[3]
  for (int i = 0; i < 3; ++i)
    set_iaPlayersRequestedMove(i, 0, _iaXyz[i]);

  return false;  // player wants to continue
 
return false;  // player wants to continue
}  
//***** END testPlayXyzInpu METHOD 
//*************************************************************************************************
//*************************************************************************************************/


//*************************************************************************************************
//*************************************************************************************************
//***** START testPlayersMovementRequestInBounds METHOD
// 
// The PLAYER is constrained to the ‘game space’  the current dimension are
// GSL GAME_SPACE_LENGTH    GSW GAME_SPACE_WIDTH    GSH GAME_SPACE_HIGHT  If the PLAYER enter a movement request that will 
// put them out of the ‘game space’ then the PLAYERS movement request is “clipped” to keep the PLAYER in the ‘game space’
// QED : PLAYER is at X == GAME_SPACE_LENGTH – 5 ‘game space units’, the PLAYER enters a movement request of X += 10, 
// this would put the PLAYER out of the ‘game space’ by 5 ‘game space units’, so instead of warning the PLAYER of this 
// the ‘game’ will simply clip, the X axis movement request by 5 gsu(‘game space units’), giving the PLAYER an X axis 
// position of X == GAME_SPACE_LENGTH.
// This is also enforced for the Y, and Z axis.

bool GameFunctions::testPlayersMovementRequestInBounds()
{
  for (int i{ 0 }; i<nsGF::NUMBER_OF_DIMENSIONS; ++i)  // Save old position need it to refresh ‘game space’ display 
    _iaPlayersLastPosition[i] = _iaPlayersCurrentPosition[i];

  int _LiaXyz[3]{ { _iaPlayersCurrentPosition[0] + _iaPlayersRequestedMove[0][0]},
                 {  _iaPlayersCurrentPosition[1] + _iaPlayersRequestedMove[1][0]},
                 {  _iaPlayersCurrentPosition[2] + _iaPlayersRequestedMove[2][0]}};

  int _LiaGameSpaceDimentions[nsGF::NUMBER_OF_DIMENSIONS]{ {nsGF::GSL},{nsGF::GSW}, {nsGF::GSH} };
  int _LiTempPcP{ -1 };   // local temp PLAYERS current position


  for (int i{ 0 }; i < sizeof(_LiaXyz) / sizeof(int); ++i)
  {
    if (_LiaXyz[i] < 0)
    {
     _LiTempPcP = _iaPlayersCurrentPosition[i];
     _iaPlayersCurrentPosition[i] = 0; // The [n, m]  n == to requested position to move to   when that requested position is tested if it is found to be out of bounds on any axis   that axis request will be modified to keep the Player’s token in bounds and m == will be   to 0 to show that modification has taken place 
     _iaPlayersRequestedMove[i][1] = 0;
     _iaPlayersRequestedMove[i][0] = _LiTempPcP *= -1;
    }
    else if (_LiaXyz[i] >= _iaGameSpaceDimentions[i])
    {
      _LiTempPcP = _iaPlayersCurrentPosition[i];
      _iaPlayersCurrentPosition[i] = _iaGameSpaceDimentions[i] - 1; // The [n, m]  n == to requested position to move to   when that requested position is tested if it is found to be out of bounds on any axis   that axis request will be modified to keep the Player’s token in bounds and m == will be set to 0 to show that modification has taken place 
      _iaPlayersRequestedMove[i][1]= 0;
     // (i, 0) == value of X,Y,Z  (i, 1) == 1 true good move,  == 0 PLAYER's move request had to be modified to keep PLAYER in 'game space' boundes  
      _iaPlayersRequestedMove[i][0] = _iaGameSpaceDimentions[i] - _LiTempPcP;
    }
    else {      
      _iaPlayersCurrentPosition[i] = _iaPlayersCurrentPosition[i] + _iaPlayersRequestedMove[i][0];
      _iaPlayersRequestedMove[i][1] = TRUE;  // PLAYER’s requested move on the ‘i’ axis is legitimate
    }
  }  
  return true; // player wants to continue  
}
//***** END testPlayersMovementRequestInBounds METHOD
//*************************************************************************************************
//*************************************************************************************************

//**********************************************************************************************
//***** START testForGoalPossession METHOD STARTS **********************************************
// After every move, kickout, or bump event must check and update goal possession state of both GAME and PLAYER.
void GameFunctions::testSetGoalPossession(std::string icon)
{
  bool _LbPlayersPS{ false };  // PLAYER’s possession state STATIC 
  bool _LbGamesPS{ false }; // GAME’s possession state STATIC 
  bool _LbPFirstTime{ false };
  bool _LbGamesFirstTime{ false };
  int _LiaGoalsP[3][2]{ {_iaGoalsCurrentPerimeter[0][0], _iaGoalsCurrentPerimeter[0][1]}, {_iaGoalsCurrentPerimeter[1][0], _iaGoalsCurrentPerimeter[1][1]},{_iaGoalsCurrentPerimeter[2][0], _iaGoalsCurrentPerimeter[2][1]} };
  int _LiaGoalsLastP[3][2]{ {_iaGoalsLastPerimeter[0][0], _iaGoalsLastPerimeter[0][1]}, {_iaGoalsLastPerimeter[1][0], _iaGoalsLastPerimeter[1][1]}, {_iaGoalsLastPerimeter[0][0], _iaGoalsLastPerimeter[0][1]} };
  int _LiaPp[3]{ _iaPlayersCurrentPosition[0], _iaPlayersCurrentPosition[1], _iaPlayersCurrentPosition[2] };
  int _LiaPLastP[3]{ _iaPlayersLastPosition[0], _iaPlayersLastPosition[1], _iaPlayersLastPosition[2]};
  int _LiaGamesP[3]{ _iaGamesCurrentPosition[0], _iaGamesCurrentPosition[1], _iaGamesCurrentPosition[2] };
  int _LiaGamesLastP[3]{ _iaGamesLastPosition[0], _iaGamesLastPosition[1], _iaGamesLastPosition[2] };


  if (icon == "PLAYER")
  {
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)   // Test if PLAYER is in GOAL’s perimeter
    {
      if (_LiaPp[i] >= _LiaGoalsP[i][0] && _LiaPp[i] <= _LiaGoalsP[i][1])
        _LbPlayersPS = true;   // If PLAYER is in the GOAL’s perimeter then _LbPS will stay true.  This will set up PLAYER for a possession state increase
      else
      {
        _LbPlayersPS = false;  // If one or more of the PLAYER’s X,Y, or Z position is out side of the GOAL’s  
        _baPlayersPossessionState[0] = false;  // perimeter the _LbPS is set to ‘false’ and both PLAYER’s possession states are set to ‘false’.
        _baPlayersPossessionState[1] = false;
        break;
      }
    }
    if (_LbPlayersPS && !_baPlayersPossessionState[0])
      _baPlayersPossessionState[0] = true;
    else  //  Push up PLAYER’s possession state.        
      if (_baPlayersPossessionState[0] == true )
        _baPlayersPossessionState[1] = true;
     
        
  } // end 'if' on PLAYER ---------------------------------------------------------------------------------------------

  else if (icon == "GAME")     // Repeat above but for GAME ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  {
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)   // Test if PLAYER is in GOAL’s perimeter
    {
      if (_LiaGamesP[i] >= _LiaGoalsP[i][0] && _LiaGamesP[i] <= _LiaGoalsP[i][1])
        _LbPlayersPS = true;
      else
      {
        _LbPlayersPS = false;
        _baGamesPossessionState[0] = false;
        _baGamesPossessionState[1] = false;
        break;
      }
    }
    if (_LbPlayersPS)
      if (_baGamesPossessionState[0] == true)
        _baGamesPossessionState[1] = true;
      else
        _baGamesPossessionState[0] = true;
  } // end else if (icon++"GAME")---------------------------------------------------------------------------------------


  // GOAL's possession state now use it to stop GOAL from moving or size change.  
  _baGoalsPossessionState[0] = _baGoalsPossessionState[1] = false;  // flush out out states of possession

  if (_baPlayersPossessionState[0] || _baGamesPossessionState[0])
    _baGoalsPossessionState[0] = true;

  if (_baPlayersPossessionState[1] || _baGamesPossessionState[1])
     _baGoalsPossessionState[1] = true; 

}
//***** END testPlayersMovementRequestInBounds METHOD ENDS **************************************
//***********************************************************************************************


//**********************************************************************************************/
//**********************************************************************************************
//***** START setUpWindow METHOD
 int GameFunctions::setUpWindow()
{
  HWND hWnd = GetConsoleWindow();
  if (hWnd == NULL) 
    std::cerr << "Could not get console window handle." << std::endl;

  // Remove the window's title bar and borders by changing the style to WS_POPUP
  // DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
  // SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW | WS_POPUP);

    // Get the screen dimensions
    RECT fullscreenRect;
    // Use the primary monitor's dimensions
    SystemParametersInfo(SPI_GETWORKAREA, 0, &fullscreenRect, 0);

    // Resize and position the window to cover the entire screen
    SetWindowPos(hWnd, HWND_TOP,
      fullscreenRect.left, fullscreenRect.top,
      fullscreenRect.right - fullscreenRect.left, fullscreenRect.bottom - fullscreenRect.top,
      SWP_NOZORDER | SWP_FRAMECHANGED);


    // Maximize the window (optional, but ensures it fills the space correctly)
    ShowWindow(hWnd, SW_MAXIMIZE);
    
    /*************** hold on to this may need it later
    std::cout << "Window is now in full-screen mode. Press Enter to exit." << std::endl;
    std::cin.get();

    // Restore the window (optional cleanup)
    ShowWindow(hWnd, SW_RESTORE);
    SetWindowLong(hWnd, GWL_STYLE, dwStyle);
    SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOZORDER | SWP_FRAMECHANGED); // Restore original size/pos (example)
    *******************/
 
  return 1;
}
// ***** END OF setUpWindow METHOD
//**********************************************************************************************/
//**********************************************************************************************/

 //*********************************************************************************************
 //***** START setFontSize METHOD setFontSize STARTS *******************************************
 void GameFunctions::setFontSize(int a, int b)  // has default arguments in definition 
 {
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   if (hStdOut == NULL) 
     std::cerr << "Could not get console window handle." << std::endl;

   PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
     lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);   
     GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);   
     lpConsoleCurrentFontEx->dwFontSize.X = a;
     lpConsoleCurrentFontEx->dwFontSize.Y = b;   
     SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);   
}
 //***** END setFontSize METHOD setFontSize ENDS ***********************************************
 //*********************************************************************************************

 //*********************************************************************************************
 //***** START clearInputFieldsWarnings METHOD clearInputFieldsWarnings STARTS *****************
 void GameFunctions::clearInputFieldsWarnings(int index)
 {   
   for (int i{0}; i <  nsGF::NUMBER_OF_DIMENSIONS; ++i)  // This will clear out any bad entries below the Z entry field like
   {                                                         // Z:
                                                             // 0
     placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN , nsGF::PLAYER_X_POSITION_PROMPT_ROW + i);  // + nsGF::_saEntryProms[i].size()
     std::print("                          ");
     placement(nsGF::PLAYER_X_POSITION_PROMPT_COLUMN, nsGF::PLAYER_X_POSITION_PROMPT_ROW + i + nsGF::NUMBER_OF_DIMENSIONS);
     std::print("       "); // If PLAYER hit ‘Enter’ before entering a digit, input field could look like this
   }                        // Enter X axis movement:
   if (index == 86)         // 5 
     return;                // Enter Y axis movement:    // that is why the ROW (Y axis) if set to nsGF::PLAYER_X_POSITION_PROMPT_ROW + i + nsGF::NUMBER_OF_DIMENSIONS 
   placement(nsGF::BAD_INPUT_WARNING_COLUMN, nsGF::BAD_INPUT_WARNING_ROW);
   for (char c : nsGF::_saEntryErrorProms[index])
   {   
   std::print(" ");
   if (c == '\n')
     std::cout<<std::endl;
   }
 }
 //***** END clearInputFieldsWarnings METHOD clearInputFieldsWarnings ENDS ********************
//*********************************************************************************************

//*********************************************************************************************
//***** START goalPossessionThrowDownCalculations STARTS **************************************************
 
// When PLAYER and GAME are both in the GOAL's perimeter then no mater who has what possession state a throw down is mandated.  
// To win the throw-down the contestant must both pick a card that not only has a higher value than the other contestant's 
// card pick, but a movement value that the contestant can move along the X, and or Y, and or Z axis without exiting the 
// GOAL’s perimeter.  Winner gets both first and second stage possession, and the loser gets ejected their highest card 
// value plus two ‘game space units’. 
// The contestant has the option of not entering the throw-down and abandoning the GOAL for a better position to reenter on a subsequent move. 

void GameFunctions::goalPossessionThrowDownCalculations()
 {  
  // OODA loop GAME need to find it longest path that it can move in the GOAL from its present position  
  // OODA GAME needs to know PLAYER’s longest path inside the GOAL from PLAYER's present position  
 
  // Get the longest distance both PLAYER and GAME can move inside the GOAL both XYZ axis movement and total movement
  for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
  {
    if (std::abs(_iaGoalsCurrentPerimeter[i][0] - _iaGamesCurrentPosition[i]) <= _iaGoalsCurrentPerimeter[i][1] - _iaGamesCurrentPosition[i])
      _iaGamesLongestXYZPath[i] = _iaGoalsCurrentPerimeter[i][1] - _iaGamesCurrentPosition[i];
    else
      _iaGamesLongestXYZPath[i] = _iaGoalsCurrentPerimeter[i][0] - _iaGamesCurrentPosition[i];
    if (std::abs(_iaGoalsCurrentPerimeter[i][0] - _iaPlayersCurrentPosition[i]) <= _iaGoalsCurrentPerimeter[i][1] - _iaPlayersCurrentPosition[i])
      _iaPlayersLongestXYZPath[i] = _iaGoalsCurrentPerimeter[i][1] - _iaPlayersCurrentPosition[i];
    else
      _iaPlayersLongestXYZPath[i] = _iaGoalsCurrentPerimeter[i][0] - _iaPlayersCurrentPosition[i];

    _iGamesLongestPathTotal += std::abs(_iaGamesLongestXYZPath[i]);
    _iPlayersLongestPathTotal += std::abs(_iaPlayersLongestXYZPath[i]);
  }
  // Now use that data to find if GAME’s _LiGamesLongestPathTotal is greater than PLAYER’s _LiPlayersLongestPathTotal if it is then fine one of GAME’s cards
  // with a value just greater than _LiPlayersLongestPathTotal, but lest than GAME’s _LiGamesLongestPathTotal play that card and done.
 
  return;
 }
//***** END goalPossessionThrowDownCalculations ENDS ******************************************************
//*********************************************************************************************