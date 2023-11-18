#include "main.h"

/**
 * get_flags - Determines active formatting flags
 * @format: Formatted string indicating how to print the arguments
 * @index: Current index in the format string
 * Return: Active flags
 */
int get_flags(const char *format, int *index)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8 16 */
    int char_index, current_index;
    int flags = 0;
    const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (current_index = *index + 1; format[current_index] != '\0'; current_index++)
    {
        for (char_index = 0; FLAGS_CHARACTERS[char_index] != '\0'; char_index++)
        {
            if (format[current_index] == FLAGS_CHARACTERS[char_index])
            {
                flags |= FLAGS_ARRAY[char_index];
                break;
            }
        }

        if (FLAGS_CHARACTERS[char_index] == 0)
            break;
    }

    *index = current_index - 1;

    return flags;
}
