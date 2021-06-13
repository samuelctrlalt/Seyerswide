#define BTN   12   // Button?
#define PULSE 9   // OUTPUT Pulse to ...
#define POT   A3  // POT
#define FIL   2000

#define MAX_TIME 1000

unsigned char RELEASE = 1;
unsigned int ADC_POT, FILTER = 0;;
unsigned long previousMillis = 0;
const long interval = 1000; // interval at which to blink (milliseconds)
  unsigned long currentMillis = millis();
void setup() 
{
  Serial.begin(115200);
  pinMode(BTN,    INPUT_PULLUP);
  pinMode(PULSE, OUTPUT);
}

void loop() 
{
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    ADC_POT = analogRead(POT);
    if(ADC_POT < 10)
      ADC_POT = 10;
    else
    {
      ADC_POT -= (ADC_POT%10);
    }
    Serial.print(ADC_POT);
    Serial.println(" ms "); 
  }
  if((digitalRead(BTN)==HIGH) && (RELEASE == 1))
  {
    if(FILTER < FIL+1)
      FILTER++;
    if(FILTER > FIL)
    {
      FILTER = 0;
      RELEASE = 0;
    }
  }

  if((digitalRead(BTN)==LOW) && (RELEASE == 0))
  {
    RELEASE = 1;
    FILTER  = 0;    

    digitalWrite(8, HIGH);
    delay(ADC_POT);
    digitalWrite(8, LOW);   
    Serial.println("STRIKE");
  }
}
