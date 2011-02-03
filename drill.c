#include <z51.h>

#include "delay.h"
#include "init.h"

void SAWMotorEN(unsigned char Saw_RUN,unsigned char Saw_PWM)
{
	 SawDir= Saw_RUN	;
	 SawPWM= Saw_PWM	;
}
void PunchDOWN()
{
	DrillContactDOWN=1;
	
	PunchDir=0;
 	PunchPWM=1;
	
}

void PunchUP()
{
	DrillContactUP=1;
	
	PunchDir=1;	
 	PunchPWM=1;
	while(!DrillContactUP);
	delay(555);
	PunchPWM=0;
}