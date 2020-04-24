// nova verzija koda

#include <avr/io.h>
#include <avr/interrupt.h>
#define POD_A
unsigned char slika_led = 0xFF;
unsigned char t0_cnt = 0;
int a = 0;
ISR(TIMER0_COMPA_vect)
{
 //prekid tajmera 0 usled dostizanja vrednosti registra OCR0A
 t0_cnt++;
}
int main()
{

 DDRD = 0xff; //port D -> izlaz
 DDRB |= 1 << 4; //PB4 -> izlaz
 PORTB &= ~(1 << 4); //PB4 = 0, cime se ukljucuje tranzistor Q0

 //inicijalizacija tajmera 0:
 TCCR0A = 0x02; //tajmer 0: CTC mod
#ifdef POD_A
 TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
 OCR0A = 123; //perioda tajmera 0: 124 Tclk (OCR0A + 1 = 124)
#else
 TCCR0B = 0x04; //tajmer 0: fclk = fosc/256
 OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
#endif
 TIMSK0 = 0x02; //dozvola prekida tajmera 0
 //usled dostizanja vrednosti registra OCR0A

 sei(); //I = 1 (dozvola prekida)
 
 while(1)
 {
#ifdef POD_A
 if (t0_cnt){
#else
 if (t0_cnt == 125){
#endif
 t0_cnt = 0;
 slika_led ^= 0x01;
 PORTD = slika_led;
 }
 }
 return 0;
}
