# Helper2.h


## 環境

+ Arduino Pro or Pro Mini
+ ATmega 328 (3.3V, 8MHz)

## Class

### Accel

+ 加速度センサーの値を保持するクラス
+ インスタンスをグローバルで作成済み(accel)
+ tap検知の閾値をコンストラクタの引数から変更可能

#### float x(), y(), z()

+ 加速度センサーの x, y, z 軸の値 (0.0 - 1.0)

#### bool active()

+ 加速度センサーが動いているかどうか

#### bool freefall()

+ 加速度センサーが自由落下しているかどうか

#### bool tap()

+ 加速度センサーがタップされたかどうか (コツンと叩く)

#### bool doubletap()

+ 加速度センサーがダブルタップされたかどうか

#### void resetFlags()

+ tapなどの状態を示すフラグを`false`にリセットする
+ `wait()`の先頭で呼び出されること

#### void updateFlags()

+ tapなどの状態を示すフラグを更新
+ `wait()`の中で呼び出されある程度保存してあるデータから判定

#### bool debug

+ デバッグモードを有効化
+ Default: false

#### void init()

+ 加速度センサーを初期化
+ `setup()`関数の中で呼び出されないとクラッシュ
+ `initialize()`に内包

#### void updateAccel()

+ `wait()`の中で呼び出され加速度センサーの値を保存

#### void debug_print(int i)

+ 内部で保持する x, y, z 軸の値を Serial でプリントします
+ i: 0 - 29 (29が最新の値)

### LED

インスタンスをグローバルで作成済み(led1, led2)

#### bool on()

+ 設定した色でledを点灯
+ デフォルトhsl = (0.0, 0.7, 0.3)

#### bool off()

+ ledを消灯

#### bool flip()

+ ledを消灯してたら点灯、点灯してたら消灯

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

#### void debug_print()

+ debug用
+ serialにRGBとHLSの値を表示