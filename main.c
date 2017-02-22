
#include "mylib.h"
#include <stdlib.h>
#include "stdio.h"
#include "stdbool.h"

#define REG_DISPCTL *(u16 *)0x4000000
#define MODE_3 3
#define MODE_4 4
#define BG2_EN (1 << 10)
//int* KEYS = (int*)0x04000130;

int l_beatMap[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int a_beatMap[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0};
int b_beatMap[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
int r_beatMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0};
enum GBAState {     
	START,
	GAME,
	GAME_OVER,
    WIN
	// TODO add more states here!
};
int start();
int game();
int gameOver();
int Win();
void FlipPage();
int hitCheck(BEAT * beat, MARKER marker);
void initBeats(int row, BEAT * beats, int * beatMap, u32 length, int offset);
int hit;
int score;
int miss;
int main() {
	
	REG_DISPCTL = BG2_EN | MODE_4;
	enum GBAState state = START;
	
	while(1) {
        switch(state) {
        	case START:
                state = start();
        	    break;
        	case GAME:
                state = game();
        	    break;
        	case GAME_OVER:
                state = gameOver();
        	    break;
            case WIN:
                state = Win();
                break;
        };
	}
	return 0;
}

int start() {
    glamour_stop();
    while(1) {
        if(ISDOWN(KEY_START)) {
            return GAME;
        }
    DMA[3].src = title_palette;
    DMA[3].dst = PALETTE;
    DMA[3].cnt = DMA_ON | 256;
    drawFullScreen(title);

    waitforVBlank();
    FlipPage();
    }
    return 0;
}

int game() {
	//BEAT beat = {15, 100, 10, 20, 2, 0};
	//BEAT beat2 = {0, 100, 10, 20, 2, 0};
	u16 colors[] = {BLACK, GREY, RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, WHITE};
    
    for(int i = 247; i < 256; i++) {
        PALETTE[i] = colors[i - 247];
    }
	
	int uOffset = 4;
	BEAT l_beats[LEN(l_beatMap)];
	BEAT a_beats[LEN(a_beatMap)];
	BEAT b_beats[LEN(b_beatMap)];
	BEAT r_beats[LEN(r_beatMap)];
	MARKER l_marker = {140, 80, 10, 20};
	MARKER a_marker = {140, 100, 10, 20};
	MARKER b_marker = {140, 120, 10, 20};
	MARKER r_marker = {140, 140, 10, 20};
	initBeats(80, l_beats, l_beatMap, LEN(l_beatMap), uOffset);
	initBeats(100, a_beats, a_beatMap, LEN(a_beatMap), uOffset);
	initBeats(120, b_beats, b_beatMap, LEN(b_beatMap), uOffset);
	initBeats(140, r_beats, r_beatMap, LEN(r_beatMap), uOffset);
	

    glamour_play();
    int speed = 3;
    int incY = 1;
    score = 0;
    hit = 0;
    miss = 0;
    HEALTH bar = {10, 80, 160, 80, 10};
    int r_lastButtonPressed = 0;
    int b_lastButtonPressed = 0;
    int a_lastButtonPressed = 0;
    int l_lastButtonPressed = 0;
    //int hD = 0;
    //int begin = 0
	//Game Loop

    while(1) {
        if(!ISDOWN(KEY_R)) {
        	r_lastButtonPressed = 0;
        }
        if(!ISDOWN(KEY_B)) {
        	b_lastButtonPressed = 0;
        }
        if(!ISDOWN(KEY_A)) {
        	a_lastButtonPressed = 0;
        }
        if(!ISDOWN(KEY_L)) {
        	l_lastButtonPressed = 0;
        }
        if(ISDOWN(KEY_SELECT)) {
            return START;
        }

    	//fillScreen4(248); //Grey
    	DMA[3].src = bg_palette;
        DMA[3].dst = PALETTE;
        DMA[3].cnt = DMA_ON | 49;
        DMA[3].src = beatimg_palette;
        DMA[3].dst = &PALETTE[49];
        DMA[3].cnt = DMA_ON | 11;
        
    	drawImage4(0, 0, 240, 160, bg);
        
    	for(u32 j = 0; j < LEN(r_beats); j++) {
            if(l_beats[j].row < 160) {
    	    spawnBeat(l_beats[j]);
    	} else  {
    		if(l_beats[j].isDead == 0) {
    		bar.health--;
    		bar.row += 8;
    		bar.height -= 8;
    		l_beats[j].isDead = 1;
            miss++;
    	    }
    	}
    	    if(a_beats[j].row < 160) {
    		spawnBeat(a_beats[j]);
    	} else {
    		if(a_beats[j].isDead == 0) {
    		bar.health--;
    		bar.row += 8;
    		bar.height -= 8;
    		a_beats[j].isDead = 1;
            miss++;
    	    }
    	}
    	    if(b_beats[j].row < 160) {
    		spawnBeat(b_beats[j]);
    	} else {
    		if(b_beats[j].isDead == 0) {
    		bar.health--;
    		bar.row += 8;
    		bar.height -= 8;
    		b_beats[j].isDead = 1;
            miss++;
    	    }
    	}
    	    if(r_beats[j].row < 160) {
    		spawnBeat(r_beats[j]);
    	} else {
    		if(r_beats[j].isDead == 0) {
    		bar.health--;
    		bar.row += 8;
    		bar.height -= 8;
    		r_beats[j].isDead = 1;
            miss++;
    	    }
    	}
    		l_beats[j].row += speed*incY;
    		a_beats[j].row += speed*incY;
    		b_beats[j].row += speed*incY;
    		r_beats[j].row += speed*incY;


    	}
    	//spawnBeat(beat); //red rect
        
    	spawnMarker(l_marker);
    	spawnMarker(a_marker);
    	spawnMarker(b_marker);
    	spawnMarker(r_marker);
    	u32 k;
    	if(ISDOWN(KEY_R) && r_lastButtonPressed == 0) {
        for(k = 0; k < LEN(l_beats); k++) {
    	  //Expand to all buttons
    		score += hitCheck(r_beats + k, r_marker);

    		r_lastButtonPressed = 1;
    		
    	}
    }
        
    	if(ISDOWN(KEY_B) && b_lastButtonPressed == 0) {
        for( k = 0; k < LEN(l_beats); k++) {
    	  //Expand to all buttons
    		score += hitCheck(b_beats + k, b_marker);
    		b_lastButtonPressed = 1;
    		
    	}
    }
        
    	if(ISDOWN(KEY_A) && a_lastButtonPressed == 0) {
        for( k = 0; k < LEN(l_beats); k++) {
    	  //Expand to all buttons
    		score += hitCheck(a_beats + k, a_marker);
    		a_lastButtonPressed = 1;
    		
    	}
    }
        
    	if(ISDOWN(KEY_L) && l_lastButtonPressed == 0) {
        for( k = 0; k < LEN(l_beats); k++) {
    	  //Expand to all buttons
    		score += hitCheck(l_beats + k, l_marker);
    		l_lastButtonPressed = 1;
    		
    	}
    }

        if(bar.health <= 0) {
            glamour_stop();
        	return GAME_OVER;
        }
        MARKER marker = r_marker;
        u32 term = LEN(r_beatMap) - 1;//LEN(r_beats) - 1;
        if(r_beats[term].row + r_beats[term].height - 1 > marker.row &&
            marker.row + marker.height - 1 > r_beats[term].row &&
            r_beats[term].col + r_beats[term].width - 1 > marker.col &&
            marker.col + marker.width - 1 > r_beats[term].col) {
                glamour_stop();
                return WIN;
            
        }
        char str[10];
        char scoreBuff[6];
        sprintf(scoreBuff, "Score: ");
        sprintf(str, "%d", score);
        //drawRect4(0, 95, 10, 145, 255);
        drawString(0, 165, scoreBuff, 255);
        drawString(0, 215, str, 255);
    	drawHealth(bar);
    	waitforVBlank();
    	FlipPage();
        

    }
    return 0;
}

int gameOver() {
    int frame = 0;
    while(1) {
        if(ISDOWN(KEY_SELECT)) {
            return START;
        }
    DMA[3].src = game_over_palette;
    DMA[3].dst = PALETTE;
    DMA[3].cnt = DMA_ON | 102;
    drawFullScreen(game_over_frames[frame]);
    char str[20];
    char words[20];
    sprintf(str, "Words from a Beat Master");
    sprintf(words, "That was awful...");
    drawString(16, 57, str, 247); 
    drawString(62, 118, words, 255);
    frame++;
    if(frame > 7) {
        frame = 0;
    }
    waitforVBlank();
    FlipPage();

}

    return 0;
}

int Win() {
    while(1) {
        if(ISDOWN(KEY_SELECT)) {
            return START;
        }
    DMA[3].src = win_palette;
    DMA[3].dst = PALETTE;
    DMA[3].cnt = DMA_ON | 52;
    PALETTE[52] = WHITE;
    drawFullScreen(win);
    char hitB[20];
    char missB[20];
    char scoreB[20];
    sprintf(hitB, "Hit: %d", hit);
    sprintf(missB, "Miss: %d", miss);
    sprintf(scoreB, "Score: %d", score);
    drawString(72, 14, hitB, 52);
    drawString(82, 14, missB, 52);
    drawString(92, 14, scoreB, 52);
    waitforVBlank();
    FlipPage();
    }
    return 0;
}

void FlipPage()
{
    if(REG_DISPCTL & BUFFER1FLAG)
    {
        // We were display BUFFER1
        REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
        videoBuffer = BUFFER1;
    }
    else
    {
        REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
        videoBuffer = BUFFER0;
    }
}

int hitCheck(BEAT * beat, MARKER marker) {
	if((*beat).row + (*beat).height - 1 > marker.row &&
            marker.row + marker.height - 1 > (*beat).row &&
            (*beat).col + (*beat).width - 1 > marker.col &&
            marker.col + marker.width - 1 > (*beat).col) {
		int percentHit = ((*beat).row + (*beat).height - 1 - marker.row);// / marker.height;
	    (*beat).isDead = 1;
        hit++;

        
        for(int i = 10; i < 101; i += 10) {
        	if(percentHit < i) {
        		return i;
        	}
        }
	    
	    //playMusic();
        

        return percentHit;  //Percentage hit
	}
	return 0;
}

void initBeats(int col, BEAT * beats, int * beatMap, u32 length, int offset) {
	for(u32 i = 0; i < length; i++) {
		if(i == 0) {
			if(beatMap[i] == 1) {
				BEAT newBeat = {51, col, 10, 20, 249, 0};
				beats[i] = newBeat;
			} else {
				BEAT newBeat = {51, col, 10, 20, 249, 1};
				beats[i] = newBeat;
			}
		} else {
		if(beatMap[i] == 1) {
			BEAT newBeat = {beats[i - 1].row - offset*beats[i-1].height - 1 - 35, col, 10, 20, 249, 0};
			beats[i] = newBeat;
		} else {
			BEAT newBeat = {beats[i - 1].row - offset*beats[i-1].height - 1 - 35, col, 10, 20, 249, 1};
			beats[i] = newBeat;
		}
	}
	}
}

