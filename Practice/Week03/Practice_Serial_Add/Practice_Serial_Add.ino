void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    String str;
    str = Serial.readString();

    int pos = str.lastIndexOf(',');

    String num1_str = str.substring(0, pos);
    String num2_str = str.substring(pos + 1, str.length());

    Serial.println(num1_str.toInt() + num2_str.toInt());
  }
}