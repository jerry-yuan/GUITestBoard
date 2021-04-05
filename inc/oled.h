#ifndef OLED_H
#define OLED_H

#include <stm32f10x.h>
#include <SGUI_Common.h>
typedef enum{
	OLED_COMMAND=0,
	OLED_DISPLAY=1
} BufferType;

void OLED_Initialize();
void OLED_Clear();
void OLED_Commit();
SGUI_COLOR OLED_GetPixel(SGUI_INT x,SGUI_INT y);
void OLED_SetPixel(SGUI_INT x,SGUI_INT y,SGUI_COLOR color);


#endif
