#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<conio.h>
#include"Astar.h"
using namespace std;
int main()
{
  
   system("cls");;
  
 elementstruct* newnode = newelement();

 cout<<endl<<"                   The Eight Tiles Puzzle!"<<endl;;
 //printf("\nThe Eight Puzzle!\n");

 cout<<endl<<"Represent tiles with numbers 1 to 8, and the blank space as 'x'"<<endl;
  /* printf("\nPlease Enter the initial state of the game \n"
	    " [Represent tiles with numbers 1 to 8, and the blank space as 'x'.\n"
	    " Start writing them from left to right for each row. Start from the topmost row to the bottommost row.\n"
	    " Your final string will look similar to this '1 4 2 3 x 6 7 8 5'.\n"
	    " Do not forget the spaces in between the characters]\n");
*/
  int i = 0;
  while(i<9)
	{
	char chr;
	cin>>chr;
	//chr = fgetc(stdin);
	if (chr==' ')
		continue;
	if (chr=='x') 
		block[i] = 8;
	else if (chr >= '1' && chr <= '9') 
		block[i] = chr - '1';
	i++;
	}
//	  for(i =0;i<9;i++)
//	  {
////	  printf("%d",block[i]);
//     //	  getch();
//	  }
//    //	else { printf("Invalid Input. Example of valid input...2 1 3 4 7 5 6 8 x.", chr); return 1; }
//   //	i++;
//    //	}

  //fgetc(stdin); //flush out the end of line character
  cin.ignore();
  printf("\n Now Enter the Goal State in a similar way. (Typical. 1 2 3 4 5 6 7 8 x): ");

  i = 0;
  while(i<9)
	{
	char chr;
	chr = fgetc(stdin);
	if (chr==32) continue;
	if (chr=='x') goal_block[i] = 8;
	else if (chr >= '1' && chr <= '9') goal_block[i] = chr - '1';
	else { printf("chr=%d. Invalid Input. Example of valid input...2 1 3 4 7 5 6 8 x.",(int) chr); return 1; }
	i++;
	}

  printf("Enter the maximum depth you want to search (<25 is solved quickly): ");
  scanf("%d", &maxdepth);

  printf("\nWorking...");

  top = newelement();
  for(i=0; i<9; i++)
    top->block[i] = block[i];
  top->totalcost = heur(block);

  

  while (1)
    {
	 elementstruct* node = bestnodefromqueue();
	 if (node == NULL) {
	printf("done!\n");
	printf("There is no solution to this of less than %d depth.\n", maxdepth);
	printf("Try increasing the depth by 5.\n");
	printf("If there is no solution within 35-40 depth, the pattern is usually unsolvable.\n\n");
	break;
	 }
	 else if (goal(node->block)) {
	char chr[15];
	printf("done. \nFound the solution of least number of steps (%d).", node->pathcost);
	printf("\nWant a graphical display of each step? (Y/N)?");
	scanf("%s", chr);
	if(chr[0] =='n' || chr[0]=='N') {
	  printf("\n (Move Blank u=up, d=down, l=left, r=right)\n");
	  printf(node->str);
	  printf("\n");
	  break;
	}

	int block2[9];
	for (i=0; i<node->pathcost; i++)
	  {
	    print_block(block);
	    apply(block2, block, op(node->str[i]));
	    for(int j=0; j<=8; j++)
		 block[j] = block2[j];
	  }
	print_block(block);

	printf("\nGraphical Display Complete.\nThe steps taken were: (Move blank u=up, d=down, l-left, r=right)\n");
  //	printf(node->str);
    //	printf("\n");
	getch();
	break;

	 }

	 if (node->totalcost > maxdepth) continue;

	 for(i=0; i<=3; i++) {
	if (apply(newnode->block, node->block, i) == -1)
	  continue;

	if (notonqueue(newnode->block)) {
	  prepend(newnode, node, i);
	  newnode = newelement();
	  if (newnode==NULL) { printf ("ERROR!! insufficient memory!! Try decreasing depth!"); return 1; }
	}
	 }

	}
  system("pause");
	return 0;
}
