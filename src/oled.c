#include<oled.h>

#define OLED_PIN_DC		GPIO_Pin_2
#define OLED_PIN_RES	GPIO_Pin_3
#define OLED_PIN_CS		GPIO_Pin_4
#define OLED_PIN_CLK	GPIO_Pin_5
#define OLED_PIN_MOSI	GPIO_Pin_7

void OLED_SendBuffer(BufferType type,const uint8_t* buffer,uint32_t length);
uint8_t OLED_FrameBuffer[1024]={0};
const uint8_t oledInitializeCommands[]={
	0xAE,		// 关闭显示
	0x00,0x01,	// 设置列地址
	0x40,		// 设置行地址
	0x81,		// 设置对比度
	0xCF,		// 设置输出亮度
	0xA1,		// 设置左右反置
	0xC8,		// 设置上下反置
	0xA6,		// 设置正常输出(0xA6:正常 0xA7:反向)
	0xA8,0x3f,	// 设置扫描行为从0~64
	0xD3,0x00,	// 设置显示偏移为0
	0xD5,0x80,	// 设置刷新频率为100FPS
	0xD9,0xF1,	// 设置预充电阈值
	0xDA,0x12,	// 设置引脚定义
	0xDB,0x40,	// 设置VCOMH输出
	0x20,0x00,	// 设置页内存寻址模式为Horizontal mode
	0x8D,0x14,	// 设置电荷泵启用
	0xA4,		// 关闭全局显示
	0xA6,		// 关闭反向显示
	0xAF		// 开启OLED显示
};

void OLED_Initialize() {
	//初始化GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	//初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = OLED_PIN_CLK | OLED_PIN_MOSI| OLED_PIN_CS;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_PIN_DC | OLED_PIN_RES;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//初始化SPI1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	// 初始化SPI1
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_SSOutputCmd(SPI1,ENABLE);
	// 使能SPI1
	SPI_Cmd(SPI1,ENABLE);

	// 初始化DMA1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	// 初始化DMA1
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)0;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = 0;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel3,&DMA_InitStructure);

    // 启用SPI1的DMA
    SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);

	// 初始化屏幕
	GPIO_ResetBits(GPIOA,OLED_PIN_RES);
	GPIO_SetBits(GPIOA,OLED_PIN_RES);
	OLED_SendBuffer(OLED_COMMAND,oledInitializeCommands,sizeof(oledInitializeCommands));

	OLED_SendBuffer(OLED_DISPLAY,OLED_FrameBuffer,sizeof(OLED_FrameBuffer));
}

void OLED_SendBuffer(BufferType type,const uint8_t* buffer,uint32_t length){
	// 调整DC线电平
	GPIO_WriteBit(GPIOA,OLED_PIN_DC,type);

	// 清除中断
	DMA_ClearITPendingBit(DMA1_IT_GL3);
	DMA_ClearFlag(DMA1_FLAG_GL3);

	// 设置DMA参数
	DMA1_Channel3->CNDTR	= (uint32_t)length;
	DMA1_Channel3->CMAR		= (uint32_t)buffer;

	//启动DMA
	DMA_Cmd(DMA1_Channel3,ENABLE);

	//等待结束
	while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET){
	}

	// 关掉DMA
	DMA_Cmd(DMA1_Channel3,DISABLE);
}

void OLED_Clear(){
	memset(OLED_FrameBuffer,0,sizeof(OLED_FrameBuffer));
}

void OLED_Commit(){
	OLED_SendBuffer(OLED_DISPLAY,OLED_FrameBuffer,sizeof(OLED_FrameBuffer));
}

SGUI_COLOR OLED_GetPixel(SGUI_INT x,SGUI_INT y){
	return OLED_FrameBuffer[y/8*128+x]>>(y%8)&0x1;
}
void OLED_SetPixel(SGUI_INT x,SGUI_INT y,SGUI_COLOR color){
	if(color)
		OLED_FrameBuffer[y/8*128+x] |= 0x1<<(y%8);
	else
		OLED_FrameBuffer[y/8*128+x] &= ~(0x1<<(y%8));
}
