1.5.4 Pertanyaan Praktikum:
1. Pada kondisi apa program masuk ke blok if?
- Program masuk ke blok if ketika nilai timeDelay sudah kurang dari atau sama dengan 100, yang menandakan LED berada pada kondisi berkedip sangat cepat sehingga perlu dilakukan reset.
2. Pada kondisi apa program masuk ke blok else?
- Program masuk ke blok else ketika nilai timeDelay masih lebih besar dari 100, sehingga nilainya akan terus dikurangi dan menyebabkan LED berkedip semakin cepat.
3. Apa fungsi dari perintah delay(timeDelay)?
- Perintah delay(timeDelay) berfungsi sebagai jeda waktu dalam eksekusi program yang menentukan cepat atau lambatnya kedipan LED.
4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
## Source Code
```cpp
const int ledPin = 6;      // Menentukan pin digital 6 sebagai output untuk LED
int timeDelay = 1000;      // Nilai awal delay 1000 ms (LED berkedip lambat)

void setup() {
  pinMode(ledPin, OUTPUT); // Mengatur pin LED sebagai output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Menyalakan LED
  delay(timeDelay);           // Menahan LED tetap menyala sesuai nilai delay

  digitalWrite(ledPin, LOW);  // Mematikan LED
  delay(timeDelay);           // Menahan LED tetap mati sesuai nilai delay

  if (timeDelay > 500) {      
    timeDelay -= 200;         // Mengurangi delay cukup besar → dari lambat ke sedang
  } else if (timeDelay > 200) {
    timeDelay -= 100;         // Mengurangi delay lebih kecil → dari sedang ke cepat
  } else {
    digitalWrite(ledPin, LOW); // Memastikan LED dalam kondisi mati
    while (true);              // Menghentikan program agar LED tetap mati
  }
}
```

1.6.4 Pertanyaan Praktikum:
1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!
- <img width="1023" height="796" alt="Screenshot (1126)" src="https://github.com/user-attachments/assets/84c6b841-74c9-4651-927d-b2613c1c7d6d" />
2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
- Efek LED berjalan dari kiri ke kanan dihasilkan melalui penggunaan struktur perulangan for yang melakukan inkrementasi pada variabel pin. Program memulai perulangan dari pin terendah, kemudian secara bertahap berpindah ke pin yang lebih tinggi. Pada setiap iterasi, LED akan dinyalakan, diberikan jeda waktu, lalu dimatikan sebelum berpindah ke pin berikutnya, sehingga menghasilkan efek pergerakan dari kiri ke kanan.
3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
- Efek LED kembali dari kanan ke kiri dihasilkan melalui struktur perulangan for yang melakukan dekrementasi pada variabel pin. Program memulai perulangan dari pin tertinggi dan bergerak menuju pin yang lebih rendah. Pada setiap proses, LED dinyalakan, diberi jeda, kemudian dimatikan kembali, sehingga secara visual LED tampak bergerak dari kanan ke kiri.
4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
## Source Code
```cpp
void setup() {
  for (int i = 2; i <= 7; i++) {     // Melakukan perulangan untuk setiap pin dari 2 sampai 7
    pinMode(i, OUTPUT);              // Mengatur semua pin tersebut sebagai output
  }
}

void loop() {
  digitalWrite(2, HIGH);             // Menyalakan LED pada pin 2 (bagian kiri)
  digitalWrite(3, HIGH);             // Menyalakan LED pada pin 3 (bagian kiri)
  digitalWrite(4, HIGH);             // Menyalakan LED pada pin 4 (bagian kiri)
  digitalWrite(5, LOW);              // Mematikan LED pada pin 5 (bagian kanan)
  digitalWrite(6, LOW);              // Mematikan LED pada pin 6 (bagian kanan)
  digitalWrite(7, LOW);              // Mematikan LED pada pin 7 (bagian kanan)
  delay(500);                        // Memberikan jeda agar pola terlihat jelas

  digitalWrite(2, LOW);              // Mematikan LED pada pin 2
  digitalWrite(3, LOW);              // Mematikan LED pada pin 3
  digitalWrite(4, LOW);              // Mematikan LED pada pin 4
  digitalWrite(5, HIGH);             // Menyalakan LED pada pin 5 (bagian kanan)
  digitalWrite(6, HIGH);             // Menyalakan LED pada pin 6 (bagian kanan)
  digitalWrite(7, HIGH);             // Menyalakan LED pada pin 7 (bagian kanan)
  delay(500);                        // Memberikan jeda sebelum pola diulang kembali
}
```
