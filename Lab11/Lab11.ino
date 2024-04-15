int relayPin = 9;
int no_input_pin = 11;

long start = 0;
long end = 0;

void setup() {
  Serial.begin(57600);
  Serial.println("Hello");
  pinMode(relayPin, OUTPUT);
  pinMode(no_input_pin, INPUT_PULLUP);
}

void loop() {
  start = micros();
  //digitalWrite(relayPin, 1);
  PORTB = 0b00000010 | PORTB;

  while((PINB & 0b00001000) != 0) {
    // wait
  }
  end = micros();
  long diff = end - start;
  Serial.println(diff);

  digitalWrite(relayPin, 0);

  delay(1000);
}
