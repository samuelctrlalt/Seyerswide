
/*
Project: Generate a pulse from the ADC input from a POT
Date:    13th June 2021
Author:  Samuel Raj
Company: Seyerswide Pte Ltd (Singapore)
Email:   info@seyerswide.com 
*/
#define BTN          12   // Button/Switch
#define PULSE        9    // OUTPUT Pulse to trigger
#define POT          A3   // POTENTIAL 

#define INTERVAL     1000 // 1000ms (1 second)
#define FIL          2000 // Simple debounce filter
#define MIN_WIDTH    10

unsigned char RELEASE         = 1;
unsigned int  ADC_POT, FILTER = 0;
unsigned long previousMillis  = 0;
const    long interval        = INTERVAL; // Sampling rate of ADC
unsigned long currentMillis;

void setup() 
{
  Serial.begin(115200);  // You can get a 1 second update of the current interval programmed
  pinMode(BTN,    INPUT_PULLUP); // Set as active low
  pinMode(PULSE, OUTPUT);
}

void loop() 
{
  currentMillis = millis(); 
  
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    
    ADC_POT = analogRead(POT);
    if(ADC_POT < MIN_WIDTH)
    {
      ADC_POT = MIN_WIDTH;
    }
    else
    {
      ADC_POT -= (ADC_POT%10);
    }
    Serial.print(ADC_POT);  
    Serial.println(" ms"); 
  }
  if((digitalRead(BTN)==HIGH) && (RELEASE == 1))
  {
    if(FILTER < FIL+1) // Prevent overflow of counter
      FILTER++;
      
    if(FILTER > FIL)   // Debounce filter
    {
      FILTER = 0;
      RELEASE = 0;    // Flag release of button from ACTIVE position
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
