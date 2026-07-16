#pragma once

static const std::string greetingString = "Welcome to \"Top Trumps 3D\", this is a test bed for game logic.\n\
Human(s) play against the program.\n\  
At game start a deck of standard playing cards is shuffled and dealt out to PLAYER and GAME, each gets twenty-six cards, no \"Joker\".\n\
The objective of the game is to occupy the GOAL;  the GOAL is a three-dimensional space that is located somewhere in the GAME-SPACE;  the GAME-SPACE is the playing area of the game.\n\
It is also a three-dimensional space with (X axis) length of 130 game-space-units, (Y axis) depth of 30 game-space-units, and (Z axis) height of 100 game-space-units.\n\
The GOAL is displayed on the GAME-SPACE map as a rectangle, the GAME-SPACE map is a two-dimensional display, it shows length (X axis) and width (Y axis) , but no height (Z axis).\n\
Both PLAYER and GAME's position on the GAME-SPACE map are shown as the capital letter P, and G respectively.   If both occupy the same (x, y) coordinate the capital letter B will be displayed.\n\    
The Z axis location or height, of the PLAYER, GAME, and GOAL, along with their X, and Y axis location are displayed on the screen along side the GAME-SPACE map.\n\
To occupy the GOAL, PLAYER or GAME must first move into the GOAL.  This is done by simply moving into the GOAL's area.   The PLAYER has at the start of the game 26 cards;\n\
each card has a unique movement value.  The movement value is the sum of the face value of the card (Ace==1, 2==2... 10==10, Jack==11, King==13), plus the suit value of the \n\
card (Spade==1, Club==2, Diamond==3, Heart==4.)    qed: the FOUR of CLUBS has a value of six movement points.    Each movement point can be used to move from one game-space-location\n\
to another.   The points can be used all in moving on one axis or spread out over all three axis.   qed:  PLAYER is as X==i, Y==j, Z==k, wants to move to X==i+3, Y==j-4, Z==k+2, \n\
the sum of the movement points needed is 3+4+2==9==EIGHT of SPADES==SEVEN of CLUBS==SIX of DIMONDS==FIVE of HEARTS.    If the PLAYER has any of those four cards the PLAYER can make that move.\n\

";
