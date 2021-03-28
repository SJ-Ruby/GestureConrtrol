#include "ctd_trans.h"
//USART2_RX_STA
//USART2_RX_BUF
void cTd_trans(float *pitch,float *roll,float *yaw){
	int flag=0;
	char temp[3][200];
	int temp_len=0;
	int i;
	for(i=0;i<(USART2_RX_STA&0x7fff);i++){
		if(USART2_RX_BUF[i]!=',') temp[flag][temp_len++]=USART2_RX_BUF[i];
		else {
			temp[flag][temp_len]='\0';
			flag++;
			temp_len=0;
		}
	}
	*pitch=(float)atof(temp[0]);
	*roll=(float)atof(temp[1]);
	*yaw=(float)atof(temp[2]);
}

