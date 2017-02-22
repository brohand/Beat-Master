/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=4 -start=49 -palette=20 beatimg beatimg.bmp 
 * Time-stamp: Monday 11/09/2015, 15:08:41
 * 
 * Image Information
 * -----------------
 * beatimg.bmp 20@10
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef BEATIMG_H
#define BEATIMG_H

#define BEATIMG_PALETTE_OFFSET  49

extern const unsigned short beatimg_palette[11];
#define BEATIMG_PALETTE_SIZE 11

extern const unsigned short beatimg[100];
#define BEATIMG_SIZE 100
#define BEATIMG_WIDTH 20
#define BEATIMG_HEIGHT 10

#endif

