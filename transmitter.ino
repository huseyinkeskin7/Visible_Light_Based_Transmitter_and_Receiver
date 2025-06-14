const int MAX_STRING_LENGTH = 100; // Maksimum string length 
char receivedString[MAX_STRING_LENGTH]; // An array to store the received string
bool newcom=1; // When the program starts, it determines that there is a new communication.
#define LED 13
#define period 200 // sending time for each bit
void setup() {
pinMode(LED, OUTPUT); // We determine our light source as output
Serial.begin(9600);   // starts serial monitor 
}

void loop() {
if (Serial.available() > 0) {
    // If data came from the serial port
    String inputString = Serial.readStringUntil('\n'); // Read data up to end of line
    inputString.toCharArray(receivedString, MAX_STRING_LENGTH); // Convert to char array
    // Process data
    for (int i = 0; i < inputString.length(); i++) 
    {//sends each character one by one to the start communication function
    startcommunication(inputString[i]);
    delay(200);// delay for idle 
    }
  }
}

void startcommunication(char chracter)
{
  if(newcom){sendsenkron();} // if its first input it goes to sendsenkron function 
  digitalWrite(LED, LOW);// start bit
  delay(period); // delay for bit
  for (int i = 7; i >= 0; --i) {//It sets the light source to 0 or 1, starting from the 7th bit and ending with the 0th bit, depending on the ASCII code of the character.
    digitalWrite(LED,(bitRead(chracter, i)));
    Serial.print(bitRead(chracter, i));
    delay(period);
  }
  Serial.println(" ");
  digitalWrite(LED, HIGH);// idle
}

void sendsenkron() {// send sync pulse for one time which is 10101010
delay(period);

  for (int i = 0; i < 3; i++) {
    digitalWrite(LED, HIGH);
    delay(period);
    digitalWrite(LED, LOW);
    delay(period);
  }
  digitalWrite(LED, HIGH);
  delay(period);
  digitalWrite(LED, LOW);
  newcom =! newcom;
}
