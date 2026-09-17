
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



  
