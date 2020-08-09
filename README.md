# obnizSampleForEsp32Dev
obnizOSを手持ちのESP32ボードにインストールすることができるようになりました。(https://obniz.io/ja/doc/reference/obnizos-for-esp32/quick-start/)  
またpulgin機能で、ESP32側に独自プログラムを走らせ同時にobnizOSでの制御ができるようになりました。  

この場合動作確認でトラブルになった場合には、
<dl>
<dt>・ESP32へのobnizOSのインストール</dt>
<dt>・ESP32のobnizサーバへの登録</dt>
<dt>・ESP32に書き込んだpulginのプログラム</dt>
<dt>・ESP32とobnizサーバとの通信</dt>
<dt>・htmlファイル
</dl>

以上のように関係する箇所が多く原因追及に時間がかかります。
この対応として、そのままで動くサンプルプログラムを用意しました。

<dl>
<dt>・pluginModeCheck</dt>
<dd>
    ESP32とobnizサーバとの接続確認を行う。htmlファイルは不要
 </br>ESP32にobnizOSをインストールして、obnizサーバに登録できていれば動く
    </dd>
<dt>・pluginGPIO</dt>
<dd>
　htmlからESP32のデジタル入出力を行うプログラム
</dd>
<dt>・pluginSendAndRecive </dt>
<dd>
　ESP32側に書き込んだpulginプログラムとhtmlとの送受信
</dd>
</dl>

<dl>
<dt>使用ボード</dt>
<dd>ESP32-DevKitC-32D  [秋月](http://akizukidenshi.com/catalog/g/gM-13628/)
</dl>

各フォルダにarduinoのinoファイルと、htmlファイルがあります。</br>
ESP32のLED,SWの配線はinoファイルに記載してあります。