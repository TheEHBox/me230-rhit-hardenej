// C++ code
//


static constexpr int numDigital = 2;
static constexpr int digitalIns[numDigital] = {2, 3};
static constexpr int digitalLeds[numDigital] = {4, 5};
static constexpr int digitalOuts[numDigital] = {12, 13};

static constexpr int numAnalog = 1;
static constexpr int analogIns[numAnalog] = {0}; //analog 0
static constexpr int analogLeds[numAnalog] = {6};
static constexpr int analogOuts[numAnalog] = {11};


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  for(int i=0; i<numDigital; i++) {
	pinMode(digitalIns[i], INPUT_PULLUP);
    pinMode(digitalLeds[i], OUTPUT);
    pinMode(digitalOuts[i], OUTPUT);
  }
  
  for(int i=0; i<numAnalog; i++) {
	//don't need to set analog in, they are always input
    pinMode(analogLeds[i], OUTPUT);
    pinMode(analogOuts[i], OUTPUT);
  }
  
}

//true if pressed, false if not
int readButton(int index) {
	return !digitalRead(digitalIns[index]);
}

void loop()
{
  for(int i=0; i<numDigital; i++) {
    int read = readButton(i);
	digitalWrite(digitalLeds[i], read);
    digitalWrite(digitalOuts[i], read);
  }
  
  for(int i=0; i<numAnalog; i++) {
    int read = analogRead(analogIns[i])/4; //div by 4 to match the scales
    //analog read is [0,1024) and analog write is [0,256)
	//don't need to set analog in, they are always input
    analogWrite(analogLeds[i], read);
    analogWrite(analogOuts[i], read);
  }
  
  delay(10);
}