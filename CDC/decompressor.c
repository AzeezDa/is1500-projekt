#include <stdio.h>

int main()
{
    int arr_size, i;
    scanf("%d", &arr_size);
    unsigned char array[arr_size];

    for (i = 0; i < arr_size; i++)
        scanf("%hhx,", &array[i]);

    for (i = 0; i < arr_size; i++)
    {
        if (array[i] == 0x00)
        {
            for (int zeroes = array[++i]; zeroes > 0; zeroes--) {
                printf("0x00,");
            }

            continue;
        }
        printf("0x%02X,", array[i]);
    }
    return 0;
}