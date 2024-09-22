#include <stdio.h>
#include <stdlib.h>

unsigned long long recursiveFibProvider(int val);
unsigned long long recursiveFib(int val);
unsigned long long iterativeFibProvider(int val);
unsigned long long iterativeFib(int val);
unsigned long long overflowCheck(unsigned long long firstVal, unsigned long long secondVal);
void memoInitialization();

unsigned long long memo[100];
void memoInitialization()
{
   for (int i = 0; i < 100; i++)
   {
      memo[i] = -1;
   }
}

unsigned long long overflowCheck(unsigned long long firstVal, unsigned long long secondVal)
{
   return firstVal <= ULLONG_MAX - secondVal;
}

unsigned long long recursiveFibProvider(int val)
{
   if (val <= 1)
   {
      return 0;
   }

   else if (val == 2)
   {
      return 1;
   }

   return recursiveFib(val);
}

unsigned long long recursiveFib(int val)
{

   if (val >= 95)
   {
      printf("Overflow occurs at the %dth term: ", 95);
      return ULLONG_MAX;
   }

   if (memo[val] != -1)
   {
      return memo[val];
   }

   unsigned long long prevNum = recursiveFibProvider(val - 1);
   unsigned long long prevPrevNum = recursiveFibProvider(val - 2);

   if (overflowCheck(prevNum, prevPrevNum))
   {
      memo[val] = prevNum + prevPrevNum;
   }

   return memo[val];
}

unsigned long long iterativeFibProvider(int val)
{
   unsigned long long prevPrevNum = 0;
   unsigned long long prevNum = 0;
   unsigned long long currentNum = 1;

   for (int i = 2; i < val; i++)
   {
      prevPrevNum = prevNum;
      prevNum = currentNum;
      if (overflowCheck(prevPrevNum, prevNum))
      {
         currentNum = prevPrevNum + prevNum;
      }

      else
      {
         printf("Overflow occurs at the %dth term: ", i + 1);
         return ULLONG_MAX;
      }
   }
   return currentNum;
}

unsigned long long iterativeFib(int val)
{

   if (memo[val] != -1)
   {
      return memo[val];
   }

   memo[val] = iterativeFibProvider(val);
   return memo[val];
}

int main(int argc, char **argv)
{
   int input = atoi(argv[1]);
   unsigned long long output = 0;

   memoInitialization();

   if (argv[2][0] == 'r')
   {
      output = recursiveFib(input);
   }

   else if (argv[2][0] == 'i')
   {
      output = iterativeFib(input);
   }
   printf("%llu\n", output);
   return 0;
}