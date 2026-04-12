#include <Arduino.h>

// 7-Segment Display (Efficient Version)
// Display 0 - 9 and A - F

// Pin mapping segment (berdasarkan Tabel 1.4)
// a, b, c, d, e, f, g, dp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Segment pattern for 0-F
// Urutan segmen: a, b, c, d, e, f, g, dp
// 1 = ON, 0 = OFF (Common Cathode)
byte digitPattern[16][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 1, 0, 1, 1, 0}, // 9
  {1, 1, 1, 0, 1, 1, 1, 0}, // A
  {0, 0, 1, 1, 1, 1, 1, 0}, // b
  {1, 0, 0, 1, 1, 1, 0, 0}, // C
  {0, 1, 1, 1, 1, 0, 1, 0}, // d
  {1, 0, 0, 1, 1, 1, 1, 0}, // E
  {1, 0, 0, 0, 1, 1, 1, 0}  // F
};

// Fungsi menampilkan digit
void displayDigit(int num) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup() {
  // Mengatur semua pin segment sebagai OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Menampilkan angka 0 sampai 15 (F) secara berurutan
  for (int i = 0; i < 16; i++) {
    displayDigit(i);
    delay(1000); // Jeda 1 detik setiap angka
  }
}
