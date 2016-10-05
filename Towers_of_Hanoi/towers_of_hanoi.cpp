/*
Author: Miguel Martinez
Date: July 16th, 2016
Description: A small program to solve the towers of hanoi problem
Resources: https://www.cs.cmu.edu/~cburch/survey/recurse/hanoiex.html
*/

#include <iostream>
using namespace std;

void movetower(int disk, char source, char dest, char spare){
  if (disk <= 1)
    cout << "Moving: " << source << " to " << dest << endl;//movetower(0, source, spare, dest);
  else{
    movetower(disk-1, source, spare, dest);
    cout << "Moving: " << source << " to " << dest << endl;//cout 
    movetower(disk-1, spare, dest, source);
  }
  return;
}

int main(){
  movetower(5, 'a', 'b', 'c');
}
