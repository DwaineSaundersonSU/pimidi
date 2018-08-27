#include <wiringPi.h>

const int redPin = 26;
const int greenPin = 19;
const int bluePin = 13;

pi_gpio_init(void)
{
    wiringPiSetupGpio();
    pinMode(redPin, INPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, PWM_OUTPUT);

}

void handle_disarm(void)
{
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
}

handle_arm(void)
{
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}

void pi_handle( unsigned char *buffer, size_t len )
{
    if (len == 3 && buffer[0] == 0xb0 && buffer[1] == 0x2c) {
        switch(buffer[2]) {
            case 0x47:
                handle_arm();
                break;

            case 0x07:
                handle_disarm();
                break;
        }
    }
}