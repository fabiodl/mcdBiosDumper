#include <stdint.h>
#include <genesis.h>
#include <stdbool.h>

volatile uint8_t* DATA1 = (volatile uint8_t*)0xA10003;
volatile uint8_t* DATA2 = (volatile uint8_t*)0xA10005;


volatile uint8_t* TXDATA2 = (volatile uint8_t*)0xA10015;
volatile uint8_t* RXDATA2 = (volatile uint8_t*)0xA10017;
volatile uint8_t* SCTRL2 =  (volatile uint8_t*)0xA10019;



volatile uint8_t* TXDATA3 = (volatile uint8_t*)0xA1001B;
volatile uint8_t* RXDATA3 = (volatile uint8_t*)0xA1001D;
volatile uint8_t* SCTRL3 =  (volatile uint8_t*)0xA1001F;

#define BPS1  0x80
#define BPS0  0x40
#define SIN   0x20
#define SOUT  0x10
#define RINT  0x08
#define RERR  0x04
#define RRDY  0x02
#define TFUL  0x01

#define OFFSET 0x400000

static uint8_t* const start=(uint8_t*)OFFSET;
static uint8_t* const end=(uint8_t*)(OFFSET+0x20000);


int main(){

  VDP_drawText("Press up of controller 1", 0, 0);
  while(*DATA1&1);
  VDP_drawText("Dumping to pin 6 (TL) of controller 2", 0, 1);
  *SCTRL2=SOUT;
  char buffer[10];
  uint8_t* p=start;  
  while (p<end){
    for (uint16_t i=0;i<1024;i++){
      while(*SCTRL2&TFUL);
      *TXDATA2=*p;
      p++;
    }
    sprintf(buffer,"%ld Kb",(p-start)>>10);
    VDP_drawText(buffer, 0, 2);
  }
  VDP_drawText("Dumping complete", 0, 3);
  while (true);
}
