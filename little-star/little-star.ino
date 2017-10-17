int speakerPin = 12;
int buttonPin = 2;
 
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

int isPlaying = false;
int currentNotes = 0;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
void setup() {
  pinMode(buttonPin,INPUT_PULLUP); // Use input pullup
  pinMode(speakerPin, OUTPUT);
}
 
void loop() {
  int n = digitalRead(2);
  if (n == LOW) {
    isPlaying = !isPlaying;

    // Point to the start if turning off
    if (!isPlaying) {
      currentNotes = 0;
    }
  }

  if (isPlaying) {
    // Play the current note
    if (notes[currentNotes] == ' ') {
      delay(beats[currentNotes] * tempo); // rest
    } else {
      playNote(notes[currentNotes], beats[currentNotes] * tempo);
    }
 
    // pause between notes
    delay(tempo / 2); 

    // Next note position
    if (currentNotes == length - 1) {
      currentNotes = 0;
    } else {
      currentNotes ++;
    }
  }
}
