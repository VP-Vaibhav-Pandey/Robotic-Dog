#include <ESP32Servo.h>
#include <math.h>

float thighLength = 100.0;
float shinLength = 134.5;

Servo servo1; // Create a servo object for the first servo
Servo servo2; // Create a servo object for the second servo

float diameter = 20.0; // Initial diameter of the semi-circle

void setup() {
  servo1.attach(22);  // Attach servo 1 to pin 9
  servo2.attach(23); // Attach servo 2 to pin 10
  Serial.begin(9600);
}

void loop() {
  // Move end effector in a semi-circle with variable diameter
  for (int angle = 0; angle <= 180; angle += 5) {
    // Convert angle to radians
    float radians = -angle * PI / 180.0;

    // Calculate target positions for semi-circle trajectory with variable diameter
    float targetX = 50 * cos(radians); // X-coordinate
    float targetY = 50 * sin(radians); // Y-coordinate
    float targetZ = 0.0; // Assuming the leg moves on a flat plane

    calculateIK(targetX, targetY, targetZ); // Call the inverse kinematics function

    delay(100); // Adjust delay as needed for smoother motion
  }

  // Change the diameter for the next semi-circle
  diameter += 10; // Increment the diameter (you can adjust this value)
}

void calculateIK(float targetX, float targetY, float targetZ) {
  // Calculate distance from hip to foot
  float distance = sqrt(targetX * targetX + targetY * targetY);

  // Calculate angles
  float theta1 = atan2(targetY, targetX);
  float theta2 = acos((thighLength * thighLength + shinLength * shinLength - distance * distance) /
                      (2 * thighLength * shinLength)) + atan2(targetZ, distance);

  // Convert radians to degrees for servo control
  int servoAngle1 = degrees(theta1);
  int servoAngle2 = degrees(theta2);

  // Move the servos or control mechanisms with these angles
  // For example:
  servo1.write(servoAngle1);
  servo2.write(180- servoAngle2);
}
