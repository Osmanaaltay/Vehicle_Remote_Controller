#include <12F629.h>
#fuses INTRC_IO, NOWDT, NOMCLR
#use delay(clock=4000000)

// UART: sadece TX, 9600 baud
#use rs232(baud=9600, xmit=PIN_A4, bits=8, parity=N, stop=1)

int8 veri1 = 0xA5;
int8 veri2 = 0x3C;
int8 veri3 = 0x7E;
int8 dly=200;
void main() {
   set_tris_a(0b11101111); // GP3, GP1, GP0 giriþ; GP4 (TX), GP2 (LED) çýkýþ

   output_high(PIN_A4);     // UART TX hattýný IDLE'a çek
   output_low(PIN_A2);      // LED baþlangýçta kapalý

   delay_ms(dly);           // Baþlangýç gecikmesi

   while(TRUE) {
      int1 buton1 = input(PIN_A3); // GP3 - pin 4
      int1 buton2 = input(PIN_A1); // GP1 - pin 6
      int1 buton3 = input(PIN_A0); // GP0 - pin 7

      if (buton1) {
         putc(veri1);
         output_high(PIN_A2);
         delay_ms(dly);
         output_low(PIN_A2);
      }
      else if (buton2) {
         putc(veri2);
         output_high(PIN_A2);
         delay_ms(dly);
         output_low(PIN_A2);
      }
      else if (buton3) {
         putc(veri3);
         output_high(PIN_A2);
         delay_ms(dly);
         output_low(PIN_A2);
      }

      delay_ms(10); // Döngü beklemesi
   }
}

