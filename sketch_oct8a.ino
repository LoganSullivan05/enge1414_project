void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  // pinMode(10, INPUT);
  // pinMode(10, INPUT);

	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

// TEST_MODE values:
// 0: base test (output 440hz constantly)
// 1: play note0 (regardless of 0 or not)
// 2: play note0 only if one photoresistor reaches threshold
// 3: play chords (multiple notes at once)

const int TEST_MODE = 3;

void loop() {

  int value0 = analogRead(A1);
  int value1 = analogRead(A2);
  int value2 = analogRead(A3);
  int value3 = analogRead(A4);
  int value4 = analogRead(A5);
  int value5 = analogRead(A6);
  int value6 = analogRead(A7);

	Serial.print(value0);
	Serial.print(", ");
  Serial.print(value1);
	Serial.print(", ");
  Serial.print(value2);
	Serial.print(", ");
	Serial.print(value3);
  Serial.print(", ");
  Serial.print(value4);
	Serial.print(", ");
	Serial.print(value5);
  Serial.print(", ");
	Serial.println(value6);
  
  if(TEST_MODE == 0){
    tone(10, 440);
    delay(100); // this line delays 500ms for test_mode 0 (change val to change log speed)
    noTone(10);
    return;
  }

  int note0 = 0, note1 = 0, note2 = 0, note3 = 0, note4 = 0, note5 = 0, note6 = 0;
  int note_threshold = 400;
  if(value0 < note_threshold) note0 = 370;
  if(value1 < 400) note1 = 393;
  if(value2 < note_threshold) note2 = 415;
  if(value3 < note_threshold) note3 = 440;
  if(value4 < note_threshold) note4 = 468;
  if(value5 < note_threshold) note5 = 490;
  if(value6 < note_threshold) note6 = 530;

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
    playChord(note0, note1, note2, note3, note4, note5, note6, 100);
  }
}



//! doesnt work as intended
void playChord(int f1, int f2, int f3, int f4, int f5, int f6, int f7, int duration) {
	unsigned long start = millis();

  int duration_ms = 5;
  int delay_ms = duration_ms;

	while (millis() - start < duration) {
		if(f1 != 0) { tone(10, f1, duration_ms); delay(2); }
		if(f2 != 0) { tone(10, f2, duration_ms); delay(2); }
		if(f3 != 0) { tone(10, f3, duration_ms); delay(2); }
    if(f4 != 0) { tone(10, f4, duration_ms); delay(2); }
    if(f5 != 0) { tone(10, f5, duration_ms); delay(2); }
    if(f6 != 0) { tone(10, f6, duration_ms); delay(2); }
    if(f7 != 0) { tone(10, f7, duration_ms); delay(2); }
	}

	noTone(10);
}
