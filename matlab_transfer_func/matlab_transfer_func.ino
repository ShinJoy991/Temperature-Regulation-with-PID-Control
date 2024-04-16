#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(6, 5, 4, 3);
double input, output;    // Current input and output
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0
int pwmval = 0;
const int PWM = 11;

void setup() {
  Serial.begin(115200, SERIAL_8N1); // Set the baud rate to match the MATLAB script
  pinMode(PWM, OUTPUT);
  thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
}

void loop() {

  input = thermo.temperature(RNOMINAL, RREF);

  if (Serial.available() > 0)
  {
    pwmval = Serial.parseInt();
    Serial.println(input, 6); // 6 decimal places precision
  }

  analogWrite(PWM, pwmval);

// Print out for debug
//  Serial.println(pwmval);
//  Serial.println(input);
// The delay is pretty slow if you ask
  delay (500);

}