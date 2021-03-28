#include "sys.h"
#include "usart.h"
#include "iic.h"
#include "mpu6050.h"
#include "delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "usart2.h"
#include "ctd_trans.h"

void USART2_Send_Byte(u8 data) {
	USART2->DR=data;
	while((USART2->SR&(1<<6))==0);
}

int main() {
	float pitch,roll,yaw;
	int len1,len2;
	int i;
	Stm32_Clock_Init(9);
	delay_init(72);
	//MPU6050_Init();
	uart_init(72,38400);
	USART2_Init(36,38400);

	while(1){
		if(USART2_RX_STA&0x8000){
			cTd_trans(&pitch,&roll,&yaw);
			printf("pitch:%f roll=%f yaw=%f\r\n",pitch,roll,yaw);
			USART2_RX_STA=0;
		}
		
	}
}

