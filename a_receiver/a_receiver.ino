#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int n = 6;
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

struct Data
{
  int a[n];  
} data;

int packets = 0;
void printData(const struct Data& d)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(packets);
  for (int i = 0; i < n - 1; ++i)
  {
    display.println(d.a[i]);
//    Serial.print(d.a[i]);
//    Serial.print(" ");
  }
  display.println(d.a[n - 1]);
//  Serial.println(d.a[n - 1]);
  display.display();
}

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F0E2LL;

void setup(void)
{
  radio.begin();
  radio.setAutoAck(true);
  radio.setDataRate(RF24_250KBPS);
  
  radio.openReadingPipe(1, pipe);
  radio.startListening(); 
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

int thispackets = 0;
unsigned long lastsec = 0;
void loop(void)
{
  while (radio.available())
  {
    unsigned long newsec = millis() / 1000;
    if (newsec != lastsec)
    {
      lastsec = newsec;
      packets = thispackets;
      thispackets = 0;
    }

    radio.read(&data, sizeof(Data));
    printData(data);
    ++thispackets;
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
