#include "MQTT.h"
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void callback(char *MJCtest1, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void callback(char *MJCtest1, byte *payload, unsigned int length)
{
  Serial.println("Got it");

  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();
  if (String(p).equals("high"))
  {
    digitalWrite(D7, HIGH);
  }
  else if (String(p).equals("low"))
  {
    digitalWrite(D7, LOW);
  }
  else
  {
    Serial.println("hello");
  }
}

void setup()
{
  pinMode(D7, OUTPUT);
  display.setup();
}

void loop()
{
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("MJCtest1");
  }
  display.loop();
  if (display.pressedA())
  {
    Serial.println("Button A Pressed");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Button A  Pressed");
    display.display();
    client.publish("MJCtest1", "Button A Pressed");
    }
  else if (display.pressedB())
  {
    Serial.println("Button B Pressed");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Button B  Pressed");
    display.display();
    client.publish("MJCtest1", "Button B Pressed");
  }

  else if (display.pressedC())
  {
    Serial.println("Button C Pressed");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Button C  Pressed");
    display.display();
    client.publish("MJCtest1", "Button C Pressed");
  }
}