int trigPin = 8;
int echoPin = 2;
volatile bool echo_interrupt_pending = true;
volatile long echo_end = 0;

void setup() {
  // set up serial output
  Serial.begin(57600);
  // set up ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  // set up interrupt handler
  attachInterrupt(digitalPinToInterrupt(echoPin), handle_echo_change, FALLING);
}

// interrupt handler passed to attachInterrupt
void handle_echo_change() {
  // check if the echo pin is changing the direction you expect
  // if not, just return early
  if(digitalRead(echoPin) == 0) {
    // record the micros() time of the echo to a global variable
    echo_end = micros();
    // mark that we saw the echo in another global variable
    echo_interrupt_pending = false;
    return;
  } else {
    Serial.println("ERROR echoPin state wrong");
    return;
  }
}

void loop() {
  echo_interrupt_pending = true;
  // trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); /* fire! */
  digitalWrite(trigPin, LOW);

  // record start of echo
  long echo_start = micros();
  
  while (echo_interrupt_pending) { // watch the global variable shared by the interrupt handler
    delay(10); 
  }

  // print the roundtrip travel time: echo interrupt time - start time
  long echo_time = echo_end - echo_start;
  float distance_mm = echo_time*0.343/2;
  Serial.println(distance_mm);
  delay(50); // keep the total echo rate low
}

