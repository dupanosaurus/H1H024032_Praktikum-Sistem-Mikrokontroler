//# Proyek LED: 3 Kiri dan 3 Kanan Menyala Bergantian

//Proyek ini adalah modifikasi program Arduino yang mengontrol 6 buah LED. Alur nyala LED dirubah dari yang awalnya "berjalan" (running/chaser) menjadi menyala secara berkelompok:
//* **Kelompok Kiri (Pin 2, 3, 4)** akan menyala bersamaan, sementara Kelompok Kanan mati.
//* Selanjutnya, **Kelompok Kanan (Pin 5, 6, 7)** akan menyala bersamaan, sementara Kelompok Kiri mati.
//* Pola ini berulang terus-menerus (flip-flop kelompok).

//---

//## Kode Program (`main.ino`)

//```cpp
int timer = 500; 

void setup() {
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // --- FASE 1: 3 LED KIRI MENYALA, 3 LED KANAN MATI ---
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  
  delay(timer);

  // --- FASE 2: 3 LED KIRI MATI, 3 LED KANAN MENYALA ---
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  
  delay(timer);
}