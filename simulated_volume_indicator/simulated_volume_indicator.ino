String askForInput = "Enter a volume (0-10): ";

void setup() {
  Serial.begin(57600);

  for (int i = 2; i <= 11; i++) {
    pinMode(i, OUTPUT);
  }

  Serial.println(askForInput);
}

void loop() {
  while (!Serial.available());

  String volume = Serial.readString();
  if (!volume.toInt()) {
    Serial.println("Invalid input. Please enter a number between 0 and 10.");
    return;
  }

  int selectedVolume = volume.toInt();

  //Turn off all LEDs
  for (int i = 2; i <= 11; i++) {
    digitalWrite(i, LOW);
  }

  //Turn on LEDs up to the selected volume
  for (int i = 2; i <= selectedVolume + 1; i++) {
    digitalWrite(i, HIGH);
    delay(200);
  }

  Serial.print("You chose: ");
  Serial.println(selectedVolume);
}
