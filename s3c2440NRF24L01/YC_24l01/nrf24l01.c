/*
    NRF24L01.C    NRF24L01�������� ����YC2440ƽ̨
    Sigmax6      2011��3��3��18:51:32
*/

//*ϵͳ
#include <linux/init.h>
#include <linux/module.h>         
#include <linux/kernel.h> 
//-����
#include <linux/fs.h>                  //������struct inode �Ķ��壬MINOR��MAJOR��ͷ�ļ���
#include <linux/delay.h>            //ϵͳ�ṩ����ʱ����
#include <linux/miscdevice.h>  //������miscdevice�ṹ�Ķ��弰��صĲ���������
#include <asm/uaccess.h>       //������copy_to_user��copy_from_user���ں˷����û������ڴ��ַ�ĺ������塣
//!ƽ̨
#include <asm/arch/gpio.h>
#include <asm/arch/regs-gpio.h>    //ƽ̨��ص�GPIO�����������������
//=�Զ���
#include "nrf24l01.h"

//#define DEBUG 1
#define DEBUG2 1

//*LICENSE��ָ����ģ��ʹ�õ����֤
MODULE_LICENSE("Dual BSD/GPL");
//-������Ϣ
MODULE_AUTHOR("sigmax6@live.com");
//-ģ������
MODULE_DESCRIPTION("nrf24l01 driver for Mini2440");


//============================================================

/**************************************************
����:int io_nrf24l01_init(void)

����:
    ��ʼ��nrf24l01��IO�˿� ��ʼ���ɹ�����1
**************************************************/
int io_nrf24l01_init(void)
{
	//���������
    MISO_UP;             //MISO����
    IRQ_UP;
    CE_OUT;
    CSN_OUT;
    SCK_OUT;
    MOSI_OUT;
    MISO_IN;
    IRQ_IN;
    
    //��ʼ���˿�
    udelay(500); 		 //SPIʱ����ʱ

    CE_L;
    ndelay(60);
    CSN_H;
    ndelay(60);
    SCK_L;
    ndelay(60);
    IRQ_H;
    ndelay(60);

    nrf24l01_setRx();            //Set to Rx mode
/*    
    //24l01�Ĵ������ø�λ
    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);         // д���ص�ַ 
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);  // д���ն˵�ַ
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);                  //  Ƶ��0�Զ� ACKӦ������ 
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);        //  ������յ�ַֻ��Ƶ��0
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);         // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);                        //   �����ŵ�����Ϊ2.4GHZ��ѡ����Ƶͨ��0x40,�շ�����һ��
    SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);               // IRQ�շ�����ж���Ӧ��16λCRC ��������

    CE_H;
i*/
   // mdelay(1000);             //�ȴ��������
    
    return 1;
}

/**************************************************
������SPI_RW(uchar byte)

������
    ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01
	����һ�ֽ�
**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar i;
#ifdef DEBUG
       printk(">> SPI_RW byte to read is %x\n",byte);
#endif

   	for(i=0; i<8; i++)          // ѭ��8��
   	{
   		if (byte & 0x80)     // byte���λ�����MOSI
   		{
   			MOSI_H;            //������1

#ifdef DEBUG
    printk("MOSI_H\n");
#endif
   		}
   		else
   		{
   			MOSI_L;             //������0

#ifdef DEBUG
    printk("MOSI_L\n");
#endif
   		}
   		byte <<= 1;             // ��һλ��λ�����λ

                udelay(2);                  //Tdc min 2ns

   		SCK_H;                      // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����

#ifdef DEBUG
    printk("SCK_H\n");
#endif


   		byte |= MISO_STU;       	// ��MISO��byte���λ

   		udelay(4);                 //Tch min 40 ns

   		SCK_L;            	// SCK�õ�
#ifdef DEBUG
    printk("SCK_L\n");
#endif
   		udelay(2);
   	}


#ifdef DEBUG2
//    printk(">> SPI_RW return :%x\n",byte);
#endif
    return(byte);           	// ���ض�����һ�ֽ�

}

/**************************************************
������SPI_RW_Reg()

������
    д����value��reg�Ĵ���
**************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;

  	CSN_L;                      // CSN�õͣ���ʼ��������
#ifdef DEBUG
    printk("CSN_L\n");
#endif
  	//udelay(3);                 //Tcc min 2ns

  	status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
       // udelay(5);
        ndelay(20);
  	SPI_RW(value);             // Ȼ��д���ݵ��üĴ���

  	CSN_H;                   // CSN���ߣ��������ݴ���

#ifdef DEBUG
    printk("CSN_H\n");
#endif
  	udelay(10);                //Tcwh min 50ns

  	return(status);            // ����״̬�Ĵ���
}

/**************************************************
������SPI_Read()

������
    ��reg�Ĵ�����һ�ֽ�
**************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;

  	CSN_L;                    // CSN�õͣ���ʼ��������
#ifdef DEBUG
    printk("CSN_L\n");
#endif
  	udelay(3);

  	SPI_RW(reg);                // ѡ��Ĵ���
       // udelay(5);
        ndelay(20);
  	reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������

  	CSN_H;                    // CSN���ߣ��������ݴ���
#ifdef DEBUG
    printk("CSN_H\n");
#endif
  	udelay(10);

  	return(reg_val);            // ���ؼĴ�������
}

/**************************************************
������SPI_Read_Buf()

������
    ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ��
	���ݻ����/���͵�ַ
**************************************************/
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN_L;                    // CSN�õͣ���ʼ��������
#ifdef DEBUG
    printk("CSN_L\n");
#endif
  	udelay(3);

  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
#ifdef DEBUG
        printk("SPI_Read_Buf sta:%d:",status);
#endif
  	for(i=0; i<bytes; i++)
        {
        	pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
                ndelay(20);
          //      udelay(5);
        }

  	CSN_H;                    // CSN���ߣ��������ݴ���
#ifdef DEBUG
    printk("CSN_H\n");
#endif
  	udelay(10);

  	return(status);             // ����״̬�Ĵ���
}

/**************************************************
������SPI_Write_Buf()

������
    ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢
	��ͨ�����ݻ����/���͵�ַ
**************************************************/
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;

  	CSN_L;                                 // CSN�õͣ���ʼ��������

#ifdef DEBUG
    printk("CSN_L\n");
#endif
  	udelay(3);

  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
#ifdef DEBUG
        printk("SPI_Write_Buf sta: %d",status);
#endif 
  	for(i=0; i<bytes; i++)
       {
    	    SPI_RW(pBuf[i]);               // ����ֽ�д��nRF24L01
            ndelay(20);
//           udelay(5);
       }

  	CSN_H;                              // CSN���ߣ��������ݴ���
#ifdef DEBUG
    printk("CSN_H\n");
#endif
  	udelay(10);

  	return(status);                    // ����״̬�Ĵ���
}

/**************************************************
������nrf24l01_rxPacket(uchar * rx_buf)

������
    ��rx_buf ָ��Ļ�����λ�ð���RX_PLOAD_WIDTH������ݽ���
**************************************************/
int nrf24l01_rxPacket(uchar * rx_buf)
{
        int rx_result=0;

	sta=SPI_Read(STATUS);
#ifdef DEBUG
       printk("Statue is %x",sta);
#endif 

	if(sta & (1<<RX_DR) )           //�յ�����
    {
#ifdef DEBUG
       printk("Data received!\n");
#endif       
//    	    CE_L;
//    	    udelay(10);           
    	    SPI_Read_Buf(RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);  //�ӽڵ��ȡ���ݵ�RxBuffer
    	    rx_result = 1;
    }

    SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���RX_DS�жϱ�־

    return rx_result;

}

/**************************************************
������nrf24l01_txPacket(uchar * tx_buf)

������
    ��tx_buf ָ��Ļ�����λ�ð���TX_PLOAD_WIDTH������ݷ���
**************************************************/
void nrf24l01_txPacket(uchar * tx_buf)
{
	CE_L;
//	ndelay(60);
        udelay(2);

	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
  	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);         // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	udelay(6);
/*
   	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
   	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
    SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);              // װ������ 
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);            // IRQ�շ�����ж���Ӧ��16λCRC��������
*/
        CE_H; 
        udelay(20);            //�����
  }
  
/**************************************************
������nrf24l01_setRx()

������
    ���ýڵ��л�Ϊ����ģʽ
**************************************************/
void nrf24l01_setRx(void)
{
    CE_L;
#ifdef DEBUG
    printk("CE_L\n");
#endif
    udelay(2);
/*
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);         // д���ص�ַ 
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);     // д���ն˵�ַ
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);                        //  Ƶ��0�Զ� ACKӦ������ 
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);        //  ������յ�ַֻ��Ƶ��0
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);         // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
    SPI_RW_Reg(WRITE_REG + RF_CH, 40);                        //   �����ŵ�����Ϊ2.4GHZ��ѡ����Ƶͨ��0x40,�շ�����һ��
    SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);               // IRQ�շ�����ж���Ӧ��16λCRC ��������
*/
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ

#ifdef DEBUG
    printk("=========================================\n");
    printk("WRITE_REG + EN_AA : %x\n",SPI_Read(WRITE_REG + EN_AA));
	printk("WRITE_REG + EN_RXADDR : %x \n",SPI_Read(WRITE_REG + EN_RXADDR));
    printk("WRITE_REG + RF_CH : %x \n",SPI_Read(WRITE_REG + RF_CH));
	printk("WRITE_REG + RX_PW_P0 : %x \n",SPI_Read(WRITE_REG + RX_PW_P0));
	printk("WRITE_REG + RF_SETUP : %x \n",SPI_Read(WRITE_REG + RF_SETUP));
	printk("WRITE_REG + CONFIG : %x \n",SPI_Read(WRITE_REG + CONFIG));
  	//SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	//SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
  	//SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
  	//SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	//SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	//SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
 #endif
    udelay(6);
    CE_H;
#ifdef DEBUG
    printk("CE_H\n");
#endif
     
    udelay(130);
 


}
//==========================================================

/**************************************************
����������nrf24l01_write()

������
    д�豸����
**************************************************/
static ssize_t nrf24l01_write(struct file *filp, const char *buffer,size_t count, loff_t *ppos)
{
	uchar * TxBuf = 
	(uchar *)kmalloc(((count+TX_PLOAD_WIDTH-1)/TX_PLOAD_WIDTH)*TX_PLOAD_WIDTH * sizeof(uchar),0);                                                                                                            //���뻺������Ϊ���ͻ���
	if (copy_from_user(TxBuf,buffer,count))                           //���û��ռ临�Ʒ������� ����ɹ�����0
	{
		printk(DEVICE_NAME "Can't get user data!\n");              //��ʧ�� ������˳�
		kfree(TxBuf);
		return -EFAULT;
	}
	else
	{
		int countDevide = (count+TX_PLOAD_WIDTH-1)/TX_PLOAD_WIDTH;      
		uchar * TxBufPtr = TxBuf;
		//   count /TX_PLOAD_WIDTH����ȡ����Ϊ���ʹ��� ��֤count ��Ŀ����ȫ������
		while(countDevide)
		{
			nrf24l01_txPacket(TxBufPtr);
			SPI_RW_Reg(WRITE_REG+STATUS,0XFF); 
			TxBufPtr += TX_PLOAD_WIDTH;
			countDevide--;
		}
	}
	kfree(TxBuf);

        udelay(200);

	nrf24l01_setRx();                                     //������� �л��豸Ϊ����״̬

	return count;
}

/**************************************************
����������nrf24l01_read()

������
    ���豸����
**************************************************/
static ssize_t nrf24l01_read(struct file *filp, const char *buffer,size_t count, loff_t *ppos)
{

#ifdef DEBUG
	printk("================================================");
        printk("Reading ... \n");
        printk("The read count is %d \n",count);
       
#endif
    //    nrf24l01_setRx();

	uchar * RxBuf = 
	(uchar *)kmalloc(((count+RX_PLOAD_WIDTH-1)/RX_PLOAD_WIDTH)*RX_PLOAD_WIDTH * sizeof(uchar),0);                                                                                                            //���뻺������Ϊ���ջ���
	int countDevide = (count+RX_PLOAD_WIDTH-1)/RX_PLOAD_WIDTH;
	int countDevideTmp = countDevide;
#ifdef DEBUG
        printk("countDevide is %d \n",countDevide);
#endif
	int readCount = 0;
	uchar * RxBufPtr = RxBuf;
		//   count /TX_PLOAD_WIDTH����ȡ����Ϊ���ʹ��� ��֤count ��Ŀ����ȫ������
	while(countDevide)
	{
		    if(nrf24l01_rxPacket(RxBufPtr))          //����������
		    {  
			    RxBufPtr += RX_PLOAD_WIDTH;                   //�����λ ׼������������
				SPI_RW_Reg(WRITE_REG+STATUS,0XFF);            //�������״̬
			    readCount ++;                                 //��ȡ����������
			}
			countDevide--;
	}
	if (copy_to_user(buffer,RxBuf,count))                           //���û��ռ临�ƽ������� ����ɹ�����0
	{
		printk(DEVICE_NAME "Can't send data to user!\n");              //��ʧ�� ������˳�
		kfree(RxBuf);
		return -EFAULT;
	}      
	kfree(RxBuf);
#ifdef DEBUG
        printk("readCount is %d \n",readCount);
#endif

	if(readCount == countDevideTmp)
	{

		return count;
	}

	return readCount*RX_PLOAD_WIDTH;		

}

/**************************************************
����������nrf24l01_open()

������
    �����豸����
**************************************************/
static int nrf24l01_open(struct inode *node, struct file *file)
{
	int open_result = 0;
	if(deviceCounter == 1)
	{
			return -EBUSY;                                   //���豸�Ѿ��� �򱨴��˳�
	}
	open_result = io_nrf24l01_init();               //��ʼ���豸
	if(open_result == 0)                                  //��ʼ��ʧ��
	{
		printk(DEVICE_NAME "Unable to open!\n");  
		return -1;
	}
	else
	{
		deviceCounter ++;
		printk(DEVICE_NAME "Device opened!\n");
		return 0;
	}
}

/**************************************************
����������nrf24l01_release()

������
    �ͷ��豸����
**************************************************/
static int nrf24l01_release(struct inode *node, struct file *file)
{
  deviceCounter --;
  printk(DEVICE_NAME "Device released !\n");
  return 0;
}

/*           ���Ӹ�����������������    */

static struct file_operations nrf24l01_fops = {
  .owner = THIS_MODULE,
  .open = nrf24l01_open,
  .write = nrf24l01_write,
  .read = nrf24l01_read,
  .release = nrf24l01_release
};

static struct miscdevice nrf24l01_dev = {
  NRF24L01_MAJOR,
  DEVICE_NAME,
  &nrf24l01_fops
};
 
/**************************************************
����������nrf24l01_init()

������
    �豸������ʼ������
**************************************************/
static int __init nrf24l01_init(void)
{
	int ret = 0;
	printk(DEVICE_NAME "Initializing ...... \n");
//	ret = register_chrdev(NRF24L01_MAJOR,DEVICE_NAME,&nrf24l01_fops);
       ret = misc_register(&nrf24l01_dev);
/*        devfs_mk_cdev(
                      MKDEV(NRF24L01_NAJOR,NRF24L01_MINOR),
                      S_IFCHR|S_IRUSR|S_IWUSR|S_IRGRP,
                      DEVICE_NAME
                     );
*/
	mdelay(10);
	if(ret < 0)
	{
		printk(DEVICE_NAME "Can't register device \n");
		return ret;
	}
	else
	{
		printk(DEVICE_NAME "Register success \n");
		deviceCounter = 0;
		return 0;
	}
}

/**************************************************
����������nrf24l01_exit()

������
    �豸����ע������
**************************************************/
static void __exit nrf24l01_exit(void)
{
//	unregister_chrdev(NRF24L01_MAJOR,DEVICE_NAME);
//        devfs_remove(DEVICE_NAME);
        misc_deregister(&nrf24l01_dev);
	printk(DEVICE_NAME "Unregister success \n");
}

module_init(nrf24l01_init);
module_exit(nrf24l01_exit);
