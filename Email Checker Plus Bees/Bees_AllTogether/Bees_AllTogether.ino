//-------------------------------------------------------- ABOUT & RESOURCES
/*
Much of this code comes from Arduino IDE included examples (Thanks Tom Igoe
and Limor Fried) and is reworking of code posted by Jim Lindblom under a 
beerware license.  

https://learn.sparkfun.com/tutorials/galileo-unread-email-counter/introduction

It works with a python script to check an email inbox and return the count
of emails in that inbox.

The count will shake 3 pager motors at various PWMs depending on that email
count. 

*/

//------------------------------------------------------------ START LICENSE
/*The MIT License (MIT)

Copyright (c) 2014 Carlyn Maw

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
// ---------------------------------------------------------------- END LICENSE
 #include <WiFi.h>
 #include <SD.h> 


int emailCount = 0; // Stores the last email count
int beePins[beeTotalNumber] = {9, 10, 11 };

void setup() {
  delay(5000);
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  wifiNotEncrypted();
  initSDCard();  // Initializes the SD class

}

//----------------------------------------------------------------- LOOP
void loop() {
  emailHandler();
  updateBees(emailCount, maxBeeVar);
}
