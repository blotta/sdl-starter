#include "game_utils.h"

void bits_to_pixels(
	uint32_t* pixels,
	const char* bits,
	uint32_t bytes_per_row,
	uint32_t row_count,
	uint8_t r, uint8_t g, uint8_t b)
{
    const uint8_t BITS_IN_BYTE = 8;

    uint32_t target_color =
		(r << 3 * BITS_IN_BYTE) |
		(g << 2 * BITS_IN_BYTE) |
		(b << 1 * BITS_IN_BYTE);

	for (uint32_t row = 0; row < row_count; row++)
	{
		for (uint32_t col = 0; col < BITS_IN_BYTE * bytes_per_row ; col++)
		{
			int bit_col = col % BITS_IN_BYTE;
			int current_byte = (row * bytes_per_row) + (col / BITS_IN_BYTE);

			uint32_t pixel = 0;

			if ((bits[current_byte] & (1 << (BITS_IN_BYTE - 1 - bit_col))) > 0)
			{
				pixel = target_color | 0xFF;
			}

			pixels[col + row * BITS_IN_BYTE * bytes_per_row] = pixel;

			// printf("%c", pixel > 0 ? '0' : '.');
		}
		// printf("\n");
	}
	// printf("\n");
}