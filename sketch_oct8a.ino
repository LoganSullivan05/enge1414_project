void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

// TEST_MODE values:
// 0: base test (output 440hz constantly)
// 1: play note0 (regardless of 0 or not)
// 2: play note0 only if one photoresistor reaches threshold
// 3: play chords (multiple notes at once)

const int TEST_MODE = 0;

void loop() {

  int value0 = analogRead(A0);
  int value1 = analogRead(A1);
  int value2 = analogRead(A2);
  int value3 = analogRead(A3);

	Serial.print(value0);
	Serial.print(", ");
  Serial.print(value1);
	Serial.print(", ");
  Serial.print(value2);
	Serial.print(", ");
	Serial.println(value3);

  if(TEST_MODE == 0){
    tone(10, 440);
    delay(100);
    noTone(10);
    return;
  }

  int note0 = 0, note1 = 0, note2 = 0, note3 = 0;
  if(value0 < 200) note0 = 370;
  if(value1 < 200) note1 = 393;
  if(value2 < 200) note2 = 415;
  if(value3 < 200) note3 = 440;

    if(TEST_MODE == 1){
      tone(10, note0);
      delay(100);
      noTone(10);
      return;
    }

    if(TEST_MODE == 2){
      if(note0 == 0) return;
      tone(10, note0);
      delay(100);
      noTone(10);
      return;
    }

    if(TEST_MODE == 3){
      playChord(note0, note1, note2, note3, 100);
    }
}



void playChord(int f1, int f2, int f3, int f4, int duration) {
	unsigned long start = millis();
  int delay_ms = 2;
	while (millis() - start < duration) {
		if(f1 != 0) tone(10, f1, delay_ms); delay(delay_ms);
		if(f2 != 0) tone(10, f2, delay_ms); delay(delay_ms);
		if(f3 != 0) tone(10, f3, delay_ms); delay(delay_ms);
    if(f4 != 0) tone(10, f4, delay_ms); delay(delay_ms);
	}
	noTone(10);
}
