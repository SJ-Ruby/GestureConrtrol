#include "sys.h"
#include "usart.h"
#include "iic.h"
#include "mpu6050.h"
#include "delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "usart2.h"
#include "string.h"

void MPU6050_Display(void)
{
    /* 打印 x, y, z 轴加速度 */
    printf("ACCEL_X: %d\t", MPU6050_Get_Data(ACCEL_XOUT_H));
    printf("ACCEL_Y: %d\t", MPU6050_Get_Data(ACCEL_YOUT_H));
    printf("ACCEL_Z: %d\t", MPU6050_Get_Data(ACCEL_ZOUT_H));
    
    /* 打印温度，需要根据手册的公式换算为摄氏度 */
    printf("TEMP: %0.2f\t", MPU6050_Get_Data(TEMP_OUT_H) / 340.0 + 36.53);
    
    /* 打印 x, y, z 轴角速度 */
    printf("GYRO_X: %d\t", MPU6050_Get_Data(GYRO_XOUT_H));
    printf("GYRO_Y: %d\t", MPU6050_Get_Data(GYRO_YOUT_H));
    printf("GYRO_Z: %d\t", MPU6050_Get_Data(GYRO_ZOUT_H));
    
    printf("\r\n");
}

void USART2_Send_Byte(u8 data) {
	USART2->DR=data;
	while((USART2->SR&(1<<6))==0);
}

int main() {
	float pitch,roll,yaw;
	int i;
	char USART_TX_BUF[200];
	Stm32_Clock_Init(9);
	delay_init(72);
	MPU6050_Init();
	uart_init(72,38400);
	USART2_Init(36,38400);
	LED_Init();
	
	while(mpu_dmp_init());//直到为0初始化成功
	
	LED=0;//用来提示mpu是否初始化成功
	
	while(1){

		if(mpu_dmp_get_data(&pitch,&roll,&yaw)== 0) {//因为正确的情况只有一种，所以0是正确接收
			printf("pitch:%f roll=%f yaw=%f\r\n",pitch,roll,yaw);
			sprintf(USART_TX_BUF,"%f,%f,%f",pitch,roll,yaw);
			for(i=0;i<strlen(USART_TX_BUF);i++){
					USART2_Send_Byte(USART_TX_BUF[i]);
			}
			delay_ms(100);
		}	
		//delay_ms(10);
	}
}
