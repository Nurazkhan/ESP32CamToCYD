# ESP32CamToCYD

https://github.com/user-attachments/assets/e61bd18a-d6d0-4eaa-a44b-fe041a96ba3a

This project allows you to stream live JPEG images from an ESP32-CAM to a cheap yellow display board on ESP32, using WebSockets for real-time, low-latency transmission. Ideal for DIY wireless monitors, embedded vision projects, and ESP32 learning.

 Features
📡 WebSocket communication between ESP32-CAM (client) and CYD (server)

🖼️ JPEG image streaming with TJpg_Decoder on-the-fly

🧠 Smart image decoding using hardware-accelerated pushImage() rendering

⚡ Lightweight protocol for fast updates without HTTP overhead

📲 ESP32-CAM auto-connects to display as a client and pushes frame data in base64 or raw JPEG format

🧰 Library	Description
TJpg_Decoder- Decodes JPEG images and renders directly to TFT
bb_spi_lcd - Ultra-fast SPI TFT driver (used for yellow display)
ArduinoWebsockets - Full-featured WebSocket client/server
WiFi.h (built-in)	Used for both Access Point and STA WiFi modes
SPI.h (built-in)	Required for TFT communication





https://github.com/user-attachments/assets/d1d3c6bd-b736-4fa6-9dd4-d2daf3fae05c


Tags
 esp32-cam, esp32 display, websocket streaming, tft display esp32, jpeg streaming, live video esp32, st7735, ili9341, esp32 camera, image transfer, bb_spi_lcd, tjpg_decoder, cheap tft esp32, wireless image display, embedded graphics, arduino display project


