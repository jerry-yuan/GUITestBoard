#include "stm32f10x_conf.h"
#include <usart.h>
#include <oled.h>
#include <w25x.h>
#include <SGUI_Text.h>
#include <SGUI_FontResource.h>

int main(void) {
	char pstTips[20]={0};
    SGUI_SCR_DEV screen;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART_Config();
    OLED_Initialize();
    W25X_Initialize();

    screen.stSize.iWidth=128;
    screen.stSize.iHeight=64;
    screen.fnClear=OLED_Clear;
    screen.fnGetPixel=OLED_GetPixel;
    screen.fnSetPixel=OLED_SetPixel;
    screen.fnSyncBuffer=OLED_Commit;

    SGUI_RECT rect= {0,0,128,12};
    SGUI_POINT point= {0,0};

    SGUI_Text_DrawText(&screen,"System Work Well!",SGUI_FONT_REF(FONT_12),&rect,&point,1);
    OLED_Commit();

    W25XJEDECId_t j;
    W25X_Read_JEDECId(&j);
    sprintf(pstTips,"id=0x%04X,manu=0x%04X",j.uiFlashId,j.uiManufacture);
    rect.iY += 12;
	SGUI_Text_DrawText(&screen,pstTips,SGUI_FONT_REF(FONT_12),&rect,&point,1);
	OLED_Commit();
    while(1) {
    }
}
void HardFault_Handler() {

    while(1);
}
