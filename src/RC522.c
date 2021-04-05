#include <RC522.h>
#include <stdio.h>
/**
 *	RC522			STM32F103
 *	SDA		---->	PB12
 *	SCK		---->	PB13
 *	MOSI	---->	PB15
 *	MISO	---->	PB14
 *	IRQ		---->	PB6
 *	RST		---->	PA8
 */
#define RC522_PIN_IRQ	GPIO_Pin_6
#define RC522_PIN_RESET	GPIO_Pin_8
#define RC522_PIN_CS	GPIO_Pin_12
#define RC522_PIN_CLK	GPIO_Pin_13
#define RC522_PIN_MISO	GPIO_Pin_14
#define RC522_PIN_MOSI	GPIO_Pin_15

char RC522_Exchange(char send);
uint8_t RC522_ReadReg(uint8_t addr);

void RC522_Initialize(){
	/**
	 * 初始化GPIO
	 */
	// 打开GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	// 初始化GPIO
	GPIO_InitTypeDef GPIO;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin	= RC522_PIN_CS;
	GPIO_Init(GPIOB,&GPIO);

	GPIO_SetBits(GPIOB,RC522_PIN_CS);

	GPIO.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin	= RC522_PIN_RESET;
	GPIO_Init(GPIOA,&GPIO);

	GPIO.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO.GPIO_Pin	= RC522_PIN_CLK | RC522_PIN_MOSI | RC522_PIN_MISO;
	GPIO_Init(GPIOB,&GPIO);
	/**
	 * 初始化SPI
	 */
	// 打开SPI时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	// 初始化SPI
	SPI_InitTypeDef SPI;

	SPI.SPI_Direction			= SPI_Direction_2Lines_FullDuplex;
	SPI.SPI_Mode				= SPI_Mode_Master;
	SPI.SPI_DataSize			= SPI_DataSize_8b;
	SPI.SPI_CPOL				= SPI_CPOL_Low;
	SPI.SPI_CPHA				= SPI_CPHA_1Edge;
	SPI.SPI_NSS					= SPI_NSS_Soft;
	SPI.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_256;
	SPI.SPI_FirstBit			= SPI_FirstBit_MSB;
	SPI.SPI_CRCPolynomial		= 7;
	SPI_Init(SPI2,&SPI);
	SPI_NSSInternalSoftwareConfig(SPI2,ENABLE);
	SPI_Cmd(SPI2,ENABLE);

	/**
	 * 初始化DMA
	 * /
	// 初始化DMA1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_InitTypeDef DMA;
	// 初始化公用结构体
	DMA.DMA_PeripheralBaseAddr	= (uint32_t)&SPI2->DR;
	DMA.DMA_MemoryBaseAddr		= (uint32_t)0;
	//DMA.DMA_DIR					=
	DMA.DMA_BufferSize			= (uint32_t)0;
	DMA.DMA_PeripheralInc		= DMA_PeripheralInc_Disable;
	DMA.DMA_MemoryInc			= DMA_MemoryInc_Enable;
	DMA.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_Byte;
	DMA.DMA_MemoryDataSize		= DMA_MemoryDataSize_Byte;
	DMA.DMA_Mode				= DMA_Mode_Normal;
	DMA.DMA_Priority			= DMA_Priority_VeryHigh;
	DMA.DMA_M2M					= DMA_M2M_Disable;

	// 初始化DMA1_Channel4(RX)
	DMA_DeInit(DMA1_Channel4);
	DMA.DMA_DIR					= DMA_DIR_PeripheralSRC;
	DMA_Init(DMA1_Channel4,&DMA);

	// 初始化DMA1_Channel5(TX)
	DMA_DeInit(DMA1_Channel5);
	DMA.DMA_DIR					= DMA_DIR_PeripheralDST;
	DMA_Init(DMA1_Channel5,&DMA);

	// 使能SPI2通过DMA收发数据
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);*/
	/**
	 * 初始化RC522
	 */
	// 重置RC522
	GPIO_ResetBits(GPIOA,RC522_PIN_RESET);
	GPIO_SetBits(GPIOA,RC522_PIN_RESET);

	RC522_WriteReg(CommandReg,PCD_RESETPHASE);

	RC522_WriteReg(ModeReg,0x3D);            //和Mifare卡通讯，CRC初始值0x6363
    RC522_WriteReg(TReloadRegL,30);
    RC522_WriteReg(TReloadRegH,0);
    RC522_WriteReg(TModeReg,0x8D);
    RC522_WriteReg(TPrescalerReg,0x3E);
    RC522_WriteReg(TxAutoReg,0x40);

    RC522_SetAntennaState(DISABLE);
    RC522_SetAntennaState(ENABLE);

    // 设置工作模式为ISO14443_A
    RC522_ClearBitMask(Status2Reg,0x08)
    RC522_WriteReg(ModeReg,0x3D);//3F
	RC522_WriteReg(RxSelReg,0x86);//84
    RC522_WriteReg(RFCfgReg,0x7F);
    RC522_WriteReg(TReloadRegL,30);
    RC522_WriteReg(TReloadRegH,0);
    RC522_WriteReg(TModeReg,0x8D);
    RC522_WriteReg(TPrescalerReg,0x3E);
}
char RC522_Exchange(char send){
	// 等待上一次发送完成
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	// 发送数据
	SPI_I2S_SendData(SPI2,send);
	// 等待接收缓冲非空
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(SPI2);
}

uint8_t RC522_ReadReg(uint8_t addr){
	uint8_t data;
	addr = ((addr<<1)&0x7E) | 0x80;
	GPIO_ResetBits(GPIOB,RC522_PIN_CS);

	data=RC522_Exchange(addr);
	data=RC522_Exchange(0x00);

	GPIO_SetBits(GPIOB,RC522_PIN_CS);
	return data;
}
void RC522_WriteReg(uint8_t addr,uint8_t data){
	addr = ((addr<<1)&0x7E);
	GPIO_ResetBits(GPIOB,RC522_PIN_CS);

	RC522_Exchange(addr);
	RC522_Exchange(data);

	GPIO_SetBits(GPIOB,RC522_PIN_CS);
}

void RC522_SetBitMask(uint8_t reg,uint8_t mask){
	RC522_WriteReg(reg,RC522_ReadReg(reg) | mask);
}
void RC522_ClearBitMask(uint8_t reg,uint8_t mask){
	RC522_WriteReg(reg,RC522_ReadReg(reg)&(~mask));
}

void RC522_SetAntennaState(FunctionalState state){
	if(state==ENABLE){
		RC522_SetBitMask(TxControlReg, 0x03);
	}else{
		RC522_ClearBitMask(TxControlReg, 0x03);
	}
}
