#include <LiquidCrystal_I2C.h>
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
int fullRotation = 700;

Stepper stepper1 = Stepper(stepsPerRevolution, 5, 6, 7, 8);
Stepper other = Stepper(stepsPerRevolution, 9, 10, 11, 12);

LiquidCrystal_I2C lcd(0x3F,  16, 2);

void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(middleButton, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  other.setSpeed(5);
  stepper1.setSpeed(5);
}

void loop() {
    if(start == 0)
    {
      lcd.setCursor(0,0);
      lcd.print("Minutes taken:");
      Serial.println("s");
      if(digitalRead(rightButton) == 0)
      {
        minutes++;
        lcd.setCursor(0,1);
        lcd.print(minutes);
        delay(50);
      }
      if(digitalRead(leftButton) == 0)
      {
        minutes--;
        lcd.setCursor(0,1);
        lcd.print(minutes);
        delay(50);
      }
      if(digitalRead(middleButton) == 0)
      {
        start++;
        lcd.clear();
        delay(200);
      }
    }
    if(start == 1)
    {
      for(int i = 0; i < (minutes * 60 * 20); i++)
      {
        counter++;
        stepper1.step((fullLength)/(minutes * 60 * 20));
        moveMotor();
        delay(50);
      }
      start++;
      stepper1.setSpeed(10);
      other.setSpeed(10);
      stepper1.step(0-fullLength);
      other.step(fullRotation);
    }
  }

void moveMotor()
{
  if(counter % 10 == 0)
  {
    other.step(0-(fullRotation)/(minutes * 60 *10));
  }
}
