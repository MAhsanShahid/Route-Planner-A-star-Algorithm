#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<conio.h>


struct elementstruct
{
  int block[9];
  char* str;
  int pathcost;
  int valid;
  int totalcost;
  elementstruct* next;
};
char rep[] = "dulr";
int notvalid1[4] = { 6, 0, 0, 2 };
int notvalid2[4] = { 7, 1, 3, 5 };
int notvalid3[4] = { 8, 2, 6, 8 };
int applyparam[4] = { +3, -3, -1, +1 };
int goal_block[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8}; //8 indicates no tile
int maxdepth;
elementstruct* top;
int block[9];


int heur(int* block)
{
#ifdef H2
  int to_return = 0;

  for(int i=0; i<9; i++)
    {
    to_return += abs((i/3) - (block[i]/3))

    to_return += abs((i%3) - (block[i]%3));
    }
  return to_return;

#else
  int to_return = 0;

  for(int i=0; i<9; i++)
    {
	 if (block[i] != i) to_return++;
    }
  return to_return;

#endif

}

//void prepend(elementstruct* newnode, elementstruct* oldnode, int operator1);

void prepend(elementstruct* newnode, elementstruct* oldnode, int op)
{
  newnode->next = top;
  top = newnode;

  strcpy(newnode->str, oldnode->str);
  newnode->str[oldnode->pathcost] = rep[op];
  newnode->str[oldnode->pathcost+1] = 0;

  newnode->pathcost = oldnode->pathcost+1;
  newnode->totalcost = newnode->pathcost + heur(newnode->block);
  if (newnode->totalcost < oldnode->totalcost) newnode->totalcost = oldnode->totalcost;
}

//int goal(int* block);
//int notonqueue(int block[]);
//elementstruct* bestnodefromqueue();
//void print_block(int* block);
//int apply (int* newstate, int* oldstate, int op);
//elementstruct* newelement();
//int op(char);
//char to_char(int i);

int goal(int* block)
{
  int* g_block = goal_block;

  for(int i=0; i<9; i++)
    if ((*(block++))!=(*(g_block++)))
	 return 0;

  return 1;
}

int notonqueue(int* block)
{
  int i,j;
  elementstruct* t = top;

  while (t!=NULL)
    {
	 for(i=0; i<9; i++)
	if (t->block[i] != block[i]) break;
	 if (i==9) return 0;

	 t = t->next;
    }
  return 1;
}

elementstruct* bestnodefromqueue()
{
  elementstruct* t = top;
  int min_totalpathcost = 1000;
  int totalpathcost;
  elementstruct* to_return = NULL;

  while (t != NULL)
    {
	  if (t->valid==1 && t->totalcost < min_totalpathcost)
	{
	min_totalpathcost = t->totalcost;
	to_return = t;
	}
	 t = t->next;
    }

  if (to_return != NULL) to_return->valid = 0;

  return to_return;
}

int apply (int* newstate, int* oldstate, int op)
{
  int j;
  int blank;

  for (j=0; j<9; j++)
	if (oldstate[j]==8) { blank=j; break; }

  if (blank==notvalid1[op] || blank==notvalid2[op] || blank==notvalid3[op])
    return -1;

  for (j=0; j<9; j++)
    newstate[j] = oldstate[j];

  newstate[blank] = newstate[blank+applyparam[op]];
  newstate[blank+applyparam[op]] = 8;

  return 1;
}

elementstruct* newelement()
{
  elementstruct* t = new elementstruct;
  if (t==NULL) return NULL;
  t->valid = 1;
  t->str = new char[maxdepth+1];
  if (t->str ==NULL) return NULL;
  t->str[0] = 0;
  t->pathcost = t->totalcost = 0;
  t->next = NULL;
  return t;
}

char to_char(int i)
{
  if (i>=0 &&i<=7) return i+'1';
  else if (i==8) return 'x';
  else { printf("ERROR in Program!"); return -1; }

}

void print_block(int* block)
{
  printf("\n");
  printf ("\n-------");
  printf ("\n|%c|%c|%c|", to_char(block[0]), to_char(block[1]), to_char(block[2]));
  printf ("\n-------");
  printf ("\n|%c|%c|%c|", to_char(block[3]), to_char(block[4]), to_char(block[5]));
  printf ("\n-------");
  printf ("\n|%c|%c|%c|", to_char(block[6]), to_char(block[7]), to_char(block[8]));
  printf ("\n-------");
}



int op(char i)
{
switch (i)
  {
  case 'd': return 0;
  case 'u': return 1;
  case 'l': return 2;
  case 'r': return 3;
  default: printf("ERROR!"); return -1;
  }
}

