// General Texture definition
typedef struct _Texture 
{
    v2 dimensions;
    // v2._1 = WIDTH, v2._2 = HEIGHT
    UBYTE *texture;
} Texture;

// Constructor for a Texture
Texture* new_texture(UBYTE *texture, v2 dimensions) 
{
	Texture *t = (Texture*)malloc(sizeof(Texture));
	if(t == NULL) {
		// uh-oh out of memoryyyyyyy
		return NULL;
	}
	t->texture = texture;
    t->dimensions._1 = dimensions._1;
    t->dimensions._2 = dimensions._2;
	return t;
}

// Draw textures at a given pos
void draw(v2 pos, Texture *tex) 
{
    // Check validity of coordinates
    if(pos._1  < 0 || pos._1  > 128 - tex->dimensions._1 || pos._2 < 0 || pos._2 > 31) return;
    int i, j;
    
    for(i = 0; i < tex->dimensions._1; i++) 
    {
        UBYTE col = tex->texture[i];
        for(j = 0; j < tex->dimensions._2; j++) 
        {
            if (col & 1)
                pixon(pos._1 + i, pos._2 + j);
            else
                pixoff(pos._1  + i, pos._2 + j);
            
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

UBYTE f1_fw[5] = {0x02, 0x01, 0x01, 0x01, 0x02};
UBYTE f2_fw[8] = {0x0c, 0x0a, 0x07, 0x05, 0x05, 0x07, 0x0a, 0x0c};
UBYTE f3_fw[14] = {0x18, 0x24, 0x34, 0x3e, 0x1d, 0x15, 0x15, 0x15, 0x15, 0x1d, 0x3e, 0x34, 0x24, 0x18};
UBYTE f3_l[14] = {0x34, 0x1e, 0x1d, 0x15, 0x15, 0x15, 0x1d, 0x17, 0x25, 0x3d, 0x1e, 0x1c, 0x1c, 0x38};
UBYTE f3_r[14] = {0x38, 0x1c, 0x1c, 0x1e, 0x3d, 0x25, 0x17, 0x1d, 0x15, 0x15, 0x15, 0x1d, 0x1e, 0x34};

/**
 * PLAYABLE CAR
 */
UBYTE car[14] = {0x70, 0xc8, 0xe8, 0xfe, 0x79, 0x49, 0x4b, 0x4b, 0x49, 0x79, 0xfe, 0xe8, 0xc8, 0x70};

void init_textures() 
{
    v2 dim = {5.0, 2.0};
    Texture *frame1 = new_texture(f1_fw, dim);
    dim = {8.0, 4.0};
    Texture *frame2 = new_texture(f1_fw, dim);
    dim = {14.0, 6.0};
    Texture *frame3 = new_texture(f1_fw, dim);
    Texture *frame3_l = new_texture(f1_fw, dim);
    Texture *frame3_r = new_texture(f1_fw, dim);
}