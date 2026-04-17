3.5.4 Pertanyaan Praktikum:
1. Jelaskan proses dari input keyboard hingga LED menyala/mati!
- Proses dimulai dari input keyboard yang dikirim melalui Serial Monitor ke Arduino dalam bentuk data serial. Arduino membaca data tersebut menggunakan fungsi `Serial.read()`, kemudian mengevaluasi nilainya menggunakan struktur percabangan. Jika data sesuai (misalnya ‘1’ atau ‘0’), maka Arduino akan mengirimkan sinyal HIGH atau LOW ke pin LED sehingga LED menyala atau mati.
2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
- Fungsi `Serial.available()` digunakan untuk memastikan bahwa terdapat data yang masuk sebelum dilakukan pembacaan. Jika fungsi ini dihilangkan, maka Arduino dapat membaca data kosong sehingga berpotensi menghasilkan nilai tidak valid atau perilaku program menjadi tidak stabil.
3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
  
```cpp
#include <Arduino.h>              // Library utama Arduino
const int PIN_LED = 12;           // Menentukan pin digital 12 untuk LED
char mode = '0';                  // Menyimpan mode LED (default mati)

void setup() {
  Serial.begin(9600);             // Memulai komunikasi serial dengan baudrate 9600
  Serial.println("Ketik '1' (ON), '0' (OFF), '2' (BLINK)"); // Instruksi ke user
  pinMode(PIN_LED, OUTPUT);       // Mengatur pin LED sebagai output
}

void loop() {
  if (Serial.available() > 0) {   // Mengecek apakah ada data masuk dari serial
    char data = Serial.read();    // Membaca 1 karakter dari serial
    if (data == '1') {            // Jika input '1'
      mode = '1';                 // Set mode menjadi ON
      Serial.println("LED ON");   // Tampilkan status ke serial monitor
    }
    else if (data == '0') {       // Jika input '0'
      mode = '0';                 // Set mode menjadi OFF
      Serial.println("LED OFF");  // Tampilkan status
    }
    else if (data == '2') {       // Jika input '2'
      mode = '2';                 // Set mode menjadi BLINK
      Serial.println("LED BLINK");// Tampilkan status
    }
    else if (data != '\n' && data != '\r') {    // Jika bukan input valid
      Serial.println("Perintah tidak dikenal"); // Tampilkan error
    }
  }

  // Eksekusi berdasarkan mode
  if (mode == '1') {              // Jika mode ON
    digitalWrite(PIN_LED, HIGH);  // LED menyala terus
  }
  else if (mode == '0') {         // Jika mode OFF
    digitalWrite(PIN_LED, LOW);   // LED mati
  }
  else if (mode == '2') {         // Jika mode BLINK
    digitalWrite(PIN_LED, HIGH);  // LED menyala
    delay(500);                   // Tunggu 500 ms
    digitalWrite(PIN_LED, LOW);   // LED mati
    delay(500);                   // Tunggu 500 ms
  }
}
```

4. Tentukan apakah menggunakan `delay()` atau `milis()`! Jelaskan pengaruhnya terhadap sistem!
- Pada program ini digunakan fungsi `delay()` sebagai pengatur waktu. Penggunaan `delay()` menyebabkan eksekusi program berhenti sementara selama waktu yang ditentukan, sehingga selama periode tersebut Arduino tidak dapat memproses input lain. Dampaknya, sistem menjadi kurang responsif, terutama ketika digunakan pada kondisi yang membutuhkan interaksi real-time seperti pembacaan input dari serial atau sensor. Sebaliknya, jika menggunakan `milis()`, program dapat berjalan tanpa blocking karena waktu dihitung berdasarkan selisih waktu sejak Arduino mulai berjalan. Hal ini memungkinkan sistem tetap menjalankan proses lain secara bersamaan, sehingga lebih responsif terhadap perubahan input. Dengan demikian, penggunaan `milis()` lebih direkomendasikan untuk sistem yang membutuhkan multitasking atau respon cepat.

3.6.4 Pertanyaan Praktikum:
1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
- Komunikasi I2C antara Arduino dan LCD bekerja melalui dua jalur utama, yaitu SDA (data) dan SCL (clock). Arduino bertindak sebagai master yang mengirimkan data ke LCD sebagai slave berdasarkan alamat I2C tertentu, sehingga data seperti nilai ADC dapat ditampilkan pada layar.
2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!
- Konfigurasi pin potensiometer sebaiknya mengikuti susunan yang benar, yaitu pin tengah sebagai output (ke analog Arduino), sedangkan dua pin samping sebagai VCC dan GND. Jika pin kiri dan kanan tertukar, potensiometer tetap dapat bekerja, namun arah perubahan nilainya akan terbalik. Artinya, saat diputar ke satu arah nilai ADC justru menurun, bukan meningkat, sehingga pembacaan menjadi tidak sesuai dengan ekspektasi.
3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:

| ADC: 0 | Volt: 0.00 V | Persen: 0% |
| --- | --- | --- |

- Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
- Berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
  
```cpp
#include <Wire.h>                  // Library komunikasi I2C
#include <LiquidCrystal_I2C.h>     // Library LCD I2C
#include <Arduino.h>               // Library utama Arduino

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD (alamat 0x27, 16x2)
const int pinPot = A0;              // Pin analog untuk potentiometer

void setup() {
  Serial.begin(9600);             // Memulai komunikasi serial (UART)
  lcd.init();                     // Inisialisasi LCD
  lcd.backlight();                // Menyalakan backlight LCD
}

void loop() {
  int nilai = analogRead(pinPot);          // Membaca nilai ADC (0 - 1023)
  float volt = nilai * (5.0 / 1023.0);     // Konversi ke tegangan (Volt)
  float persen = nilai * (100.0 / 1023.0); // Konversi ke persen
  int bar = map(nilai, 0, 1023, 0, 16);    // Mapping untuk panjang bar LCD

  // Outpur Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" | Volt: ");
  Serial.print(volt, 2);          // 2 angka di belakang koma
  Serial.print(" V | Persen: ");
  Serial.print(persen, 0);        // tanpa desimal
  Serial.println("%");

  // ===== OUTPUT LCD =====
  lcd.setCursor(0, 0);            // Baris 1 kolom 0
  lcd.print("ADC:");
  lcd.print(nilai);
  lcd.print("    ");              // Clear sisa karakter

  lcd.setCursor(0, 1);            // Baris 2 kolom 0
  for (int i = 0; i < 16; i++) {  // Loop 16 kolom LCD
    if (i < bar) {
      lcd.print((char)255);       // Karakter blok penuh
    } else {
      lcd.print(" ");             // Kosongkan
    }
  }

  delay(200);                     // Delay agar stabil
}
```

4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor!

| ADC | Volt(V) | Persen(%) |
| --- | --- | --- |
| 1 |	0.0	| 0 |
| 21	| 0.10	| 2 |
| 49	| 0.24	| 5 |
| 74	| 0.36	| 7 |
| 96	| 0.47	| 9 |
