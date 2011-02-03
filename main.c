#include <z51.h>

#include "queue.h"
#include "delay.h"
#include "init.h"
#include "Spray.h"
#include "drill.h"

//#define _SPRAY
#define _DRILL

ZQUEUE qSerial;

void Serial_ISR()	interrupt 4
{
	if(RI)
	{
		RI=0;
		QueueInsert(&qSerial,SBUF);
	}
}

void SetMotor(
	unsigned char fldir,unsigned char bldir,unsigned char frdir,unsigned char brdir,
	unsigned char flpwm,unsigned char blpwm,unsigned char frpwm,unsigned char brpwm)
{
	MotorFLDir=fldir;
	MotorBLDir=bldir;
	MotorFRDir=frdir;
	MotorBRDir=brdir;
	
	MotorFLPwm=flpwm;
	MotorBLPwm=blpwm;
	MotorFRPwm=frpwm;
	MotorBRPwm=brpwm;
}

int main()
{
	PortInit();
	SerialInit();
	QueueInit(&qSerial);
	
	EnableSerialISR();
	MotorDirInit();
	MotorCannonInit();
	
	delay(1000);

	while(1)
	{
		if(!QueueIsEmpty(&qSerial))
		{
			unsigned char stmp=0;
			QueueDelete(&qSerial,&stmp);
			SBUF=stmp;
			
			switch(stmp)
			{
				case 0x44	://left
					//SetMotor(0,0,0,1,0,0,1,1);  //jetsada
					 // SetMotor(0,1,0,1,1,1,1,1); //SPRAY
					 SetMotor(1,0,1,0,1,1,1,1);// drill
					break;
				case 0x43	://right
					//SetMotor(1,0,0,0,1,1,0,0);
					 // SetMotor(1,0,1,0,1,1,1,1);  //SPRAY
					  SetMotor(0,1,0,1,1,1,1,1);
					break;
				case 0x41	://front
					//SetMotor(0,0,0,0,1,1,1,1);//SPRAY
					SetMotor(1,1,1,1,1,1,1,1);//DRILL
					break;
				case 0x42	://back
					//SetMotor(1,1,1,1,1,1,1,1); //SPRAY
					  SetMotor(0,0,0,0,1,1,1,1); //DRILL
					break;
				case 'a'	://stop
					SetMotor(0,0,0,0,0,0,0,0);
					break;
					
				#ifdef _SPRAY					
				case 'x'	://spray N
					SetCannonWater(1,0,0,0);
					break;
				case 'y'	://spray P
					SetCannonWater(0,1,0,0);
					break;
				case 'z'	://spray K
					SetCannonWater(0,0,1,0);
					break;		
				case 'b'	://spray TT
					SetCannonWater(0,0,0,1);
					break;
				case 'c'	://stop spray
					SetCannonWater(0,0,0,0);
					break;				
				#else ifdef _DRILL
				case 'z'	:// sawEN
					SAWMotorEN(0,1);
					break;
				case 'x'	:// sawOFF
					SAWMotorEN(0,0);
					break;
				case 'v'	:// drill down
					PunchDOWN();
					break;		
				case 'b'	:// drill up
			 		PunchUP();
					break;	
				case 's'	:// drill up
			 		PunchPWM=0;
					break;			
				#endif
			}
		}
	}	
	return 0;
}


