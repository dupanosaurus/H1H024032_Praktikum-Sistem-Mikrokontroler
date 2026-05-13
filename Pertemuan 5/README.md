Pertanyaan Praktikum Percobaan 5A
1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
- Ketiga task pada FreeRTOS berjalan secara bergantian melalui scheduler, bukan paralel murni karena Arduino Uno hanya memiliki satu prosesor. Scheduler akan mengatur perpindahan eksekusi antar task dengan sangat cepat. Saat sebuah task menjalankan `vTaskDelay()`, task tersebut berhenti sementara sehingga prosesor dapat digunakan oleh task lain. Mekanisme ini membuat beberapa task terlihat berjalan secara bersamaan.
2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
- Untuk menambahkan task keempat, perlu dibuat fungsi task baru terlebih dahulu, misalnya `TaskBlink3()`. Setelah itu, task didaftarkan menggunakan `xTaskCreate()` di dalam `setup()`. Setelah scheduler dijalankan, FreeRTOS akan mengatur eksekusi task baru tersebut bersama task lainnya secara multitasking.
3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md.

```cpp
#include <Arduino_FreeRTOS.h> // Library FreeRTOS
void TaskBlink1(void *pvParameters); // Deklarasi task pertama
void TaskBlink2(void *pvParameters); // Deklarasi task kedua

const int potPin = A0; // Deklarasi pin analog

void setup() {
  Serial.begin(9600); // Mengaktifkan komunikasi serial dengan baud rate 9600

  // Membuat task 1 
  xTaskCreate(
    TaskBlink1, // Nama fungsi task
    "task1",    // Nama task
    128,        // Ukuran stack memory
    NULL,       // Parameter task
    1,          // Prioritas task
    NULL        // Handle task
  );

  // Membuat task 2
  xTaskCreate(
    TaskBlink2,
    "task2",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler(); // Scheduler FreeRTOS
}

void loop() { // Kosong karena semua proses dijalankan oleh task FreeRTOS
}

// Task LED 1
void TaskBlink1(void *pvParameters) {

  pinMode(8, OUTPUT); // Pin 8 dijadikan output LED

  while (1) {
    int adc = analogRead(potPin); // Membaca nilai ADC dari potensiometer (0–1023)
    int delayLed = map(adc, 0, 1023, 50, 1000); // Mengubah nilai ADC menjadi delay 50–1000 ms

    // Monitoring serial
    Serial.print("ADC: ");
    Serial.print(adc);

    // Menampilkan nilai ADC dan delay ke Serial Monitor
    Serial.print(" | Delay: ");
    Serial.println(delayLed);

    digitalWrite(8, HIGH); // Menyalakan LED
    vTaskDelay(delayLed / portTICK_PERIOD_MS); // Delay sesuai nilai potensiometer

    digitalWrite(8, LOW); // Mematikan LED
    vTaskDelay(delayLed / portTICK_PERIOD_MS); // Delay sesuai nilai potensiometer
  }
}

// Task LED 2
void TaskBlink2(void *pvParameters) {

  pinMode(7, OUTPUT); // Pin 7 dijadikan output LED kedua

  while (1) {
    digitalWrite(7, HIGH); // LED menyala
    vTaskDelay(300 / portTICK_PERIOD_MS); // Delay tetap 300 ms

    digitalWrite(7, LOW); // LED mati
    vTaskDelay(300 / portTICK_PERIOD_MS); // Delay tetap 300 ms
  }
}
```

Pertanyaan Praktikum Percobaan 5B
1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
- Kedua task pada program FreeRTOS berjalan secara bergantian melalui scheduler, bukan paralel murni karena Arduino Uno hanya memiliki satu prosesor. Scheduler akan mengatur perpindahan eksekusi antar task dengan sangat cepat sehingga terlihat berjalan bersamaan. Saat task `read_data` menjalankan `vTaskDelay()`, prosesor akan digunakan oleh task display untuk menerima dan menampilkan data dari queue.
2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
- Program ini memiliki potensi race condition yang sangat kecil karena komunikasi data antar task dilakukan menggunakan queue FreeRTOS. Queue berfungsi sebagai mekanisme sinkronisasi sehingga data dikirim dan diterima secara teratur tanpa diakses bersamaan oleh dua task. Dengan demikian, konflik akses data dapat dihindari dan pertukaran data antar task menjadi lebih aman.
3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.

Link modifikasi: https://wokwi.com/projects/463836179959802881
<img width="1920" height="1200" alt="image" src="https://github.com/user-attachments/assets/25a50348-2aef-4546-8dae-7ef27050673f" />

```cpp
#include <DHT.h> // Library sensor DHT

#define DHTPIN 2 // Pin data sensor di D2
#define DHTTYPE DHT22 // Tipe sensor DHT22

DHT dht(DHTPIN, DHTTYPE); // Membuat objek sensor

// Variabel pengganti Scheduler RTOS
unsigned long waktuSebelumnya = 0; // Menyimpan waktu sebelumnya
const long jedaWaktu = 2000; // Interval pembacaan 2 detik

void setup() {
  Serial.begin(9600); // Memulai Serial Monitor
  dht.begin(); // Mengaktifkan sensor DHT
  Serial.println("Sistem Mulai Membaca Sensor...");
}

void loop() {

  unsigned long waktuSekarang = millis(); // Membaca waktu saat ini

  // Mengecek apakah sudah lewat 2 detik
  if (waktuSekarang - waktuSebelumnya >= jedaWaktu) {
    waktuSebelumnya = waktuSekarang; // Update waktu terakhir
    float t = dht.readTemperature(); // Membaca suhu
    float h = dht.readHumidity(); // Membaca kelembapan

    // Mengecek apakah data valid
    if (!isnan(t) && !isnan(h)) {
      Serial.print("Temperature: ");
      Serial.print(t); // Menampilkan suhu
      Serial.println(" °C");
      Serial.print("Humidity: ");
      Serial.print(h); // Menampilkan kelembapan
      Serial.println(" %");
      Serial.println("-------------------");
    } else {
      Serial.println("Gagal membaca sensor DHT!");
    }
  }
}
```
