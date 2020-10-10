
#include "mbed.h"
#include "Adafruit_ST7735.h"
#include "DHT.h"
#include <OneWire.h> 

#define TFT_CS PA_15
#define TFT_RST PA_11
#define TFT_DC PA_10
#define TFT_MOSI PB_5
#define TFT_SCLK PB_3
#define TFT_MISO PB_4
#define DHT_22 PA_9
#define ds18b20 PB_15

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_MOSI,TFT_MISO,TFT_SCLK,TFT_CS,TFT_DC,TFT_RST);
DHT dht22(DHT_22,DHT22);  
OneWire ds(ds18b20);

int main()
{ 
    tft.initR(INITR_GREENTAB);
    //tft.setRotation(1);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextCursor(0,10);
    tft.setTextColor(ST7735_RED);
    
    tft.printf("Starting!!!\n");
    uint8_t  data[2];
    float temperature;
   
    while(1) {
       int err=dht22.readData();
       if (err==0) {
          ds.reset();
          ds.write_byte(0xCC);
          ds.write_byte(0x44);
          tft.printf("T: %.1f C\n",dht22.ReadTemperature(CELCIUS));
          
          wait(1);
          ds.reset();
          ds.write_byte(0xCC);
          ds.write_byte(0xBE);
          data[0]= ds.read_byte();
          data[1] = ds.read_byte();
         temperature=((data[1]<<8)|data[0])*0.0625;
         tft.printf("T2: %.1f C \n",temperature);
         tft.printf("H %.1f ",dht22.ReadHumidity());
          tft.printf("%%");
          tft.printf("\n\r");
       }
       else {
         dht22.printErr(err);
       }  
    
    }
}
