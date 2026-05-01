Pertanyaan Praktikum Percobaan 4A
1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
- Fungsi analogRead() digunakan untuk membaca tegangan analog yang berasal dari potensiometer melalui pin analog Arduino. Nilai tegangan tersebut kemudian dikonversi oleh modul ADC internal menjadi data digital dengan rentang 0 hingga 1023. Pada praktikum ini, hasil pembacaan tersebut digunakan sebagai masukan untuk menentukan sudut putaran motor servo. Ketika potensiometer diputar, nilai analogRead() berubah dan servo bergerak mengikuti perubahan nilai tersebut.
2. Mengapa diperlukan fungsi map() dalam program tersebut?
- Fungsi map() diperlukan untuk mengubah rentang nilai hasil pembacaan ADC menjadi rentang nilai yang sesuai dengan perangkat output. Nilai dari analogRead() berada pada rentang 0–1023, sedangkan motor servo bekerja pada rentang sudut 0–180 derajat. Oleh karena itu, map() digunakan agar perubahan nilai potensiometer dapat diterjemahkan secara proporsional menjadi sudut servo. Tanpa fungsi ini, nilai ADC tidak dapat langsung digunakan secara tepat untuk mengendalikan posisi servo.
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md
  
```cpp
#include <Servo.h> // library untuk servo motor

Servo myservo; // membuat objek servo

// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan servo
const int potensioPin = A0;  // Pin analog A0 untuk membaca potensiometer
const int servoPin = 9;      // Pin digital 9 (PWM) untuk mengontrol servo

// ===================== VARIABEL =====================
// Variabel untuk menyimpan data ADC dan sudut servo
int pos = 0; // Tipe data integer, inisialisasi awal pada sudut 0
int val = 0; // Tipe data integer, inisialisasi awal nilai ADC 0

void setup() {

  // Hubungkan servo ke pin yang sudah ditentukan
  myservo.attach(servoPin); // Menggunakan variabel servoPin (Pin 9)

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600); // Baud rate standar 9600 bps

}

void loop() {

  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer (rentang 0–1023)
  val = analogRead(potensioPin); // Membaca tegangan dari pin A0

  // ===================== KONVERSI DATA =====================
  // Ubah nilai ADC menjadi sudut servo (30–150 derajat)
  pos = map(val,
             0,    // nilai minimum ADC
             1023, // nilai maksimum ADC (resolusi 10-bit Arduino standar)
             30,    // sudut minimum servo
             150   // sudut maksimum servo
             );

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); // Menggerakkan servo ke sudut 'pos'

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan sudut servo ke Serial Monitor
  Serial.print("ADC Potensio: ");
  Serial.print(val); // Menampilkan nilai ADC murni

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); // Menampilkan sudut konversi

  // ===================== STABILISASI =====================
  // Delay untuk memberi waktu servo bergerak stabil
  delay(15); // Waktu tunda 15 milidetik agar pergerakan servo halus
}
```

Pertanyaan Praktikum Percobaan 4B
1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!
- LED dapat diatur tingkat kecerahannya menggunakan fungsi analogWrite() karena fungsi ini menghasilkan sinyal PWM (Pulse Width Modulation) pada pin tertentu Arduino. PWM bekerja dengan cara menyalakan dan mematikan LED sangat cepat dalam satu periode waktu. Perbandingan lama kondisi ON terhadap OFF disebut duty cycle. Semakin lama LED berada pada kondisi ON, maka cahaya akan tampak semakin terang. Sebaliknya, jika waktu ON lebih sedikit, LED terlihat lebih redup. Karena proses ini berlangsung sangat cepat, mata manusia melihatnya sebagai perubahan tingkat kecerahan.
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
- Nilai ADC merupakan hasil pembacaan tegangan analog oleh Arduino dengan resolusi 10-bit, sehingga memiliki rentang 0 sampai 1023. Sedangkan nilai PWM pada fungsi analogWrite() menggunakan resolusi 8-bit, sehingga memiliki rentang 0 sampai 255. Oleh karena itu, nilai ADC perlu dikonversi terlebih dahulu agar sesuai dengan rentang PWM. Biasanya digunakan fungsi map() untuk mengubah nilai 0–1023 menjadi 0–255 secara proporsional.
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

```cpp
#include <Arduino.h> // Library dasar Arduino

// ===================== PIN SETUP =====================
// Menentukan pin yang digunakan
const int potPin = A0;   // Pin analog A0 untuk potensiometer
const int ledPin = 9;    // Pin digital 9 (PWM) untuk LED

// ===================== VARIABEL =====================
int nilaiADC = 0; // Menyimpan hasil pembacaan ADC
int pwm = 0;      // Menyimpan nilai PWM

void setup() {

  // Mengatur pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // Mengaktifkan Serial Monitor
  Serial.begin(9600);
}

void loop() {

  // ===================== PEMBACAAN ADC =====================
  // Membaca nilai potensiometer (0–1023)
  nilaiADC = analogRead(potPin);

  // ===================== KONVERSI ADC KE PWM =====================
  // Mengubah rentang ADC menjadi PWM (0–255)
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // ===================== LOGIKA RENTANG KECERAHAN =====================
  // LED hanya menyala jika PWM berada di antara 50 sampai 200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm); // LED menyala sesuai tingkat PWM
  } else {
    analogWrite(ledPin, 0);   // LED mati
  }

  // ===================== MONITORING DATA =====================
  Serial.print("ADC: ");
  Serial.print(nilaiADC);

  Serial.print(" | PWM: ");
  Serial.println(pwm);

  // ===================== DELAY =====================
  delay(50); // Delay agar pembacaan stabil
}
```
