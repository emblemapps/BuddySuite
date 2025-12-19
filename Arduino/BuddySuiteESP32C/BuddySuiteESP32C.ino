//19Dec2025
#include <SPI.h>
#include <BuddySuiteESP32C3.h>
#include <./fonts/Open_Sans_Condensed_Italic_19.h>
#include <./fonts/Open_Sans_Italic_23.h> 
#include <./fonts/Open_Sans_Italic_21.h>
#include <./fonts/Roboto_Condensed_Italic_17.h>
//For ESP -> ST7789 TFT connections, see "Utils" tab
Utils utils;
JB_Main jbMain;
LittleFSManager littleFS;
JoystickPushSwitchReader jsPushSwitchReader;

void setup() {
  Serial.begin(115200);
  jbMain.initJB();
  jbMain.startJB();
  littleFS.setup();
  jsPushSwitchReader.setup();
  // Serial.println ("setup1 on main ino");
  // delay(500);
  // littleFS.writeTextFile();
  // Serial.println ("setup2 on main ino");
  // delay(500);
  // Serial.println ("about to list files..");
  // littleFS.listFiles();
  // delay(500);
  // //spiffs.writeTextFile();
  // //littleFS.get_data_from_file();
 
  //  delay(500);
  
}

void loop() 
{	
	// littleFS.listFiles();
  // delay (1000);
  // String filenm = "/testing.txt";
  // //littleFS.readFile(filenm);
  // delay (1000);
  jbMain.loop();
  
}
