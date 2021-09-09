const int buttonPin = 7;
bool buttonPin_high;
bool button_went_back_low = true;

int pressCounter = 0;
int mode;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:

  pinMode(buttonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonPin_high = digitalRead(buttonPin);
  if (button_went_back_low && buttonPin_high) {
    button_went_back_low = false;
    Serial.print("Button Pressed");
  } else if (!button_went_back_low && !buttonPin_high) {
    pressCounter+=1;
    mode = pressCounter % 5;
    Serial.println("Number of Presses:");
    Serial.println(pressCounter);
    Serial.println("State Mode:");
    Serial.println(mode);
    button_went_back_low = true;
  }
}
