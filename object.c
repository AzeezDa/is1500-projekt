#include "helpers.h"

// Draw textures at a given pos
void draw(v2 pos, const texture *tex) 
{
    int x = pos._1, y = pos._2;

    if(x  < SCREEN_X_MIN || x  > SCREEN_X_MAX - tex->width || y < SCREEN_Y_MIN || y > SCREEN_Y_MAX) return;
    int i, j;
    for(i = 0; i < tex->width; i++) 
    {
        UBYTE col = tex->texture[i];
        for(j = 0; j < tex->height; j++)
        {
            if (col & 1)
                pixon(x + i, y + j);
            else
                pixoff(x  + i, y + j);
            
            col = col >> 1;
        } 
    }
}

/* ==========================================
 * |               TEXTURES                 |
 * ==========================================
 */

/**
 * NPC CAR
 */
const UBYTE f1_fw[5] = {0x02, 0x01, 0x01, 0x01, 0x02};
const UBYTE f2_fw[8] = {0x0c, 0x0a, 0x07, 0x05, 0x05, 0x07, 0x0a, 0x0c};
const UBYTE f3_fw[14] = {0x18, 0x24, 0x34, 0x3e, 0x1d, 0x15, 0x15, 0x15, 0x15, 0x1d, 0x3e, 0x34, 0x24, 0x18};
const UBYTE f3_l[14] = {0x34, 0x1e, 0x1d, 0x15, 0x15, 0x15, 0x1d, 0x17, 0x25, 0x3d, 0x1e, 0x1c, 0x1c, 0x38};
const UBYTE f3_r[14] = {0x38, 0x1c, 0x1c, 0x1e, 0x3d, 0x25, 0x17, 0x1d, 0x15, 0x15, 0x15, 0x1d, 0x1e, 0x34};

/**
 * PLAYABLE CAR
 */
const UBYTE car_texture[14] = {0x70, 0xc8, 0xe8, 0xfe, 0x79, 0x49, 0x4b, 0x4b, 0x49, 0x79, 0xfe, 0xe8, 0xc8, 0x70};

texture frame1 = {5, 2, f1_fw};
texture frame2 = {8, 4, f2_fw};
texture frame3 = {14, 6, f3_fw};
texture frame3_l = {14, 6, f3_l};
texture frame3_r = {14, 6, f3_r};
texture frame_car = {14, 8, car_texture};