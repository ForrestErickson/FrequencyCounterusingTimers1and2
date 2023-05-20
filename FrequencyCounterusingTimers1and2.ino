//====================================
//Frequency Counter using Timers 1 & 2
// From: https://akuzechie.blogspot.com/2021/02/frequency-counter-using-arduino-timers.html
//====================================

//====================================
//Frequency Counter using Timers 1 & 2
// Input on pin D5
//====================================
#include <Wire.h>
#include <Adafruit_SSD1306.h>
//------------------------------------------
Adafruit_SSD1306 display(128, 64, &Wire, 4);
//------------------------------------------
volatile unsigned long totalCounts;
volatile bool nextCount;
volatile unsigned long Timer1overflowCounts;
volatile unsigned long overflowCounts;
unsigned int counter, countPeriod;
//=================================================================
void setup()
{
  Serial.begin(112500);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  analogReference(INTERNAL);
}
//=================================================================
void loop()
{
  startCount(1000);
  while(!nextCount) {}

  display.setTextColor(WHITE); display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5,0); display.print("Frequency");
  display.setCursor(0,18); display.print("=== Hz ===");
  display.setTextSize(3); display.setCursor(0,42);
  display.print(totalCounts);
  Serial.print("Total counts ");
  Serial.println(totalCounts);
  display.display();
}
//=================================================================
void startCount(unsigned int period)
{
  nextCount = false;
  counter = 0;
  Timer1overflowCounts = 0;
  countPeriod = period;
  
  //Timer 1: overflow interrupt due to rising edge pulses on D5
  //Timer 2: compare match interrupt every 1ms
  noInterrupts();
  TCCR1A = 0; TCCR1B = 0; //Timer 1 reset
  TCCR2A = 0; TCCR2B = 0; //Timer 2 reset
  TIMSK1 |= 0b00000001;   //Timer 1 overflow interrupt enable
  TCCR2A |= 0b00000010;   //Timer 2 set to CTC mode
  OCR2A = 124;            //Timer 2 count upto 125
  TIMSK2 |= 0b00000010;   //Timer 2 compare match interrupt enable
  TCNT1 = 0; TCNT2 = 0;   //Timer 1 & 2 counters set to zero
  TCCR2B |= 0b00000101;   //Timer 2 prescaler set to 128
  TCCR1B |= 0b00000111;   //Timer 1 external clk source on pin D5
  interrupts();
}
//=================================================================
ISR(TIMER1_OVF_vect)
{
  Timer1overflowCounts++;
}
//=================================================================
ISR (TIMER2_COMPA_vect)
{
  overflowCounts = Timer1overflowCounts;
  counter++;
  if(counter < countPeriod) return;

  TCCR1A = 0; TCCR1B = 0;   //Timer 1 reset  
  TCCR2A = 0; TCCR2B = 0;   //Timer 2 reset    
  TIMSK1 = 0; TIMSK2 = 0;   //Timer 1 & 2 disable interrupts

  totalCounts = (overflowCounts * 65536) + TCNT1;
  nextCount = true;
}
