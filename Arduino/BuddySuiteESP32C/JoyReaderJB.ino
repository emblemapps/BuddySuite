//19Dec2025
void JB_JoystickReader::getSelectedRow()
{
  joystickXRaw = analogRead(JOYSTICK_X_PIN);  joystickYRaw = analogRead(JOYSTICK_Y_PIN);
	readAndConvertJoystickX	 (joystickXRaw)  ;  //Converts raw X joystick input values ~0-4095 to ~ -10 to +10 in joystickXMapped, also populates joystickForce enum
 
 if (isCentredYRaw(oldJoystickYRaw) && !isCentredYRaw(joystickYRaw)) //has the joystick moved from Y centre?
 {
 	   if (millisSinceRowLastChanged > millis() - 350) {/**Serial.println (String("too recent, returning"));*/ return;} 
 	   millisSinceRowLastChanged = millis();
     if(joystickCentreYRaw > joystickYRaw){rowSelectedJB--;}
     else {rowSelectedJB++;}
   
    rowSelectedJB = rowSelectedJB%4;
    //Serial.println (String("y=") + String(joystickY) + String(", row=") + String(rowSelected) + String(", isCentred?") + (joystick.isCentred(joystickY))); 
 }
 oldJoystickYRaw=joystickYRaw;
}

/**
 * Populates joystickXMapped,but no joystickYMapped
 * Converts raw joystick input values ~0-4095 to ~ -10 to +10
 */
void JB_JoystickReader::readAndConvertJoystickX(const int & joystickXRawVal)
{
  joystickXMapped = map(joystickXRawVal, 0, 3900, -10, 10);  
   uint8_t absJoystickXMapped = abs(joystickXMapped);
   joystickForce = absJoystickXMapped>9?HARD:(absJoystickXMapped<=9 && absJoystickXMapped>6)?MEDIUM:(isCentredXRaw())? NONE:LIGHT;
}
