#include "helpers.h"

// Draw textures at a given pos
void draw(v2 pos, const texture *tex) 
{
    int x = pos._1, y = pos._2;
    
    int i, j;
    for(i = 0; i < tex->width; i++) 
    {
        int stride = 0, idx_max = 7;
        UBYTE col = tex->texture[i];
        for(j = 0; j < tex->height; j++)
        {
            if (j > idx_max)
            {   
                stride++;
                idx_max += 7;
                col = tex->texture[tex->width + i * stride];
            }
                
            if (col & 1)
                pixon(x + i, y + j);
            else
                pixoff(x + i, y + j);
            
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

/**
 * LAMPS 
 */

const UBYTE l_l1[2] = {0x01, 0x0f}; 
const UBYTE l_l2[4] = {0x03, 0x01, 0x1f}; 
const UBYTE l_l3[4] = {0x03, 0x03, 0x01, 0x3f}; 
const UBYTE l_r1[2] = {0x0f, 0x01}; 
const UBYTE l_r2[3] = {0x1f, 0x01, 0x03}; 
const UBYTE l_r3[4] = {0x3f, 0x01, 0x03, 0x03};


/**
 * BUILDINGS
*/

const UBYTE b1_f1[7] = {0x7f, 0x13, 0x7d, 0x7b, 0x7d, 0x73, 0x7f};

const UBYTE b1_f2[22] = {0xff, 0x41, 0x59, 0xc5, 0xc5, 0xd9, 0xc5, 0xc5, 0xd9, 0xc1, 0xff, 
                         0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};

/**
 * TREES
*/
const UBYTE t_f1[3] = {0x01, 0x06, 0x01}; 
const UBYTE t_f2[6] = {0x02, 0x05, 0x1e, 0x05, 0x02}; 
const UBYTE t_f3[6] = {0x02, 0x15, 0x7a, 0x7d, 0x0a, 0x05};

texture frame1 = {5, 2, f1_fw};
texture frame2 = {8, 4, f2_fw};
texture frame3 = {14, 6, f3_fw};
texture frame3_l = {14, 6, f3_l};
texture frame3_r = {14, 6, f3_r};
texture frame_car = {14, 8, car_texture};

texture lamp[6] = {{2, 4, l_l1}, {2, 4, l_r1}, 
                  {3, 5, l_l2}, {3, 5, l_r2},
                  {4, 6, l_l3}, {4, 6, l_r3}};

texture building_1 = {7, 7, b1_f1}; 
texture building_2 = {11, 10, b1_f2}; 
texture tree_f1 = {3, 3, t_f1};
texture tree_f2 = {5, 5, t_f2};
texture tree_f3 = {6, 7, t_f3};