#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Arduino.h>

const char *ssid = "ESP32-AP";      // SSID of the AP
const char *password = "123456789"; // Password of the AP

WiFiServer server(80);

const int pin1 = 12;
const int pin2 = 13;
const int pin3 = 14;
const int pin4 = 15;

enum NUMS
{
    NONE,
    ONE,
    TWO,
    THREE,
    FOUR
};

NUMS state = NONE;

NUMS stringToNum(int num)
{
    if (num == 49)
        return ONE;
    else if (num == 50)
        return TWO;
    else if (num == 51)
        return THREE;
    else if (num == 52)
        return FOUR;
    else if (num == 10)
        return state;
    else
        return NONE;
}

void setup()
{
    Serial.begin(115200);

    // Set up the AP
    Serial.println("Setting up AP...");
    WiFi.softAP(ssid, password);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Start the server
    server.begin();
    Serial.println("Server started");

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
}

void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (client)
    {
        // Read data from the client
        while (client.connected())
        {
            if (client.available())
            {
                int input = client.read();
                Serial.println(input);
                state = stringToNum(input);
                switch (state)
                {
                case ONE:
                    Serial.println("Number is ONE");
                    digitalWrite(pin1, HIGH);
                    digitalWrite(pin2, LOW);
                    digitalWrite(pin3, LOW);
                    digitalWrite(pin4, LOW);
                    break;
                case TWO:
                    Serial.println("Number is TWO");
                    digitalWrite(pin1, HIGH);
                    digitalWrite(pin2, HIGH);
                    digitalWrite(pin3, LOW);
                    digitalWrite(pin4, LOW);
                    break;
                case THREE:
                    Serial.println("Number is THREE");
                    digitalWrite(pin1, HIGH);
                    digitalWrite(pin2, HIGH);
                    digitalWrite(pin3, HIGH);
                    digitalWrite(pin4, LOW);
                    break;
                case FOUR:
                    Serial.println("Number is FOUR");
                    digitalWrite(pin1, HIGH);
                    digitalWrite(pin2, HIGH);
                    digitalWrite(pin3, HIGH);
                    digitalWrite(pin4, HIGH);
                    break;
                default:
                    Serial.println("OFF");
                    digitalWrite(pin1, LOW);
                    digitalWrite(pin2, LOW);
                    digitalWrite(pin3, LOW);
                    digitalWrite(pin4, LOW);
                    break;
                }
            }
        }
    }
}
