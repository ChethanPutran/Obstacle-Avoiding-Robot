int enable_pin1_2 = 9;
int enable_pin3_4 = 3;
int input1 = 8;
int input2 = 7;
int input3 = 5;
int input4 = 4;
int trigger_pin = 11;
int echo_pin = 11;

long read_distance(){
  	// Variable for the duration of sound wave travel
	long duration; 
   	// Variable for the distance measurement
	int distance;
  
 	pinMode(trigger_pin, OUTPUT);  // Clear the trigger
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);

    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigger_pin, LOW);
    pinMode(echo_pin, INPUT);

    // Reads the echo pin,the sound wave travel time in microseconds
    duration = pulseIn(echo_pin, HIGH);

    //distance = 0.01723 * pulseIn(echoPin, HIGH);
    //distance = (distance / 2.54);
    distance = duration * 0.034 / 2;
    return distance;
}

void setup()
{
  // Set all the motor control pins to outputs
	pinMode(enable_pin1_2, OUTPUT);
	pinMode(enable_pin3_4, OUTPUT);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
	pinMode(input3, OUTPUT);
	pinMode(input4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
	digitalWrite(input3, LOW);
	digitalWrite(input4, LOW);
  
  
    // Serial Communication is starting with 9600 of baudrate speed
    Serial.begin(9600);
}

void loop()
{
  long distance = 0.0;
  distance = read_distance();
  Serial.print("Distance :");
  Serial.println(distance);
  if (distance > 15) {
    Serial.println("OBJECT FOUND!");
    forward();
  } else {
    right();
    distance = read_distance();
    if (distance < 15) {
    	left();
    }
  }
  delay(10);
}

void set_speed(int speed){
  	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enable_pin1_2, speed);
	analogWrite(enable_pin3_4, speed);
}

void forward(){
  	Serial.println("GOING FORWARD...");
  	set_speed(255);
	// Turn on motors
	digitalWrite(input1, HIGH);
	digitalWrite(input2, LOW);
	digitalWrite(input3, HIGH);
	digitalWrite(input4, LOW);
	delay(2000);
}

void backward(){
  	Serial.println("GOING BAKWARD...");
  	set_speed(150);
	//hange motor directions
	digitalWrite(input1, LOW);
	digitalWrite(input2, HIGH);
	digitalWrite(input3, LOW);
	digitalWrite(input4, HIGH);
	delay(2000);
}

void right(){
  	Serial.println("TURNING RIGHT...");
  	set_speed(100);
	digitalWrite(input1, HIGH);
	digitalWrite(input2, LOW);
	digitalWrite(input3, LOW);
	digitalWrite(input4, LOW);
	delay(2000);
}

void left(){
  	Serial.println("TURNING LEFT...");
  	set_speed(100);
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
	digitalWrite(input3, HIGH);
	digitalWrite(input4, LOW);
}

void stop(){
  	Serial.println("STOPPING MOTORS...");
  	set_speed(0);
	// Turn off motors
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
	digitalWrite(input3, LOW);
	digitalWrite(input4, LOW);
}