#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
//ALIENTEK Mini STM32�����巶������1
//�����ʵ��		   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{		 
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	     	//��ʱ��ʼ��
	LED_Init();		  	 	//��ʼ����LED���ӵ�Ӳ���ӿ�    
	while(1)
	{
		LED=0;
		delay_ms(3000);
		LED=1;
		delay_ms(3000);

	}	 
}

























