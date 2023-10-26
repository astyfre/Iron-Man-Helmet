#include <Servo.h>

Servo servo1;
Servo servo2;
int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;
int servoPosition = 0; // 0 for open, 1 for closed
int ledPin = 4;
int ledState = LOW;
unsigned long buttonPressStartTime = 0; // Variable to store the start time of the button press
bool longPressDetected = false; // Flag to indicate a long press

void setup() {
  servo1.attach(9);  // Attach servo to pin 9
  servo2.attach(10); // Attach servo to pin 10
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  servoPosition = 1;
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Check if the button state has changed
  if (buttonState != lastButtonState) {
    // If the button is pressed
    if (buttonState == HIGH) {
      buttonPressStartTime = millis(); // Record the start time of the press
      longPressDetected = false; // Reset longPressDetected flag
    } else {
      unsigned long buttonPressDuration = millis() - buttonPressStartTime; // Calculate the duration of the press
      if (buttonPressDuration >= 1000) { // Adjust the duration as needed for your long-press threshold
        longPressDetected = true; // Set longPressDetected flag
      } else {
        // Toggle the servo position
        servoPosition = 1 - servoPosition;
        servo1.attach(9);
        servo2.attach(10);
        // Set the servos based on the servoPosition
        if (servoPosition == 1) {
          // Closed position
          servo1.write(65);
          servo2.write(120);
          digitalWrite(ledPin, HIGH);
          delay(500);
          servo1.detach();
          servo2.detach();
        } else {
          // Open position
          servo1.write(5);
          servo2.write(175);
          digitalWrite(ledPin, LOW);
          delay(500);
          //servo1.detach();
          //servo2.detach();
        }
      }
    }
    delay(50); // debounce delay
  }

  // Check for a long press and toggle the LED
  if (longPressDetected) {
    ledState = !ledState; // Toggle the LED state
    digitalWrite(ledPin, ledState); // Apply the new LED state
    longPressDetected = false; // Reset longPressDetected flag
  }

  // Store the current button state for comparison
  lastButtonState = buttonState;
}
