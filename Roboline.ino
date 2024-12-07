#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3);  // RX, TX
#define enA 10                   // Enable1 Pin L298 enA
#define in1 9                    // Motor1 Pin L298 in1
#define in2 8                    // Motor1 Pin L298 in2
#define in3 7                    // Motor2 Pin L298 in3
#define in4 6                    // Motor2 Pin L298 in4
#define enB 5                    // Enable2 Pin L298 enB
#define R_S A0                   // Sensor IR Kanan
#define M_S A2                   // Sensor IR Tengah
#define L_S A1                   // Sensor IR Kiri
int bt_data;                     // Variabel untuk menerima data dari port
serial int Kecepatan = 130;
int mode = 0;
void setup() {          // kode setup, dijalankan sekali
  pinMode(R_S, INPUT);  // Deklarasikan sensor IR kanan
  sebagai input
    pinMode(M_S, INPUT);  // Deklarasikan sensor IR tengah
  sebagai input
    pinMode(L_S, INPUT);  // Deklarasikan sensor IR kiri
  sebagai input
    pinMode(enA, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 enA
    pinMode(in1, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 in1
    pinMode(in2, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 in2
    pinMode(in3, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 in3
    pinMode(in4, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 in4
    pinMode(enB, OUTPUT);  // Deklarasikan sebagai output untuk
  Pin L298 enB
    Serial.begin(9600);  // Mulai komunikasi serial dengan
  kecepatan 9600bps BT_Serial.begin(9600);
  delay(500);
}
void loop() {
  if (BT_Serial.available() > 0) {  // Jika ada data yang
    dikirim, baca dan simpan dalam variabel state
               bt_data = BT_Serial.read();
    if (bt_data > 20) {
      Kecepatan = bt_data;
    }
  }
  if (bt_data == 8) {
    mode = 1;
    Kecepatan = 130;  // Perintah Auto Line Follower
  } else if (bt_data == 9) {
    mode = 0;
    Berhenti();  // Perintah Kontrol Manual dari Aplikasi
    Android
  }
  analogWrite(enA, Kecepatan);  // Tulis Duty Cycle 0 hingga
  255 pada Pin Enable A untuk Kecepatan Motor1
    analogWrite(enB, Kecepatan);  // Tulis Duty Cycle 0 hingga
  255 pada Pin Enable B untuk Kecepatan Motor2 if (mode == 0) {
    //======================================================
    == == == == == == == == == == == == =
      // Perintah Kontrol Tombol
      //======================================================
      == == == == == == == == == == == == =
        if (bt_data == 1) {
      maju();  // jika bt_data adalah '1' motor DC akan maju
    }
    else if (bt_data == 2) {
      mundur();  // jika bt_data adalah '2' motor akan mundur
    }
    else if (bt_data == 3) {
      belokKiri();  // jika bt_data adalah '3' motor akan
      belok kiri
    }
    else if (bt_data == 4) {
      belokKanan();  // jika bt_data adalah '4' motor akan
      belok kanan
    }
    else if (bt_data == 5) {
      Berhenti();  // jika bt_data adalah '5' motor akan
      berhenti
    }
    //======================================================
    == == == == == == == == == == == == =
      // Perintah Kontrol Suara
      //======================================================
      == == == == == == == == == == == == =
        else if (bt_data == 6) {
      belokKiri();
      delay(100);
      bt_data = 5;
    }
    else if (bt_data == 7) {
      belokKanan();
      delay(100);
      bt_data = 5;
    }
  }
  else {
    //======================================================
    == == == == == == == == == == == == =
      // Kontrol Pengikut Garis
      //======================================================
      == == == == == == == == == == == == =
        if ((digitalRead(R_S) == 0) && (digitalRead(M_S) == 0)
            && (digitalRead(L_S) == 0)) {
      maju();  // Jika semua sensor berada di atas putih,
      maju
    }
    else if ((digitalRead(R_S) == 1) && (digitalRead(M_S) == 0) && (digitalRead(L_S) == 0)) {
      belokKanan();  // Jika sensor kanan berada di atas
      hitam, belok kanan
    }
    else if ((digitalRead(R_S) == 0) && (digitalRead(M_S) == 0) && (digitalRead(L_S) == 1)) {
      belokKiri();  // Jika sensor kiri berada di atas hitam,
      belok kiri
    }
    else if ((digitalRead(R_S) == 0) && (digitalRead(M_S) == 1) && (digitalRead(L_S) == 0)) {
      maju();  // Jika sensor tengah berada di atas hitam,
      maju
    }
    else if ((digitalRead(R_S) == 1) && (digitalRead(M_S) == 1) && (digitalRead(L_S) == 0)) {
      belokKanan();  // Jika sensor kanan dan tengah berada
      di atas hitam, belok kanan
    }
    else if ((digitalRead(R_S) == 0) && (digitalRead(M_S) == 1) && (digitalRead(L_S) == 1)) {
      belokKiri();  // Jika sensor kiri dan tengah berada di
      atas hitam, belok kiri
    }
    else if ((digitalRead(R_S) == 1) && (digitalRead(M_S) == 1) && (digitalRead(L_S) == 1)) {
      Berhenti();  // Jika semua sensor berada di atas hitam,
      berhenti
    }
  }
  delay(10);
}
void maju() {               // Maju
  digitalWrite(in1, HIGH);  // Pin motor kanan maju
  digitalWrite(in2, LOW);   // Pin motor kanan mundur
  digitalWrite(in3, LOW);   // Pin motor kiri mundur
  digitalWrite(in4, HIGH);  // Pin motor kiri maju
}
void mundur() {             // Mundur
  digitalWrite(in1, LOW);   // Pin motor kanan maju
  digitalWrite(in2, HIGH);  // Pin motor kanan mundur
  digitalWrite(in3, HIGH);  // Pin motor kiri mundur
  digitalWrite(in4, LOW);   // Pin motor kiri maju
}
void belokKanan() {         // Belok kanan
  digitalWrite(in1, LOW);   // Pin motor kanan maju
  digitalWrite(in2, HIGH);  // Pin motor kanan mundur
  digitalWrite(in3, LOW);   // Pin motor kiri mundur
  digitalWrite(in4, HIGH);  // Pin motor kiri maju
}
void belokKiri() {          // Belok kiri
  digitalWrite(in1, HIGH);  // Pin motor kanan maju
  digitalWrite(in2, LOW);   // Pin motor kanan mundur
  digitalWrite(in3, HIGH);  // Pin motor kiri mundur
  digitalWrite(in4, LOW);   // Pin motor kiri maju
}
void Berhenti() {          // Berhenti
  digitalWrite(in1, LOW);  // Pin motor kanan maju
  digitalWrite(in2, LOW);  // Pin motor kanan mundur
  digitalWrite(in3, LOW);  // Pin motor kiri mundur
  digitalWrite(in4, LOW);  // Pin motor kiri maju
}
