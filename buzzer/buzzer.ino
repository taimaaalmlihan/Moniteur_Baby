/* Arduino tutorial - Passive Buzzer Module 
   More info and circuit: http://www.ardumotive.com
   Dev: Giannis Vasilakis // Date: 12/11/2017  */
   

#define interruptPin 0 // PIN 0 for interrupt with PRG button
bool Pushdetected = false; // reset peak freq
int buzzer = 23 ;

int lum_max=700;
void gotPush(){   // reset peak freq on interrupt
 Pushdetected = true;
}

void setup ()
{

  // Define interrupt on PRG button to reset peak freq
  pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), gotPush, CHANGE);
  pinMode (buzzer, OUTPUT) ;
}
void loop ()
{
  unsigned char i, j ;
  
  while (1)
  {
if (Pushdetected){
  delay(100000000000000000000);
}
    
    for (i = 0; i <80; i++) // When a frequency sound
    {
      digitalWrite (buzzer, HIGH) ; //send tone
      delay (1) ;
      digitalWrite (buzzer, LOW) ; //no tone
      delay (1) ;
    }
    for (i = 0; i <100; i++) 
    {
      digitalWrite (buzzer, HIGH) ;
      delay (2) ;
      digitalWrite (buzzer, LOW) ;
      delay (2) ;
    }
  }
}
