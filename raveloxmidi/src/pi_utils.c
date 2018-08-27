#include <stdlib.h>
#include <wiringPi.h>
#include <stdio.h>

const int redPin = 26;
const int greenPin = 19;
const int bluePin = 13;

int rec_flag = 0;

pi_gpio_init(void)
{
    wiringPiSetupGpio();
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void handle_disarm(void)
{
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    printf("Got Disarm!\n");
}

void handle_record(void)
{
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    printf("Got Record!\n");
}

void handle_arm(void)
{
    if (rec_flag) {
        return;
    }

    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    printf("Got Arm!\n");
}

void handle_cleanup(void)
{
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}

void pi_handle( unsigned char *buffer, size_t len )
{
    if (len == 3 && buffer[0] == 0xb0 && buffer[1] == 0x2c) {

        printf("Got Command %x\n", buffer[2]);g

        switch(buffer[2]) {
            case 0x47:
                handle_arm();
                break;

            case 0x07:
                handle_disarm();
                break;

            case 0x55:
                rec_flag = 1;
                handle_record();
                break;
        }
    }
}
