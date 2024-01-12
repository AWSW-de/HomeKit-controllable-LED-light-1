// ###########################################################################################################################################
// #
// # Code for the printables.com "HomeKit controllable LED light #1" project:
// # https://www.printables.com/de/model/717957-homekit-controllable-led-light-1
// #
// # Code by https://github.com/AWSW-de
// #
// # Released under licenses:
// # GNU General Public License v3.0: https://github.com/AWSW-de/HomeKit-controllable-LED-light-1#GPL-3.0-1-ov-file and
// # Creative Commons Attribution-NonCommercial 3.0 Unported License http://creativecommons.org/licenses/by-nc/3.0
// # Important: NonCommercial — You may not use the material for commercial purposes !
// # License information of the HomeSpan library are listed at the end of this file.
// #
// ###########################################################################################################################################


// ###########################################################################################################################################
// # Settings:
// ###########################################################################################################################################
#define NEOPIXEL_RGB_PIN 33            // Pin you attached the DIN pin of the LED to on the ESP32 board
#define NEOPIXELAMOUNT 64              // Number of LEDs
#define DEVICE_SUFFIX "AWSW"           // Device name suffix to be listed on pairing with HomeKit
#define WIFISSID "YourWiFiSSID"        // Your WiFI SSID name
#define WIFIPASS "YourWiFiPASS"        // Your WiFI password
#define PAIRINGCODE "11122333"         // HomeKit paring code to enter during pairing
#define BRIDGENAME "ESP32 bridge "     // Bridge name of the new device in HomeKit (can be changed during paring)
#define DEVICENAME "ESP32 LED light "  // Device name to be listed in HomeKit (can be changed during paring)
// ###########################################################################################################################################
// # ! Do not change anything after this line !
// ###########################################################################################################################################


// ###########################################################################################################################################
// # Includes:
// #
// # You will need to add the following library to your Arduino IDE to use the project:
// #
// # - HomeSpan        by HomeSpan        https://github.com/HomeSpan/HomeSpan
// #
// ###########################################################################################################################################
#include "HomeSpan.h"
#include "extras/Pixel.h"


// ###########################################################################################################################################
// # Version of the code:
// ###########################################################################################################################################
#define CODEVERSION "V1.0.0"


// ###########################################################################################################################################
// # RGB LED function:
// ###########################################################################################################################################
struct NeoPixel_RGB : Service::LightBulb {
  Characteristic::On power{ 0, true };
  Characteristic::Hue H{ 0, true };
  Characteristic::Saturation S{ 0, true };
  Characteristic::Brightness V{ 100, true };
  Pixel *pixel;
  uint8_t nPixels;
  NeoPixel_RGB(uint8_t pin, uint8_t nPixels)
    : Service::LightBulb() {
    V.setRange(5, 100, 1);
    pixel = new Pixel(pin);
    nPixels = NEOPIXELAMOUNT;
    this->nPixels = nPixels;
    update();
  }
  boolean update() override {
    int p = power.getNewVal();
    float h = H.getNewVal<float>();  
    float s = S.getNewVal<float>();  
    float v = V.getNewVal<float>();  
    Pixel::Color color;
    pixel->set(color.HSV(h * p, s * p, v * p), nPixels);  
    return (true);
  }
};


// ###########################################################################################################################################
// # Startup function:
// ###########################################################################################################################################
void setup() {
  Serial.begin(115200);
  homeSpan.setSerialInputDisable(false);
  homeSpan.setPairingCode(PAIRINGCODE);
  homeSpan.setWifiCredentials(WIFISSID, WIFIPASS);
  homeSpan.begin(Category::Lighting, BRIDGENAME DEVICE_SUFFIX);
  SPAN_ACCESSORY();  
  SPAN_ACCESSORY(DEVICENAME DEVICE_SUFFIX);
  new NeoPixel_RGB(NEOPIXEL_RGB_PIN, 8);
}


// ###########################################################################################################################################
// # Runtime loop function:
// ###########################################################################################################################################
void loop() {
  homeSpan.poll();
}


// ###########################################################################################################################################
// # HomeSpan license information:
// ###########################################################################################################################################

/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/