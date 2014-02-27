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

//This code is testing code for the circuit to make sure all of the
//physical Arduino I/O is working. It checks a potentiometer or other
//sensor on the AO PIN and equates it to the future number of mails
//in the inbox. 
//On each pin 9, 10 and 11 are 220 Ohm resistors leading to the bases of 
//PN2222A transistors. The collector is attached to the motor and the 
//emitter to ground. 

//------------------------------------------------- OUTPUTS AND THEIR VARIABLES
//the total number of bees bing controlled
const int beeTotalNumber = 3;

int beePins[beeTotalNumber] = {9, 10, 11 };

//INPUTS AND THEIR VARIABLES
int howManyNewEmails = 0; 

//--------------------------------------------------------  GLOBAL BEE SETTINGS

//the number of emails the bees hit maximum freakout.
//ideally it should be divisible by the number of
//beeActivityLevels
int maxBeeVar = 1023;

//how many different states the Bees can be in
const int beeActivityLevels = 16;

//The area that dictates the 16 BeeActivityLevels.
int b[beeActivityLevels][beeTotalNumber] =
{
  { 0, 0, 0 },
  { 0, 0, 50 },
  { 0, 50, 50 },
  { 50, 50, 50 },
  { 50, 50, 100 }, 
  { 50, 100, 100 }, 
  { 100, 100, 100 }, 
  { 100, 100, 150 }, 
  { 100, 150, 150 }, 
  { 150, 150, 150 }, 
  { 150, 150, 200 }, 
  { 150, 200, 200 }, 
  { 200, 200, 200 },
  { 200, 200, 250 }, 
  { 200, 250, 250 }, 
  { 255, 255, 255 },
};


//---------------------------------------------------------------------- SETUP
void setup() {                
   Serial.begin(9600);
}


//----------------------------------------------------------------------- LOOP
void loop() {
  //get the data determining bee behavior
  howManyNewEmails = analogRead(A0);
  //Serial.println(howManyNewEmails);
  
  //update the bees
  updateBees(howManyNewEmails, maxBeeVar);
  
  //mini-pause
  delay(10);

}

//---------------------------------------------------------------- updateBees()
void updateBees(int v, int maxVal) {
  //ignore any values of V above maximum freakout level
  // v = min(v, maxVal); does not work in Intel Galileo MacOS IDE
  
  if (v > maxVal) {
    v = maxVal;
  }
  
  //map the newly constrained V to the beeActivityLevel array
  //the top value is 1 less than the number than the array size
  //because the an array starts with the index number 0
  int mappedV = map(v, 0, maxVal, 0, beeActivityLevels-1);
  //Serial.println(mappedV);
  
  //for each bee, get the value it supposed to be and set it there
  for (int i=0; i <= beeTotalNumber-1; i++){
    //Serial.println(b[mappedV][i]);
    analogWrite(beePins[i], b[mappedV][i]);
  }
  
}

