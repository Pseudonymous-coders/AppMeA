int sensorPin = A0;
int ledPin = 11;
int sensorVal = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i; i < 30; i++) {
    sensorVal = analogRead(sensorPin);
    if (sensorVal >= 78) {
      counter += 1;
    }
    delay(500);
  }
  Serial.println(counter);
  counter = 0;
  delay(200);
}
