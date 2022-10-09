void setup() {
Serial.begin(115200); 
}

void loop()  

{
int analogValue = analogRead(A0);
float temp = ((analogValue / 1241.21) / 0.01) - 0.50;
Serial.print("in Degree C =   ");
Serial.println(temp);

Serial.print("Raw value :");
Serial.println(analogValue);

delay(500);
}