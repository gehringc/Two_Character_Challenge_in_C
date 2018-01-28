#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

static int numOfUniqueChar;                                 /*number of kinds of char in the input s*/
static int l;                                               /*length of the inputted string, input by the user in the console*/
static int potentialTlength;                                /*length of the string made from two characters, updated throughout*/
static int pairCount;
char* charsPresent(char* s);
char* decideCharPairs(char* s);
int numberOfPairs( void );
bool isValidT(char first, char second, char* potentialT);
char * removeExcept(char first, char second, char* s);
int solveForAllT(char* charPairs, char* s);
int twoCharacters(char* s); 
    
int main() 
{
    scanf("%i", &l);
    char* s = malloc(l * sizeof(char));
    scanf("%s", s);
    int result;
    result = twoCharacters(s);
    printf("%d",result);
    free(s);
    return 0;
}    

/**
 * int twoCharacters(char* s)
 *
 * Inputs a string from the console and then determines the
 * longest possible string T. T is defined as a string with
 * two and only two alternating characters. 
 * This method of finding the longest T utlizies a limited
 * number of predifined c libraries in order to demonstrate 
 * detailed, component style approach to problem solving.
 *
 * @param char* s: the string input to the console
 * @return int maxLength: The length of longest possible T.
 */
int twoCharacters(char* s) 
{
    char *charPairs;
    charPairs = decideCharPairs(s);
    int maxLength = solveForAllT(charPairs, s);
    free(charPairs);
    return maxLength;    
}

/**
 * int solveForAllT(char* charPairs, char* s)
 *
 * Inputs the orginal string from the console and a string
 * containing all of the possible character combinations to create
 * a valid T. It solves for all possible T and determines the length longest length of T
 *
 * @param char* s: the string input to the console
 * @param char* charPairs: the possible character combinations for T.
 * @return int max: The length of longest possible T.
 */
int solveForAllT(char* charPairs, char* s)
{
    int max = 0;
    bool goodT = false;
    char* possibleT;
    int pairCount = numberOfPairs();
    pairCount = pairCount * 2;
    char firstChar;
    char secondChar;
    for (int i = 0; i < pairCount; i++)                         /*Create a new string of new characters and test it for each combo*/
    {
        firstChar = *charPairs;
        charPairs++;
        secondChar = *charPairs;
        charPairs++;
        possibleT = removeExcept(firstChar, secondChar, s);
        goodT = isValidT(firstChar, secondChar, possibleT);
        if (goodT)
        {
            if (potentialTlength >= max)                    /*If the length is longer than previous, set to max*/
            {
                max = potentialTlength;
            }
        }
        i++;
        free(possibleT);                                    /*Free the allocated mem from removeExcept each iteration
                                                              if possibleT is large, and pairCount is large 
                                                              heap memory can be used up quickly*/ 
    }
    return max;
}

/**
 * char * removeExcept(char first, char second, char* s)
 *
 * Creates a possible T by removing all characters in the console string
 * besides the two characters specified at input
 *
 * @param char first: the first char used to make T.
 * @param char second: the second char used to make T.
 * @param char* s: The string input to the console.
 * @return char* newT: A string with only two characters
 * @note  MEM IS NOT FREED IN THIS FUNCTION, please free the returned pointer when done
 *        using the data
 */
char * removeExcept(char first, char second, char* s)
{
    char *newT = malloc(l * sizeof(char));      /*allocate memory for new two character string*/
    potentialTlength = 0;                       /*Reset length*/
    for (int i = 0; i < l; i++)
    {
        if ( (*s == first) || (*s == second) )      /*If it is one of the selcted two characters, add to new string*/
        {
            *newT = *s;
            newT++;
            potentialTlength++;
        }
        s++;
    }
    newT = newT - potentialTlength;
    s = s - l;                                  /*go back to beginning of array for further processing*/
    return newT;
}

/**
 * bool isValidT(char first, char second, char* potentialT)
 *
 * Checks whether the string input string composed of two
 * designated characters is a valid t (two characters, alternating)
 *
 * @param char first: the first char used to make T.
 * @param char second: the second char used to make T.
 * @param char* potetialT: the possible character combinations for T.
 * @return bool isT: indicates whether the inputted string is a valid T
 */
bool isValidT(char first, char second, char* potentialT)
{
    bool parity = false;                                    /*Is the 1st char of potentialT first or second?*/
    bool isT = true;
    int i;
    if (potentialTlength > 1)                               /*T must be longer than 1 char*/
    {
        if ((*potentialT == second))                        /*Set parity flag, if 1st char in array is second*/
        {
               parity = true;
        }
        else if ( *potentialT != first )                    /*Not two char*/
        {
               isT = false;
        }
        for ( i = 0; i < potentialTlength; i++ )        /*Checks if they are alternating or not*/
        {
            if (!parity)                                    /*If first char is first, format should be first,second,first...*/
            {
                if ( i % 2 != 0)
                {
                    if (*potentialT != second)
                    {
                        isT = false;
                    }
                }
                else
                {
                    if (*potentialT != first)
                    {
                        isT = false;
                    }
                }
            }
            else
            {
                if ( i % 2 == 0)
                {
                    if (*potentialT != second)
                    {
                        isT = false;
                    }
                }
                else
                {
                    if (*potentialT != first)
                    {
                        isT = false;
                    }
                }
            }
            potentialT++;
        }
        potentialT = potentialT - potentialTlength;    
    }
    return isT;
}
    
/**
 * int decideCharPairs(char* s)
 *
 * Inputs a string from the console and then determines all of the 
 * possible combinations to decompose the string into a valid T.
 *
 * @param char* s: the string input to the console
 * @return int listOfPairs: All possible char combos placed in array. 
 * @note  MEM IS NOT FREED IN THIS FUNCTION, please free the returned pointer when done
 *        using the data
 */
char* decideCharPairs(char* s)
{
    char *charList;
    char *listOfPairs = malloc(650 * sizeof(char));       /*allocate enough memory for list of all combos*/
    charList = charsPresent(s);                                 /*Get all characters*/
    char firstOfPair;
    int count = 0;                                             /*Used to determine number of pairs, counts for each row*/
    for (int i = 0; i < numOfUniqueChar - 1; i++)
    {
        firstOfPair = *charList;                            /*First char part of combo to put in list*/
        for (int j = 0; j < numOfUniqueChar - count - 1; j++) 
        {
            *listOfPairs = firstOfPair;                     /*first part of pair*/
            listOfPairs++;
            charList++;
            *listOfPairs = *charList;                       /*second part of pair*/
            listOfPairs++;
        }
        count++;
        charList = charList - numOfUniqueChar + count + 1;
    }
    pairCount = numberOfPairs();
    pairCount = pairCount * 2; 
    listOfPairs = listOfPairs - pairCount;
    charList = charsPresent(s);                        /*Reset pointer address to ensure it is in allocated space, and then free it*/
    free(charList);
    return listOfPairs;
}

/**
 * int numberOfPairs( void )
 *
 * Determines the number of possible two character combinations
 * using recursive algorithm
 * result = numOfUniqueChar!/((numOfUniqueChar - 2)!*2!)
 *
 * @return int result: The resulting number of combinations.
 */
int numberOfPairs( void )
{
    int result = 0;
    for (int i = 1; i < numOfUniqueChar; i++)
    {
        result = result + i;               /* ex. x = 5, result = 4 + 3 + 2 + 1 = 15 */
    }
    return result;
}

/**
 * char* charsPresent( char* s )
 *
 * Determines each character in the input string and counts number of 
 * unique characters
 *
 * @param  char *s: the string input to the console
 * @return char* charList: a string containing a list of all the char.
 * @note  MEM IS NOT FREED IN THIS FUNCTION, please free the returned pointer when done
 *        using the data
 */
char* charsPresent(char* s)
{
    char* charList = malloc(26 * sizeof(char)); /*max char is 26*/
    bool isNotNew = false;                      /*Used to flag whether the char is new or not*/  
    int i;
    numOfUniqueChar = 0;
    for (int j = 0; j < l; j++)
    {
        /*Check each list member and add if unique*/
        for (i = 0; i <= numOfUniqueChar; i++)
        {
            if (*s == *charList)
            {
                isNotNew = true;
            }
            charList++;
        }
        charList = charList - i;                                    /*Go back to beginning of list for checking*/
        if (!isNotNew)                                              /*If its a new char, add to list and incr counter*/
        {
            charList = charList + numOfUniqueChar;                 /*Go  to first null postion*/
            *charList = *s;                                         /*Add character to list*/
            charList = charList - numOfUniqueChar;                /*Go back to beginning of array*/
            numOfUniqueChar++;                                      
        }       
        isNotNew = false;
        s++;                                                    
    }
    s = s - l; /*go back to beginning of array for further processing*/
    return charList;
}
