int enable_pin1_2 = 9;
int enable_pin3_4 = 3;
int input1 = 13;
int input2 = 8;
int input3 = 7;
int input4 = 4;
int sensor_f = 10;
int sensor_r = 11;
int sensor_b = 6;
int sensor_l = 5;

long read_distance(int sensor_pin)
{
    // Variable for the duration of sound wave travel
    long duration;
    // Variable for the distance measurement
    int distance;

    pinMode(sensor_pin, OUTPUT); // Clear the trigger
    digitalWrite(sensor_pin, LOW);
    delayMicroseconds(2);

    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(sensor_pin, HIGH);
    delayMicroseconds(10);

    digitalWrite(sensor_pin, LOW);
    pinMode(sensor_pin, INPUT);

    // Reads the echo pin,the sound wave travel time in microseconds
    duration = pulseIn(sensor_pin, HIGH);

    // distance = 0.01723 * pulseIn(echoPin, HIGH);
    // distance = (distance / 2.54);
    distance = duration * 0.034 / 2;
    return distance;
}

bool check_obj(int pin)
{
    long distance = 0.0;
    distance = read_distance(pin);
    Serial.print("Distance :");
    Serial.println(distance);
    if (distance > 15)
    {
        return false;
    }
    return true;
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
    forward();
    if (check_obj(sensor_f))
    {
        Serial.println("OBSTACLE at FRONT!");
    repeat:
        if (check_obj(sensor_r))
        {
            Serial.println("OBSTACLE at RIGHT!");
            if (check_obj(sensor_l))
            {
                Serial.println("OBSTACLE at LEFT!");
                if (check_obj(sensor_b))
                {
                    Serial.println("OBSTACLE at BACK!");
                    stop();
                }
                else
                {
                    backward();
                    goto repeat;
                }
            }
            else
                left();
                }
        else
            right();
    }

    else
        forward();

    delay(10);
}

void set_speed(int speed)
{
    // Set motors to maximum speed
    // For PWM maximum possible values are 0 to 255
    analogWrite(enable_pin1_2, speed);
    analogWrite(enable_pin3_4, speed);
}

void forward()
{
    Serial.println("GOING FORWARD...");
    set_speed(255);
    // Turn on motors
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
    delay(2000);
}

void backward()
{
    Serial.println("GOING BAKWARD...");
    set_speed(150);
    // hange motor directions
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
    delay(2000);
}

void right()
{
    Serial.println("TURNING RIGHT...");
    set_speed(100);
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
    delay(2000);
}

void left()
{
    Serial.println("TURNING LEFT...");
    set_speed(100);
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}

void stop()
{
    Serial.println("STOPPING MOTORS...");
    set_speed(0);
    // Turn off motors
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
}