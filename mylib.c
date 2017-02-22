#include "mylib.h"
u16* videoBuffer = (u16*) 0x6000000;
 int* KEYS = (int*)0x04000130;
 
// A function to set pixel (r, c) to the color passed in.
void setPixel(int x, int y, u16 color){
// @todo implement :)
    videoBuffer[y*240 + x] = color;
}

void setPixel4(int row, int col, u8 index)
{
    
    int whichShort = (row*240+col)/2;

    if(col&1)
    {
        // Odd column must insert index into left side

        videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
    }
    else
    {
        // Even column
        videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | index;
    }
}

// A function to draw a FILLED rectangle starting at (r, c)
void  drawRect(int  x,  int  y,  int  width, int  height,  u16 color){
// @todo implement :)

    for(int row = 0; row < height; row++) {
	    for(int col = 0; col < width; col++) {
		    videoBuffer[(y + row)*240 + (x + col)] = color;

	    }
    }
}

void drawRect4(int row, int col, int height, int width, u8 index) {
    volatile u16 color = (index<<8) | index;
    int r;
    for(r=0; r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240) / 2;
        DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | (width/2); 

        
    }
    /*int r,c;
    for(r=0; r<height; r++)
    {
        for(c=0; c<width; c++)
        {
            setPixel4(row+r, col+c, index);
        }
    }*/
}

// A function to draw  HOLLOW rectangle starting at (r,c)
// NOTE: It has to run in O(w+h) time.
void  drawHollowRect(int  x,  int  y,  int  width,  int  height, u16 color){
// @todo implement :)

    for(int row = 0; row < height; row++) {
	    videoBuffer[(y + row)*240 + (x)] = color;
	    videoBuffer[(y + row)*240 + (x + width - 1)] = color;
    }

    for(int col = 0; col < width; col++) {

        videoBuffer[(y)*240 + (x + col)] = color;
	    videoBuffer[(y + height - 1)*240 + (x + col)] = color;
    }

}

void drawHollowRect4(int x,  int y,  int  width,  int  height, u8 index) {

    for(int row = 0; row < height; row++) {
        //videoBuffer[(y + row)*240 + (x)] = color;
        setPixel4(row+y, x, index);
        //videoBuffer[(y + row)*240 + (x + width - 1)] = color;
        setPixel4(row + y, x + width - 1, index);
    }

    for(int col = 0; col < width; col++) {

        //videoBuffer[(y)*240 + (x + col)] = color;
        setPixel4(y, x + col, index);
        //videoBuffer[(y + height - 1)*240 + (x + col)] = color;
        setPixel4(y + height - 1, x + col, index);
    }
}






void waitforVBlank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);

}



void drawImage3(int x, int y, int width, int height, const unsigned short *image) {

	// TODO Draw the image with the top left corner at (x,y).
	// Recall that the GBA screen is 240 pixels wide, and 160 tall.
	// The videoBuffer is a 1-dimensional array of these pixels.
	// For example, to set pixel (37,21) to white:
	//   videoBuffer[21 * 240 + 37] = 0x7FFF;
    int j = 0;
    for(int row = 0; row < height; row++) {
	    for(int col = 0; col < width; col++) {
		    videoBuffer[(y + row)*240 + (x + col)] = image[j];
		    j++;

	    }
    }




}

void drawImage4(int row, int col, int width, int height, const u16* image) {
    for(int r = 0; r < height; r++) {
        DMA[3].src = image + OFFSET(r, 0, width) / 2;
        DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240) / 2;
        DMA[3].cnt = width / 2 | DMA_ON;
    }
}

void drawFullScreen(const unsigned short bitmap[])
{   
    DMA[3].src = bitmap;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = DMA_ON | 19200;    
}



void drawChar(int row, int col, char ch, u8 color)
{
    int r,c;
    for(r=0; r<8; r++)
    {
        for(c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c,6)+ch*48])
            {
                setPixel4(row+r, col+c, color);
            }
        }
    }
}

void drawString(int row, int col, char *str, u8 color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}



void fillScreen4(u8 index)
{   
    volatile u16 color = (index<<8) | index;
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | 19200; 
}

void spawnBeat(BEAT beat) {
    if(beat.isDead == 0 && beat.row >= 0 /*&& beat.row < 150*/) {
    //drawRect4(beat.row, beat.col, beat.height, beat.width, beat.index);
    drawImage4(beat.row, beat.col, beat.width, beat.height, beatimg);
    }
}

void spawnMarker(MARKER marker) {
    drawHollowRect4(marker.col, marker.row, marker.width, marker.height, 255);
}

void drawHealth(HEALTH health) {
    drawRect4(health.row, health.col, health.height, health.width, 250);
}


