#define LED_BUILTIN 2 // integrated led diode on D2 pin
#define BUTTON 15 // button on D15 pin
#define PWM_OUT 4 // 433mhz transmitter on D4 pin

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //led setup
  pinMode(BUTTON, INPUT);  //button setup
  pinMode(PWM_OUT, OUTPUT);  //transmitter setup
}

void loop() {
  if (digitalRead(BUTTON)){ //if the button is pressed
    digitalWrite(LED_BUILTIN, HIGH); //turn on led
    analogWrite(PWM_OUT, 127); //generate signal
  }else{ //the button is not pressed
    digitalWrite(LED_BUILTIN, LOW); //turn off led
    analogWrite(PWM_OUT, 0);  //dont send a new signal
  }
  
  delay(100);
}
