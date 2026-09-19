
// this will tell if P is to the left or right of the GOAL and inside the bump_range 
P < GX0 && P >= GX0 - bump_range  ||  P > GX1 && P <= GX1 + bump_range 
// now need to find if P is both inside of GY0 to GY1, and at same time inside of GZ0 to GZ1 
P >= GY0 &&  P <= GY1   &&  P >= GZ0 &&  P <= GZ1
// if all this comes back as true then 
// this will put P on GOAL's left or right side in it's bump_rang

// this will tell if P is on the top or the bottom of the GOAL and inside the bump_range 
P < GY0 && P >= GY0 - bump_range  ||  P > GY1 && P <= GY1 + bump_range 
// now need to find if P is both inside of GX0 to GX1, and at same time inside of GZ0 to GZ1 
P >= Y0 &&  P <= Y1   &&  P >= Z0 &&  P <= Z1
// if all this comes back as true then 
// this will put P on top of the GOAL or under it bottom and in it's bump_rang

// this will tell if P is in front of or behind the GOAL and inside the bump_range 
P < GZ0 && P >= GZ0 - bump_range  ||  P > GZ1 && P <= GZ1 + bump_range 
// now need to find if P is both inside of GX0 to GX1, and at same time inside of GY0 to GY1 
P >= GX0 &&  P <= GX1   &&  P >= GY0 &&  P <= GY1
// if all this comes back as true then 
// this will put P in front of or behinid the GOAL and in it's bump_rang

/***********************************************************************************************************************************
1. find the GOAL perimeter axes that are the closes to GAME’s current position
2. if GAME is outside the confines of any axis sets then head for the closes corner of the GOAL’s perimeter
3. if inside one axis confine;  qed  GAME < X0, Y0 < GAME < Y1, and GAME > Z1
move parallel to the Y0 or Y1 axis while moving down to Z1 value
4. if inside two axes confines (a double); qed  GAME < X0, Y0 < GAME < Y1, and Z0 < GAME < z1
only move parallel to the Y0 or Y1 axis   this will make your path a right angle to one of the GOAL’s sides
          |	           | 
      G0	|       G1           |      G2
----------|--------------------|--------------- Y0
          |		 | 
     G3   |         G4         |      G5
          |		 |
----------|--------------------|--------------- Y1
      G6	|          G7        |       G8
           X0                   X1
G0, G2, G3, G5, G6, and G8 are out of any axis confine
G3, G5, G6, and G8 are in a single axis confine
G4 is in a double axis confine
************************************************************************************************************************************/
#include <cmath> // for sqrt() function
#include <iostream>

int main()
{
  int Goal[3][2]{ {10,20}, {30, 40},{50, 60} };
  int Game[3]{ 0 , 0, 0 };
          
  while (1)
  { 
    std::cout << '\n' << "Enter Game's X: ";
    std::cin >> Game[0];
    std::cout << '\n' << "Enter Game's Y: ";
    std::cin >> Game[1];
    std::cout << '\n' << "Enter Game's Z: ";
    std::cin >> Game[2];
    // G0, G2, G3, G5, G6, and G8 are out of any axis confine

     if ((Game[0] < Goal[0][0] && (Game[1]<Goal[1][0] || Game[1]>Goal[1][1])) ||
      (Game[0] > Goal[0][1] && (Game[1]<Goal[1][0] || Game[1]>Goal[1][1])))
    {
      std::cout << '\n' << "Out of any axis confine.";
      if(Game[2]<Goal[2][0])
      {
          std::cout<<'\n'<<"<Goal[2][0]";
      }
      else if(Game[2]>Goal[2][1])
       {
          std::cout<<'\n'<<">Goal[2][1]"; 
       }
       else 
       {
           std::cout<<'\n'<<"[Goal[2][0] Goal[2][1]";
       }
    }
    // G3, G5, G6, and G8 are in a single axis confine
    else if (((Game[0] > Goal[0][0] && Game[0] < Goal[0][1]) && (Game[1]<Goal[1][0] || Game[1]>Goal[1][1])) ||
      (Game[0]<Goal[0][0] || Game[0]>Goal[0][1] && Game[1] > Goal[1][0] && Game[1] < Goal[1][1]))
    {
      std::cout << '\n' << "In single asix confine.";
       if(Game[2]<Goal[2][0])
      {
          std::cout<<'\n'<<"<Goal[2][0]";
      }
      else if(Game[2]>Goal[2][1])
       {
          std::cout<<'\n'<<">Goal[2][1]"; 
       }
       else 
       {
           std::cout<<'\n'<<"[Goal[2][0] Goal[2][1]";
       }
    }
    //  G4 is in a double axis confine
    else if ((Game[0] > Goal[0][0] && Game[0]<Goal[0][1] && Game[1]>Goal[1][0] && Game[1] < Goal[1][1]))
    {
      std::cout << '\n' << "In double axis confine.";
       if(Game[2]<Goal[2][0])
      {
          std::cout<<'\n'<<"<Goal[2][0]";
      }
      else if(Game[2]>Goal[2][1])
       {
          std::cout<<'\n'<<">Goal[2][1]"; 
       }
       else 
       {
           std::cout<<'\n'<<"[Goal[2][0] Goal[2][1]";
       }
    }
  }
  return 0;
}
