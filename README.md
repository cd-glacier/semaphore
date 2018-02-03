# semaphore

学校の課題.
mac環境で動作確認.

## 13.2

./src/13.2/
にソースコードを作成した。
セマフォを使用しないtransfer.cとobserv.cの組みと, 
セマフォを使用するSemaphoreTransfer.cとsemaphoreObserv.cである.

semaphoreを用いない物結果は以下のようになった.
```sh
~/D/d/s/g/g/s/s/13.2 >><(( ○> ./transfer
A Address: 65559
B Address: 65560
(a, b) = (100, 0)
(a, b) = (99, 1)
(a, b) = (98, 2)
(a, b) = (97, 3)
(a, b) = (96, 4)
(a, b) = (95, 5)
(a, b) = (94, 6)
(a, b) = (93, 7)
(a, b) = (92, 8)
(a, b) = (91, 9)
(a, b) = (90, 10)
(a, b) = (89, 11)
^C⏎ 

~/D/d/s/g/g/s/s/13.2 >><(( ○> ./observ 65559 65560
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
a + b = 100
a + b = 99
^C⏎ 

値を移動する際の共有メモリ上の値を読み込んでしまって、
aとbの和が99の時が存在している。

次にsemaphoreを使った場合の物を確認する.

```sh
~/d/d/s/g/g/s/s/13.2 >><(( ○> ./transfer                                       [master]
a address: 131081
b address: 131082
(a, b) = (100, 0)
(a, b) = (99, 1)
(a, b) = (98, 2)
(a, b) = (97, 3)
(a, b) = (96, 4)
(a, b) = (95, 5)
(a, b) = (94, 6)
(a, b) = (93, 7)
(a, b) = (92, 8)
(a, b) = (91, 9)
(a, b) = (90, 10)
(a, b) = (89, 11)
(a, b) = (88, 12)
(a, b) = (87, 13)

~/d/d/s/g/g/s/s/13.2 >><(( ○> ./observ 131081 131082                           [master]
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
a + b = 100
```
"aから1引き、bに1足す"
という動きを一単位として扱うように
semaphoreを用いた.
正常に動いているように見える。

## 13.3

例のコードを改善する内容である。
結果は以下のようになった.
```sh
~/D/d/s/g/g/s/s/13.3 >><(( ○> ./send 196609                                    [master]
Input any string> hoge
Input any string> foo
Input any string> quit

~/D/d/s/g/g/s/s/13.3 >><(( ○> ./receive                                        [master]
Shared memory ID = 196609
Initial
Initial
hoge
foo
```
今回は、
"sendで書いたメッセージをreceiveで受け取る"
という動作を一単位として扱った。

