// explains which LED is in which pin
int greenLED = 11;
int yellowLED = 10;
int redLED = 9;
int whiteLED = 6;
int blueLED = 5;

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

// track wave time
int wave_start;
int wave_int = 100;

// track ramp time
long ramp_start;
int ramp_int = 5;
int brightness = 0;
int ramp_slope = 5;


enum states {
  NONE,
  OFF,
  ON,
  BLINK,
  WAVE,
  RAMP
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

  // set up potentiometer inputs
  pinMode(A0, INPUT);
  
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
    case WAVE:
      wave();
      break;
    case RAMP:
      ramp();
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
    Serial.println("Mode: Off");

  }
  //turns all the LEDs off
  
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(whiteLED, LOW);
  digitalWrite(blueLED, LOW);

  if (buttonPress()) {
    state = ON;
  }
}

void on() {

  
   if (state != prior_state) {         // If we are entering the state, do initialization stuff
    prior_state = state; 
    Serial.println("Mode: On");

  }
  // turns all the LEDs on

  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(whiteLED, HIGH);
  digitalWrite(blueLED, HIGH);

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
    Serial.println("Mode: Blink");

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
  Serial.println("does it get into this loop?");
  state = WAVE;
}



}
void wave() {
  if (prior_state != state){
    // enter the state
    prior_state = state;
    Serial.println("Mode: Wave");

    // start counting up for wave
    wave_start = millis();

    //initiate all of the LED toggles
    digitalWrite(greenLED, 0);
    digitalWrite(yellowLED, 0);
    digitalWrite(redLED, 0);
    digitalWrite(whiteLED, 0);
    digitalWrite(blueLED, 0);
  }
  unsigned long t = millis();
  
  if (t - wave_start >= wave_int) {
    wave_start = t;
    if (digitalRead(greenLED)) {
      
      digitalWrite(greenLED, 0);
      digitalWrite(yellowLED, 1);
      digitalWrite(redLED, 0);
      digitalWrite(whiteLED, 0);
      digitalWrite(blueLED, 0);
      
    }
    else if (digitalRead(yellowLED)) {
      digitalWrite(greenLED, 0);
      digitalWrite(yellowLED, 0);
      digitalWrite(redLED, 1);
      digitalWrite(whiteLED, 0);
      digitalWrite(blueLED, 0);
      
    } else if (digitalRead(redLED)) {
      digitalWrite(greenLED, 0);
      digitalWrite(yellowLED, 0);
      digitalWrite(redLED, 0);
      digitalWrite(whiteLED, 1);
      digitalWrite(blueLED, 0);
      
    } else if (digitalRead(whiteLED)) {
      digitalWrite(greenLED, 0);
      digitalWrite(yellowLED, 0);
      digitalWrite(redLED, 0);
      digitalWrite(whiteLED, 0);
      digitalWrite(blueLED, 1);
    } else {
      digitalWrite(greenLED, 1);
      digitalWrite(yellowLED, 0);
      digitalWrite(redLED, 0);
      digitalWrite(whiteLED, 0);
      digitalWrite(blueLED, 0);
    }
  }
  
  if (buttonPress()) { 
    state = RAMP;
  }


}


void ramp() {
  if (prior_state != state) {
    prior_state = state;
    Serial.println("Mode: Ramp");

    ramp_start = millis();

    setAllLEDsAnalog(brightness);
    
  }
  
  ramp_int = scaleRampTime(analogRead(A0));

  

  long t = millis();

  if (t - ramp_start >= ramp_int) {

    brightness = brightness + ramp_slope;

    if (brightness <= 0 || brightness >= 255) {
      ramp_slope = -ramp_slope;
    }
    
    setAllLEDsAnalog(brightness);
    ramp_start = t;
    
  }

  if (buttonPress()){
    state = OFF;
  }

}

void setAllLEDsAnalog(int val){
    analogWrite(greenLED, val);
    analogWrite(yellowLED, val);
    analogWrite(redLED, val);
    analogWrite(whiteLED, val);
    analogWrite(blueLED, val);
}

int scaleRampTime(int analogOutput) {

    int analogMin = 0;
    int analogMax = 670;
    int tMin = 5;
    int tMax = 100;
    analogOutput = max(analogMin, analogOutput);
    analogOutput = min(analogMax, analogOutput);
    return (analogOutput - analogMin) * (tMax - tMin) / (analogMax - analogMin) + tMin;

}
