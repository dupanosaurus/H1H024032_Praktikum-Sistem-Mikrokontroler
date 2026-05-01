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