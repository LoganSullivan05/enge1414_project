
// Changing the setup. Instead of playing notes if the frequencies are !=0, play notes if values are below the threshold.
global double note0 = 262, note1 = 294, note2 = 330, note3 = 349, note4 = 392, note5 = 440, note6 = 494;
// 			  C4			 D4			    E4			   F4			  G4			 A5				B5
global double[] noteArr = {note0, note1, note2, note3, note4, note5, note6};

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
	if (digitalRead(4)) {
		fifthUP();
	}
	else if (digitalRead(5)) {
		fifthDOWN();
	}
	else if (digitalRead(6)) {
		fifthRESET();
	}

  int value0 = analogRead(A1);
  int value1 = analogRead(A2);
  int value2 = analogRead(A3);
  int value3 = analogRead(A4);
  int value4 = analogRead(A5);
  int value5 = analogRead(A6);
  int value6 = analogRead(A7);

	int[] valArr = {value0, value1, value2, value3, value4, value5, value6};

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
    playChord(noteArr, valArr, 100);
  }
}

// Changing to operate with arrays instead
//! doesnt work as intended
void playChord(double[] frequencies, int[] thresholds, int duration) {
	unsigned long start = millis();

  int duration_ms = 5;
  int delay_ms = duration_ms;

	while (millis() - start < duration) {
		if(thresholds[0] > 400) { tone(10, frequencies[0], duration_ms); delay(2); }
		if(thresholds[1] > 400) { tone(10, frequencies[1], duration_ms); delay(2); }
		if(thresholds[2] > 400) { tone(10, frequencies[2], duration_ms); delay(2); }
    if(thresholds[3] > 400) { tone(10, frequencies[3], duration_ms); delay(2); }
    if(thresholds[4] > 400) { tone(10, frequencies[4], duration_ms); delay(2); }
    if(thresholds[5] > 400) { tone(10, frequencies[5], duration_ms); delay(2); }
    if(thresholds[6] > 400) { tone(10, frequencies[6], duration_ms); delay(2); }
	}

	noTone(10);
}

void fifthUP() {
	for (int i = 0; i < sizeof(noteArr)/sizeof(noteArr[0]); i++) {
		noteArr[i] *= (2.0**(7.0/12.0));
	}
}
void fifthDOWN() {
	for (int i = 0; i < sizeof(noteArr)/sizeof(noteArr[0]); i++) {
		noteArr[i] /= (2.0**(7.0/12.0));
	}
}
void fifthRESET() {
	note0 = 262, note1 = 294, note2 = 330, note3 = 349, note4 = 392, note5 = 440, note6 = 494;
}
