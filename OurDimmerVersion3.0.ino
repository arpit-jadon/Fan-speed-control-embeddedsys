int dimming = 50;
void setup() {
 pinMode(3,OUTPUT);
 pinMode(2,INPUT);
// pinMode(13,INPUT);

Serial.begin(9600);
    
   // int AC_LOAD = 3;    // Output to Opto Triac pin
  // Dimming level (0-128)  20 = ON, 50 = OFF


  attachInterrupt(0, zero_crosss_int, RISING);  // Choose the zero cross interrupt # from the table above
}

//the interrupt function must take no parameters and return nothing
void zero_crosss_int()  //function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation : 1 full 50Hz wave =1/50=20ms 
  // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) 
  // For 60Hz => 8.33ms (10.000/120)
  // 10ms=10000us
  // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65

  int dimtime = (75*dimming);    // For 60Hz =>65    
  delayMicroseconds(dimtime);    // Wait till firing the TRIAC
  digitalWrite(3, HIGH);   // Fire the TRIAC
  delayMicroseconds(300);         // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(3, LOW);    // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
}

void loop()  {
  int pot=analogRead(A1);
  Serial.println(pot);
  if (pot<300)
  { 
    dimming=25;
    delay(10);
   }
   else if (pot>=300 && pot<500)
  { 
    dimming=50;
    delay(10);
   }
   else if (pot>=500 && pot<700)
  { 
    dimming=75;
    delay(10);
   }
     else if (pot>=700 && pot<900)
  { 
    dimming=95;
    delay(10);
   }
     else if (pot>=900 && pot<1020)
  { 
    dimming=110;
    delay(10);
   } 
   else 
  { 
    dimming=0;
    delay(10);
   }
}
