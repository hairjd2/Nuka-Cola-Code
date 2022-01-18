#include <Stepper.h>

const int CAP_BUTTON = 2; //quarter button
const int LED_PIN = 13;// the number of the LED pin
const int NEEDED_VALUE = 4;
const int MOTOR_SPEED = 50;
const int MOTOR_PIN = 9;
const int LOW_SPEED = 0;
const int HIGH_SPEED = 100;

// Variables will change:
int ledState = LOW;
int capState;
int lastCapState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int inputtedValue = 0;

void setup() {
  pinMode(CAP_BUTTON, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  // set initial LED state
  digitalWrite(LED_PIN, ledState);
  // digitalWrite(MOTOR_PIN, LOW);
  analogWrite(MOTOR_PIN, 0);
}

void loop() {
  // read the state of the switch into a local variable:
  int readingCap = digitalRead(CAP_BUTTON);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingCap != lastCapState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingCap != capState) {
      capState = readingCap;


      // only toggle the LED if the new button state is HIGH
      if (capState == HIGH) {
        inputtedValue++;
      }
    }

    if(inputtedValue >= NEEDED_VALUE) {
      inputtedValue -= NEEDED_VALUE;
      digitalWrite(LED_PIN, HIGH);
      // digitalWrite(MOTOR_PIN, HIGH);
      analogWrite(MOTOR_PIN, MOTOR_SPEED);
      delay(5000);
      analogWrite(MOTOR_PIN, 0);
      // digitalWrite(MOTOR_PIN, LOW);
    }
  }

  // set the LED:
  digitalWrite(LED_PIN, LOW);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastCapState = readingCap;
}
