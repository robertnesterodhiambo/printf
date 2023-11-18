#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @character: Character to be evaluated
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int is_printable(char character)
{
    if (character >= 32 && character < 127)
        return 1;

    return 0;
}

/**
 * append_hexa_code - Appends ASCII in hexadecimal code to the buffer
 * @buffer: Array of characters
 * @index: Index at which to start appending
 * @ascii_code: ASCII code
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int index)
{
    char map_to[] = "0123456789ABCDEF";

    /* The hexadecimal format code is always 2 digits long */
    if (ascii_code < 0)
        ascii_code *= -1;

    buffer[index++] = '\\';
    buffer[index++] = 'x';

    buffer[index++] = map_to[ascii_code / 16];
    buffer[index] = map_to[ascii_code % 16];

    return 3;
}

/**
 * is_digit - Verifies if a character is a digit
 * @character: Character to be evaluated
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int is_digit(char character)
{
    if (character >= '0' && character <= '9')
        return 1;

    return 0;
}

/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of the number
 */
long int convert_size_number(long int number, int size)
{
    if (size == S_LONG)
        return number;
    else if (size == S_SHORT)
        return (short)number;

    return (int)number;
}

/**
 * convert_size_unsgnd - Casts an unsigned number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}
