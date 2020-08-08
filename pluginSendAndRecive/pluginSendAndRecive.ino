/* obnizOs Plugin obniz.js(PCのweb)とESP32間での送受信動作確認用プログラム 
 *  ESP32にobnizOS pluginをインストールする手順 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide
 *  module: ESP32Dev 
 *  io23: GPO arduinoProgram動作確認用　led 1s毎に点滅
 *        io23(GPO) --- (anode)LED(cathod) --- R(1kΩ) --- GND
 *        
 *  obnizOSの動作結果は"Serial.println"で出力する
 *  
 *  obniz pluginの説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/
 *  このプログラムで対応している命令の主な説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/arduino-ide
 *  
 *  このプログラムでは、PC側のhtmlが必要になる。 pluginSendAndRecive.htmlを実行する。
 *  パソコン側でwebを開いてボタンを押すとESP32に1byteのデータを送信する。ESP32側はこのデータをSerial.printlnで出力する
 *  ESP32側で2[s]毎に+1する1byteのカウンタ値をパソコンのwebに送信する。パソコン側で個のカウント値を出力する。
*/

#include <obniz.h>
#define LEDPin (23)


//===============================================================
// obnizOSからarduinoへの送信
// js側の命令 https://obniz.io/ja/doc/reference/common/plugin
// js-arduino両方の命令の説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/custom-communication
// 
// 以下の命令をsetup()で呼び出す。
// obniz.commandReceive(onCommand);
//===============================================================
void onCommand(uint8_t* data, uint16_t length){
  Serial.println("");
  Serial.println("-------------------------------");
  Serial.println("onCommand");
  Serial.write(data,length);
  Serial.println("\nEnd onCommand");
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
  obniz.start();
  obniz.commandReceive(onCommand);  // onCommand()の呼び出し
  
  pinMode(LEDPin, OUTPUT);
}

//===============================================================
// loop function
//===============================================================
uint8_t counter = 0;  // 送信用のカウンタ変数

void loop() {

  //---------------------------------
  // モニタ用 LED点滅
  //---------------------------------
  digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LEDPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  //---------------------------------
  // arduinoからobnizOS経由でデータを送信する
  // js側の命令 https://obniz.io/ja/doc/reference/common/plugin
  // js-arduino両方の命令の説明 https://obniz.io/ja/doc/reference/obnizos-for-esp32/plugin/custom-communication
  //---------------------------------
  counter++;
  // ESP32とパソコンが接続されているときのみ処理する
  if (obniz.isOnline()) {
      // パソコンへのデータ送信
    obniz.commandSend((uint8_t*)&counter,1);
    
    // 送信したカウンタ値をSerialに出力する（値のモニタ用）
    Serial.println("");
    Serial.println("-------------------------------");
    Serial.print("send to obnizOS = "); 
    Serial.println(counter);
    Serial.println("-------------------------------");
  }
}
