//5Dec2025
int oldJoystickYRaw=0; 
int oldJoystickXRaw=0;
 
int joystickXRaw=0;
int joystickYRaw=0;
int joystickCentreXMapped=0; int joystickCentreXRaw=0;
int joystickCentreYMapped=0; int joystickCentreYRaw=0;
;

void JB_JoystickReader::setup()
{
   //calibrate centres on power up
    joystickCentreXRaw=analogRead(JOYSTICK_X_PIN);
    joystickCentreYRaw=analogRead(JOYSTICK_Y_PIN);
}

int JB_JoystickReader::getJoystickXMappedVal()
{
	return joystickXMapped;
}

boolean JB_JoystickReader::isCentredYRaw(int joystickInYRaw)
{
	//Serial.println(String("joystickYRaw=") + String(joystickYRaw) + String(", min=") + String(joystickCentreYRaw-1000) + String(", max=") + String(joystickCentreYRaw+1000));
	if(joystickInYRaw<=joystickCentreYRaw-550 || joystickInYRaw>=joystickCentreYRaw+550)
  {return false;}
   return true;
}

boolean JB_JoystickReader::isCentredYRaw() 
{
	return isCentredYRaw(analogRead(JOYSTICK_Y_PIN));
}

boolean JB_JoystickReader::isCentredXRaw()
{
	return isCentredXRaw(analogRead(JOYSTICK_X_PIN));
}

boolean JB_JoystickReader::isCentredXRaw(int joystickInXRaw)
{
if(joystickInXRaw<=joystickCentreXRaw-250 || joystickInXRaw>=joystickCentreXRaw+250)
  {return false;}
   return true;
}

/**
 joystick has gnd x, y, vcc, two self-centring 10k pots 
10 bit resolution 0-1023, mid point approx 512 

incX and incY tell us how many to increment the X and Y columns and rows.  
Probably Y will only be 1, 0 or -1 since these shift between totalJuice, DeemsRat, and PG/VG
*/
unsigned long  millisSinceRowLastChanged				= 0;
void JB_JoystickReader::getSelectedRow(uint8_t & selectedRow)
{
	joystickXRaw = analogRead(JOYSTICK_X_PIN);  joystickYRaw = analogRead(JOYSTICK_Y_PIN);
	jb_lcdHandler.setJoystickMeter(joystickXRaw);
  readAndConvertJoystick				(joystickXRaw, joystickYRaw); //  populate joystickXRaw and joystickYRaw with -10 to +10 ish values
	
 if (isCentredYRaw(oldJoystickYRaw) && !isCentredYRaw(joystickYRaw)) //has the joystick moved from Y centre?
 {
 	  // Serial.println ( String (millisSinceRowLastChanged) + String(", millis=") + String(millis()) + String(", millis-30 =")+ String (millis() - 30));
 	   if (millisSinceRowLastChanged > millis() - 350) {/**Serial.println (String("too recent, returning"));*/ return;} 
 	   millisSinceRowLastChanged = millis();
     if(joystickCentreYRaw > joystickYRaw){rowSelected--;}
     else {rowSelected++;}
     rowSelected = rowSelected%4;
//  //Serial.println (String("y=") + String(joystickY) + String(", row=") + String(rowSelected) + String(", isCentred?") + (joystick.isCentred(joystickY))); 
 }
 oldJoystickYRaw=joystickYRaw;
}
//char  joystickMeter [] = "     |     ";

/**
 * Populates joystickXMapped and joystickYMapped
 * Converts raw joystick input values ~0-4095 to ~ -10 to +10
 */
void JB_JoystickReader::readAndConvertJoystick(const int & incRawX, const int & incRawY)
{
  joystickXMapped = map(incRawX, 0, 3900, -10, 10);  
   uint8_t absJoystickXMapped = abs(joystickXMapped);
   joystickForce = absJoystickXMapped>9?HARD:(absJoystickXMapped<=9 && absJoystickXMapped>6)?MEDIUM:(isCentredXRaw())? NONE:LIGHT;
   //joystickYMapped = map(incRawY, 0, 4096,  -10, 10);  //0-10 i.e. 11 values with 5 in middle 01234 5 6798A
//makeJoystickMeterString(incX);
}



unsigned long timeJoystickLastOffCentred=0;
uint16_t durationJoystickCentred=0;
void JB_JoystickReader::makeJoystickMeterString(uint8_t & incX)
{
//  uint8_t x=0;
//  for(x=0; x<11; ++x)
//  {
//          joystickMeter[x]= (x==5?'|' : ' ');
//          if (incX>=x && x>5) {joystickMeter[x]='>';}
//    else  if (x>=incX && x<5 ){joystickMeter[x]='<';}
//  }
//
//  if (incX==5) //i.e. joystick centred
//  {
//    #ifdef SSD1306I2C
//    display.setCursor(0, 58); 
//    display.setTextColor(WHITE, BLACK);
//    display.print("     |     ");
//    display.display();
//    #endif 
//
//    #ifdef ST7567I2C
//    display.Cursor(0, 7); 
//    if(durationJoystickCentred>1) //must be centered for 2 or more seconds to show centred
//    {
//      String outtt= String("Totl ") + String(values.totalWeightOfDJuice_g,(values.totalWeightOfDJuice_g>=10?2:3)) + String("g");
//      char buffy[13];
//      outtt.toCharArray(buffy, 12);
//      display.Display(buffy, INVERT_DISPLAY);
//    }
//  else
//  { 
////    display.Cursor(0, 7); 
//    display.Display("     |     ", INVERT_DISPLAY);
//  }
//    #endif
//  }
//  else
//  {
//   timeJoystickLastOffCentred=millis();
//  }
//  durationJoystickCentred = (millis() - timeJoystickLastOffCentred)/1000;
// 
////  if(durationJoystickCentred>2) //must be centered for >2 seconds to show centred
////  {
////    display.Cursor(0, 7); 
////    display.Display("Totl 1.045g", INVERT_DISPLAY);
////  }
// // else {Serial.println("NOT Centred");}  
  
}
