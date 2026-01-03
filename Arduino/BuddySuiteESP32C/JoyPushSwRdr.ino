//03Jan2026
boolean OldJoyPushSwitchStatus           = 1;
void JoystickPushSwitchReader::setup()
{
  pinMode(JOYSTICK_PUSHSW_PIN, INPUT_PULLUP);   
}

void JoystickPushSwitchReader::checkForSwitchPush()
{
  boolean joyPushSwitchStatus = digitalRead(JOYSTICK_PUSHSW_PIN);
  if (!OldJoyPushSwitchStatus && joyPushSwitchStatus)
  {
     sendPushSwitchNotification();
  }
  OldJoyPushSwitchStatus=joyPushSwitchStatus;
}

void JoystickPushSwitchReader::sendPushSwitchNotification()
{
  if (jb_lcdHandler.screenShowing==JB) //{JB, JBSAV};
  {   
      jb_SaveScreenHndlr.setupScreen(valuesJB); //draws background static graphics
      joystickReaderJBSAV.setup(); //oldJoystickXRaw=joystickCentreXRaw and  oldJoystickYRaw=joystickCentreYRaw;
  }    
  else if(jb_lcdHandler.screenShowing==JBSAV)
  {
    if(rowSelectedJBSAV==0)
    {
      returnToJuiceBuddyScreen();
    } 
    else
    {
      jb_SaveScreenHndlr.doClick();
      rowSelectedJBSAV=0;
      jb_SaveScreenHndlr.setSelectedRow(0);
      pressedRecently=true;
    }
    
  }
}

boolean JoystickPushSwitchReader::wasPressedRecently()
{
  boolean ret  = pressedRecently;
  pressedRecently=false;   //done like this so we don't need to reset it
  return ret;
}

void JoystickPushSwitchReader::returnToJuiceBuddyScreen()
{
    jb_lcdHandler.setupScreen();
    jb_lcdHandler.setSelectedField(rowSelectedJB);
    jb_calc.calculate             (valuesJB, false);
    jb_lcdHandler.updateScreen    (valuesJB, true);  
}
