#define RF_PIN 10       // 433 MHz receiver pin
#define MOSFET_PIN 8    // MOSFET LR7843 pin

void setup() {
  Serial.begin(9600);
  pinMode(MOSFET_PIN, OUTPUT);   //MOSFET setup
  pinMode(RF_PIN, INPUT);        //receiver setup
  Serial.println("System ready");
}

void loop() {
  unsigned long highTime = pulseIn(RF_PIN, HIGH);
  unsigned long lowTime = pulseIn(RF_PIN, LOW);
  unsigned long cycleTime = highTime + lowTime; 
  float dutyCycle = 0.0;
  
  if (cycleTime > 0) {
    dutyCycle = ((float)highTime / (float)cycleTime) * 100;
  }

  //debug
  Serial.print("Duty cycle: ");
  Serial.println(dutyCycle);

  // if the class is in the range about 45%-55.5%, it will disable the MOSFET
  if ((dutyCycle >= 45.0) && (dutyCycle <= 55.5)) {
    Serial.println("Signal detected - Deactivating MOSFET");
    digitalWrite(MOSFET_PIN, LOW);  //disable the mosfet (change to HIGHT instead of LOW if your mosfet activates at this point)
    delay(10000);  //10 seconds delay for cooling
    digitalWrite(MOSFET_PIN, HIGH);   //activate mosfet (change to LOW instead of HIGH if your mosfet disables at this point)
  } else { //If the class is in a different range
    digitalWrite(MOSFET_PIN, HIGH);  // MOSFET is still activated until the signal is detected
  }

  delay(100);
}
