#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int n = 2;

struct Data
{
  int a[n];  
} data;

void printData(const struct Data& d)
{
  for (int i = 0; i < n - 1; ++i)
  {
    Serial.print(d.a[i]);
    Serial.print(" ");
  }
  Serial.println(d.a[n - 1]);
}

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F0E2LL;

void setup(void)
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  
  radio.openReadingPipe(1, pipe);
  radio.startListening(); 
  Serial.begin(115200);
}

void loop(void)
{
  while (radio.available())
  {
    radio.read(&data, sizeof(Data));
    printData(data);
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
