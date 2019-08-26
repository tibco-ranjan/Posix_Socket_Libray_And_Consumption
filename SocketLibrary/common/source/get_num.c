#include<get_num.h>
#include"tlpi_hdr.h"

// A utility function to check whether x is numeric
BOOLEAN isNumericChar(char x)
{
    return (x >= '0' && x <= '9')? TRUE:FALSE;
}
  
// A simple atoi() function. If the given string contains
// any invalid character, then this function returns 0
int myAtoi(char *str)
{
    if (NULL == str)
       return 0;
  
    int res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit
  
    // If number is negative, then update sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;  // Also update index of first digit
    }
  
    // Iterate through all digits of input string and update result
    for (; str[i] != '\0'; ++i)
    {
        if (isNumericChar(str[i]) == FALSE)
            return 0; // You may add some lines to write error message
                      // to error stream
        res = res*10 + str[i] - '0';
    }
    
    // Return result with sign
    if(res > 0 && res < INT_MAX)
    	return sign*res;
    else 
	return 0;
}
  
long myAtol(char *str)
{
    if (NULL == str)
       return 0;
  
    long res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit
  
    // If number is negative, then update sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;  // Also update index of first digit
    }
  
    // Iterate through all digits of input string and update result
    for (; str[i] != '\0'; ++i)
    {
        if (isNumericChar(str[i]) == FALSE)
            return 0; // You may add some lines to write error message
                      // to error stream
        res = res*10 + str[i] - '0';
    }
    
    // Return result with sign
    if(res > 0 && res < LONG_MAX)
    	return sign*res;
    else 
	return 0;
}

// Driver program to test above function
/*int main()
{
    char str[] = "-134";
    int val = myAtoi(str);
    printf("%d ", val);
    return 0;
}*/
