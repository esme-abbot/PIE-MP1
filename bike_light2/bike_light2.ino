// explains which LED is in which pin
int greenLED = 13;
int yellowLED = 12;
int redLED = 11;
int whiteLED = 10;
int blueLED = 9;

// define button digital pin
const int buttonPin = 7;

// define bools for button press logic
bool buttonPin_high;
bool button_went_back_low = true;

// track button state
int pressCounter = 0;
int mode;


// track blink time 
int blink_start;
int blink_int = 500;

// track blink modes
int greenState, blueState, redState, yellowState, whiteState;

enum states {
  NONE,
  OFF,
  ON,
  BLINK
};

states state, prior_state;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:

  pinMode(buttonPin, INPUT);

  // set up LED outputs
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  prior_state = NONE;
  state = OFF;
}

void loop() {
switch (state) {
    case OFF:
      off();
      break;
    case ON:
      on();
      break;
    case BLINK:
      blink();
      break;
  }

}


bool buttonPress() { 
   buttonPin_high = digitalRead(buttonPin);
  if (button_went_back_low && buttonPin_high) {
    button_went_back_low = false;
    Serial.print("Button Pressed");
  } else if (!button_went_back_low && !buttonPin_high) {
    /*pressCounter+=1;
    mode = pressCounter % 5;
    Serial.println("Number of Presses:");
    Serial.println(pressCounter);
    Serial.println("State Mode:");
    Serial.println(mode);
    changeMode(mode);*/
    button_went_back_low = true;
    return true;
  }
  return false;
}

// helper functions for modes
void off() {

   if (state != prior_state) {         // If we are entering the state, do initialization stuff
    prior_state = state;
  }
  //turns all the LEDs off
  
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(whiteLED, LOW);
  digitalWrite(blueLED, LOW);
  Serial.println("Mode: Off");

  if (buttonPress()) {
    state = ON;
  }
}

void on() {

  
   if (state != prior_state) {         // If we are entering the state, do initialization stuff
    prior_state = state;
  }
  // turns all the LEDs on

  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(whiteLED, HIGH);
  digitalWrite(blueLED, HIGH);
  Serial.println("Mode: On");

  if (buttonPress()) {
    state = BLINK;
  }

}

void blink() {
  if (prior_state != state) {
      // all of the LEDs turn on for 500ms before turning off for 500ms
    greenState = LOW;
    yellowState = LOW;
    redState = LOW;
    whiteState = LOW;
    blueState = LOW;

    blink_start = millis();
    prior_state = state;
  }

  unsigned long currentMillis = millis(); // counts the time in ms

  // checks if it's been 500ms since the last state change
  if (currentMillis - blink_start >= blink_int) {
    blink_start = currentMillis;
    
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

if (buttonPress()) {
  state = OFF;
}


    Serial.println("Mode: Blink");

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

  Serial.println("Mode: Wave");

}
