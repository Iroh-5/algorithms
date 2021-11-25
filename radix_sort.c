#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
 * Radix sort algorithm implementation
 * All 32-bit numbers are considered 4-digit numbers with 8-bit digit
*/

// 11111111 11111111 11111111 11111111 
//
// 00000000 00000000 00000000 11111111 x & 0x000000FF
// 00000000 00000000 11111111 00000000 x & 0x0000FF00
// 00000000 11111111 00000000 00000000 x & 0x00FF0000
// 11111111 00000000 00000000 00000000 x & 0xFF000000

uint32_t get_digit(uint32_t x, int digit)
{
    static uint32_t mask[] = { 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };
    static uint32_t shift[] = { 0, 8, 16, 24 };

    return (x & mask[digit]) >> shift[digit];
}

void counting_sort(uint32_t* arr, int n, int digit)
{
    size_t cnt[256] = {0};
    for (int i = 0; i < n; ++i)
	cnt[get_digit(arr[i], digit)]++;

    for (int i = 1; i < 256; ++i)
	cnt[i] += cnt[i - 1];

    uint32_t tmp[n];
    for (int i = 0; i < n; ++i)
    {
	tmp[cnt[get_digit(arr[i], digit)] - 1] = arr[i];
	cnt[get_digit(arr[i], digit)]--;
    }

    for (int i = 0; i < n; ++i)
	arr[i] = tmp[i];
}

int main(void)
{
    uint32_t arr[] = { 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFC };
    counting_sort(arr, 4, 0);

    for (int i = 0; i < 4; ++i)
	printf("%X\n", arr[i]);

    return EXIT_SUCCESS;
}
