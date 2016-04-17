#include "HaD_Badge.h"
//Hint: look in HaD_Badge.h for function and constant definitions

// definitions
uint8_t boardX;
uint8_t boardY;
uint8_t board_len;
uint8_t ballX;
uint8_t ballY;
uint8_t movX;
uint8_t movY;

void begin() {
    // reset
    boardX = 4;
    boardY = 14;
    board_len = 3;
    ballX = 4;
    ballY = 9;
    movX = 1;
    movY = 1;

    for(uint8_t i = boardX; i < boardX+board_len; i++) {
        displayPixel(i, boardY, ON);
    }

    displayPixel(ballX, ballY, ON);
    displayLatch();
}

void erase_pixel(uint8_t tail_x, uint8_t tail_y) {
    //uses global variables to erase current ball
    displayPixel(tail_x, tail_y, OFF);
    displayLatch();
}

void move_left() {
    if (boardX > 0) {
        //only move if we're not already at the edge
        erase_pixel(boardX+board_len-1, boardY);
        --boardX;
        displayPixel(boardX, boardY, ON);
        displayLatch();
    }
}
void move_right() {
    if (boardX+board_len-1 < TOTPIXELX-1) {
        //only move if we're not already at the edge
        erase_pixel(boardX, boardY);
        ++boardX;
        displayPixel(boardX+board_len-1, boardY, ON);
        displayLatch();
    }
}

void move_ball() {
    if (ballY > 13) {
        displayClear();
        begin();
    }
    erase_pixel(ballX, ballY);
    if (ballX <= 0 || ballX >= TOTPIXELX-1) {
        movX *= -1;
    }
    if (ballY <= 0 || ballY >= TOTPIXELY-1) {
        movY *= -1;
    }
    if (ballY == 13) {
        if (ballX >= boardX && ballX < boardX+board_len) {
            movY *= -1;
        }
    }
    ballX += movX;
    ballY += movY;
    displayPixel(ballX, ballY, ON);
    displayLatch();
}

void animateBadge(void) {
    begin();
    
    uint32_t last_time = getTime();
    
    while(1) {
        if (getTime() > last_time+350) {
            last_time = getTime();
            move_ball();
        }
        //This shows how to get user input
        switch (getControl()) {
            case (ESCAPE):
                displayClose();
                return;
            case (LEFT):
                move_left();
                break;
            case (RIGHT):
                move_right();
                break;
	}
    }
}