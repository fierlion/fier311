#include <stdio.h>
#include <cs50.h>

int main(void)
{
  //factorials aren't defined for negative numbers
  int num = 0;
  do {
    printf("enter a positive integer: ");
    num = GetInt();
  }
  while (num < 0);

  int factorial= 0;
  for(int i = 1; i <= num; i++)
    factorial = factorial * i;

  printf("%d! = %d\n", num, factorial);

  return 0;
}
