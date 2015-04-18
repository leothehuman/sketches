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
  
  radio.openWritingPipe(pipe);
  Serial.begin(115200);  
  delay(750);
}

void loop(void)
{
  for (int i = 0; i < n; ++i)
  {
    data.a[i] = map(analogRead(i), 0, 1023, 1000, 2000);
  }
  printData(data);
  radio.write(&data, sizeof(Data));
  delay(10);
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
