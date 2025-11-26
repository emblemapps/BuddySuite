// C:\Users\Rob\Documents\Arduino\libraries\BuddySuiteESP32C3_LibsC:\Users\Rob\Documents\Arduino\libraries\BuddySuiteESP32C3_Libs
void CurrentValuesJB::setup()
{
    tojMl     = 3; 
    deemsRatio= 4;
    pgRatio   = 60;
//  solubility=SOLUBLE; //others are PART_SOLUBLE, NOT_SOLUBLE
//  pgMl    =0;
//  vgMl    =0;  these values are calculated
//  deemsMg =0;

//juiceCalc.calculate(tojMl, deemsRatio, pgRatio, pgMl, vgMl, deemsMg);

}

void CurrentValuesJB::setTojMl(float tojMlin)
{
  tojMl=(roundf(tojMlin * 10))/10.0 ;//round to 0.1  
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

void CurrentValuesJB::incrementValue (const int & incValueIn, uint8_t selectedField)
{
  //0 - dJuice Reqd >  1 - dRatio g/ml > 2 - PG/VG 3 - DMT
  //Serial.println(String("incValue=") + incValue + String(", sel field=") + selectedField);
float incValue=incValueIn;
//if (incValueIn==2) {incValue=1;}  if (incValueIn==-2) {incValue=-1;}

//Serial.println( String("incValIn=") + String(incValueIn) + String(",incval=") + String(incValue));
  
   if(incValue<0) {incValue = _max(-10, incValue);}
   else if (incValue>0) {incValue = _min(10, incValue);}
   
   uint8_t absIncValue = abs(incValue);
  
   
  switch(selectedField)
  {
    case 0:  
            if (absIncValue>8) 
            {
            	tojMl+=incValue/10;
            	//Serial.println (String ("tojMl=") + String (tojMl) + String(", incValue=") + String(incValue));
            }
            else               {tojMl+=incValue/100;} //set increment based on stick excursion
						
            
            tojMl = _max(tojMl, MIN_tojMl); tojMl =_min(tojMl, MAX_tojMl);
            break;
    case 1: deemsRatio+=incValue/100; 
            deemsRatio= _max(deemsRatio, MIN_DEEMSRATIO); deemsRatio =+ _min(deemsRatio, MAX_DEEMSRATIO);
            break;
    case 2: pgRatio   -=incValue/2;
            //Serial.println(pgRatio);
            pgRatio = _max(pgRatio, MIN_tojMl); pgRatio=_min(pgRatio, MAX_PG);
            break;
    case 3: deemsMg += incValue*abs(incValue); //preserve the sign - or + in the square op
            deemsMg = _max(deemsMg, 0); deemsMg=_min(deemsMg, 9999);
            break;    
  }

  delay (100);
 ////if ( absIncValue<10) {delay(10);} //so we can knock onto our desired value
 //  if ( absIncValue<8) {delay(50);} //so we can knock onto our desired value
 //  if ( absIncValue<24) {delay(100);} //so we can knock onto our desired value
   //delay for 5 = none, for 4=100, 1,2,3 = 200

  // Serial.println(String("tojMl=") + tojMl + String(", DeemMg=") + deemsMg);
}
