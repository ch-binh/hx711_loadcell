#include "hal_utils.h"

void hal_utils_float_to_str(float value, char *buffer, int decimal_places)
{
    if (decimal_places < 0)
        decimal_places = 0;

    // Handle negative values
    int is_negative = (value < 0);
    if (is_negative)
    {
        value = -value;
        *buffer++ = '-'; // Add '-' sign and move buffer pointer
    }

    // Apply rounding correction to prevent floating-point drift
    float rounding_offset = 0.5;
    for (int i = 0; i < decimal_places; i++)
    {
        rounding_offset /= 10.0f;
    }
    value += rounding_offset; // This ensures correct rounding

    // Extract integer and decimal parts
    int integer_part = (int)value;
    float decimal_part = value - (float)integer_part;

    // Convert integer part to string
    int pos = 0;
    do
    {
        buffer[pos++] = '0' + (integer_part % 10);
        integer_part /= 10;
    } while (integer_part > 0);

    // Reverse integer part
    for (int i = 0, j = pos - 1; i < j; i++, j--)
    {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Add decimal point
    if (decimal_places > 0)
    {
        buffer[pos++] = '.';
    }

    // Convert decimal part
    for (int i = 0; i < decimal_places; i++)
    {
        decimal_part *= 10;
        int digit = (int)decimal_part;
        buffer[pos++] = '0' + digit;    
        decimal_part -= digit;
    }

    // Null-terminate string
    buffer[pos] = '\0';
}