#include "main.h"

void output_printer(char output[], int *output_index);

/**
 * custom_printf - Implementation of a custom printf function.
 * @format_str: Input format string.
 * Return: Total number of characters printed.
 */
int custom_printf(const char *format_str, ...)
{
    int index, printed = 0, total_printed_chars = 0;
    int format_flags, field_width, precision, size_specifier, output_index = 0;
    va_list args;
    char output[OUTPUT_BUFFER_SIZE];

    if (format_str == NULL)
        return (-1);

    va_start(args, format_str);

    for (index = 0; format_str && format_str[index] != '\0'; index++)
    {
        if (format_str[index] != '%')
        {
            output[output_index++] = format_str[index];
            if (output_index == OUTPUT_BUFFER_SIZE)
                output_printer(output, &output_index);
            total_printed_chars++;
        }
        else
        {
            output_printer(output, &output_index);
            format_flags = get_flags(format_str, &index);
            field_width = get_width(format_str, &index, args);
            precision = get_precision(format_str, &index, args);
            size_specifier = get_size(format_str, &index);
            ++index;
            printed = handle_print(format_str, &index, args, output,
                                   format_flags, field_width, precision, size_specifier);
            if (printed == -1)
                return (-1);
            total_printed_chars += printed;
        }
    }

    output_printer(output, &output_index);

    va_end(args);

    return (total_printed_chars);
}

/**
 * output_printer - Outputs the stored characters if they exist.
 * @output: Array containing characters to be printed.
 * @output_index: Index pointing to the next character to be added.
 */
void output_printer(char output[], int *output_index)
{
    if (*output_index > 0)
        write(1, &output[0], *output_index);

    *output_index = 0;
}
