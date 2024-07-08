
#include <Stepper.h>
 
#define STEPS 32
 
#define IN1  11
#define IN2  10
#define IN3   9
#define  IN4   8
 
Stepper stepper(STEPS, IN4, IN2,  IN3, IN1);
 
#define  joystick  A0
 
void setup()
{
  
}
 
void loop()
{
  int val = analogRead(joystick);
  
  if(  (val > 500)  && (val < 523) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2,  LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
 
  else
  {
    while (val  >= 523)
    {
      int speed_  = map(val, 523, 1023, 5, 500);
      stepper.setSpeed(speed_);
  
      stepper.step(1);
 
      val  = analogRead(joystick);
    }
 
    while (val <= 500)
    {
      int speed_ = map(val, 500, 0, 5, 500);
      stepper.setSpeed(speed_);
  
      stepper.step(-1);
 
      val  = analogRead(joystick);
    }
 
  }
 
}
