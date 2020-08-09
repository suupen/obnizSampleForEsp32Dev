/* obnizOs Plugin obniz.js(PCのweb)とESP32間でのGPIO動作確認用プログラム 
 *  ESP32にobnizOS pluginをインストールする手順 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide
 *  module: ESP32Dev
 *  
 *  io23: ESP32のProgram動作確認用　led 1s毎に点滅
 *        LEDの接続方法: io23 --- (anode)LED(cathod) --- R(1kΩ) --- GND
 *        
 *  io0: Webからの2[s]周期でのHi/Lo指示を出力      
 *        LEDの接続方法: io0 --- (anode)LED(cathod) --- R(1kΩ) --- GND
 *  io5: Webのボタン操作によるHi/Lo指示を出力
 *        LEDの接続方法: io5 --- (anode)LED(cathod) --- R(1kΩ) --- GND
 *        
 *  pluginGPIO.ino プログラムではio23の設定と出力処理のみ行う。      
 *  io0, io5の制御はobnizOSで行うのでinoファイルでの設定は不要になる。
 *        
 *  obniz pluginの説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/
 *  
 *  このプログラムでは、PC側のhtmlが必要になる。 pluginGPIO.htmlを実行する。
 *  パソコン側でwebを開いてボタンを押すと1ESP32に1byteのデータを送信する。ESP32側はこのデータをSerial.printlnで出力する
 *  ESP32側で2[s]毎に+1する1byteのカウンタ値をパソコンのwebに送信する。パソコン側で個のカウント値を出力する。
*/
#include <obniz.h>
#define LEDPin (23)

//===============================================================
// setup function
//===============================================================
void setup() {
  // obniz関係の関数呼び出し順序は
  // https://obniz.io/ja/doc/guides/obniz-starter-guide/plugin/event
  // を参照する。
  obniz.start();
  
  pinMode(LEDPin, OUTPUT);
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
}
