Pertanyaan Praktikum Percobaan 6A
1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt!
- Ketika push button ditekan, kondisi sinyal pada pin interrupt berubah dari HIGH menjadi LOW karena menggunakan mode FALLING. Perubahan sinyal tersebut akan dideteksi oleh mikrokontroler dan secara otomatis memicu Interrupt Service Routine (ISR). ISR kemudian mengubah nilai variabel ledState menjadi kondisi kebalikannya, yaitu dari ON ke OFF atau sebaliknya. Setelah ISR selesai dijalankan, program utama kembali berjalan normal dan kondisi LED diperbarui sesuai nilai terbaru dari variabel ledState.
2. Apa fungsi attachInterrupt() pada program tersebut?
- Fungsi attachInterrupt() digunakan untuk menghubungkan pin interrupt dengan ISR yang akan dijalankan ketika kondisi tertentu terjadi. Pada program ini, attachInterrupt() digunakan untuk mendeteksi perubahan sinyal pada pin 2 Arduino dan menjalankan ISR saat tombol ditekan menggunakan mode interrupt FALLING.
3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?
- Penggunaan delay() di dalam ISR tidak disarankan karena dapat menghentikan jalannya sistem sementara waktu dan membuat interrupt lain tidak dapat diproses. Selain itu, Serial.print() juga tidak disarankan karena komunikasi serial membutuhkan interrupt internal sehingga dapat menyebabkan konflik atau program menjadi tidak stabil. Oleh karena itu, ISR sebaiknya dibuat singkat dan sederhana agar sistem tetap responsif.
4. Apa fungsi keyword volatile pada variabel ledState?
- Keyword volatile digunakan agar compiler selalu membaca nilai terbaru dari variabel ledState dan tidak melakukan optimasi penyimpanan nilai. Hal ini penting karena variabel tersebut diakses oleh ISR dan program utama secara bersamaan sehingga nilainya dapat berubah sewaktu-waktu akibat interrupt.
5. Pada percobaan digunakan mode interrupt FALLING. Modifikasikan program menggunakan mode interrupt lain (RISING, CHANGE, atau LOW) kemudian:
- Jelaskan perbedaan cara kerja masing-masing mode interrupt tersebut
    - RISING : Interrupt aktif ketika sinyal berubah dari LOW ke HIGH
    - FALLING : Interrupt aktif ketika sinyal berubah dari HIGH ke LOW
    - CHANGE : Interrupt aktif ketika sinyal berubah dari LOW ke HIGH atau dari HIGH ke LOW
    - LOW : Interrupt aktif ketika sinyal LOW
- Analisis perubahan perilaku LED yang terjadi pada setiap mode
    - Mode RISING : LED berubah kondisi ketika tombol dilepas karena sinyal berubah dari LOW ke HIGH.
    - Mode FALLING : LED berubah kondisi ketika tombol ditekan karena sinyal berubah dari HIGH ke LOW.
    - Mode CHANGE : LED dapat berubah dua kali, yaitu saat tombol ditekan dan saat dilepas karena setiap perubahan sinyal memicu interrupt.
    - Mode LOW : Interrupt terus aktif selama tombol ditekan karena kondisi pin tetap LOW. Hal ini dapat menyebabkan LED berubah sangat cepat dan terlihat berkedip.
- Sertakan source code dan penjelasan program dalam bentuk README.md

```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
    ledState = !ledState;
}

void setup() {
    pinMode(13, OUTPUT);
    pinMode(2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2),
    tombolInterrupt,
    RISING);
}

void loop() {
    digitalWrite(13, ledState);
}
```

- Penjelasan Program
  - Program menggunakan interrupt pada pin 2 untuk mengubah kondisi LED pada pin 13. Mode RISING akan memicu interrupt saat sinyal berubah dari LOW ke HIGH, yaitu ketika tombol dilepas. ISR tombolInterrupt() digunakan untuk mengubah nilai ledState sehingga kondisi LED ikut berubah.
- Alur Kerja
  - Tombol dilepas → RISING → interrupt aktif → LED berubah kondisi

Pertanyaan Praktikum Percobaan 6B
1. Jelaskan bagaimana fungsi millis() bekerja pada program tersebut!
- Fungsi millis() bekerja dengan menghitung waktu dalam satuan milidetik sejak Arduino mulai dijalankan. Program akan membandingkan waktu saat ini dengan waktu sebelumnya yang disimpan pada variabel tertentu. Jika selisih waktunya sudah mencapai interval yang ditentukan, maka kondisi LED akan diubah.
2. Apa perbedaan utama antara delay() dan millis()?
- delay() akan menghentikan sementara seluruh program selama waktu tertentu sehingga program tidak dapat menjalankan proses lain. Sedangkan millis() bekerja secara non-blocking sehingga program tetap dapat menjalankan proses lain sambil menghitung waktu.
3. Mengapa metode millis() disebut non-blocking?
- Karena penggunaan millis() tidak menghentikan jalannya program utama. Loop() tetap berjalan terus sehingga mikrokontroler masih dapat menjalankan proses lain secara bersamaan selama proses perhitungan waktu berlangsung.
4. Modifikasi program agar:
- LED pertama berkedip setiap 1 detik
- LED kedua berkedip setiap 500 ms
- Tanpa menggunakan delay()
Berikan penjelasan setiap baris program dalam bentuk README.md.

```cpp
const int led1 = 13;
const int led2 = 12;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

const long interval1 = 1000;
const long interval2 = 500;

bool ledState1 = LOW;
bool ledState2 = LOW;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis1 >= interval1) {
        previousMillis1 = currentMillis;
        ledState1 = !ledState1;
        digitalWrite(led1, ledState1);
    }

    if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        ledState2 = !ledState2;
        digitalWrite(led2, ledState2);
    }
}
```

Penjelasan Program
- led1 dan led2 digunakan untuk menentukan pin LED yang digunakan.
- previousMillis1 dan previousMillis2 digunakan untuk menyimpan waktu terakhir LED berubah kondisi.
- interval1 bernilai 1000 ms untuk LED pertama, sedangkan interval2 bernilai 500 ms untuk LED kedua.
- ledState1 dan ledState2 digunakan untuk menyimpan kondisi LED saat ini.
- Pada fungsi setup(), kedua pin LED diatur sebagai output.
- Fungsi millis() digunakan untuk mengambil waktu saat ini dalam satuan milidetik.
- Program membandingkan selisih waktu sekarang dengan waktu sebelumnya.
- Jika selisih waktu mencapai interval yang ditentukan, kondisi LED akan dibalik menggunakan operator !.
- Program tidak menggunakan delay() sehingga kedua LED dapat berkedip dengan interval berbeda secara bersamaan.
