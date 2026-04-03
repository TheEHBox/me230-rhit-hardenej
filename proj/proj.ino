// C++ code
//

#define PIN_DYNAMO_CRANK_MID 0 //analog 0.  motor->diode->resistor->resistor-(here)>resistor-(ground)>resistor->diode->motor
#define PIN_DYNAMO_CRANK_HIGH 1 //analog 1. motor->diode->resistor-(here)>resistor->resistor-(ground)>resistor->diode->motor

#define PIN_SINGLE_BUTTON_CRANK 2 //digital 1. simple button that gets pressed by a cam connected to the crank

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_SINGLE_BUTTON_CRANK, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}


//true if pressed, false if not
int readButton(int pin) {
	return !digitalRead(pin);
}




static constexpr int LOOP_TIME = 300; // how long the main processor waits between loops
unsigned long lastLoopTime = 0;

void loop()
{

  if(millis()-lastLoopTime>LOOP_TIME){
    lastLoopTime = millis();



    //printRaw();
    Serial.println(getSigned());
  }
  

  digitalWrite(LED_BUILTIN, readButton(PIN_SINGLE_BUTTON_CRANK));
}


int getSigned() {
  int mid = analogRead(PIN_DYNAMO_CRANK_MID);  
  int high = analogRead(PIN_DYNAMO_CRANK_HIGH);
  int diff = mid-high;
  if(diff<0) diff = -diff; //absolute value
  
  if(diff<5) return high; //if they are close, then reading a positive voltage
  return -high; //if they are not close (mid is close to 0) then it is negative
}

void printRaw() {
  Serial.print("mid: ");
  Serial.print(analogRead(PIN_DYNAMO_CRANK_MID));
  Serial.print("\thigh: ");
  Serial.println(analogRead(PIN_DYNAMO_CRANK_HIGH));
}