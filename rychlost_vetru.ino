const byte WSPEED = 3;
long lastSecond;
long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
byte seconds;

float windspeedmph = 0; // [mph instantaneous wind speed]
float windspdmph_avg2m = 0; // [mph 2 minute average wind speed mph]

void setup()
{
  Serial.begin(9600);

  pinMode(WSPEED, INPUT_PULLUP); // input from wind meters windspeed sensor

  seconds = 0;
  lastSecond = millis();
  
  attachInterrupt(WSPEED, wspeedIRQ, FALLING);


}

void wspeedIRQ()
// Activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3
{
  if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
  {
    lastWindIRQ = millis(); //Grab the current time
    windClicks++; //There is 1.492MPH for each click per second.
  }
}

void loop()
{
  //Keep track of which minute it is
  if(millis() - lastSecond >= 1000)
  {
    // digitalWrite(STAT1, HIGH); //Blink stat LED
    
    lastSecond += 1000;

    //Calc the wind speed and direction every second for 120 second to get 2 minute average
    windspeedmph = get_wind_speed();
    

    // digitalWrite(STAT1, LOW); //Turn off stat LED
  }
 Serial.print(windspeedmph);
}




  float get_wind_speed() //získání hodnot - rychlost větru
{
  float deltaTime = millis() - lastWindCheck; //750ms

  deltaTime /= 1000.0; //Covert to seconds

  float windSpeed = (float)windClicks / deltaTime; //3 / 0.750s = 4

  windClicks = 0; //Reset and start watching for new wind
  lastWindCheck = millis();

  windSpeed *= 1.492; //4 * 1.492 = 5.968MPH

  return(windSpeed);
}
