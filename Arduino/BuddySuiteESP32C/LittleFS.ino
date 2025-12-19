//19Dec2025
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


//String readFile(String & filename);
String LittleFSManager::readFile(String & filenameIn)
{
String filename = String("/") + filenameIn;
File file = LittleFS.open(filename, "r");
String ret="";
 if(!file || file.isDirectory()){
        //Serial.println(String("- failed to open file for reading, ") + String(filename));
        return ret;
    }
  while (file.available()) 
  {
    ret+=file.readString();
     //Serial.println(String(filename) + String("=")  + ret);
  }
  file.close();
  return ret;
}

/**
Populate String array "filenames" with files that have names
starting with "jb" and end with ".sav£, e.g. jb1.sav
 */
void LittleFSManager::listSavFiles(String (& fileNames) [5])
{
	File root = LittleFS.open("/");
  File file = root.openNextFile();
  uint8_t fileNum=0;
  while(file)
  { 
    //jb1.sav to jb5.sav
    String currFileName(file.name());
     if (currFileName.endsWith(".sav") &&  currFileName.startsWith("jb"))
     {
        int fileNum  = (currFileName.substring(currFileName.indexOf("jb")+2, currFileName.indexOf(".sav"))).toInt();
        fileNames[fileNum-1] = file.name();
     }
     file = root.openNextFile();
     //fileNum++;
  }
}

void LittleFSManager::deleteFile(String & filenameIn)
{
    String filename = String("/") + filenameIn;
    LittleFS.remove(filename); 
}

void LittleFSManager::writeTextFile(String & filenameIn, String & text2Write)  //writeTextFile
{
  String filename = String("/") + filenameIn;
	File file = LittleFS.open(filename, FILE_WRITE);
  if (!file) 
   {
     //Serial.println("Error opening file for writing");
     return;
   }
  if (file.print(text2Write)) {} //Serial.println("File was written");} 
  else 
  {
     // Serial.println("File write failed");
  }
  file.close();
}
