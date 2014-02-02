//Thank you Tom Igoe
File myFile;

void initSDCard() {
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
   if (SD.exists("pyMailCheck.py")) {
    Serial.println("python script exists.");
  }
  else {
    Serial.println("python script does not exist.");  
  }
}

