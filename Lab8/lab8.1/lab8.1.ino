unsigned int last = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(56700);
  randomSeed(analogRead(A0));
  Serial.println("Started up :)");
}

void corruptMemory(void *startPointer,int nBytes,unsigned long bitErrorRate)
{
  const unsigned long megaMask=0xFFFFF; // == 20 set bits, approx 1 million
  unsigned char *start=(unsigned char *)startPointer;
  for (int i=0;i<nBytes;i++)
    for (unsigned int bit=0;bit<8;bit++)
      if ((random()&megaMask)<bitErrorRate)
        start[i] ^= (1<<bit); // flip this bit
}


void periodic_function() {
  corruptMemory((int *)0, 32, 1000);
  Serial.println(last);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int current = millis();
  unsigned int diff = current - last;

  if(diff >= 100) {
    periodic_function();
    last = millis();
  }
}
