// C++ code
//

static constexpr int numDigital = 2;
static constexpr int digitalIns[numDigital] = {2, 3};
static constexpr int digitalLeds[numDigital] = {4, 5};
static constexpr int digitalOuts[numDigital] = {12, 13};

static constexpr int numAnalog = 1;

static constexpr int analogIns[numAnalog] = {0}; // analog 0
static constexpr int analogLeds[numAnalog] = {6};
static constexpr int analogOuts[numAnalog] = {11};

static constexpr int LOOP_TIME = 400; // how long the main processor waits between loops
unsigned long lastLoopTime = 0;

bool patternFullStep[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {1, 0, 0, 1}};

class MyStepper
{
public:
    MyStepper(int pin1, int pin2, int pin3, int pin4) : pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4)
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
        writePins();
    }

    void stepForward()
    {
        stepIndex++;
        if (stepIndex == 4)
            stepIndex = 0;
        totalSteps++;

        writePins();
    }

    void stepBackward()
    {
        stepIndex--;
        if (stepIndex < 0)
            stepIndex = 3;
        totalSteps--;

        writePins();
    }
    
    void autostep() {
        if(millis() - lastStepTime >= stepInterval) {
            if (targetSteps > totalSteps)
                stepForward();
            else if (targetSteps < totalSteps)
                stepBackward();
            lastStepTime=millis();
        }
    }
    
    void setStepInterval(unsigned long inputStepInterval) {
        stepInterval = inputStepInterval;
    }
    
    void setTargetSteps(long inputTargetSteps) {
        targetSteps = inputTargetSteps;
    }
    
    void changeTargetSteps(long delta) {
        targetSteps += delta;
    }


private:
    long totalSteps = 0;
    long targetSteps = 0;
    int stepIndex = 0;
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    unsigned long stepInterval=100;
    unsigned long lastStepTime=0;

    void writePins()
    {
        digitalWrite(pin1, patternFullStep[stepIndex][0]);
        digitalWrite(pin2, patternFullStep[stepIndex][1]);
        digitalWrite(pin3, patternFullStep[stepIndex][2]);
        digitalWrite(pin4, patternFullStep[stepIndex][3]);
    }
};

// true if pressed, false if not
int readButton(int index)
{
    return !digitalRead(digitalIns[index]);
}

// steps per rotation for real stepper: 2048
MyStepper mystep{8, 9, 10, 11};

void setup()
{

    Serial.begin(9800);
    pinMode(LED_BUILTIN, OUTPUT);

    for (int i = 0; i < numDigital; i++)
    {
        pinMode(digitalIns[i], INPUT_PULLUP);
        pinMode(digitalLeds[i], OUTPUT);
        pinMode(digitalOuts[i], OUTPUT);
    }

    for (int i = 0; i < numAnalog; i++)
    {
        // don't need to set analog in, they are always input
        pinMode(analogLeds[i], OUTPUT);
        pinMode(analogOuts[i], OUTPUT);
    }
}

long targetSteps = 0;

void loop()
{
    
    // set speed to potentiometer reading
    mystep.setStepInterval(map(analogRead(0), 0, 1024, 100, 5));
    mystep.autostep();
    
    // todo: create object for buttons to encapsulate this rising edge detection
    static bool zeroPressed = false;
    if (zeroPressed && !readButton(0))
        zeroPressed = false;
    if (!zeroPressed && readButton(0))
    {
        zeroPressed = true;
        mystep.changeTargetSteps(2048/4);//  2048 is one rotation
    }

    static bool onePressed = false;
    if (onePressed && !readButton(1))
        onePressed = false;
    if (!onePressed && readButton(1))
    {
        onePressed = true;
        mystep.changeTargetSteps(-2048/4);//  2048 is one rotation
    }
    
    
    
    // read and write digital
    for (int i = 0; i < numDigital; i++)
    {
        int read = readButton(i);
        digitalWrite(digitalLeds[i], read);
        digitalWrite(digitalOuts[i], read);
    }

    // read and write analog
    for (int i = 0; i < numAnalog; i++)
    {
        int read = analogRead(analogIns[i]) / 4; // div by 4 to match the scales
        // analog read is [0,1024) and analog write is [0,256)
        // don't need to set analog in, they are always input
        analogWrite(analogLeds[i], read);
        analogWrite(analogOuts[i], read);
    }
}