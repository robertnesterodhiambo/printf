#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments
 * @index: Index of the current character in the format string
 * @list: List of arguments to be printed
 * @buffer: Buffer array to handle print
 * @flags: Active flags for formatting
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed or -1 if an unknown format is encountered
 */
int handle_print(const char *format, int *index, va_list list, char buffer[],
                  int flags, int width, int precision, int size)
{
    int i, unknown_length = 0, printed_chars = -1;
    fmt_t fmt_types[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}};
    
    for (i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (format[*index] == fmt_types[i].fmt)
            return fmt_types[i].fn(list, buffer, flags, width, precision, size);
    }

    if (fmt_types[i].fmt == '\0')
    {
        if (format[*index] == '\0')
            return -1;

        unknown_length += write(1, "%%", 1);

        if (format[*index - 1] == ' ')
            unknown_length += write(1, " ", 1);
        else if (width)
        {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%')
                --(*index);
            
            if (format[*index] == ' ')
                --(*index);

            return 1;
        }

        unknown_length += write(1, &format[*index], 1);
        return unknown_length;
    }

    return printed_chars;
}
