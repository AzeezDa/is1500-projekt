#include <stdio.h>

int main()
{
    int arr_size = 0;
    scanf("%d", &arr_size);
    unsigned char array[arr_size];
    int final_size = arr_size;
    
    int i;
    for (i = 0; i < arr_size; i++)
        scanf("%hhx,", &array[i]);
    
    for (i = 0; i < arr_size; i++)
    {
        if (!array[i])
        {
            printf("0x00,");
            int j;
            for (j = i + 1; j < arr_size && !array[j]; j++, final_size--);

            final_size += 1;
            printf("0x%02X,", j - i);
            i = j - 1;
            continue;
        }
        printf("0x%02X,", array[i]);
    }
    printf("\nSize:%d\n", final_size);

    return 0;
}