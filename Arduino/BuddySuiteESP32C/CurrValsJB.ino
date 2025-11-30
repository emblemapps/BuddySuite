//30Nov2025
// C:\Users\name\Documents\Arduino\libraries\BuddySuiteESP32C3_LibsC:\Users\name\Documents\Arduino\libraries\BuddySuiteESP32C3_Libs
void CurrentValuesJB::setup()
{
    tojMl     = 3; 
    deemsRatio= 4;
    pgRatio   = 60;
//  solubility=SOLUBLE; //others are PART_SOLUBLE, NOT_SOLUBLE
//  pgMl    =0;
//  vgMl    =0;  these values are calculated
//  deemsMg =0;
}

void CurrentValuesJB::setTojMl(float tojMlin)
{
  tojMl=(roundf(tojMlin * 10))/10.0 ; //round to 0.1  
}

float CurrentValuesJB::getTojMl()
{
  return tojMl;
}

#define MIN_tojMl 0
#define MAX_tojMl 50
#define MIN_PG 0
#define MAX_PG 100
#define MIN_DEEMSRATIO 0.5
#define MAX_DEEMSRATIO 20


unsigned long millisLastChangedtojMl			=0;
unsigned long millisLastChangeddeemsRatio	=0;
unsigned long millisLastChangedpgRatio		=0;
unsigned long LastChangeddeemsMg					=0;
const uint16_t joystickIncrementDelayMillis = 150;

void CurrentValuesJB::incrementValue (const int & incValueIn, uint8_t selectedField)
{
   //0 - dJuice Reqd,  1 - dRatio g/ml, 2 - PG/VG, 3 - Deems
	 float incValue=incValueIn;
	 if(incValue<0) 			{incValue = _max(-10, incValue);}
   else if (incValue>0) {incValue = _min(10, incValue);}
   uint8_t absIncValue = abs(incValue);
   boolean hardPush 	 = absIncValue>9;
   boolean mediumPush  = absIncValue<=9 && absIncValue>6;
   boolean pushRight 	 = incValue   >0;
   //uint16_t delays=10;
   switch(selectedField)
  	{
    	case 0:                                    
    					if (millisLastChangedtojMl > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangedtojMl = millis();
    					if(pushRight){tojMl+=(hardPush?1:0.1);} else {tojMl-=(hardPush?1:0.1);}
            	tojMl = _max(tojMl, MIN_tojMl); tojMl =_min(tojMl, MAX_tojMl);
            	break;
    	case 1: if (millisLastChangeddeemsRatio > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangeddeemsRatio = millis();
    					if(pushRight){deemsRatio+=(hardPush?1:0.1);} else {deemsRatio-=(hardPush?1:0.1);}
            	deemsRatio= _max(deemsRatio, MIN_DEEMSRATIO); deemsRatio =+ _min(deemsRatio, MAX_DEEMSRATIO);
            	//delays+=85;
            	break;
    	case 2: if (millisLastChangedpgRatio > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangedpgRatio = millis();
    					if(pushRight){pgRatio-=(hardPush?10:1);} else {pgRatio+=(hardPush?10:1);}
            	pgRatio = _max(pgRatio, MIN_tojMl); pgRatio=_min(pgRatio, MAX_PG);
            	//delays+=85;//if(!hardPush){delays+=150;} else{delays+=100;}
            	break;
    	case 3: //deemsMg += incValue*abs(incValue); //preserve the sign - or + in the square op
    					if (LastChangeddeemsMg > millis() - joystickIncrementDelayMillis) {break;}
    					LastChangeddeemsMg 		= millis();
    					if(pushRight) {deemsMg+=(hardPush?100:mediumPush?10:1);} else {deemsMg-=(hardPush?100:mediumPush?10:1);}
            	deemsMg = _max(deemsMg, 0); deemsMg=_min(deemsMg, 9999);
            	break;    
  	}
  delay (5);
 ////if ( absIncValue<10) {delay(10);} //so we can knock onto our desired value
 //  if ( absIncValue<8) {delay(50);} //so we can knock onto our desired value
 //  if ( absIncValue<24) {delay(100);} //so we can knock onto our desired value
 //	 delay for 5 = none, for 4=100, 1,2,3 = 200
}
