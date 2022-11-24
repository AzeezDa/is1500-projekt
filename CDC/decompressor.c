#include <stdio.h>

int main()
{
    int arr_size, i, zeroes;
    scanf("%d", &arr_size);
    unsigned char array[arr_size];

    for (i = 0; i < arr_size; i++)
        scanf("%hhx,", &array[i]);

    int count = 0;
    for (i = 0; i < arr_size; i++)
    {
        if (array[i] == 0x00)
        {
            zeroes = array[++i];
            if (zeroes == 0xFF)
                zeroes += array[++i] + 1;

            for (; zeroes > 0; zeroes--, count++)
                printf("0x00,");

            continue;
        }
        printf("0x%02X,", array[i]);
        count++;
    }
    printf("\n%d\n", count);
    return 0;
}