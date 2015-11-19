# Helper2.h


## 環境

+ Arduino Pro or Pro Mini
+ ATmega 328 (3.3V, 8MHz)

## Class

### LED

インスタンスをグローバルで作成済み(led1, led2)

#### bool on()

+ 設定した色でledを点灯
+ デフォルトrgb = (100, 100, 100)

#### bool off()

+ ledを消灯

#### void color(uint8_t red, uint8_t green, uint8_t blue)

+ rgbで色を設定
+ それぞれ(0-255)

#### void color(float hue)

+ 色相を指定
+ 0-1
  
#### void brightness(float brightness)

+ 明るさを指定
+ 0-1

#### void saturation(float saturation);

+ 彩度を指定
+ 0-1

#### void randomcolor()

+ ランダムな色を表示
  
#### void InfoRGBHLS()

+ debug用
+ serialにRGBとHLSの値を表示