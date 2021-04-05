#include "stm32f10x_conf.h"
#include <usart.h>
#include <oled.h>
#include <RC522.h>
#include <SGUI_Text.h>
#include <SGUI_FontResource.h>

int main(void) {
	SGUI_SCR_DEV screen;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART_Config();
    OLED_Initialize();
    RC522_Initialize();
    screen.stSize.iWidth=128;
    screen.stSize.iHeight=64;
    screen.fnClear=OLED_Clear;
    screen.fnGetPixel=OLED_GetPixel;
    screen.fnSetPixel=OLED_SetPixel;
    screen.fnSyncBuffer=OLED_Commit;

    SGUI_RECT rect={0,0,128,12};
    SGUI_POINT point={0,0};

    SGUI_Text_DrawText(&screen,"System Work Well!",SGUI_FONT_REF(FONT_12),&rect,&point,1);
	OLED_Commit();
    while(1) {

    }
}
