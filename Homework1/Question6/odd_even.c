/*
Ray Allan Foote
footer@onid.oregonstate.edu
CS311_400
Assignment 1 (question 6)

  $RCSfile$
  $Revision$
  $Author$
  $Date$
  $Log$

  from:
  http://www.programmingsimplified.com/c/source-code/c-program-check-odd-even

 */


#include<stdio.h>
 
int main()
{
   int n;
 
   printf("Enter an integer\n");
   scanf("%d", &n);
 
   if (n & 1)
      printf("Odd\n");
   else
      printf("Even\n");
 
   return 0;
}
