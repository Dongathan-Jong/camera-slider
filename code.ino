
#include <Stepper.h>
 
#define STEPS 32
 
#define IN1  11
#define IN2  10
#define IN3   9
#define  IN4   8
 
Stepper stepper(STEPS, IN4, IN2,  IN3, IN1);
 
#define  joystick  A0
 #include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#define leftButton 3
#define rightButton 4
#define middleButton 5

int xPos = 0;
int yPos = 0;
int pos1 = 0;
int pos2 = 0;
int setupSetting = 0;
int minutes = 0;
int horiInt = 0;
int rotInt = 0;

int start = 0;
const int stepsPerRevolution = 2038;

Stepper stepper1 = Stepper(stepsPerRevolution, 6, 7, 8, 9);
Stepper stepper2 = Stepper(stepsPerRevolution, 10, 11, 12, 13);

LiquidCrystal_I2C lcd(0x3F,  16, 2);

void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(middleButton, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if(start == 0)
  {
    if(setupSetting == 0)
    {
      lcd.print("X pos:");
      if(digitalRead(leftButton) == 1)
      {
        xPos-= 10;
        stepper1.setSpeed(50);
        stepper1.step(-10);
        delay(5);
      }
      if(digitalRead(rightButton) == 1)
      {
        xPos+= 10;
        stepper1.setSpeed(50);
        stepper1.step(10);
        delay(5);
      }
      if(digitalRead(middleButton) == 1)
      {
        setupSetting++;
        lcd.clear();
      }
    }
    else if(setupSetting == 1)
    {
      lcd.print("Rot1 pos:");
      if(digitalRead(leftButton) == 1)
      {
        pos1-= 10;
        stepper2.setSpeed(50);
        stepper2.step(-10);
        delay(5);
      }
      if(digitalRead(rightButton) == 1)
      {
        pos1+= 10;
        stepper2.setSpeed(50);
        stepper2.step(10);
        delay(5);
      }
      if(digitalRead(middleButton) == 1)
      {
        setupSetting++;
        lcd.clear();
      }
    }
    else if(setupSetting == 2)
    {
      lcd.print("Y pos:");
      if(digitalRead(leftButton) == 1)
      {
        yPos-= 10;
        stepper1.setSpeed(50);
        stepper1.step(-10);
        delay(5);
      }
      if(digitalRead(rightButton) == 1)
      {
        yPos+= 10;
        stepper1.setSpeed(50);
        stepper1.step(10);
        delay(5);
      }
      if(digitalRead(middleButton) == 1)
      {
        setupSetting++;
        lcd.clear();
      }
    }
    else if(setupSetting == 3)
    {
      lcd.print("Rot2 pos:");
      if(digitalRead(leftButton) == 1)
      {
        pos2-= 10;
        stepper2.setSpeed(50);
        stepper2.step(-10);
        delay(5);
      }
      if(digitalRead(rightButton) == 1)
      {
        pos2+= 10;
        stepper2.setSpeed(50);
        stepper2.step(10);
        delay(5);
      }
      if(digitalRead(middleButton) == 1)
      {
        setupSetting++;
        lcd.clear();
      }
    } 
    else if(setupSetting == 4)
    {
      lcd.print("Minutes taken:");
      if(digitalRead(rightButton) == 1)
      {
        minutes++;
      }
      if(digitalRead(leftButton) == 1)
      {
        minutes--;
      }
      if(digitalRead(middleButton) == 1)
      {
        setupSetting++;
        lcd.clear();
      }
    }
    else if(setupSetting == 5)
    {
      start = 1;
    }
  } 
  if(start == 1)
  {
    lcd.print("Preview");
    stepper2.step(pos2);
    stepper1.step(yPos);
    start++;
    delay(2000);
  }
  if(start == 2)
  {
    horiInt = (int)((0-yPos) / (minutes * 2));
    rotInt = (int)((0-pos2) / (minutes * 2));

    for(int i = 0; i < (minutes * 2); i++)
    {
      stepper1.setSpeed(10);
      stepper2.setSpeed(10);
      stepper2.step(horiInt);
      stepper1.step(rotInt);
      delay(500);
    }
    lcd.clear();
    lcd.print("Finished!");
    start++;
  }
}



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
