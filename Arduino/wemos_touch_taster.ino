
/* Touch button firmware *
** Author:  Oliver Alff (necotec) **
** License: GPLv3 */

#define TOUCHTASTER 16 // define pin 16 (D0) as pin for the touchpad
#define TEST_LED    4 // define pin 4 (D2) as pin for the touchpad

bool led = false; // boolean for the led state

void setup() {
  
  // set up the pins
  pinMode(TOUCHTASTER, INPUT);
  pinMode(TEST_LED, OUTPUT);

  // toggle of the led by starting
  digitalWrite(TEST_LED, LOW);
  
  // begin a serial connection for output
  Serial.begin(9600);
  Serial.println("Program started.");
}

void loop() {
  // check the state of the pin and toggle
  if(digitalRead(TOUCHTASTER))
  {
    Serial.println("Welcome to the button part."); // give a feedback on serial console
    if(led)
    {
      led = false;
    }
    else{
      led = true;
    }
    
    Serial.print("Wait / debounce..."); // give more feedback on serial console
    while(digitalRead(TOUCHTASTER))
    {
      Serial.print("."); // give more more feedback on serial console
      delay(250);
    }
    Serial.println();
    toggleLed(led); // and now, toggle the led
  }

  
}

// function for led toggle
void toggleLed(bool state)
{
  if(state)
  {
    digitalWrite(TEST_LED, HIGH);
  }
  else
  {
    digitalWrite(TEST_LED, LOW);
  }

  Serial.print("State of the LED: ");
  Serial.println(state);
}
