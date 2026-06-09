#include"gameFunctions.h"

//*************************************************************************************************
//*************************************************************************************************
//***** START testIfGoalShouldMove METHOD

/*-------------------------------------------------------------------------------------------------
the Goal's existents and movement in the Universe
the game space "the universe"  is a three dimensional int array
the first position is at x = 0, y = 0, z = 0 the last position is at x = height, y = length, z = width, the game
space can be set at the start of a match
the Game and the Player each occupy one unit of game space
a game space is noted as x = n, y = n, z = n, to x = n + 1, y = n + 1, z = n + 1
Goal will start the match occupying some number of game spaces
as the match goes on the Goal will randomly move from position to position through the game space,
and randomly shrink and expend in size by some number of randomly selected game spaces,
the Goal will never have a negative game spaces value
when the Goal randomly shrinks to one game space the match is ended
the Goal will be centered around one game space and will extend out an even number of +/-x, +/-y and +/-z game spaces

EX : Goal's centered is at x=n, y=n, z=n,  and its five game spaces in length, width, and height
its outer boundaries would be x = n - 2 to x = n + 2, y = n - 2 to y = n + 2, z = n - 2 to z = n + 2
the Goal is constrained to being totally in the game space, so if the Goal is eleven game spaces in length then its
center can not be any less then y = 5, or any more than y = (length of game space) - 5 game spaces or if game space
is 0 to 99 in length then the Goal would have it y axis centered on y = 97 and it would extend out to y = 99

How and when the Goal changes its shape and moves.     At any time that the Goal is not possessed (occupied) by the Player,
or the Game, a random generated number will decide if the Goal is to 1. change it position and 2. change it shape.
The Goal’s new position and or shape will be tested to make sure no part of it is outside the game space.
If any portion is out of game space bounds the Goal will have a new position generated and tested.

the Goal and its behavior before and after the Player or Game have possession  of it
the Goal will move and change shape randomly until it is possessed
once possessed (level one possession) its movement is under the control of the possessor (Player, or Game)

Goal possession and control steps

1. a token is moved into the Goal's boundaries:
Ex. Goal's  center is at Xn, Yn, and Zn, and had has boundaries of Xn-5 to Xn+5, Yn-5 to Yn+5, and Zn-5 to Zn+5  then a
token moving from Xn-7, Yn-7, Zn-7, which is  to units of game space inferior to Goal's position to Xn-4, Yn-4,  and Zn-4  which is
two units of game space inside of the Goal's boundaries    Note:  the Goal's area are from the center of the Goal up to and in
including the game space its boundaries lays on
[                     ]  Y axis
-5-4-3-2-1 0 +1+2+3+4+5

as soon as a token "jumps" into the Goal's boundary the Goal will no longer move on its own nor will it change shape during the first stage of
possession this is to give the token a change to take total possession  the Goal is now in the first stage of possession
to gain full possession of the Goal the token's next move must be a full card value move without  moving out side of the Goal's boundaries
[  T                  ]  Y axis
-5-4-3-2-1 0 +1+2+3+4+5

if Player plays a 5 Spade on the Y axis
move X = 0
move Y = 5 Spade == 6 game space units of movement
move Z = 0

[               T     ]  Y axis
-5-4-3-2-1 0 +1+2+3+4+5

now the token has full possession of the Goal and where ever the Player moves to the Goal will fallow and center itself about that token
on all its axis
[          T          ]  Y axis
-5-4-3-2-1 0 +1+2+3+4+5

the Goal will continue to change shape  randomly from time to time as it is moved by the token that has possession of it
once an axis is randomly give the value of 1 game space unit then that axis is lock in at 1 GSU, when all the axis are locked
in at 1 GSU the match is ended

-------------------------------------------------------------------------------------------------*/

//*************************************************************************************************
//*************************************************************************************************/
//***** START testIfGoalShouldMove() METHOD 

bool GameFunctions::testIfGoalShouldMoveOrResize()
{
  // for testing
  int _iDGM{ -1 };   // dose GOAL move
  int _iDGCS{ -1 };  // does GOAL change shape
  bool _bDGCSorM[2]{ {false}, {false } }; // if no shape or position change then return false   see below  [0] shape change | [1] move

  if ((get_baGoalsPossessionState(0) && !get_baGoalsPossessionState(1))) // if {true, false} then token has first stage possession and the Goal can not move or change shape 
    return false; // no move no change shape return false to signal this

  // random number generator used to move the Goal's center and change it size
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed); // Mersenne Twister engine

  //  Define the desired distributions (e.g., uniform integer distribution between [m, n] inclusive m<=x<=n)
  std::uniform_int_distribution<int> goalSize(1, 10);
  std::uniform_int_distribution<int> goalNextX(0, nsGF::GAME_SPACE_LENGTH-1);
  std::uniform_int_distribution<int> goalNextY(0, nsGF::GAME_SPACE_WIDTH-1);
  std::uniform_int_distribution<int> goalNextZ(0, nsGF::GAME_SPACE_HIGHT-1);
  std::uniform_int_distribution<int> doesGoalMove(1, 10);
  std::uniform_int_distribution<int> doesGoalChangeSize(1, 10);

  // Generate new random Goal axis lenght, width,and height.
  // The Goal can only change size when it is either not possessed or fully possessed {false, false} or {true, true}
  // Check if both are true or both are false
  // if ((a && b) || (!a && !b)) {

  // Once an axis of GOAL size randomly hits 1, it is locked and will stay at that value to the end of the match   
  // once all axis of GOAL size randomly hits 1 the match is ended

    if ((_baGoalsPossessionState[0] && _baGoalsPossessionState[1]) || (!_baGoalsPossessionState[0] && !_baGoalsPossessionState[1]))
     if ((_iDGCS = doesGoalChangeSize(gen)) % 10 == 0)  
      {
        if (_iaGoalsLenghtWidthHeight[0] != 1) _iaGoalsLenghtWidthHeight[0] = 2 * goalSize(gen) + 1;  // this way LWH will always be odd value
        if (_iaGoalsLenghtWidthHeight[1] != 1) _iaGoalsLenghtWidthHeight[1] = 2 * goalSize(gen) + 1;
        if (_iaGoalsLenghtWidthHeight[2] != 1) _iaGoalsLenghtWidthHeight[2] = 2 * goalSize(gen) + 1;       
        _bDGCSorM[0] = true;
      }

    // If GOAL in stage two possession by GAME or PLAYER then GOAL must move with the possessor with it being centered around the possessor’s location. 
    if ((_baPlayersPossessionState[0] && _baPlayersPossessionState[1]))     // If GOAL is possessed it must move with the possessor.
      {
        _iaGoalsRequestedMove[0] = _iaPlayersCurrentPosition[0];
        _iaGoalsRequestedMove[1] = _iaPlayersCurrentPosition[1];
        _iaGoalsRequestedMove[2] = _iaPlayersCurrentPosition[2];
        _bDGCSorM[0] = true;
    }
    else if(_baGamesPossessionState[0] && _baGamesPossessionState[1])   // GAME and PLAYER can not both be in possession of the GOAL at the same time.
    {
      _iaGoalsRequestedMove[0] = _iaGamesCurrentPosition[0];
      _iaGoalsRequestedMove[1] = _iaGamesCurrentPosition[1];
      _iaGoalsRequestedMove[2] = _iaGamesCurrentPosition[2];
      _bDGCSorM[0] = true;
      }


    // Generate random position for Goal to move to. 
    if ((!_baGoalsPossessionState[0] && !_baGoalsPossessionState[1]))     // Goal only moves randomly if its' possession state is {false, false}
     if ((_iDGM = doesGoalMove(gen)) % 10 == 0)  
      {
        _iaGoalsRequestedMove[0] = goalNextX(gen);
        _iaGoalsRequestedMove[1] = goalNextY(gen);
        _iaGoalsRequestedMove[2] = goalNextZ(gen);     
        _bDGCSorM[1] = true;       
      }
    

    // a safety check that will not let the Goal move to a position that will put 
    // some of its dimension out of the Universe's bounds 
    // 
    // PLAYER and GAME are both bound by this SAFETY CHECK if GAME or PLAYER is in possession of the GOAL and they move to a location 
    // that will put some part of the GOAL’s perimeter out of the ‘game space’ their movement is modified to keep all of the GOAL’s perimeter 
    // in bounds.      Just like when GAME or PLAYER move without the GOAL in tow.
    if (_bDGCSorM[0] || _bDGCSorM[1])
    {
      int x{ _iaGoalsRequestedMove[0]};  //  the GOAL requested move will always put it's center in bounds [[0 L], [0 W], [0 H]]
      int y{ _iaGoalsRequestedMove[1]};
      int z{ _iaGoalsRequestedMove[2]};

      int xL{ _iaGoalsLenghtWidthHeight[0] / 2 };   // if L == 7 then 7/2 = 3  then test 3 to left and 3 to right
      int yW{ _iaGoalsLenghtWidthHeight[1] / 2 };
      int zH{ _iaGoalsLenghtWidthHeight[2] / 2 };

      if (x - xL < 0) _iaGoalsCurrentCenter[0] = abs(xL);
      else if (x + xL > nsGF::GAME_SPACE_LENGTH - 1) _iaGoalsCurrentCenter[0]= abs(nsGF::GAME_SPACE_LENGTH - xL - 1);
      else (_iaGoalsCurrentCenter[0] = _iaGoalsRequestedMove[0]);

      if (y - yW < 0) _iaGoalsCurrentCenter[1] = abs(yW);
      else if (y + yW > nsGF::GAME_SPACE_WIDTH - 1) _iaGoalsCurrentCenter[1] = abs(nsGF::GAME_SPACE_WIDTH - yW - 1);
      else (_iaGoalsCurrentCenter[1] = _iaGoalsRequestedMove[1]);

      if (z - zH < 0) _iaGoalsCurrentCenter[2] = abs(zH);
      else if (z + zH > nsGF::GAME_SPACE_HIGHT - 1) _iaGoalsCurrentCenter[2]= abs(nsGF::GAME_SPACE_HIGHT - zH - 1);
      else (_iaGoalsCurrentCenter[2] = _iaGoalsRequestedMove[2]);
    }

  // Once an axis of GOAL size randomly hits 1, it is locked and will stay at that value to the end of the match   
  // once all axis of GOAL size randomly hits 1 the match is ended
    if (_iaGoalsLenghtWidthHeight[0] == _iaGoalsLenghtWidthHeight[1] == _iaGoalsLenghtWidthHeight[2] == 1)
    {
      std::cout << "\n Match has ended!\n\n";
      return false;
    }
    // Update GOAL’s current dimensions low[0] and highs[1] on the ‘game space’ axis....................................... 
    // Updata GOAL's bump dimenstions low[0]-BumpRange and highs[1]+BumpRange on the ‘game space’ axis
    for (int i{ 0 }; i < nsGF::NUMBER_OF_DIMENSIONS; ++i)
    {
      _iaGoalsLastPerimeter[i][0] = _iaGoalsCurrentPerimeter[i][ 0];
      _iaGoalsBumpRangePerimeter[i][0] = _iaGoalsCurrentPerimeter[i][0] - _iGoalsBumpRange;
      _iaGoalsCurrentPerimeter[i][0] = _iaGoalsCurrentCenter[i] - _iaGoalsLenghtWidthHeight[i] / 2;
      _iaGoalsLastPerimeter[i][1] = _iaGoalsCurrentPerimeter[i][1];
      _iaGoalsBumpRangePerimeter[i][1] = _iaGoalsCurrentPerimeter[i][1] + _iGoalsBumpRange;
      _iaGoalsCurrentPerimeter[i][1] = _iaGoalsCurrentCenter[i] + _iaGoalsLenghtWidthHeight[i] / 2;
    }
    if (_bDGCSorM[0] || _bDGCSorM[1]) return true;
    else return false;
}
//***** END testIfGoalShouldMove() METHOD 
//*************************************************************************************************
//*************************************************************************************************/




