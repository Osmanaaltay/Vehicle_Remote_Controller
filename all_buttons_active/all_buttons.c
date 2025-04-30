#include <12F629.h>
#fuses INTRC_IO, NOWDT, NOMCLR
#use delay(clock=4000000)

// UART: sadece TX, 9600 baud
#use rs232(baud=9600, xmit=PIN_A4, bits=8, parity=N, stop=1)

// Gönderilecek veriler
int8 veri1 = 0xA5;
int8 veri2 = 0x3C;
int8 veri3 = 0x7E;
int8 veri4 = 0x5A;  // 4. veri

// Yazýlým debouncer için sayaçlar ve durumlar
#define DEBOUNCE_THRESHOLD 5  // Stabilize için gereken döngü sayýsý

int1 stable1 = 0, stable2 = 0, stable3 = 0;
int8 counter1 = 0, counter2 = 0, counter3 = 0;

void debounce_buttons() {
   int1 raw1 = input(PIN_A3);
   int1 raw2 = input(PIN_A1);
   int1 raw3 = input(PIN_A0);
   
   // Button 1
   if (raw1 == stable1) {
      counter1 = 0;
   } else {
      counter1++;
      if (counter1 >= DEBOUNCE_THRESHOLD) {
         stable1 = raw1;
         counter1 = 0;
      }
   }
   // Button 2
   if (raw2 == stable2) {
      counter2 = 0;
   } else {
      counter2++;
      if (counter2 >= DEBOUNCE_THRESHOLD) {
         stable2 = raw2;
         counter2 = 0;
      }
   }
   // Button 3
   if (raw3 == stable3) {
      counter3 = 0;
   } else {
      counter3++;
      if (counter3 >= DEBOUNCE_THRESHOLD) {
         stable3 = raw3;
         counter3 = 0;
      }
   }
}

void main() {
   // GP3, GP1, GP0 = giriþ; GP4 = TX çýkýþ; GP2 = LED çýkýþ
   set_tris_a(0b11101111);

   // UART idle HIGH, LED kapalý
   output_high(PIN_A4);
   output_low(PIN_A2);
   delay_ms(200);

   while(TRUE) {
      // Debounce iþlemi
      debounce_buttons();

      // Buton basýlýyken sürekli veri gönderme öncelikli
      if (stable1) {
         putc(veri1);
         output_high(PIN_A2);
         delay_ms(200);
         output_low(PIN_A2);
      }
      else if (stable2) {
         putc(veri2);
         output_high(PIN_A2);
         delay_ms(200);
         output_low(PIN_A2);
      }
      else if (stable3) {
         putc(veri3);
         output_high(PIN_A2);
         delay_ms(200);
         output_low(PIN_A2);
      }
      // Hiçbiri basýlý deðilse sürekli veri4 gönder
      else {
         putc(veri4);
         output_high(PIN_A2);
         delay_ms(200);
         output_low(PIN_A2);
      }

      // Döngü hýzý kontrolü
      delay_ms(10);
   }
}

