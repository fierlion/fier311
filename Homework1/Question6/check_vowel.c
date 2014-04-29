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
  http://www.programmingsimplified.com/c/source-code/c-program-check-vowel

 */


#include <stdio.h>
 
int main()
{
  char ch;
 
  printf("Input a character\n");
  scanf("%c", &ch);
 
  switch(ch)
  {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
      printf("%c is a vowel.\n", ch);
      break;
    default:
      printf("%c is not a vowel.\n", ch);
  }  
  return 0;            
}
