#include <SPI.h>
#include <TJpg_Decoder.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <bb_spi_lcd.h>
BB_SPI_LCD lcd;



#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2



const char* ssid = "ESP32CAM_to_ESP32"; 
const char* password = "myesp32server"; 


IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


int centerX, centerY;

using namespace websockets;
WebsocketsServer server;
WebsocketsClient client;






bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
 
  if ( y >= lcd.height() ) return 0;

 
  lcd.pushImage(x, y, w, h, bitmap);


  return 1;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(3000);

  Serial.println();
  Serial.println("-------------Create ESP32 as Access Point and start the server.");
  Serial.println("WIFI mode : AP");
  WiFi.mode(WIFI_AP);
  
  Serial.println();
  Serial.println("Setting AP.");
  WiFi.softAP(ssid, password);
  delay(500);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  IPAddress IP = WiFi.softAPIP();
  Serial.println();
  Serial.print("AP IP Address : ");
  Serial.println(IP);

  server.listen(8888);
  Serial.println();
  Serial.println(server.available());
  


  lcd.begin(DISPLAY_CYD);
  TJpgDec.setSwapBytes(true); // if the colors are inverted or distorted set false instead of true
  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLUE);
  lcd.setFont(FONT_12x16);
 
  lcd.setTextColor(TFT_WHITE, TFT_BLUE);
  lcd.println("Waiting for connection");
  lcd.println("from ESP32-CAM (Client)");
  Serial.println();
  Serial.println("Waiting for connection from ESP32-CAM (Client).");
  
  // 2 4 6 8
  TJpgDec.setJpgScale(1);

  TJpgDec.setCallback(tft_output);
}

void loop() {
  
  if(server.poll()){
    client = server.accept();
  }

  if(client.available()){
    client.poll();

    WebsocketsMessage msg = client.readBlocking();

    uint32_t t = millis();

   
    uint16_t w = 0, h = 0;
    TJpgDec.getJpgSize(&w, &h, (const uint8_t*)msg.c_str(), msg.length());
    Serial.print("Width = "); Serial.print(w); Serial.print(", height = "); Serial.println(h);

   
    TJpgDec.drawJpg(0, 0, (const uint8_t*)msg.c_str(), msg.length());
  
    t = millis() - t;
    Serial.print(t); Serial.println(" ms");
  } 
}
