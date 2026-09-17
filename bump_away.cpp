
// this will tell if P is to the left or right of the GOAL inside the bump_range 
P < G0 && P >= G0 - bump_range  ||  P > G1 && P <= G1 + bump_range 
// now need to find if P is both inside of Y0 to Y1, and at same time inside of Z0 to Z1 
P >= Y0 &&  P <= Y1   &&  P >= Z0 &&  P <= Z1
// if all this comes back as true then 
// this will put P on GOAL's left or right side in it's bump_range


  
