const int lightPin = 7;
const int keyPin = 2;

void setup() {
  //button
  pinMode(keyPin, INPUT_PULLUP);
  //light
  pinMode(lightPin, OUTPUT);
}

bool prevButton = false;

void loop() {
  bool button = digitalRead(keyPin);

  if(!button && button!=prevButton)
    digitalWrite(lightPin, !digitalRead(lightPin)); //flips current light state

  prevButton = button;
  delay(150);
}
