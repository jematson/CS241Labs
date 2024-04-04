// This gives names to each bit from the 16-bit pattern
typedef enum {
 c0 = 0, c1, c2, c3, c4, c5, c6, c7, // columns are low 8 bits
 r0 = 8, r1, r2, r3, r4, r5, r6, r7  // rows are high 8 bits
} rc_t;

// Example of how to call send_pattern below (call from your loop)
void send_example_patterns()
{
  send_pattern(0b0000000000000000, 1000);// all off
  delay(1000);
  send_pattern(0b1111111111111111, 1000);// all on
  delay(1000);
  send_pattern(0b0011110000111100, 1000);// light up square in middle
  delay(1000);
}

/* Show this pattern on the 8x8 LED matrix.  
  "Nice" pattern bits should be 1
  for that row or column to be active,
  and 0 for inactive.
*/
void send_pattern(unsigned int nice_pattern, int delay)
{
  unsigned int raw_pattern = 0b1111111100000000 ^ nice_pattern; // rows are 0 to be lit
  send_to_arduino_pins(raw_pattern); // top pins
  send_to_shift_reg(raw_pattern); // bottom pins
  delayMicroseconds(delay);
  unsigned int zero_pattern = 0b1111111100000000;
  send_to_arduino_pins(zero_pattern);
  send_to_shift_reg(zero_pattern);
}

/*
 Pattern is a 16 bit int = 8 rows, 8 columns
 The bits tell you what the rows and columns should be doing:
  high bits  low bits
   8 rows   8 cols
   7654321076543210
*/
bool pattern_has_bit(unsigned int raw_pattern, rc_t bit)
{
  return raw_pattern & (1<<bit); // pull out this bit of the pattern
}

// Send this raw pattern to the Arduino's pins 0 through 7
void send_to_arduino_pins(unsigned int raw_pattern)
{
  digitalWrite(0, pattern_has_bit(raw_pattern, c7));
  digitalWrite(1, pattern_has_bit(raw_pattern, c6));
  digitalWrite(2, pattern_has_bit(raw_pattern, r1));
  digitalWrite(3, pattern_has_bit(raw_pattern, c0));
  digitalWrite(4, pattern_has_bit(raw_pattern, r3));
  digitalWrite(5, pattern_has_bit(raw_pattern, c5));
  digitalWrite(6, pattern_has_bit(raw_pattern, c3));
  digitalWrite(7, pattern_has_bit(raw_pattern, r0));
  // or one big PORTD call?
}

// Set up the Arduino's pins (call from setup once)
void begin_arduino_pins()
{
  for (int pin=0;pin<=7;pin++) pinMode(pin,OUTPUT);
}

// Talk to the bottom pins via a 595 shift register
int dataPin=11; // new low bit
int shiftPin=12; // shifts in new data (SRCLK)
int outputPin=13; // output current values (RCLK)

// 595 expects 8 bits: the 8 bottom pins of the 8x8 LED matrix
void send_to_shift_reg(unsigned int raw_pattern)
{
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r6));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c1));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c2));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r7));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r5));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r2));
 
  digitalWrite(outputPin,0);
  digitalWrite(outputPin,1);
}

// Send another bit to the shift register
void send_bit_to_shift_reg(int bit)
{
  digitalWrite(dataPin,bit);
  digitalWrite(shiftPin,0);
  digitalWrite(shiftPin,1);
}

// Set up the shift register pins (call from setup)
void begin_shift_reg()
{
  pinMode(dataPin,OUTPUT);
  pinMode(shiftPin,OUTPUT);
  pinMode(outputPin,OUTPUT);  
}

unsigned short kirby_patterns[19]= {
  0b0000001000111100,
  0b0000001000111100,
  0b0000001000111100,
  0b0000010001111110,
  0b0000010001111110,
  0b0000010001111110,
  0b0000100001111110,
  0b0000100001010110,
  0b0000100001010110,
  0b0001000011111111,
  0b0001000011010111,
  0b0001000001010110,
  0b0010000011111111,
  0b0010000011111111,
  0b0010000000111100,
  0b0100000001111110,
  0b0100000000111100,
  0b0100000000110000,
  0b1000000001101110
};

// draws Kirby with shading
void draw_Kirby() {
  send_pattern(0b0000001000111100, 400);
  send_pattern(0b0000001000111100, 400);
  send_pattern(0b0000001000111100, 400);
  send_pattern(0b0000010001111110, 400);
  send_pattern(0b0000010001111110, 400);
  send_pattern(0b0000010001111110, 400);
  send_pattern(0b0000100001111110, 60);
  send_pattern(0b0000100001010110, 400);
  send_pattern(0b0000100001010110, 400);
  send_pattern(0b0001000011111111, 60);
  send_pattern(0b0001000011010111, 400);
  send_pattern(0b0001000001010110, 400);
  send_pattern(0b0010000011111111, 400);
  send_pattern(0b0010000011111111, 400);
  send_pattern(0b0010000000111100, 400);
  send_pattern(0b0100000001111110, 60);
  send_pattern(0b0100000000111100, 400);
  send_pattern(0b0100000000110000, 400);
  send_pattern(0b1000000001101110, 60);
}


void setup() {
  begin_shift_reg();
  begin_arduino_pins();
}

void loop() {
  //draw_Kirby();
}
