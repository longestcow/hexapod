#include <Servo.h>
Servo servo;
void setup() {
  servo.attach(3);
  servo.writeMicroseconds(2600);
//  delay(2000);
//  servo.writeMicroseconds(2400);

}

void loop() {
  // put your main code here, to run repeatedly:

}
