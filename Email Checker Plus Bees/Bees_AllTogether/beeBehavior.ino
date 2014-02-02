//------------------------------------------------- OUTPUTS AND THEIR VARIABLES


//--------------------------------------------------------  GLOBAL BEE SETTINGS

//the number of emails the bees hit maximum freakout.
//ideally it should be divisible by the number of
//beeActivityLevels
int maxBeeVar = 640;

//how many different states the Bees can be in
const int beeActivityLevels = 16;

//the total number of bees bing controlled
const int beeTotalNumber = 3;

//the number of emails the bees hit maximum freakout.
//ideally it should be divisible by the number of
//beeActivityLevels
int maxBeeVar = 640;

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

//---------------------------------------------------------------- updateBees()
void updateBees(int v, int maxVal) {
  //ignore any values of V above maximum freakout level
  v = min(v, maxVal);
  
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
