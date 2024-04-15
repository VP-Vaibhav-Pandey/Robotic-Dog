#include <ESP32Servo.h>
#include <math.h>

Servo servo1; // Create a servo object for the first servo
Servo servo2; // Create a servo object for the second servo
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;
Servo servo12;
//70  y limit
//50,190 hold position

const float L1 = 100.0;  // Length of the first link
const float L2 = 134.5;  // Length of the second link
float theta1;
float theta2;
float targetX;
float targetY;
float X, Y;

void setup() {
  servo1.attach(2);  // Attach servo 1 to pin 9
  servo2.attach(4); // Attach servo 2 to pin 10
  servo3.attach(5);
  servo4.attach(18);
  servo5.attach(19);
  servo6.attach(21);
  servo7.attach(22);
  servo8.attach(23);
  servo9.attach(13);
  servo10.attach(12);
  servo11.attach(14);
  servo12.attach(27);
  Serial.begin(9600);


  servo9.write(90);
  servo10.write(90);
  servo11.write(90);
  servo12.write(90);
}

void loop() {
  
  ik(40,180);
  delay(700);
  ik(40,110);
  delay(700);

}

void holdposition(){
  ik(50,190);
}


void ik(float targetX, float targetY) {
  float r = sqrt(targetX * targetX + targetY * targetY);

  float cosTheta2 = (r * r - L1 * L1 - L2 * L2) / (2 * L1 * L2);

  theta2 = acos(cosTheta2);

  float alpha = atan2(targetY, targetX);
  float beta = acos((L1 * L1 + r * r - L2 * L2) / (2 * L1 * r));
  theta1 = alpha - beta;

    // Convert angles from radians to degrees
  theta1 = degrees(theta1);
  theta2 = degrees(theta2);

  servo1.write(180 - theta1);
  servo2.write(theta2);

    // front left
  servo3.write(theta1);
  servo4.write(180 - theta2);

    // back left
  servo5.write(theta1);
  servo6.write(180 - theta2);

    // back right
  servo7.write(180 - theta1);
  servo8.write(theta2);
}

void sik(float targetX, float targetY) {
  float r = sqrt(targetX * targetX + targetY * targetY);

  float cosTheta2 = (r * r - L1 * L1 - L2 * L2) / (2 * L1 * L2);

  theta2 = acos(cosTheta2);

  float alpha = atan2(targetY, targetX);
  float beta = acos((L1 * L1 + r * r - L2 * L2) / (2 * L1 * r));
  theta1 = alpha - beta;

    // Convert angles from radians to degrees
  theta1 = degrees(theta1);
  theta2 = degrees(theta2);

  servo1.write(theta1);
  servo2.write(180 - theta2);
  Serial.print("Theta1: ");
  Serial.print(theta1);
  Serial.print(", Theta2: ");
  Serial.println(theta2);
}

