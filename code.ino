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
int fullLength = 15000;
int fullRotation = 1250;

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
      lcd.setCursor(0,0);
      lcd.print("Minutes taken:");
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
        stepper1.setSpeed(5);
        stepper2.setSpeed(5);
        stepper1.step(fullLength /(minutes* 60 * 20));
        stepper2.step(0-(fullRotation /(minutes* 60 * 20)));
        Serial.println("move");
        delay(50);
      }
    }
  }

