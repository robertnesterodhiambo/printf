#include "main.h"

void print_output(char output[], int *output_index);

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Outputs an unsigned number
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_unsigned(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    unsigned long int num = va_arg(args_list, unsigned long int);
    num = convert_size_unsgnd(num, size_specifier);

    if (num == 0)
        output_buffer[OUTPUT_BUFFER_SIZE - 2] = '0';

    output_buffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

    int temp_index = OUTPUT_BUFFER_SIZE - 2;
    while (num > 0)
    {
        output_buffer[temp_index--] = (num % 10) + '0';
        num /= 10;
    }

    temp_index++;

    return write_unsgnd(0, temp_index, output_buffer, format_flags, field_width, precision, size_specifier);
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Outputs an unsigned number in octal notation
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    unsigned long int num = va_arg(args_list, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(field_width);

    num = convert_size_unsgnd(num, size_specifier);

    if (num == 0)
        output_buffer[OUTPUT_BUFFER_SIZE - 2] = '0';

    output_buffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

    int temp_index = OUTPUT_BUFFER_SIZE - 2;
    while (num > 0)
    {
        output_buffer[temp_index--] = (num % 8) + '0';
        num /= 8;
    }

    if (format_flags & F_HASH && init_num != 0)
        output_buffer[temp_index--] = '0';

    temp_index++;

    return write_unsgnd(0, temp_index, output_buffer, format_flags, field_width, precision, size_specifier);
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Outputs an unsigned number in hexadecimal notation
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    return print_hexa(args_list, "0123456789abcdef", output_buffer,
        format_flags, 'x', field_width, precision, size_specifier);
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Outputs an unsigned number in upper hexadecimal notation
 * @args_list: List of arguments
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list args_list, char output_buffer[],
    int format_flags, int field_width, int precision, int size_specifier)
{
    return print_hexa(args_list, "0123456789ABCDEF", output_buffer,
        format_flags, 'X', field_width, precision, size_specifier);
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Outputs a hexadecimal number in lower or upper case
 * @args_list: List of arguments
 * @map_to: Array of values to map the number to
 * @output_buffer: Buffer array for handling output
 * @format_flags: Active formatting flags
 * @flag_ch: Flag character for '#' specifier
 * @field_width: Width specification
 * @precision: Precision specification
 * @size_specifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list args_list, char map_to[], char output_buffer[],
    int format_flags, char flag_ch, int field_width, int precision, int size_specifier)
{
    unsigned long int num = va_arg(args_list, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(field_width);

    num = convert_size_unsgnd(num, size_specifier);

    if (num == 0)
        output_buffer[OUTPUT_BUFFER_SIZE - 2] = '0';

    output_buffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

    int temp_index = OUTPUT_BUFFER_SIZE - 2;
    while (num > 0)
    {
        output_buffer[temp_index--] = map_to[num % 16];
        num /= 16;
    }

    if (format_flags & F_HASH && init_num != 0)
    {
        output_buffer[temp_index--] = flag_ch;
        output_buffer[temp_index--] = '0';
    }

    temp_index++;

    return write_unsgnd(0, temp_index, output_buffer, format_flags, field_width, precision, size_specifier);
}
