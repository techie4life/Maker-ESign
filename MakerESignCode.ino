const int FETout = 2; //output for the gate on the mosfet
const int ON = 7; //on button input
int buttonStateOn = 1; 
int buttonStateOff = 0;
unsigned long timer = 5000000; 
int LastButtonPress = 0;
int debounceDelay = 20;
int lastDebounce = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(FETout, OUTPUT);
pinMode(ON, INPUT_PULLUP);
//pinMode(RESET,INPUT);
Serial.begin(9600);
digitalWrite(FETout,LOW);

}


void loop() {
int reading = digitalRead(ON);
Serial.println(reading);
if(reading!= buttonStateOn){
  lastDebounce = millis();
  
}
if(millis() - lastDebounce > debounceDelay){
  LastButtonPress = millis();
}

if(millis()-LastButtonPress < timer){ //if the difference in system clock and time when button was pressed is less than the timer (the amount of time lights should be on) then
  //the lights will be turned on. When the difference in time exceeds the desired timing, the lights turn off.
  digitalWrite(FETout,HIGH);
}
else if(millis()-LastButtonPress >= timer){
digitalWrite(FETout,LOW);
}

}
