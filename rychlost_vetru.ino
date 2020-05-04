boolean state = false;
int clicked, wspd;
unsigned long lastMillis = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  pinMode(9, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("Starting wind speed measurment period.");
    lastMillis = xTaskGetTickCount();
    while(xTaskGetTickCount() - lastMillis < 10000){
        if(digitalRead(26) == HIGH) if(state == false){
            delay(50);
            clicked++;
            state = true;
        }
        if(digitalRead(26) == LOW) if(state == true) state = false;
    }
    float mps = clicked * 0.0333;
    float kph = mps * 3.6;

    Serial.print("Wind speed: ");
    Serial.print(mps);
    Serial.println( "m/s");

    
}
