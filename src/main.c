#include "stm32f10x_conf.h"
#include <usart.h>
#include <oled.h>
#include <w25x.h>
#include <SGUI_Text.h>
#include <SGUI_FontResource.h>
#include <fatfs/ff.h>
char readBuff[8192]={0};
int main(void) {
	char pstTips[20]={0};
    SGUI_SCR_DEV screen;

    uint8_t isDoErase = 0;

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
	rect.iY += 12;
	if(isDoErase){
		SGUI_Basic_DrawRectangle(&screen,rect.iX,rect.iY,rect.iWidth,rect.iHeight,0x0,0x0);
		SGUI_Text_DrawText(&screen,"Erasing Flash...",SGUI_FONT_REF(FONT_12),&rect,&point,1);
		OLED_Commit();
		W25X_Erase_Chip();
		W25X_Wait_Busy();
	}
	FATFS fs;
	FRESULT result;


	result = f_mount(&fs,"0:",1);
	if(result==FR_NO_FILESYSTEM){

		SGUI_Basic_DrawRectangle(&screen,rect.iX,rect.iY,rect.iWidth,rect.iHeight,0x0,0x0);
		SGUI_Text_DrawText(&screen,"No FS Formatting...",SGUI_FONT_REF(FONT_12),&rect,&point,1);
		OLED_Commit();

		result = f_mkfs("0:",0,readBuff,sizeof(readBuff));
		sprintf(pstTips,"RES=0x%02X",result);

		SGUI_Basic_DrawRectangle(&screen,rect.iX,rect.iY,rect.iWidth,rect.iHeight,0x0,0x0);
		SGUI_Text_DrawText(&screen,pstTips,SGUI_FONT_REF(FONT_12),&rect,&point,1);
		OLED_Commit();

		result = f_mount(&fs,"0:",1);
	}

	FIL file;
	uint32_t num;
	/*result=f_open(&file,"0:/test.txt",FA_CREATE_ALWAYS| FA_WRITE);
	printf("Result=%d\n",result);
	result=f_write(&file,"Hello World!\n",13,&num);
	printf("result=%d,num=%d\n",result,num);
	f_close(&file);*/


	result=f_open(&file,"0:/test.txt", FA_READ);
	printf("Result=%d\n",result);
	result=f_read(&file,readBuff,13,&num);
	printf("result=%d,num=%d\n",result,num);
	printf("file content:%s\n",readBuff);
	f_close(&file);




    while(1) {
    }
}
void HardFault_Handler() {

    while(1);
}
