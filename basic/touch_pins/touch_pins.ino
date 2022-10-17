
void blinki(int freq){
  digitalWrite(2, HIGH);
  delay(freq);
  digitalWrite(2,LOW);
  delay(freq);
}

void london(){
  digitalWrite(2, HIGH);
}


void ledoff(){
  digitalWrite(2, LOW);
}

void setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}
void loop(){
  int d = touchRead(4);

  Serial.println(d);
  blinki(d);
  delay(100);
}
