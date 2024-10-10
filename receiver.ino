#define RF_PIN 10       // 433 MHz přijímač
#define MOSFET_PIN 8    // MOSFET ovládající elektromagnet

void setup() {
  Serial.begin(9600);
  pinMode(MOSFET_PIN, OUTPUT);   // Pin pro MOSFET
  pinMode(RF_PIN, INPUT);        // Pin pro 433 MHz přijímač
  Serial.println("System ready");
}

void loop() {
  unsigned long highTime = pulseIn(RF_PIN, HIGH); // Změříme délku impulzu v logické HIGH
  unsigned long lowTime = pulseIn(RF_PIN, LOW);   // Změříme délku impulzu v logické LOW
  unsigned long cycleTime = highTime + lowTime;   // Vypočítáme celkovou délku PWM cyklu
  float dutyCycle = 0.0;

  // Ošetření dělení nulou - pokud není žádný signál, přeskočíme výpočet střídy
  if (cycleTime > 0) {
    dutyCycle = ((float)highTime / (float)cycleTime) * 100; // Vypočítáme střídou PWM v %
  }

  // Ladicí výpis střídy PWM
  Serial.print("Duty cycle: ");
  Serial.println(dutyCycle);

  // Pokud je střída v rozmezí 45 - 50 %, aktivuje se elektromagnet
  if ((dutyCycle >= 45.0) && (dutyCycle <= 55.5)) {
    Serial.println("Signal detected - Activating electromagnet");
    digitalWrite(MOSFET_PIN, LOW);  // Sepne MOSFET a aktivuje elektromagnet
    delay(10000);  // Elektromagnet bude aktivní po dobu 6 sekund
    digitalWrite(MOSFET_PIN, HIGH);   // Deaktivuje MOSFET
  } else {
    digitalWrite(MOSFET_PIN, HIGH);  // Elektromagnet zůstává vypnutý, pokud není signál
  }

  delay(100);  // Krátká pauza mezi cykly
}
