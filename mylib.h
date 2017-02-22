#include "bg.h"
#include "beatimg.h"
#include "glamour.h"
#include "game_over.h"
#include "title.h"
#include "win.h"


typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[12288];


#define BUFFER0 (u16 *)0x6000000
#define BUFFER1 (u16 *)0x600A000
#define BUFFER1FLAG (1<<4)
#define PALETTE ((u16 *)0x5000000)

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))
#define COLOR(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)

#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512
extern int* KEYS;
#define ISDOWN(KEY) !((*KEYS) & KEY)

#define LEN(x)  ((sizeof(x)) / (sizeof((x)[0])))

/* DMA      NOTE!!! USES U32...don't forget to typedef it */

typedef struct 
{
    const volatile void *src;
    volatile void *dst;
    volatile u32 cnt;
} DMAREC;



#define DMA ((volatile DMAREC *)0x040000B0)

#define REG_DMA0SAD         *(u32*)0x40000B0  // source address
#define REG_DMA0DAD         *(u32*)0x40000B4  // destination address
#define REG_DMA0CNT         *(u32*)0x40000B8  // control register

/* DMA channel 1 register definitions */
#define REG_DMA1SAD         *(u32*)0x40000BC  // source address
#define REG_DMA1DAD         *(u32*)0x40000C0  // destination address
#define REG_DMA1CNT         *(u32*)0x40000C4  // control register

/* DMA channel 2 register definitions */
#define REG_DMA2SAD         *(u32*)0x40000C8  // source address
#define REG_DMA2DAD         *(u32*)0x40000CC  // destination address
#define REG_DMA2CNT         *(u32*)0x40000D0  // control register

/* DMA channel 3 register definitions */
#define REG_DMA3SAD         *(u32*)0x40000D4  // source address
#define REG_DMA3DAD         *(u32*)0x40000D8  // destination address
#define REG_DMA3CNT         *(u32*)0x40000DC  // control register

/* Defines */
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000

typedef struct
{
    int row;
    int col;
    int height;
    int width;
    u8 index;
    int isDead;

} BEAT;

typedef struct 
{
    int row;
    int col;
    int height;
    int width;

} MARKER;

typedef struct
{
    int health;
    int row;
    int col;
    int height;
    int width;
    
} HEALTH;


void setPixel(int x, int y, u16 color);
void  drawRect(int  x,  int  y,  int  width, int  height,  u16 color);
void drawRect4(int  x,  int  y,  int  width, int  height,  u8 index);
void  drawHollowRect(int  x,  int  y,  int  width,  int  height, u16 color);

void drawImage3(int x, int y, int width, int height, const unsigned short *image);


void waitforVBlank();
void drawImage3(int x, int y, int width, int height, const unsigned short *image);
void drawImage4(int x, int y, int width, int height, const unsigned short *image);
void drawImage4(int row, int col, int width, int height, const u16* image);
void drawFullScreen(const unsigned short bitmap[]);
void drawChar(int row, int col, char ch, u8 color);
void drawString(int row, int col, char *str, u8 color);
void FlipPage();
void fillScreen4(u8 index);
void spawnBeat(BEAT beat);
void spawnMarker(MARKER marker);
void drawHealth(HEALTH health);



