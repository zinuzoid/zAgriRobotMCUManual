#include <z51.h>
#include "init.h"
#include "Spray.h"
void SetCannonWater(
	unsigned char NN,unsigned char PP,unsigned char KK,unsigned char TT)
{
	CannonWater_N=NN;
	CannonWater_P=PP;
	CannonWater_K=KK;
	CannonWater_TT=TT;
}