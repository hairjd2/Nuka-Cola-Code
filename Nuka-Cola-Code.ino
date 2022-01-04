const int quarterButton = 2; //quarter button
const int dimeButton = 4;
const int ledPin = 13;// the number of the LED pin

// Variables will change:
int ledState = LOW;
int quarterState;
int dimeState;
int lastQuarterState = LOW;
int lastDimeState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int inputtedValue = 0;

void setup() {
  pinMode(quarterButton, INPUT);
  pinMode(dimeButton, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int readingQuarter = digitalRead(quarterButton);
  int readingDime = digitalRead(dimeButton);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingQuarter != lastQuarterState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (readingDime != lastDimeState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingQuarter != quarterState) {
      quarterState = readingQuarter;


      // only toggle the LED if the new button state is HIGH
      if (quarterState == HIGH) {
        inputtedValue += 25;
      }
    }

    if (readingDime != dimeState) {
      dimeState = readingDime;


      // only toggle the LED if the new button state is HIGH
      if (dimeState == HIGH) {
        inputtedValue += 10;
      }
    }

    if(inputtedValue >= 50) {
      inputtedValue -= 50;
      digitalWrite(ledPin, HIGH);
      delay(5000);
    }
  }

  // set the LED:
  digitalWrite(ledPin, LOW);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastQuarterState = readingQuarter;
  lastDimeState = readingDime;
}
