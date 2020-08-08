/* obnizOs Plugin 動作確認用プログラム 
 *  ESP32にobnizOS pluginをインストールする手順 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide
 *  module: ESP32Dev 
 *  io23: GPO arduinoProgram動作確認用　led 1s毎に点滅
 *        io23(GPO) --- (anode)LED(cathod) --- R(1kΩ) --- GND
 *        
 *  obnizOSの動作結果は"Serial.println"で出力する
 *  
 *  obniz pluginの説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/
 *  このプログラムで対応している命令の主な説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide
 *  このプログラムでは、PC側のhtmlは不要。esp32とobnizのサーバ間が接続できていれば動作する
*/

#include <obniz.h>  // obnizOSを使用するために必要になる

#define LEDPin (23) // monitor LED

//===============================================================
// obniz onEvent function
// obnizOSの動作に変化があった時に実行される。各動作変化で行いたい処理を追加していく
//   setup()に "obniz.onEvent(onEvent);"　を追加しておく
//https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/reference
// https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide 
//===============================================================
void onEvent(os_event_t event, uint8_t* data, uint16_t length) {
  Serial.println("");
  Serial.println("-------------------------------");
  Serial.println("onEvent function");
  switch (event) {
  case PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED:
    Serial.println("PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED");
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED:
    Serial.println("PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED");
    break;
  case PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED:
    Serial.println("PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED");
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED:
    Serial.println("PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED");
    break;
  case PLUGIN_EVENT_NETWORK_WIFI_SCANNING:
    Serial.println("PLUGIN_EVENT_NETWORK_WIFI_SCANNING");
    break;
  case PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND:
    Serial.println("PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND");
    break;
  case PLUGIN_EVENT_NETWORK_WIFI_CONNECTING:
    Serial.println("PLUGIN_EVENT_NETWORK_WIFI_CONNECTING");
    break;
  case PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED:
    Serial.println("PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED");
    break;
  case PLUGIN_EVENT_NETWORK_WIFI_FAIL:
    Serial.println("PLUGIN_EVENT_NETWORK_WIFI_FAIL");
    break;
  case PLUGIN_EVENT_FAIL:
    Serial.println("PLUGIN_EVENT_FAIL");
    break;
  case PLUGIN_EVENT_OTA_START:
    Serial.println("");
    break;
  case PLUGIN_EVENT_OTA_END:
    Serial.println("PLUGIN_EVENT_OTA_END");
    break;
  case PLUGIN_EVENT_OTA_ERROR:
    Serial.println("PLUGIN_EVENT_OTA_ERROR");
    break;
  }
  Serial.println("-------------------------------");
}

//===============================================================
// setup function
//===============================================================
void setup() {
  Serial.begin(115200);

  // obniz関係の関数呼び出し順序は
  // https://obniz.io/ja/doc/guides/obniz-starter-guide/plugin/event
  // を参照する。
  obniz.onEvent(onEvent);           // 処理関数の本体は"void onEvent(os_event_t event, uint8_t* data, uint16_t length)"になる
  obniz.start();
  
  pinMode(LEDPin, OUTPUT);  // esp32 動作確認用LED
}

//===============================================================
// loop function
//===============================================================
void loop() {

  //---------------------------------
  // モニタ用 LED点滅
  //---------------------------------
  digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LEDPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  //---------------------------------
  // obnizOSの状態をモニタする
  //https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/reference
  // https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide 
  //---------------------------------
  Serial.println("");
  Serial.println("-------------------------------");
  Serial.print("getId = ");
  Serial.println(obniz.getId());
  
  Serial.print("getOsVersion = ");
  Serial.println(obniz.getOsVersion());
  
  Serial.print("isRunning = ");
  Serial.println(obniz.isRunning());
  
  Serial.print("isOnline = ");
  Serial.println(obniz.isOnline());
  Serial.println("-------------------------------");
}
