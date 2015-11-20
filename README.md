# Helper2.h

## 環境

+ Arduino Pro or Pro Mini
+ ATmega 328 (3.3V, 8MHz)

## Class

### Accel

+ 加速度センサーの値を取得/保持するクラス
+ インスタンスをグローバルで作成済み (accel)
+ タップ, ダブルタップ検知 の しきい値 をコンストラクタの引数から変更可能

#### float x(), y(), z()

+ 加速度センサーの x, y, z 軸の値 (0.0 - 1.0)

#### bool active()

+ 加速度センサーが動いているかどうか

#### bool freefall()

+ 加速度センサーが自由落下しているかどうか

#### bool tap()

+ 加速度センサーがタップされたかどうか (タップ: 加速度センサーをコツンと叩くこと)

#### bool doubletap()

+ 加速度センサーがダブルタップされたかどうか

#### void init()

+ 加速度センサー を初期化する
+ `wait()` を呼ぶ前に呼び出さないとクラッシュする
+ `Helper2.cpp` の `initialize()` 内で呼ばれている

#### void updateAccel()

+ 加速度センサー から値を読み取り、x, y, z の値を更新する
+ `Helper2.cpp` の `wait()` 内で呼ばれている

#### void resetFlags()

+ active, freefall, tap, doubletap のフラグを `false` にリセットする
+ `updateAccel()` の前に呼び出されることを想定
+ `Helper2.cpp` の `wait()` 内で呼ばれている

#### void updateFlags()

+ active, freefall, tap, doubletap のフラグを更新
+ `updateAccel()` の後に呼び出されることを想定
+ `Helper2.cpp` の `wait()` 内で呼ばれている

#### bool debug

+ デバッグモードを有効化
+ 有効化すると、Serial から タップ等の検出情報をプリントする
+ Default: false

#### void debug_print(int i)

+ 内部で保持する x, y, z 軸の値を Serial でプリントする
+ i: 0 - (n_frames - 1) (値が大きいほど新しい, n\_frames は Accel.h にて定義されている)
+ Default: n\_frames = 30, i = n_frame - 1

#### void debug_threshold()

+ Serial モニタから数字を5つ入力することで閾値を変更できる
+ 左から _ThMaxAtFrameA _ThMinAtFrameB _ThMaxAtLatastFrame _ThMaximumSingleTapSpace _ThMaximumDoubleTapSpace を区切りを入れて入力する
+ 一番左は詰めて数字を入力されたし
+ 確認用の出力として現在の閾値が一行で出力される

### LED

インスタンスをグローバルで作成済み(led1, led2)

#### bool on()

+ 設定した色で LED を点灯
+ デフォルトhsl = (0.0, 0.7, 0.3)

#### bool off()

+ LED を消灯

#### bool flip()

+ LED を消灯していたら点灯に、点灯していたら消灯する

#### void color(uint8_t red, uint8_t green, uint8_t blue)

+ rgbで色を設定
+ R, G, B はそれぞれ 0 - 255 の値をとる

#### void color(float hue)

+ 色相を指定
+ 0.0 - 1.0

#### void brightness(float brightness)

+ 明るさを指定
+ 0.0 - 1.0

#### void saturation(float saturation);

+ 彩度を指定
+ 0.0 - 1.0

#### void randomcolor()

+ ランダムな色を設定する

#### void debug_print()

+ デバッグ用
+ Serial にて RGB と HLS の値を 出力する
