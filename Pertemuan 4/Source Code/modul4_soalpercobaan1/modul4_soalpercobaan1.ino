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
  // Ubah nilai ADC menjadi sudut servo (0–180 derajat)
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