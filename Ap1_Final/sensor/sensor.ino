#define Sensor 12

void setup(){
  pinMode (Sensor, INPUT);
  Serial.begin(9600);

}
void loop () {
  bool ValorSensor = digitalRead(Sensor);
  
  if (ValorSensor == True) {
    Serial.println("Movimento detectado");

  } else {
    Serial.println("Sem movimento");
  }
}