//07Dec2025
//https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/
#define FORMAT_LITTLEFS_IF_FAILED true

void LittleFSManager:: setup()
{
	if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
        return;
    }
   //LittleFS.format() ;
}

void LittleFSManager::readFile(String & filename)
{
File file = LittleFS.open(filename, "r");
 if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
  //vector<String> v;
  while (file.available()) 
  {
    //Serial.println(file.readStringUntil('t'));
    Serial.println(file.readString());
  }
  file.close();
}

void LittleFSManager:: listFiles()
{
	Serial.println("listFiles littleFS....");
	File root = LittleFS.open("/");
  File file = root.openNextFile();
 
  while(file)
  {
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }
}




    /**
    File file = SPIFFS.open("/test.txt", "r");
  if (!file) 
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  //vector<String> v;
  while (file.available()) 
  {
    //Serial.println(file.readStringUntil('t'));
    Serial.println(file.readString());
  }
  file.close();
    
}
*/

void LittleFSManager::writeTextFile()
{
	 File file = LittleFS.open("/testing.txt", FILE_WRITE);
 
  if (!file) 
   {
     Serial.println("There was an error opening the file for writing");
     return;
   }
  if (file.print("now is the time for all good men to come to the aid of the party")) {
    Serial.println("File was written");
  } 
  else 
  {
    Serial.println("File write failed");
  }
  file.close();
}