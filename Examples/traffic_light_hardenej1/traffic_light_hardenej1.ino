// C++ code
//

//defining pins of choice
int red = 9;
int yellow = 8;
int green = 7;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

//race light instead of traffic light
//red, then blinking yellow, then green
void loop()
{
  //red
  digitalWrite(red, HIGH);
  delay(5000); // Wait for 5 seconds
  digitalWrite(red, LOW);
  
  //flash yellow
  for(int i=0; i<3; i++){
  	digitalWrite(yellow, HIGH);
  	delay(1000); // Wait for 1 seconds
  	digitalWrite(yellow, LOW);
  	delay(1000); // Wait for 1 seconds
  }
  
  //then green
  digitalWrite(green, HIGH);
  delay(2500); // Wait for 2.5 seconds
  digitalWrite(green, LOW);
  
  //back yellow
  digitalWrite(yellow, HIGH);
  delay(2000); // Wait for 2 seconds
  digitalWrite(yellow, LOW);
}