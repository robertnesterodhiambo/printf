#include "main.h"

void print_output(char output[], int *output_index);

/**
 * print_character - Outputs a single character
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_character(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    char character = va_arg(args_list, int);

    return handle_write_character(character, output_buffer, format_flags, field_width, precision, size_specifier);
}

/**
 * print_custom_string - Outputs a string
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_custom_string(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    char *input_string = va_arg(args_list, char *);

    UNUSED(format_flags);
    UNUSED(field_width);
    UNUSED(precision);
    UNUSED(size_specifier);
    if (input_string == NULL)
    {
        input_string = "(null)";
        if (precision >= 6)
            input_string = "      ";
    }

    int length = precision >= 0 ? strnlen(input_string, precision) : strlen(input_string);
    int padding = (field_width > length) ? field_width - length : 0;

    if (!(format_flags & F_MINUS))
        while (padding-- > 0)
            write(1, " ", 1);

    write(1, input_string, length);

    if (format_flags & F_MINUS)
        while (padding-- > 0)
            write(1, " ", 1);

    return (field_width > length) ? field_width : length;
}

/**
 * print_percent_sign - Outputs a percent sign
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_percent_sign(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    UNUSED(args_list);
    UNUSED(output_buffer);
    UNUSED(format_flags);
    UNUSED(field_width);
    UNUSED(precision);
    UNUSED(size_specifier);
    return write(1, "%%", 1);
}

/**
 * print_custom_int - Outputs an integer
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_custom_int(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    long int number = va_arg(args_list, long int);
    int is_negative = (number < 0);
    unsigned long int num = is_negative ? (unsigned long int)(-number) : (unsigned long int)number;

    char temp_buffer[OUTPUT_BUFFER_SIZE];
    int temp_index = OUTPUT_BUFFER_SIZE - 2;

    if (num == 0)
        temp_buffer[temp_index--] = '0';

    while (num > 0)
    {
        temp_buffer[temp_index--] = (num % 10) + '0';
        num /= 10;
    }

    int printed_chars = write_number(is_negative, temp_index + 1, temp_buffer, format_flags, field_width, precision, size_specifier);

    return printed_chars;
}

/**
 * print_custom_binary - Outputs an unsigned number in binary
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_custom_binary(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    unsigned int n = va_arg(args_list, unsigned int);
    unsigned int binary_array[32];
    int count = 0;

    for (int i = 0; i < 32; i++)
    {
        binary_array[i] = n & (1 << (31 - i)) ? '1' : '0';
    }

    int index = 0;
    while (index < 32 && binary_array[index] == '0')
        index++;

    int printed_chars = write(1, binary_array + index, 32 - index);

    return printed_chars;
}

