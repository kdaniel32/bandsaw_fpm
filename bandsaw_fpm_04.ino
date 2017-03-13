// Measure the RPM of the bandsaw drive wheel and display it on the LED display in FPM

// Include the TM1638 LED display module library
      // TM1638 library
      // --------------
      // Ricardo Batista
      // Email: rjbatista(at)gmail.com
      // URL: https://github.com/rjbatista/tm1638-library/

#include <TM1638.h>

// define a module on data pin 8, clock pin 9 and strobe pin 7

TM1638 module(8, 9, 7);

const int buttonPin = 5;    // the pin that the proximity sensor is attached to
const int ledPin = 13;      // the pin that the LED is attached to

const float pulses_per_revolution = 5.0;       // the drive wheel has five spokes
const float circumference_in_feet = 3.1875;    // circumference of the drive wheel
const int pulse_count_interval = 1000;         // 1000 is a one second interval
const float ms_per_minute = 60000.0;

float feet_per_pulse;
float feet_per_minute;
float pulse_count_intervals_per_minute;
int pulse_count;

int buttonState = 0;         
int lastButtonState = 0;     

unsigned long time_start;
unsigned long time_elapsed;


void setup() {
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);

   module.clearDisplay();
   feet_per_pulse = circumference_in_feet / pulses_per_revolution;
   pulse_count_intervals_per_minute = ms_per_minute / float(pulse_count_interval);

} // end setup()


void loop() {
  
   time_start = millis();
   time_elapsed = 0;
   pulse_count = 0;
  
   while ( time_elapsed < pulse_count_interval){
      buttonState = digitalRead(buttonPin);

      if (buttonState != lastButtonState) {
         // increment pulse_count on transition from LOW to HIGH
         if (buttonState == HIGH) {
            pulse_count++;
            digitalWrite(ledPin, HIGH);
         } 
         else {
            digitalWrite(ledPin, LOW);
         } //endif
      } //endif
      
      lastButtonState = buttonState;
      time_elapsed = millis() - time_start;   
   } //endwhile 
  
    
   // multiply pulse_count by feet_per_pulse and pulse_count_intervals_per_minute to get feet_per_minute
   feet_per_minute = float(pulse_count) * feet_per_pulse * pulse_count_intervals_per_minute;
  
   module.clearDisplay();
  
   if (feet_per_minute > 0) {
      // multiply feet_per_minute by 100 to get two decimal places on the display
      module.setDisplayToDecNumber(long(feet_per_minute * 100.0), 4, false);
   } 
   else {
      // set display to read 0.00
      module.setDisplayDigit(0, 5, true);
      module.setDisplayDigit(0, 6, false);
      module.setDisplayDigit(0, 7, false);
   } //endif

} // end loop()
