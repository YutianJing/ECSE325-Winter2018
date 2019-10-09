#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *decimal_to_binary(int);

/*
 * This method reads the floating point values from to separate files,
 * convert them to fixed point, and stores them in two new files
 */
void main()
{
    // Open the files
    FILE *lab3_in = fopen("lab3-In.txt", "r");
    FILE *lab3_coef= fopen("lab3-coef.txt", "r");

    // Create arrarys to hold the x values and y values
    float inputs[1000];
    float coef[25];
    int i;

    // Read each floating point number from the files and store them in their corresponding array
    for (i = 0; i < 1000; i++)
    {
        fscanf(lab3_in, "%f", &inputs[i]);
    }
    for (i = 0; i < 25; i++)
    {
        fscanf(lab3_coef, "%f", &coef[i]);
    }

    // Done with these files, close them
    fclose(lab3_in);
    fclose(lab3_coef);

    // Go through th arrary multiplying each number by 2^15 because 
    // b = a x 2^F where a = floating point number, F = fractional length
    for (i = 0; i < 1000; i++)
    {
        inputs[i] = inputs[i] * 32768;
    }
    for (i = 0; i < 25; i++)
    {
        coef[i] = coef[i] * 32768;
    }

    // Open the files where the fixed point values will be written to
    FILE *lab3_in_fixed_point = fopen("lab3-in-fixed-point.txt", "w");
    FILE *lab3_coef_fixed_point = fopen("lab3-coef-fixed-point.txt", "w");

    int n;
    char *pointer;

    // iterate through each number, convert it to binary (2's complement) then print it to it's corresponding file
    for (i = 0; i < 1000; i++)
    {
        n = (int)inputs[i];
        pointer = decimal_to_binary(n);
        fprintf(lab3_in_fixed_point, "%s\n", pointer);
    }
    for (i = 0; i < 25; i++)
    {
        n = (int)coef[i];
        pointer = decimal_to_binary(n);
        fprintf(lab3_coef_fixed_point, "%s\n", pointer);
    }

    // Free the pointer from memory and close the files because we are done with them
    free(pointer);
    fclose(lab3_in_fixed_point);
    fclose(lab3_coef_fixed_point);
}

/*
 * This method take an integer as an argument an converts it to a 16-bit binary number
 * If the integer is negative, the number gets convert to its positive binary value,
 * then gets converted again to 2's complement
 * returns a pointer to the MSB of the binary number in memory
 */
char *decimal_to_binary(int n)
{
    int c, d, count, i, invert_spot;
    char *pointer;
    int neg_number = 0;

    // intialize the counter
    count = 0;

    // will point to the MSB (sign bit) of the binary number in memory
    pointer = (char *)malloc(16 + 1);

    // Array to hold the binary digits
    int binary_digits[16];

    if (pointer == NULL)
        exit(EXIT_FAILURE);

    // If the number is negative, make it positive and set the neg_number flag high
    if (n < 0)
    {
        n = n * (-1);
        neg_number = 1;
    }

    // Converts the decimal number to its unsigned binary value storing it bit by bit in the array
    for (c = 15; c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            binary_digits[count] = 1;
        else
            binary_digits[count] = 0;
        count++;
    }

    // if the argument n was postive, simply copy the values from the array to memory starting at the pointer
    if(!neg_number)
    {
        for(i = 0; i < 16; i++)
        {
            if(binary_digits[i] == 0)
            {
                *(pointer + i) = 0 + '0';
            }
            else
            {
                *(pointer + i) = 1 + '0';
            }
        }
    }
    else
    // the argument n was positive, convert to 2's complement
    {
        // Starting from the LSB, iterate through the array backwards until the first '1' bit is reached
        // All the numbers before (and not including) this 1 value need to be inverted
        for (i = 15; i >= 0; i--)
        {
            if (binary_digits[i] == 1)
            {
                invert_spot = i;
                break;
            }
        }
         // Starting at the MSB, iterate throught the arrary storing the inverted value in memory starting at the pointer
        for (i = 0; i < 16; i++)
        {
            if (i < invert_spot)
            {
                if (binary_digits[i] == 0)
                {
                    *(pointer + i) = 1 + '0';
                }
                else
                {
                    *(pointer + i) = 0 + '0';
                }
            }
            else
            // Once the '1' found above is reached, simply copy the values over from the array to the next spot in memory
            {
                if (binary_digits[i] == 0)
                {
                    *(pointer + i) = 0 + '0';
                }
                else
                {
                    *(pointer + i) = 1 + '0';
                }
            }
        }
    }

    // Add the null terminator to the end of the string
    *(pointer + count) = '\0';

    // return a pointer the the MSB in memory
    return pointer;
}