const int button = 2; //connect to pin 2
const int ledLight = 9; //connect to pin 9
int ledMode = 0;

//fuction fade LED
unsigned long fadePreviousMillis = 0;
const unsigned long fadePeriod = 2;
byte brightness = 0; //byte value only can be around 0-255
byte fadeIncrement = 1;

//function blink LED
unsigned long blinkPreviousMillis = 0;
const unsigned long blinkPeriod = 130;
int ledState = LOW;

//variable for button debounces
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 20;

void setup() {
  pinMode(button, INPUT);
 Serial.begin(9600);
}

void loop() {

  int reading = digitalRead(button);
  Serial.println(ledMode);
 if (reading != lastButtonState) {
  lastDebounceTime = millis();
 }

 if((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != buttonState) {
    buttonState = reading;

    if (buttonState == HIGH) {
      ledMode++;
    }
  }
 }
lastButtonState = reading;

//enter LED state
if (ledMode == 0) {
  digitalWrite(ledLight, LOW);
}

//stagnant led
if (ledMode == 1) {
  digitalWrite(ledLight, HIGH);
  }
//blinking led
if (ledMode == 2) {
  if (millis() - blinkPreviousMillis >= blinkPeriod) {
    blinkPreviousMillis = millis();
  if (ledState == LOW) {
    ledState = HIGH;
  }
else {
  ledState = LOW;
}
digitalWrite(ledLight, ledState);
  }
}

//fade led mode
if (ledMode == 3) {

 if (millis() - fadePreviousMillis >= fadePeriod) {
  fadePreviousMillis = millis();

  analogWrite(ledLight, brightness);
  brightness += fadeIncrement;

  if (brightness <= 0 || brightness >= 255) {
    fadeIncrement =- fadeIncrement;
  }
 }
}

  while (ledMode >= 4) {
    ledMode = 0;
}

  }

