# Helper2.h
[![Build Status](https://travis-ci.org/UEC-giken/Helper2.h.svg?branch=master)](https://travis-ci.org/UEC-VBSeminar/Helper2.h)

## About

Arduino と フルカラーLED (PL9823), 加速度センサー (ADXL345) を用いたハードウェアで、初心者が直感的にプログラミングをできるようにしたライブラリ。

## Environment

+ Arduino Pro or Pro Mini (ATmega 328 / 3.3V, 8MHz)
+ [回路図](http://vbseminar.github.io/oc-2015summer/)

## Required Library

このライブラリを使用するためには、以下の2つのライブラリが必要です。

+ [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
+ [adxl345driver](https://github.com/kyontan/adxl345driver)

## Class

### Accel

+ 加速度センサーの値を取得/保持するクラス
+ インスタンスをグローバルで作成済み (accel)
+ タップ, ダブルタップ検知 の しきい値 をコンストラクタの引数から変更可能

#### float x(), y(), z()

+ 加速度センサーの x, y, z 軸の値 (-1.0 - 1.0)

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

#### void debugPrint(int i)

+ 内部で保持する x, y, z 軸の値を Serial でプリントする
+ i: 0 - (n_frames - 1) (値が大きいほど新しい, n\_frames は Accel.h にて定義されている)
+ Default: n\_frames = 30, i = n_frame - 1

#### void debugPrintThreshold()

+ 内部で保持する しきい値 の値を Serial でプリントする

#### void debugInputThreshold()

+ Serial モニタから数字を5つ入力することで しきい値 を変更できる
+ ThMaxAtFrameA, ThMinAtFrameB, ThMaxAtLatastFrame, ThMaximumSingleTapSpace, ThMaximumDoubleTapSpace の順に、区切り('0' - '9', '.' 以外ならなんでも良い)を入れて入力する
+ 一番左は詰めて数字を入力する必要がある
+ 確認用の出力として現在の しきい値 が一行で出力される

### LED

インスタンスをグローバルで作成済み(led1, led2)

#### bool on()

+ 設定した色で LED を点灯
+ Default: hsl = (0.0, 0.7, 0.3)

#### bool off()

+ LED を消灯

#### bool flip()

+ LED を消灯していたら点灯に、点灯していたら消灯する

#### void color(uint8\_t red, uint8\_t green, uint8\_t blue)

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

#### void randomColor()

+ ランダムな色を設定する (hue にランダムな値を入れる)

#### void stepColor(float span = 0.005)

+ 現在設定されている hue に span を足したものを 新たな hue として設定する

#### bool fadeIn(float span = 0.02, float max = 0.5, bool loop = false)

+ `max`まで`span`だけ明るくなっていく
+ 明るさが`max`まで達すると`false`を返す
+ `loop`を`true`にすることで最高まで明るくなってから最高まで暗くなり…ということを繰り返す

#### bool fadeOut(float span = 0.02, float min = 0.0, bool loop = false)

+ `min`まで`span`だけ暗くなっていく
+ 明るさが`min`まで達すると`false`を返す
+ `loop`を`true`にすることで最高まで暗くなってから最高まで明るくなり…ということを繰り返す

#### void debugPrint()

+ デバッグ用
+ Serial にて RGB と HLS の値を 出力する

## Authors

- Kyosuke Tanaka <kyontan@monora.me>
- Hiroki Kawahara <h-otter@outlook.jp>
- Azuma Ikeda <hogextend@gmail.com>
- Issei Gotoda <issei.gtd@gmail.com>
- Shoki Kishida <shoki0417@gmail.com>
