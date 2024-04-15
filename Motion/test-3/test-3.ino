#include <ESP32Servo.h>
#include <math.h>

Servo servo1; // Create a servo object for the first servo
Servo servo2; // Create a servo object for the second servo
//70

const float L1 = 100.0;  // Length of the first link
const float L2 = 134.5;  // Length of the second link

void setup() {
  servo1.attach(22);  // Attach servo 1 to pin 9
  servo2.attach(23); // Attach servo 2 to pin 10
  Serial.begin(9600);
}

void loop() {



  if (Serial.available() > 0) {
    float targetX, targetY;
    float theta1, theta2;

    // Read the X and Y coordinates of the target point from serial input
    targetX = Serial.parseFloat();
    targetY = Serial.parseFloat();

    // Calculate the inverse kinematics
    float r = sqrt(targetX * targetX + targetY * targetY);

    if (r > L1 + L2) {
      Serial.println("Target point is out of reach.");
      return;
    }

    float cosTheta2 = (r * r - L1 * L1 - L2 * L2) / (2 * L1 * L2);
    if (abs(cosTheta2) > 1) {
      Serial.println("No solution exists for the given target point.");
      return;
    }

    theta2 = acos(cosTheta2);

    float alpha = atan2(targetY, targetX);
    float beta = acos((L1 * L1 + r * r - L2 * L2) / (2 * L1 * r));
    theta1 = alpha - beta;

    // Convert angles from radians to degrees
    theta1 = degrees(theta1);
    theta2 = degrees(theta2);


    // back left
    servo1.write(theta1);
    servo2.write(180 - theta2);


    Serial.print("Theta1: ");
    Serial.print(theta1);
    Serial.print(", Theta2: ");
    Serial.println(theta2);
  }
}
