// explains which LED is in which pin
int greenLED = 13;
int yellowLED = 12;
int redLED = 11;
int whiteLED = 10;
int blueLED = 9;

void setup() {
  // put your setup code here, to run once:

pinMode(greenLED, OUTPUT);
pinMode(yellowLED, OUTPUT);
pinMode(redLED, OUTPUT);
pinMode(whiteLED, OUTPUT);
pinMode(blueLED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  blink();

}

void off() {
  //turns all the LEDs off
  
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(whiteLED, LOW);
  digitalWrite(blueLED, LOW);
}

void on() {
  // turns all the LEDs on

  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(whiteLED, HIGH);
  digitalWrite(blueLED, HIGH);
}

void blink() {
  // all of the LEDs turn on for 500ms before turning off for 500ms
  int greenState = LOW;
  int yellowState = LOW;
  int redState = LOW;
  int whiteState = LOW;
  int blueState = LOW;
  
  // unsigned long stores larger variables than int
  unsigned long previousMillis = 0; // time in ms since the LED was updated

  // const keeps a variable constant
  const long interval = 500; //blinking interval

  unsigned long currentMillis = millis(); // counts the time in ms

  // checks if it's been 500ms since the last state change
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
}

  // switch on or off
    if (greenState == LOW) {
      greenState = HIGH;
    } else {
      greenState = LOW;
    }
    if (yellowState == LOW) {
      yellowState = HIGH;
    } else {
      yellowState = LOW;
    }
    if (redState == LOW) {
      redState = HIGH;
    } else {
      redState = LOW;
    }
    if (whiteState == LOW) {
      whiteState = HIGH;
    } else {
      whiteState = LOW;
    }
    if (blueState == LOW) {
      blueState = HIGH;
    } else {
      blueState = LOW;
    }

    // set the LEDs with the States of the variable
    digitalWrite(greenLED, greenState);
    digitalWrite(yellowLED, yellowState);
    digitalWrite(redLED, redState);
    digitalWrite(whiteLED, whiteState);
    digitalWrite(blueLED, blueState);
}
void wave() {
  // all of the LEDs turn on for 500ms before turning off for 500ms
  int greenState = LOW;
  int yellowState = LOW;
  int redState = LOW;
  int whiteState = LOW;
  int blueState = LOW;
  
  // unsigned long stores larger variables than int
  unsigned long previousMillis = 0; // time in ms since the LED was updated

  // const keeps a variable constant
  const long interval = 500; //blinking interval

  unsigned long currentMillis = millis(); // counts the time in ms

  // checks if it's been 500ms since the last state change
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
}
}
