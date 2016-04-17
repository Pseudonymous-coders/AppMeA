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
  // put your main code here, to run repeatedly:
  for (int i; i < 30; i++) {
    sensorVal = analogRead(sensorPin);
    if (sensorVal >= 78) {
      counter += 1;
    }
    delay(1000);
  }
  if (counter<=5) {
    if (counter > 2) {
      Serial.println("0");
    }
  }
  if (counter > 5) {
    Serial.println("1");
  }
  if (counter <= 2) {
    Serial.println("2");
  }
  counter = 0;
  delay(200);
}
