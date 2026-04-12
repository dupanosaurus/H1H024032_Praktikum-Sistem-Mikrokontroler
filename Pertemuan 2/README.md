2.5.4 Pertanyaan Praktikum:
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
- 
2. Apa yang terjadi jika nilai num lebih dari 15?
- Jika nilai num lebih dari 15, maka program akan mencoba mengakses indeks array digitPattern yang tidak tersedia. Hal ini dapat menyebabkan tampilan 7-segment menjadi tidak sesuai (acak) atau bahkan berpotensi menimbulkan error karena terjadi akses data di luar batas array (out of bounds).
3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!
- Program ini menggunakan tipe common cathode, karena logika pada array menunjukkan bahwa nilai 1 berarti segmen menyala dan 0 berarti mati. Pada 7-segment common cathode, segmen akan menyala ketika diberikan logika HIGH. Selain itu, penggunaan operator negasi (!digitPattern) menyesuaikan kondisi output agar sesuai dengan karakteristik common cathode yang terhubung ke GND.
4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
## Source Code
```cpp
#include <Arduino.h> // Menambahkan library Arduino

// Pin mapping 7-segment (a, b, c, d, e, f, g, dp)
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4}; 
// Menentukan pin Arduino yang terhubung ke masing-masing segmen

// Segment pattern untuk 0 - F
// Urutan: a, b, c, d, e, f, g, dp
byte digitPattern[16][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0 = semua segmen menyala kecuali g dan dp
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1 = hanya segmen b dan c
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8 = semua segmen menyala
  {1, 1, 1, 1, 0, 1, 1, 0}, // 9
  {1, 1, 1, 0, 1, 1, 1, 0}, // A
  {0, 0, 1, 1, 1, 1, 1, 0}, // b
  {1, 0, 0, 1, 1, 1, 0, 0}, // C
  {0, 1, 1, 1, 1, 0, 1, 0}, // d
  {1, 0, 0, 1, 1, 1, 1, 0}, // E
  {1, 0, 0, 0, 1, 1, 1, 0}  // F
};

// Fungsi untuk menampilkan angka/karakter pada 7-segment
void displayDigit(int num) {
  // Perulangan untuk setiap segmen (a sampai dp)
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], !digitPattern[num][i]); // Mengatur nyala/mati segmen sesuai pola (dibalik karena common cathode)
  }
}

void setup() {
  // Perulangan untuk semua pin segmen
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT); // Mengatur semua pin sebagai output 
  }
}

void loop() {
  // Perulangan dari 15 ke 0 (F ke 0)
  for (int i = 15; i >= 0; i--) { 
    displayDigit(i); // Menampilkan angka/karakter sesuai indeks
    delay(1000); // Delay 1 detik sebelum pindah ke angka berikutnya
  }
}
```

2.6.4 Pertanyaan Praktikum:
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
- 
2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?
- Mode INPUT_PULLUP digunakan pada push button agar Arduino mengaktifkan resistor pull-up internal, sehingga pin input memiliki kondisi default HIGH saat tombol tidak ditekan dan berubah menjadi LOW saat tombol ditekan. Keuntungan penggunaan metode ini adalah tidak memerlukan resistor eksternal, rangkaian menjadi lebih sederhana, serta mengurangi risiko kondisi floating yang dapat menyebabkan pembacaan input tidak stabil atau noise.
3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?
- Jika salah satu LED segmen tidak menyala, penyebabnya dapat berasal dari sisi hardware maupun software. Dari sisi hardware, kemungkinan terjadi kesalahan pada pemasangan kabel, resistor yang tidak terhubung dengan baik, LED segmen yang rusak, atau koneksi yang longgar pada breadboard. Sementara itu, dari sisi software, masalah dapat disebabkan oleh kesalahan pada penentuan pin, kesalahan pola pada array digitPattern, atau logika program yang tidak sesuai sehingga segmen tertentu tidak pernah diberi sinyal aktif.
4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
## Source Code
```cpp
#include <Arduino.h> // Menambahkan library Arduino

// Pin mapping segment (a, b, c, d, e, f, g, dp)
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4}; 
// Menentukan pin Arduino yang terhubung ke masing-masing segmen

// Definisi Push button
const int btnUp = 3; // Tombol untuk Increment (menambah nilai)
const int btnDown = 2; // Tombol untuk Decrement (mengurangi nilai)

// Counter
int counter = 0; // Variabel untuk menyimpan nilai yang akan ditampilkan (0–15)

// Deklarasi masing-masing button untuk mendeteksi perubahan
bool lastBtnUpState = HIGH; // Menyimpan kondisi terakhir tombol UP (default tidak ditekan)
bool lastBtnDownState = HIGH; // Menyimpan kondisi terakhir tombol DOWN (default tidak ditekan)

// Segment pattern untuk 0 - F
// Urutan: a, b, c, d, e, f, g, dp
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5 
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,0}, // A
  {0,0,1,1,1,1,1,0}, // b
  {1,0,0,1,1,1,0,0}, // C
  {0,1,1,1,1,0,1,0}, // d
  {1,0,0,1,1,1,1,0}, // E
  {1,0,0,0,1,1,1,0}  // F
};

// Fungsi untuk menampilkan angka/karakter pada 7-segment
void displayDigit(int num) {
  // Perulangan untuk setiap segmen (a sampai dp)
  for(int i=0; i<8; i++) {
    digitalWrite(segmentPins[i], !digitPattern[num][i]); // Mengatur nyala/mati segmen sesuai pola (dibalik karena common cathode)
  }
}

void setup() {
  // Perulangan untuk semua pin segmen
  for(int i=0; i<8; i++) {
    pinMode(segmentPins[i], OUTPUT); // Mengatur semua pin sebagai output 
  }

  // Set kedua tombol menggunakan internal pull-up resistor
  pinMode(btnUp, INPUT_PULLUP);   
  // Tombol akan bernilai HIGH saat tidak ditekan, LOW saat ditekan
  pinMode(btnDown, INPUT_PULLUP);

  displayDigit(counter); 
  // Menampilkan nilai awal counter (0)
}

// Membaca status terbaru dari kedua tombol
void loop() {
  bool currentBtnUpState = digitalRead(btnUp); // Membaca kondisi tombol Up
  bool currentBtnDownState = digitalRead(btnDown); // Membaca kondisi tombol Down

  // Logika untuk tombol Up (Increment)
  if (lastBtnUpState == HIGH && currentBtnUpState == LOW) {
    counter++; // Menambah nilai counter
    if(counter > 15) counter = 0; // Jika melebihi F (15), kembali ke 0
    displayDigit(counter); // Menampilkan nilai terbaru ke 7-segment
    delay(200); // Delay untuk debounce 
  }

  // Logika untuk tombol Down (Decrement)
  if (lastBtnDownState == HIGH && currentBtnDownState == LOW) {
    counter--; // Mengurangi nilai counter
    if(counter < 0) counter = 15; // Jika kurang dari 0, kembali ke F (15)
    displayDigit(counter); // Menampilkan nilai terbaru ke 7-segment
    delay(200); // Delay untuk debounce
  }

  // Menyimpan status tombol untuk dibandingkan di loop berikutnya
  lastBtnUpState = currentBtnUpState;   
  lastBtnDownState = currentBtnDownState; 
}
```
