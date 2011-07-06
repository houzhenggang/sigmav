#include<reg52.h>
#include <intrins.h>
#include <api.h>
#define uchar unsigned char
#define uint unsigned int 
#define NUMOFCARDS 10                  //ʵ���ҳ�Ա������


/***************************************************/
#define TX_ADR_WIDTH   5  // 5�ֽڿ�ȵķ���/���յ�ַ
#define TX_PLOAD_WIDTH 10 // ����ͨ����Ч���ݿ��
#define RX_PLOAD_WIDTH 1

uchar code TX_ADDRESS[TX_ADR_WIDTH] = {0x05,0x04,0x03,0x02,0x01};  // ����һ����̬���͵�ַ

uchar idata TX_BUF[TX_PLOAD_WIDTH];	//��¼�������Ŀ���---->  �����Ƹ�ʽ
uchar  RX_BUF[RX_PLOAD_WIDTH];
uchar flag1,flag2,flag3;
uchar bdata sta;
sbit  RX_DR	 = sta^6;
sbit  TX_DS	 = sta^5;
sbit  MAX_RT = sta^4;

sbit led = P0^7;           //ָʾ�ƣ�1 ��ʾ�ſ�

sbit button = P2^0;        //��ʵ��ʱ�Ŀ��ذ�ť�����º�Ϊ0, ��ʾ�ſ�
sbit DATA0=P3^2;   			//�ж�it0
sbit DATA1=P3^3;        	//�ж�it1
uchar count_num = 0;       //���ڼ���wiegand��26λ

/**************************************************/


long data card_num[NUMOFCARDS]=			//ʵ���ҳ�Ա����
{
8761673,//������ʦ   6
881801,//��|         7
9089737,//����       8
15334330,//�ƺ�      9
863152,//��ͭ��      10
15179581,//�Ŵ���    11
5635756,//��ΰ       12
15319555,//���Ʊ�    13
868189,//����        14
9126742,//������     15


};


long card_num_in = 0;        //�����Ķ������Ŀ���---->  ʮ���Ƹ�ʽ



int judge_card();         //�ж����뿨���Ƿ�Ϊʵ���ҳ�Ա
void delay_ms(uint x);
void init_51();
void check_count_num();
void check_button();
uchar Check_ACK(bit clear);
void init_io(void);
void RX_Mode(void);
void TX_Mode(uchar * BUF);
uchar SPI_RW(uchar byte);
uchar SPI_RW_Reg(uchar reg, uchar value);
uchar SPI_Read(uchar reg);
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes);
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes);


void main(void)   
{  
      
    init_51();
	init_io();
	RX_Mode();

 while(1)
 {
	flag1=flag2=flag3=0;
	check_count_num();
	check_button();
	if(count_num>9)
	{
		EX0=0;
		EX1=0;
		led=0;
		count_num=0;
		delay_ms(500);
		led=1;
		TX_Mode(TX_BUF);
		Check_ACK(1);	
		RX_Mode();
		EX0=1;
		EX1=1;
		
	}
	delay_ms(50);
	sta = SPI_Read(STATUS);	  // ��״̬�Ĵ���
	if(RX_DR)				  // �ж��Ƿ���ܵ�����
	{

		SPI_Read_Buf(RD_RX_PLOAD, RX_BUF, RX_PLOAD_WIDTH);  // ��RX FIFO��������
		flag3 = 1;
	}
	SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���RX_DS�жϱ�־
	if(flag3)
	{

		flag3=0;
		if(RX_BUF[0]==0x55)
		{
			EA=0;
			led=0;                            //����
			delay_ms(1000);
			led=1;                            //����
			IE0=IE1=0;
			count_num=0;
			EA=1;
		}
	}


 }
}
/**************************************************/
uchar Check_ACK(bit clear)
{
	while(IRQ);	
	sta = SPI_RW(NOP);                    // ����״̬�Ĵ���
	if(MAX_RT)
		if(clear)                         // �Ƿ����TX FIFO��û������ڸ�λMAX_RT�жϱ�־���ط�
			SPI_RW(FLUSH_TX);

	SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���TX_DS��MAX_RT�жϱ�־
	IRQ = 1;
	if(TX_DS)
		return(0x00);
	else
		return(0xff);
}
/**************************************************/

void init_51()
{
	led=1;				//��ʼ�����Ź�
	button = 1;
/******************�жϳ�ʼ��************************/
	EA=0;
	EX0=1;
	EX1=1;

	IT0=1;
	IT1=1;
	EA=1;
/**********************************************/
}

void check_count_num()
{
	/***************************��������*******************************/
   if(count_num>9)
   {	
   		EA=0;                       //�ر��ж��ܿ���
        EX0=0;						//�ر�INT0�ж�
        EX1=0;						//�ر�INT1�ж�
		flag2=1;
		flag1=0;
        judge_card();               //�����жϺ���
    	
		IE0 = IE1 = 0;              //����ж�����

		EX0=1;						//�����ж��ܿ���
        EX1=1;						//����INT0�ж�
	    EA=1;						//����INT1�ж�
   }
}

void check_button()
{
	/***************************��ť��ȥ*******************************/ 
 	if(button==0)
 	{
     	 EA=0;
	  	 led=1;
	 	 delay_ms(1000);
		 led=0;
    	 IE0 = IE1 = 0; 
		 count_num=0; 
		 EA=1;
		 button = 1;
		 flag1=1;
 	}
}

/****************************�����б���***********************************************/
int judge_card()
{ 
   
   	uint m;
	uint n;

	card_num_in=TX_BUF[1];
/******************************���������Τ����Ϊʮ���Ƹ�ʽ****************************/
	 for(m=2;m<9;m++)
	 { 
	   card_num_in = card_num_in*2 + TX_BUF[m]; 
	 }
/************************�ж�ʮ���ƿ����Ƿ�Ϊcard_num�����еĿ���*********************************************/
	 for(n=0;n<NUMOFCARDS;n++)
	 {
		 if(card_num_in == card_num[n])
		 {  
		    led=1;                            //����
			delay_ms(1000);
			led=0;                            //����
			flag1=1;                           //������Ѿ���
			return 0;
		 }
	 }

	 return 0;
}


void data0() interrupt 0
{
 EX0=0;
 TX_BUF[count_num]=0x55;
 count_num++;
 //delay_ms(150);
 EX0=1;
}  

void data1() interrupt 2
{
 EX1=0;
 TX_BUF[count_num]=0xaa;
 count_num++;
 //delay_ms(150);
 EX1=1;
} 


/**************************************************
������delay_ms()

������
    �ӳ�x����
/**************************************************/
void delay_ms(uint x)
{
    uint i, j;
    i = 0;
    for(i=0; i<x; i++)
    {
       j = 250;
       while(--j);
	   j = 250;
       while(--j);
    }
}
/**************************************************/

/**************************************************
����: init_io()

����:
    ��ʼ��IO
/**************************************************/
void init_io(void)
{
	CE  = 0;        // ����
	CSN = 1;        // SPI��ֹ
	SCK = 0;        // SPIʱ���õ�
	IRQ = 1;        // �жϸ�λ
}
/**************************************************/


/**************************************************
������SPI_RW()

������
    ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01
	����һ�ֽ�
/**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar i;
   	for(i=0; i<8; i++)          // ѭ��8��
   	{
   		MOSI = (byte & 0x80);   // byte���λ�����MOSI
   		byte <<= 1;             // ��һλ��λ�����λ
   		SCK = 1;                // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   		byte |= MISO;       	// ��MISO��byte���λ
   		SCK = 0;            	// SCK�õ�
   	}
    return(byte);           	// ���ض�����һ�ֽ�
}
/**************************************************/

/**************************************************
������SPI_RW_Reg()

������
    д����value��reg�Ĵ���
/**************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;
  	CSN = 0;                   // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
  	SPI_RW(value);             // Ȼ��д���ݵ��üĴ���
  	CSN = 1;                   // CSN���ߣ��������ݴ���
  	return(status);            // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Read()

������
    ��reg�Ĵ�����һ�ֽ�
/**************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	SPI_RW(reg);                // ѡ��Ĵ���
  	reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(reg_val);            // ���ؼĴ�������
}
/**************************************************/

/**************************************************
������SPI_Read_Buf()

������
    ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ��
	���ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Write_Buf()

������
    ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢
	��ͨ�����ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	SPI_RW(pBuf[i]);        // ����ֽ�д��nRF24L01
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������RX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ���ȴ����շ����豸�����ݰ�
/**************************************************/
void RX_Mode(void)
{
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
  	CE = 1;                                            // ����CE���������豸
}
/**************************************************/

/**************************************************
������TX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ����CE=1��������10us����
	130us���������䣬���ݷ��ͽ����󣬷���ģ���Զ�ת�����
	ģʽ�ȴ�Ӧ���źš�
/**************************************************/
void TX_Mode(uchar * BUF)
{
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
  	SPI_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);         // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	CE = 1;
}
/**************************************************/
 
