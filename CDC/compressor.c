#include <stdio.h>

int main()
{
    int removed = 0, arr_size = 0;
    scanf("%d", &arr_size);
    unsigned char array[arr_size];

    int i;
    for (i = 0; i < arr_size-1; i++)
    {
        if (!array[i] && !array[i + 1])
        {
            printf("0x00,");
            int j;
            for (j = i + 1; j < arr_size && !array[j]; j++, removed++);


            removed += 2;
            printf("0x%02X,", j - i);
            i = j - 1;
            continue;
        }
        printf("0x%02X,", array[i]);
    }
    printf("0x%02X\nSize:%d\n", array[i], arr_size - removed);

}