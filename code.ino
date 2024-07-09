
#include <Stepper.h>
#define leftButton 2
#define rightButton 3
#define middleButton 4

int xPos = 0;
int yPos = 0;
int pos1 = 0;
int pos2 = 0;
int setupSetting = 0;
int minutes = 0;
int horiInt = 0;
int rotInt = 0;
int counter = 0;

int start = 0;
const int stepsPerRevolution = 2038;
int fullLength = 15630;
int fullRotation = 300;

Stepper stepper1 = Stepper(stepsPerRevolution, 5, 6, 7, 8);
Stepper other = Stepper(stepsPerRevolution, 9, 10, 11, 12);


void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(middleButton, INPUT_PULLUP);
  Serial.begin(9600);
  other.setSpeed(5);
  stepper1.setSpeed(5);
}

void loop() {

  for(int i = 0; i < (60*60); i++)
  {
    counter++;
    delay(1000);
    stepper1.step(4);
    
    if(counter % 12 == 0)
    {
      other.step(-1);
    }
  }
  stepper1.setSpeed(10);
  other.setSpeed(10);
  stepper1.step(0-fullLength);
  other.step(fullRotation);
}
