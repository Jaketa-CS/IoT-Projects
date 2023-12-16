// [Simon Says Game]
// Author: Jake Teeter
// Summary: This project  implements a simple Simon Says game where the LEDs
//              flash in a pattern, and the player must repeat the pattern by pressing
//              corresponding buttons. The game includes button debouncing for accurate
//              user input.

int LED_count = 0;

// Button and LED pin assignments
const int BUTTON_GREEN = 4;
const int BUTTON_YELLOW = 3;
const int BUTTON_RED = 2;

const int LED_GREEN = 13;
const int LED_YELLOW = 12;
const int LED_RED = 11;

// Arrays: store the randomly generated pattern and user's input
int event[4];
int guess[4];

// Index variables for tracking the current step in the pattern and user input
int userIndex = 1;
int patternIndex = 1;

long randNumber;

// Variables for button debouncing
int buttonTime = 0;
int debounceHandle = 0;

// Function to generate and display the pattern of flashing LEDs
void pattern(int LED_count) {
  while (patternIndex <= LED_count + 3) {
    delay(100);
    randNumber = rand() % 3;

    // Generate and display the pattern based on the random number
    if (randNumber < 1) {
      event[patternIndex] = 1;
      digitalWrite(LED_GREEN, HIGH);
      delay(500);
    } else if (randNumber > 1 && randNumber < 3) {
      event[patternIndex] = 2;
      digitalWrite(LED_YELLOW, HIGH);
      delay(500);
    } else {
      event[patternIndex] = 3;
      digitalWrite(LED_RED, HIGH);
      delay(500);
    }

    // Turn off LEDs and advance the pattern index
    delay(500);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    patternIndex++;
  }
}

void setup() {
  // Set up pin modes for LEDs and buttons
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_YELLOW, INPUT);
  pinMode(BUTTON_GREEN, INPUT);

  Serial.begin(57600);
  randomSeed(analogRead(A0));
  Serial.print("\n[SIMON SAYS]\n");
}

void loop() {
  // Generate and display the pattern
  pattern(LED_count);

  // User input loop
  while (patternIndex > userIndex) {
    // Read button states and debounce logic
    int buttonRedState = digitalRead(BUTTON_RED);
    int buttonYellowState = digitalRead(BUTTON_YELLOW);
    int buttonGreenState = digitalRead(BUTTON_GREEN);

    // Turn off LEDs
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);

    // Check button presses and update user input
    if (buttonGreenState == HIGH && (debounceHandle - buttonTime) >= 2000) {
      buttonTime = millis();
      digitalWrite(LED_GREEN, HIGH);
      guess[userIndex] = 1;

      // Check if the user input matches the pattern
      if (guess[userIndex] == event[userIndex]) {
        Serial.println("(correctly entered green)");
      } else {
        Serial.println("INCORRECT... Try again.");
      }

      userIndex++;
      delay(200);
    } else if (buttonYellowState == HIGH && (debounceHandle - buttonTime) >= 2000) {
      buttonTime = millis();
      digitalWrite(LED_YELLOW, HIGH);
      guess[userIndex] = 2;

      // Check if the user input matches the pattern
      if (guess[userIndex] == event[userIndex]) {
        Serial.println("(correctly entered yellow)");
      } else {
        Serial.println("INCORRECT... Try again.");
      }

      userIndex++;
      delay(200);
    } else if (buttonRedState == HIGH && (debounceHandle - buttonTime) >= 2000) {
      buttonTime = millis();
      digitalWrite(LED_RED, HIGH);
      guess[userIndex] = 3;

      // Check if the user input matches the pattern
      if (guess[userIndex] == event[userIndex]) {
        Serial.println("(correctly entered red)");
      } else {
        Serial.println("INCORRECT... Try again.");
      }

      userIndex++;
      delay(200);
    }

    debounceHandle = millis();
  }

  // Reset index variables and wait before starting a new round
  patternIndex = 1;
  userIndex = 1;
  delay(1000);
  Serial.println("-----------[Nailed it!!]-----------------");
}
//NOTES--------------------------------------------------------------------------------------------
/*
 [Debouncing] is used to eliminate or reduce the effects of noise and unwanted signals
 when reading the state of mechanical buttons. It introduces a delay to filter out
 rapid changes in button state, ensuring a stable signal is read by the microcontroller.
      In this project, debounce logic is applied to button presses
      to prevent false readings caused by the mechanical bouncing of the buttons!
*/
