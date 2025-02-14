#include <stdio.h>
#include <stdlib.h>

#include "myStringLib.h"

// [COPY AND PASTE] Copy and Paste your Lab 3 Q1 Solution Below

//  This is then your very first reusable custom C library 

int my_strlen(const char * const str1)
{
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character

	int i = 0;
	int count = 0;

	while (str1[i] != '\0')
	{
		count += 1;
		i++;
	}

	return count;

}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	
	// Criteria 1: Check their lenghts.  If not the same length, not equal

	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal

	// if passing the two criteria, strings equal

	int i = 0;
	
	if (str1 == NULL || str2 == NULL) 
	{
        // Null pointer check
        return 0;
    }


	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
		i++; 
	} 

	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return 1;
	}

	else
	{
		return 0;
	}

}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/

	// if two strings are completely identical in order, return -1.

	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character

		int i = 0;
	

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			if (str1[i] > str2[i])
			{
				return 1;
			}

			else
			{
				return 0;
			}
		}
		i++; 
	} 

	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return -1;
	}

	else
	{
		return 0;
	}

	


}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	
	/*write your implementation here*/
	
	int length_1 = my_strlen(str1);
	int length_2 = my_strlen(str2);
	int total_length = length_1 + length_2;

	z = (char*)malloc((total_length * sizeof(char)) + 1);

	int i;

	for (i = 0; i < length_1; i++)
	{
		z[i] = str1[i];
	}
	for (i = 0; i < length_2; i++)
	{
		z[length_1 + i] = str2[i];
	}
	z[total_length] = '\0';

	

	/* finally, return the string*/
	return z;

	

	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT
	
}