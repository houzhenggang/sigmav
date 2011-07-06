/*
    NRF24L01.H    NRF24L01�������� ����Mini2440ƽ̨
    ͷ�ļ� ���ݶ���
    Sigmax6      2011��3��3��18:51:32
*/

#ifndef NRF24L01_H
#define NRF24L01_H

//������������ ����ʹ����������
typedef unsigned int uint16;
typedef unsigned char uchar;

//�����豸����
#define DEVICE_NAME "nrf24l01"

//�������豸��
#define NRF24L01_MAJOR 241
#define NRF24L01_NINOR 0

/*  ƽ̨��ֲ�������������  */

// mini 2440 �� GPF0-5 ��Ӧ EINT0-5 6�Žӳ� CON6 */
/*
    GPF1/EINT1    --      CSN 
    GPF2/EINT2    --      CE
    GPF3/EINT3    --      MOSI
    GPF4/EINT4    --      SCK
    GPG9/EINT17    --      IRQ
    GPF10/EINT18    --      MISO
*/

//����NRF24L01���ӹܽ�   �ͷ����

#define SCK		S3C2410_GPF4
#define SCK_OUTP	S3C2410_GPF4_OUTP

#define MISO            S3C2410_GPG10
#define MISO_INP     S3C2410_GPG10_INP

#define IRQ                S3C2410_GPG9
#define IRQ_INP     S3C2410_GPG9_INP

#define MOSI			 S3C2410_GPF3
#define MOSI_OUTP S3C2410_GPF3_OUTP

#define CSN               S3C2410_GPF1
#define CSN_OUTP    S3C2410_GPF1_OUTP

#define CE				S3C2410_GPF2
#define CE_OUTP 		S3C2410_GPF2_OUTP

// ����ܽŲ������ߺ�
#define CE_OUT		s3c2410_gpio_cfgpin(CE,CE_OUTP)
#define CE_UP			s3c2410_gpio_pullup(CE,1)
#define CE_L              s3c2410_gpio_setpin(CE,0)
#define CE_H             s3c2410_gpio_setpin(CE,1)

#define SCK_OUT		s3c2410_gpio_cfgpin(SCK,SCK_OUTP)
#define SCK_UP			s3c2410_gpio_pullup(SCK,1)
#define SCK_L              s3c2410_gpio_setpin(SCK,0)
#define SCK_H             s3c2410_gpio_setpin(SCK,1)

#define MISO_IN   		s3c2410_gpio_cfgpin(MISO,MISO_INP)
#define MISO_UP			s3c2410_gpio_pullup(MISO,1)
#define MISO_STU        s3c2410_gpio_getpin(MISO)

#define IRQ_IN   	   s3c2410_gpio_cfgpin(IRQ,IRQ_INP)
#define IRQ_UP		   s3c2410_gpio_pullup(IRQ,1)
#define IRQ_STU          s3c2410_gpio_getpin(IRQ)
#define IRQ_H            s3c2410_gpio_setpin(IRQ,1)

#define MOSI_OUT		s3c2410_gpio_cfgpin(MOSI,MOSI_OUTP)
#define MOSI_UP			s3c2410_gpio_pullup(MOSI,1)
#define MOSI_L              s3c2410_gpio_setpin(MOSI,0)
#define MOSI_H             s3c2410_gpio_setpin(MOSI,1)

#define CSN_OUT		   s3c2410_gpio_cfgpin(CSN,CSN_OUTP)
#define CSN_UP			s3c2410_gpio_pullup(CSN,1)
#define CSN_L              s3c2410_gpio_setpin(CSN,0)
#define CSN_H             s3c2410_gpio_setpin(CSN,1)

/*  ƽ̨��ֲ�������������  */

//=======================================

/*  NRF24L01 �豸��������������        */

#define TX_ADR_WIDTH  5    //TX ��ַ����
#define RX_ADR_WIDTH  5   //RX ��ַ����

#define TX_PLOAD_WIDTH  4 // TX ����
#define RX_PLOAD_WIDTH  4 // RX ����

#define RX_DR  6
#define TX_DS  5 
#define MAX_RT 4

// SPI(nRF24L01) commands
#define READ_REG    0x00  // Define read command to register
#define WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

// SPI(nRF24L01) registers(addresses)
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address

//���͡����վ�̬��ַ��ʼ������
uchar const TX_ADDRESS[TX_ADR_WIDTH]=
{
	0x34,
	0x43,
	0x10,
	0x10,
	0x01
};
uchar const  RX_ADDRESS[RX_ADR_WIDTH]=
{
	0x34,
	0x43,
	0x10,
	0x10,
	0x01
};
/*  NRF24L01 �豸��������������        */

//===========================================

/*   ������������    */

uchar SPI_RW(uchar byte);        							 // ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01����һ�ֽ�
uchar SPI_RW_Reg(uchar reg, uchar value);    		 // д����value��reg�Ĵ���
uchar SPI_Read(uchar reg);        							 // ��reg�Ĵ�����һ�ֽ�
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes);      //  ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ�����ݻ����/���͵�ַ
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes);     // ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢��ͨ�����ݻ����/���͵�ַ
void nrf24l01_setRx();

uchar sta;                                                              //�洢�ڵ�״̬��Ϣ
int deviceCounter;                                               //��������������

//============================================

#endif
