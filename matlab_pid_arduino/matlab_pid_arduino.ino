#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(6, 5, 4, 3);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);
double input, output;    // Current input and output
int delayTime = 0;
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0
int pwmval = 0;
const int PWM = 11;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2); //SCL A5 SDA A4
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  Serial.begin(115200, SERIAL_8N1); // Set the baud rate to match the MATLAB script

  pinMode(PWM, OUTPUT);
  pinMode(8, OUTPUT);

  thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary

  lcd.init();  
  lcd.backlight();
}

void loop() {

  input = thermo.temperature(RNOMINAL, RREF);

  if (Serial.available() > 0)
  {
    pwmval = Serial.parseInt();
    Serial.println(input, 6); // 6 decimal places precision
  }

  if (input >= 39.8)
  {
    digitalWrite(8, HIGH);
  }
  else if (input < 39.8)
  {
    digitalWrite(8, LOW);
  }
  analogWrite(PWM, pwmval);

  lcd.setCursor(2,0);
  lcd.print("TEMPERATURE:");
  lcd.setCursor(0,1);
  lcd.print("Show :  "); 
  
  lcd.setCursor(10,1);
  lcd.print(input);

// Print for debug
//  Serial.println(pwmval);
//  Serial.println(input);

  delay (500);
  lcd.clear();

}



