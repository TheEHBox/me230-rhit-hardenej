// C++ code
//

#define PIN_CRANK_MID 0 //analog 0.  motor->diode->resistor->resistor-(here)>resistor-(ground)>resistor->diode->motor
#define PIN_CRANK_HIGH 1 //analog 1. motor->diode->resistor-(here)>resistor->resistor-(ground)>resistor->diode->motor

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  //printRaw();
  
  Serial.println(getSigned());
  
  delay(100);
}


int getSigned() {
  int a0 = analogRead(0);  
  int a1 = analogRead(1);
  int d = a0-a1;
  if(d<0) d = -d;
  
  if(d<5) return a1; //if they are close, then reading a positive voltage
  return -a1; //if they are not close (a0 is close to 0) then it is negative
}

void printRaw() {
  Serial.print("a0: ");
  Serial.print(analogRead(0));
  Serial.print("\ta1: ");
  Serial.println(analogRead(1));
}