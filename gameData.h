

#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>			/* for system call to cls */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>      /* for cout format */
#include <math.h>
#include <ctype.h>      /* for std::isblank */
#include <random>
#include <chrono>
#include <cstdlib>      /* Required for system() */
#include <initializer_list>
#include <cctype>
#include <print>        /* for the c++ 23 print*/




//using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// START OF namespace nsGF
namespace nsGF {
 // CARD RELATED CONSTEXPR..............................................................................
  constexpr auto NUMBER_OF_CARDS_IN_DECK = 52;
#define NCD NUMBER_OF_CARDS_IN_DECK  /* NUMBER_OF_CARDS_IN_DECK */
  constexpr auto NUMBER_OF_CARDS_IN_A_SUIT = 13;
#define NCS NUMBER_OF_CARDS_IN_A_SUIT  /* NUMBER_OF_CARDS_IN_A_SUIT */
  constexpr auto NUMBER_OF_SUITS = 4;
#define NS NUMBER_OF_SUITS /* NUMBER_OF_SUITS */
  constexpr auto MAX_NUMBER_OF_PLAYERS_CARDS = 27;  /* MAX_NUMBER_OF_PLAERS_CARDS max number of cards a play can have, the more a player winds the more cards they get */
#define MPC MAX_NUMBER_OF_PLAYERS_CARDS 	/* 26 cards 0-25, 26 will be loaded with -1, -1 those -1 will stop over run in sort and function */
  constexpr auto MAX_NUMBER_OF_GAME_CARDS = 27;
#define MGC MAX_NUMBER_OF_GAME_CARDS /* game starts with game having 26 of the 52 cards */
  constexpr auto ESC = 27; /* esc dec value used to end game*/
  constexpr auto ENTER = 13; /* used to continue game*/
  constexpr auto UP_ARROW = 24;
  constexpr auto DOWN_ARROW = 25;
  constexpr auto NUMBER_OF_CARDS_IN_ROW = 5; /* the number of cards displayed in one row */
#define NCR NUMBER_OF_CARDS_IN_ROW
  constexpr auto DISPLAY_WIDTH_SUIT = 8;  /* for cout setw() */
#define DWS DISPLAY_WIDTH_SUIT
  constexpr auto DISPLAY_WIDTH_CARD = 5;		 /* for cout setw() */
#define DWC DISPLAY_WIDTH_CARD 
  constexpr short CARDS_X_DISPLY_OFF_SET = 0;  // x asis off set  how far along the x axis before cout
#define CXDOS CARDS_X_DISPLY_OFF_SET
  constexpr short HEADER_CARDS_Y_DISPLAY_OFF_SET = 1; // y axis off set for card column title 'Game's Cards' 'Player's Card's'
#define HCYDOS HEADER_CARDS_Y_DISPLAY_OFF_SET
  constexpr short CARDS_Y_DISPLAY_OFF_SET = 2; // y axis off set  how far down the y axis before card values and suits are cout 
#define CYDOS CARDS_Y_DISPLAY_OFF_SET


 // GOAL RELATED CONSTEXPR..............................................................................
  constexpr auto GOAL_LENGTH_LOW = 7;
#define GLL GOAL_LENGTH_LOW
  constexpr auto GOAL_LENGTH_HIGH = 15;
#define GLH GOAL_LENGTH_HIGH
  constexpr auto LINE_LENGTH = 100;  // length of navigation line
#define LL  LINE_LENGTH
  constexpr auto NUMBER_OF_DIMENSIONS = 3; // for now 3D may go 4d later
#define NOD NUMBER_OF_DIMENSIONS
  constexpr short GOALS_CENTER_POSITION_HEADER_COLUMN = 26;
#define GCPHC GOALS_CENTER_POSITION_HEADER_COLUMN 
  constexpr short GOALS_CENTER_POSITION_HEADER_ROW = 45;
#define GCPHR GOALS_CENTER_POSITION_HEADER_ROW
  constexpr short GOALS_CENTER_POSITION_DATA_COLUMN = 52;
#define GCPDC GOALS_CENTER_POSITION_DATA_COLUMN      
  constexpr short GOALS_CENTER_POSITION_DATA_ROW = 45;
#define GCPDR GOALS_CENTER_POSITION_DATA_ROW
  constexpr short GOALS_DIMENSIONS_DATA_COLUMN = 100;
#define GDDC GOALS_DIMENSIONS_DATA_COLUMN 
  constexpr short GOALS_DIMENSIONS_DATA_ROW = 45;
#define GCPDR GOALS_DIMENSIONS_DATA_ROW

  constexpr short GOALS_LENTH_WIDTH_HIEGHT_HEADER_COLUMN = 26;
#define GLWHDC GOALS_LENTH_WIDTH_HIEGHT_HEADER_COLUMN
  constexpr short GOALS_LENTH_WIDTH_HIEGHT_HEADER_ROW = 46;
#define GLWHDR GOALS_LENTH_WIDTH_HIEGHT_HEADER_ROW

  constexpr short GOALS_LENTH_WIDTH_HIEGHT_DATA_COLUMN = 40;
#define GLWHDC GOALS_LENTH_WIDTH_HIEGHT_DATA_COLUMN
  constexpr short GOALS_LENTH_WIDTH_HIEGHT_DATA_ROW = 46;
#define GLWHDR GOALS_LENTH_WIDTH_HIEGHT_DATA_ROW

  constexpr short GOAL_IN_CONTENTION_HEADER_COLUMN = 0;
#define GICHC GOAL_IN_CONTENTION_HEADER_COLUMN
  constexpr short GOAL_IN_CONTENTION_HEADER_ROW = 47;
#define GICHR GOAL_IN_CONTENTION_HEADER_ROW


  // FIELD/'game space' RELATED CONSTEXPR...............................................................
  constexpr short START_ROW = 0;
#define SR START_ROW
  constexpr short START_COL = 0;
#define ST START_COL
  constexpr short FIELD_ROW_ZERO_OFF_SET = 2;  // this is (0,0) field position, all heading positions should be bast off of this
#define FRZOS FIELD_ROW_ZERO_OFF_SET
  constexpr short FIELD_COL_ZERO_OFF_SET = 26;
#define FCZOS FIELD_COL_ZERO_OFF_SET
  constexpr short ROW_HEADER_OFF_SET = 9;
#define RHOS ROW_HEADER_OFF_SET
  constexpr auto GAME_SPACE_LENGTH = 120;  // length of X axis 
#define GSL GAME_SPACE_LENGTH
  constexpr auto GAME_SPACE_WIDTH = 40;    // Width of Y axis
#define GSW GAME_SPACE_WIDTH
  constexpr auto GAME_SPACE_HIGHT = 100;   // Hight of Z axis
#define GSH GAME_SPACE_HIGHT
  constexpr short WIDTH_COL = 10;
#define WC WIDTH_COL
  constexpr short WIDTH_FIELD = 100;
#define WF WIDTH_FIELD
  constexpr short HIGHT_FIELD = 30;
#define HF HIGHT_FIELD
  constexpr short WIDTH_DIGIT = 2;
#define WD WIDTH_DIGIT
  constexpr short ICON_COLUMNE_START_OFF_SET = 27;
#define ICSOS ICON_COLUMNE_START_OFF_SET
  constexpr short ICON_ROW_START_OFF_SET = 3;
#define IRSOS ICON_ROW_START_OFF_SET 



  // PLAYER RELATED CONSTEXPR...........................................................................
  constexpr short PLAYERS_LAST_CARD_PLAYED_HEADER_COLUMN = 0;
#define PLCPH PLAYERS_LAST_CARD_PLAYED_HEADER_COLUMN 
  constexpr short PLAYERS_LAST_CARD_PLAYED_HEADER_ROW = 29;
#define PLCPH PLAYERS_LAST_CARD_PLAYED_HEADER_ROW
  constexpr short PLAYERS_POSITION_HEADER_COLUMN = 0;
#define PPHC  PLAYERS_POSITION_HEADER_COLUMN
  constexpr short PLAYERS_POSITION_HEADER_ROW = 33;
#define PPDR PLAYERS_POSITION_HEADER_ROW
  constexpr short PLAYERS_POSITION_DATA_COLUMN = 19;
#define PPDC PLAYERS_POSITION_DATA_COLUMN
  constexpr short PLAYERS_POSITION_DATA_ROW = 33;
#define PPDR PLAYERS_POSITION_DATA_ROW
  constexpr short PLAYERS_GOAL_POSSESSION_STATE_HEADER_COLUMN = 0;
#define PGPSHC PLAYERS_GOAL_POSSESSION_STATE_HEADER_COLUMN
  constexpr short PLAYERS_GOAL_POSSESSION_STATE_HEADER_ROW = 37;
#define PGPSHR PLAYERS_GOAL_POSSESSION_STATE_HEADER_ROW
  constexpr short PLAYERS_GOAL_POSSESSION_STATE_DATA_COLUMN = 11;
#define PGPSHC PLAYERS_GOAL_POSSESSION_STATE_DATA_COLUMN
  constexpr short PLAYERS_GOAL_POSSESSION_STATE_DATA_ROW = 39;
#define PGPSHR PLAYERS_GOAL_POSSESSION_STATE_DATA_ROW
  constexpr short PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN = 0;
#define PPNCPC PLAYER_PICK_NEXT_CARD_PROMPT_COLUMN
  constexpr short PLAYER_PICK_NEXT_CARD_PROMPT_ROW = 42;
#define PPNCPR PLAYER_PICK_NEXT_CARD_PROMPT_ROW
  constexpr short PLAYER_X_POSITION_PROMPT_COLUMN = 0;
#define PXPPC PLAYER_X_POSITION_PROMPT_COLUMN 
  constexpr short PLAYER_X_POSITION_PROMPT_ROW = 44;
#define PXPPR PLAYER_X_POSITION_PROMPT_ROW
  constexpr short BAD_INPUT_WARNING_COLUMN = 0;
#define BIWC BAD_INPUT_WARNING_COLUMN 
  constexpr short BAD_INPUT_WARNING_ROW = 48;
#define BIWR BAD_INPUT_WARNING_ROW



  // GAME'S RELATED CONSTEXPR...........................................................................
  constexpr short GAMES_LAST_CARD_PLAYED_HEADER_COLUMN = 152;
#define PLCPH GAMES_LAST_CARD_PLAYED_HEADER_COLUMN 
  constexpr short GAMES_LAST_CARD_PLAYED_HEADER_ROW = 29;
#define PLCPH GAMES_LAST_CARD_PLAYED_HEADER_ROW
  constexpr short GAMES_POSITION_HEADER_COLUMN = 152;
#define PPHC  GAMES_POSITION_HEADER_COLUMN
  constexpr short GAMES_POSITION_HEADER_ROW = 33;
#define PPDR GAMES_POSITION_HEADER_ROW
  constexpr short GAMES_POSITION_DATA_COLUMN = 169;
#define PPDC GAMES_POSITION_DATA_COLUMN
  constexpr short GAMES_POSITION_DATA_ROW = 33;
#define PPDR GAMES_POSITION_DATA_ROW
  constexpr short GAMES_GOAL_POSSESSION_STATE_HEADER_COLUMN = 152;
#define GGPSHC GAMES_GOAL_POSSESSION_STATE_HEADER_COLUMN
  constexpr short GAMES_GOAL_POSSESSION_STATE_HEADER_ROW = 37;
#define GGPSHR GAMES_GOAL_POSSESSION_STATE_HEADER_ROW
  constexpr short GAMES_GOAL_POSSESSION_STATE_DATA_COLUMN = 163;
#define GGPSHC GAMES_GOAL_POSSESSION_STATE_DATA_COLUMN
  constexpr short GAMES_GOAL_POSSESSION_STATE_DATA_ROW = 39;
#define GGPSHR GAMES_GOAL_POSSESSION_STATE_DATA_ROW
  constexpr short GAMES_CARDS_OFF_SET = 6;
#define GCOS GAMES_CARDS_OFF_SET

// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
// text color change....
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[370m"
#define BOLDRED "\033[1m\033[31m" // Example of combining attributes
#define YELLOW_ON_BLUE "\033[33;2;44;2m" // Yellow on Blue
#define GREEN_ON_BLACK "\033[32;2;30;2m"
#define RED_ON_BLACK "\033[31;1;43;1m"
#define ORANGE  "\033[33;1;31;1m"  // GOAL's captured collor 
#define LIME  "\033[112m" // GOAL's free collor
#define RED_ON_BLUE "\033[31;1;34;1m" 
#define HIRED "\33[1;91m"  // High Intensty


  /* CN == Card Names ex:  Ace One Two .... King */
  static  enum CN { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEN, KING, NO_CARD } c_n;
  /* CS == Card Suit ex: Spades, Clubs, Diamonds, Hearts */
  static  enum CS { SPADES, CLUBS, DIAMONDS, HEARTS, NO_SUIT } c_s;





  /* NO CARD, NO SUIT is used to show cards that have been removed from play  */
  static const std::string cardNames[14] = { "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "NO CARD" };
  static const std::string cardSuits[5] = { "SPADES", "CLUBS", "DIAMONDS", "HEARTS", "NO SUIT" };
  /* used as card title like B->2|2 == "two of dimonds" this way the player will know that entering 'b' will pick 2|2, */
  /* player's cards will be titled as */
  /* the letters alown will be used to pick a game's card to try to trump */
  /* game's cards will be displayed as Game's cards -> A, B, C,. . . . */
  /* player's cards will be title as Player's cards A->0|2, B->2|1, C->2|6, . . .*/
  static const char cardTitles[26] = { 'A', 'B', 'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',  'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z' };

  static const std::string bust[2] = { "Game", "Player" };


  static const std::string greetingString = "Top Trumps 3D is an experiment in three dimensional game design.\n\
It started out as a simple top trumps card game, one player vs. the GAME.\n\
A visual aid was added, the “Abstract Navigation Line” (ANL), to help the player have a \n\
quick visual reference to the total value of the Player's and Game's cards that were left for each of them to play.\n\
Now the game has evolved to a three dimensional strategy game.   To win the game the Player must have possession of\n\
the Goal when the last card is played.    At match start a deck of standard playing cards is evenly dealt between\n\
Player and Game (26 cards each).\n\n\
The Goal is randomly positioned at some point in the \"game space\", the \"game space\"  is a three dimensional area that \n\
the Player and Game must move through in order to take possession of the Goal.   The \"game space\"  has length, width, \n\
and height, and is divided up into evenly sized game spaces units.\n\
The Player and the Game both move through the three dimensional \"game space\" using the value of their cards.  \n\
QED;  if P (player) is at Xn and wants to move to Xn+6 and \n\
that player has the FIVE of SPADES card the player will pick that card to play.\n\
The FIVE of SPADES has a total movement value of six(the card's face value of 5 plus \n\
its suit value of 1 for a total of 6).  Playing that card will give the Player six movement points, each movement\n\
point can be used to move the player from one game space unit to the next adjacent game space unit.   Think of the \"game space\" as a checker\n\
board, then make that checker board three dimensional, each square on the board is transformed into a cube,  \n\
then stack one three dimensional checker board on top of another, all the checker boards stacked together make up the \"game space\", \n\
each cube in the stack is the same size as all the others and it takes one movement point to move from one cube (one game space unit) to the next.\n\
\n\
Card face values Ace = 1, numbered card value = that number,\n\
face cards Jack = 11, Queen = 12, King = 13. \n\
Suit values Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. \n\
QED: 8 of Diamonds == 8 + 3 == 11.\n\
When the Player picks a card to play the player gats that card's total value in movement points.\n\
Like above the 8 of Diamonds has a total of 11 movement points, those points can be used to move\n\
in any combination of directions along the three axis of movement in the \"game space\".\n\
The three axis are;  X (right/left along the length of the \"game space\"), Y (up/down the width of the \"game space\")\n\
and Z(rise/lower through the height of the \"game space\").\n\
QED:  The Player plays the 8 of Diamonds, and get credited with 11 movement points.\n\
The player is then presented with these input fields;\n\n\
Enter movement values for X:   |  Y:    |    Z:    The player can use the movement points in any combination;\n\
all in positive X and move acrose the \"game space\" 11 game space units, or  4 in X, 4 in Y, and 3 in Z, which\n\
would move the Player acrose the length of the \"game space\" 4 units, a down the width of the \"game space\" 4 units,\n\
and up the hight of the \"game space\" 3 units.\n\
To move in the opposite direction to the left on the X axis, up on the Y axis, and to lower on the Z axis\n\
simply enter the '-' sign before a number value.\n\n\
A Player must use all the movement points from the card played, if 5 of Hearts is played then 9 movement points are awarded.\n\
All 9 points must be used or \"BAD INPUT\" is displayed and the Player is prompted to reenter their X, Y, and Z selections.\n\
The same will happen if too meny movement points are entered.    If an entry field is left blank a zero entry is assumed.\n\
\n\
QED: Play 5 Hearts, get 9 movement points.\n\
Enter movement values for X:  3 | Y: 3 |  Z:  3   \"good input, move: right 3, down 3, rise 3\"\n\
Enter movement values for X:  2 | Y:   |  Z:  7   \"good input, move: right 2, Y==0 assumed no down movement, rise 7\"\n\
Enter movement values for X: -3 | Y:-1 |  Z:  5   \"good input, move: left 3, up 1, and rise 5\"\n\
Enter movement values for X: 12 | Y: 3 |  Z:  3   \"bad input,  movement points are 9, the absolute value  X+Y+Z movement request must equal 9 no more no less.\"\n\
Enter movement values for X:  1 | Y: 1 |  Z: -4   \"bad input,  movement points are 9, the absolute value  X+Y+Z movement request must equal 9, no more no less.\"\n\
Enter movement values for X: -9 | Y:   |  Z:      \"good  input,  move left 9 units, Y==Z==0 assumed no movement on Y, and Z axis\\n\
\n\n\
Player bumping. If the PLAYER jumps into the same 'game space unit' as the GAME, or vice versa, the original occupant of that 'game\n\
space unit' will be bumped out a distance totaling its highest card value plus two 'game space units'. The direction will be along a line running \n\
from the GOAL center position through the occupied 'gsu' away from the GOAL.   QED:  If the GOAL is at X, Y, Z, the PLAYER is \n\
at X+1, Y+1, Z+1, and the GAME jumps into the same 'gsu' as the PLAYER is occupying, then the PLAYER will be bumped to\n\
(X + 1 + PLAYER's highest card value plus two 'gsu') * X directional %,\n\
(Y + 1 + PLAYER's highest card value plus two 'gsu') * Y directional %,\n\
(Z + 1 + PLAYER's highest card value plus two 'gsu') * Z directional %.\n\n\
This is another advantage of winning the last throw - down and getting to pick card for next throw - down after seeing the card your opponent has \n\
picked for the next throw - down.\n\
Same as if they where 'bumped' by the GOAL.\n\
The following are instructions on how to possess the GOAL.They are explained using only one dimension(the X axis) for simplicity.\n\
The GOAL has two stages of possession;  stage one, when Player or Game first jumps in, if the Player or Game can stay in the\n\
boundaries of the GOAL for the next card play then the GOAL is in stage two of possession.\n\
If the GOAL is not possessed it will randomly move and change shape.\n\
If the GOAL is in first stage of possession it will not move or change shape.\n\
If the GOAL is in second stage of possession it will randomly change shape only.\n\
Keep in mind that the game is played in 3 dimensions, and the GOAL it self is three dimensional, it has length, width, and height.\n\
Possession of the GOAL is obtained by moving one's game piece into the GOAL range and keeping \n\
it there for a second card play, QED;  ____P_____[_____]___G____  the under bars represent the X axis of the \"game space\",\n\
the 'P' represents the player's position on the X axis, the 'G' represents the GAME's position on the \n\
X axis, the opening bracket '[' represents the low end of the GOAL's range, and the closing bracket ']'\n\
represents the high end of the GOAL's range on the X axis.  For the 'P' to take possession of the GOAL pick a card\n\
with a total card value that can give enough movement points for  'P' to move into the GOAL range.\n\
__________[_P___]___G____ Now 'P' is in the GOAL's range and has stage one possession of the GOAL,  \n\
to obtain stage two possession it must remain in the GOAL for one more card play.  'P' must play a card \n\
with a value that will keep it in the GOAL's range, if that is done then 'P' will have \n\
stage two possession of the GOAL.  \n\
If the PLAYER, or GAME jumps in the the GOAL it attains stage one possession, the GOAL will not move or change shape while PLAYER or GAME\n\
has stage one possession.   To gain stage two possession the PLAYER or GAME must play a card and by that put in a legitimate movement \n\
request, but that movement can not put them outside of the GOAL's boundaries.\n\n\
QED: PLAYER jumps into GOAL and lands on X = 3, the GOAL's boundaries or X = 2 to X = 10. The PLAYER plays Four of Spades, \n\
getting total movement points of 5.  The PLAYER moves from X = 2 to X = 7, this is within the GOAL's boundaries and the PLAYER \n\
attains stage two possession.   Once 'P' has stage two possession of the GOAL and 'P' moves the GOAL will move\n\
with the Player and be centered on 'P'.   ___[___P___]____________G____\n\
With stage two possessions when the PLAYER moves the GOAL moves with the PLAYER, and centers itself around the PLAYER.\n\
If the PLAYER (with state two possession) moves from X = 20 to X = 30 and the GOAL has a length of 7, then the PLAYER will \n\
inhabit 'game space' X = 30 and the GOAL will range from X = 27 to X = 33.  This is one reason the GOAL dimensions \n\
will always be odd values.\n\
If 'P' has possession (stage one or two) of the GOAL 'G' can contest that possession by moving into the GOAL range.\n\
This will force a pitch/move contest in the GOAL between the PLAYER and the GAME; to win the contest, the PLAYER and \n\
the GAME must pick a card to throw-down, that card must have a movement value that when put in for X, Y, and Z movement \n\
will keep the thrower in the GOAL's boundaries, but at the same time have a value higher than the opponent's throw-down card.\n\n\
If both PLAYER and GAME's cards have the same value, it is a push and they must do the forced pitch/move again.\n\
Whoever losses the contest will be \"kicked out\" (ejected) from the GOAL a random combination of X, Y, and Z game space\n\
units totaling a distance of the loser \n\
highest card value plus two units of distance.  That will make it impossible for the loser to \n\
move directly back into the GOAL range on the next turn.  ___[_____G_]____('P' highest card value + 2)___P____\n\
The winner of the contest get stage two possession.\n\
\n\
Ways to defend the GOAL, move away from the other player, this will work for a time \n\
but the \"game space\" is a closed system 'P' and 'G' can not move out of it.  Next, jump over the player \n\
approaching the GOAL with the GOAL range not encompassing the player jumped over.\n\
If 'P' has possession and jumps over 'G' but the GOAL range ends up covering 'G's position\n\
'G' is in the GOAL range and a pitch/move contest is triggered.  Lastly 'P' and 'G' can bump.  \n\
To bump; the possessing play must move to a location that will put the outer end of the \n\
GOAL range within three units of distance of the non-possessing player. \n\
The non-possessing player will be bumped away a distance of its highest \n\
card value plus two units of distance.\n\
_[___P___]____________G____ to  _[___P___]_G____ to  _[_P_]_('G' highest card value + 2)___G____\n\
Note:  If 'P' or 'G' is to be \"kicked out\" and their highest card value plus 2 will put them past\n\
one edge of the \"game space\" then they will be \"kicked out\" in the opposite direction.\n\
QED:  P_____[__G___]____|  <- edge of X axis, 'G' is to be \"kicked out\", if the \n\
randomly chosen direction is 'to the right' and the distance to be \"kicked out\" is greater than the end \n\
of the X axis, then the direction is reversed and 'G' will be \"kicked out\" 'to the left on the X axis' to a distance \n\
based off the position of the lower GOAL range on the Y axis.\n\
If both 'P' and 'G' jump into the GOAL range on the same move then a pitch/move contest is triggered.\n\
\n\n\
As a hold over from the original game the winner of a hand, the highest card value throw-down on a turn\n\
gets to throw-down last on the next hand.  This is a huge advantage.\n\
QED:  Player throws-down 4 of CLUBS Game throws_down 5 of DIAMONDS, on the next turn the Player will have to\n\
throw-down a card to play first, the game can see that card's value and use it to formulate it move, and vis versa.\n\
During the pitch/move contest the PLAYER and the GAME do not get that advantage and must pick a card with out seeing the others first.\n\
Push 'esc' at any time to exit game.  Push Enter to continue.\n";

  // prompts for player, to enter axis movement values, and if those movements were approved or modified                    
  static const std::string _saEntryProms[3] = { {"Enter X axis move: "}, {"Enter Y axis move: "}, {"Enter Z axis move: "} };
  static const std::string _saMoveMentRequestResultsAccepted[3]{ {"X axis move approved: "}, {"Y axis move approved: "}, {"Z axis move approved: "}};
  static const std::string _saMoveMentRequestModified[3]{ {"X axis move modified: "}, {"Y axis move modified: "}, {"Z axis move modified: "} };

  // error alerts and prompts to player if bad input is detected that is input that is not an int
  static const std::string _saEntryErrorProms[6] = {
    {"BAD INPUT:  Enter any character to continue: "},
    {	"BAD INPUT: You can only enter an integer value, for negative value enter '-' before any number.\n\
            You do not need to enter a '+' for possitive numbers.  Press any character to continue, or ESC to quite: "
    },
    {"BAD INPUT: absolut value of 'x' is GREATER than card value.  Press Enter to continue or ESC to EXIT: "},
    {"BAD INPUT: absolut values of 'x and y' combined are GREATER than card value. Enter any character to continue: "},
    {"BAD INPUT: absolut values of 'x, y, and z' combined are GREATER than card value. Enter any character to continue: "},
    {"BAD INPUT: absolut values of 'x, y, and z' combined are LESS than card value. Enter any character to continue: "} };

  static const std::string _saPlayersCurrentPositionProms[3] = {{"Player's current X: "}, {"Player's current Y: "}, {"Player's current Z: "} };
  static const std::string _saPlayersCardProms[2] = { {"Player has picked the "}, {" card value is "} };
  static const std::string _saGamesCurrentPositionProms[3] = { {"Game's current X: "}, {"Game's current Y: "}, {"Game's current Z: "} };
  static const std::string _saGamesCardProms[2] = { {"Game has picked the "}, {" card value is "} };
  static const std::string _saGoalsPossessionStateHeaders[4]{ {"Game's GOAL"}, {"possession state,"}, {"State one: "}, {"State two: "} };

  // goal's position and size headers
  static const std::string _sGoalsPositionDataHeaders{ "Goal's center position: X=   | Y=   | Z=   |" };
  static const std::string _sGoalsDimensionalDataHeaders{ "Goal's dimensional sizes: X=    to X=   | Y=    to Y=   | Z=    to Z=   " };
  static const std::string _sGoalsLengthWidthHeightDataHeaders{ "Goal's Length:    Width:    Height:" };
  static const std::string _saGoalsPositionsDataHeaders[nsGF::NUMBER_OF_DIMENSIONS]{ { "Goal's center position: X=" },{ "| Y=" },{ "| Z = | " } };
  static const std::string _saGoalsDimensionalDataHeaders[nsGF::NUMBER_OF_DIMENSIONS * 2]{ {"Goal's dimensional sizes: X="}, {"to X = "}, {"|Y = "}, {"to Y = "}, {" | Z = to"}, {"Z = "} };
}// END namespace nsGF 
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------



