#include <Stepper.h>

 const int stepsPerRevolution = 2048;  
 Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

 void setup() {
   myStepper.setSpeed(10);
 }

 void loop() {
   myStepper.step(stepsPerRevolution);
   delay(1000);   
   myStepper.step(-stepsPerRevolution);
   delay(1000);
 }
