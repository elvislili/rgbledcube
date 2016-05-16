
#ifndef _IR_NEC_H
#define _IR_NEC_H

#include "stm32f10x.h"
#include "LED.h"
#include "calculate.h"
#include "snake.h"

extern unsigned char NEC[4];		         									

void IR_ENC_Init(void);															


void IR_NEC(void);

void KeyHandle(void);															

#define  Step 300			     												

extern unsigned char IR_BT;														

#endif




