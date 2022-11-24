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
            int zidx, zcount;
            for (zidx = i + 1, zcount = 1; zidx < arr_size && !array[zidx]; zidx++, final_size--, zcount++)
            {
                if (zcount > 255)
                {
                    zcount = 0;
                    final_size++;
                    printf("0xFF,");
                }
            }

            final_size++;
            printf("0x%02X,", zcount);
            i = zidx - 1;
            continue;
        }
        printf("0x%02X,", array[i]);
    }
    printf("\nSize:%d\n", final_size);

    return 0;
}