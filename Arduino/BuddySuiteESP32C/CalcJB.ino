//03Jan2026
void CurrentValuesJB::setup()
{
	  tojMl     = 3; 
    deemsRatio= 4;
    pgRatio   = 60;
}

String CurrentValuesJB::toString()
{
	String outStr = utils.makeDRatString(*this);
	String ret = String(tojMl,1) + String ("ml ") + String(outStr) + String(" " )  
	+ String(pgRatio) + String("/") + String(100-pgRatio); 
	return ret;
}

void CurrentValuesJB::setTojMl(float tojMlin)
{
  tojMl=(roundf(tojMlin * 10))/10.0 ; //round to 0.1  
}

float CurrentValuesJB::getTojMl()
{
  return tojMl;
}

void CurrentValuesJB::incrementValue (const int & incValueIn, uint8_t selectedField)
{
   //0 - dJuice Reqd,  1 - dRatio g/ml, 2 - PG/VG, 3 - Deems
	 float incValue=incValueIn;
	 if(incValue<0) 			{incValue = _max(-10, incValue);}
   else if (incValue>0) {incValue = _min(10, incValue);}
   uint8_t absIncValue = abs(incValue);
  boolean pushRight 	 = incValue   >0;
   switch(selectedField)
  	{
    	case 0: if (millisLastChangedtojMl > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangedtojMl = millis();
    					if(pushRight){tojMl+=((joystickForce==HARD)?1:0.1);} else {tojMl-=((joystickForce==HARD)?1:0.1);}
            	tojMl = _max(tojMl, MIN_tojMl); tojMl =_min(tojMl, MAX_tojMl);
            	break;
    	case 1: if (millisLastChangeddeemsRatio > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangeddeemsRatio = millis();
    					if(pushRight){deemsRatio+=((joystickForce==HARD)?1:0.1);} else {deemsRatio-=((joystickForce==HARD)?1:0.1);}
            	deemsRatio= _max(deemsRatio, MIN_DEEMSRATIO); deemsRatio =+ _min(deemsRatio, MAX_DEEMSRATIO);
            	break;
    	case 2: if (millisLastChangedpgRatio > millis() - joystickIncrementDelayMillis) {break;}
    					millisLastChangedpgRatio = millis();
    					if(pushRight){pgRatio-=((joystickForce==HARD)?10:1);} else {pgRatio+=((joystickForce==HARD)?10:1);}
            	pgRatio = _max(pgRatio, MIN_tojMl); pgRatio=_min(pgRatio, MAX_PG);
            	break;
    	case 3: if (LastChangeddeemsMg > millis() - joystickIncrementDelayMillis) {break;}
    					LastChangeddeemsMg 		= millis();
    					if(pushRight) {deemsMg+=((joystickForce==HARD)?100:(joystickForce==MEDIUM)?10:1);} else {deemsMg-=((joystickForce==HARD)?100:(joystickForce==MEDIUM)?10:1);}
            	deemsMg = _max(deemsMg, 0); deemsMg=_min(deemsMg, 9999);
            	break;    
  	}
  delay (0);
}
