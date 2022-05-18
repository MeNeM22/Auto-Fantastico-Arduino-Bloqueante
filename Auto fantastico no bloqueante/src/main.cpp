#include <Arduino.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

char multiplicador = 25; //defino a multiplicador con un valor inicial de 25
int ctp = 0;

typedef enum
{
  estado_inicial,

  led1,
  led2,
  led3,
  led4,
  led5,
  led6,
  led7,
  led8,
  led9,
  led10,
  led11,
  Led12,
  led13,
  led14,
  led15
} estadoMEF;
estadoMEF estadoActual1 = estado_inicial;
;

typedef enum
{
  estado1,
  estado2
} estadoMEF_2;
estadoMEF_2 estadoActual2 = estado1;

typedef enum
{
  PULSADOR_ARRIBA,
  PULSADOR_ABAJO,
  PULSADOR_PRESIONADO,
  PULSADOR_LIBERADO
} estadoMEF_3;
estadoMEF_3 mi_pulsador1 = PULSADOR_ARRIBA;

void ordenar_bits(unsigned char valor)
{
  unsigned char x = 0;
  x = valor;
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1); // Invierto posicion de bits
  x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2); // Invierto posicion de bits
  x = ((x & 0x0F) << 4) | ((x & 0xF0) >> 4); // Invierto posicion de bits
  PORTD = (x & 0x0f) << 4;                   // Enmascaro y corro 4 bits a izq. y escribo en PORTD
  PORTB = (x & 0xf0) >> 4;                   // Enmascaro y corro 4 bits a der. y escribo en PORTB
}

void config_TIMER0(void)
{
  TCCR0A = (1 << WGM01);              //Activa el bit CTC (clear timer on compare match)
                                      //del TCCR0A (timer counter/control register)
  OCR0A = 155;                        //valor de comparacion de int cada 10ms
  TCCR0B = (1 << CS00) | (1 << CS02); //preescaler dividiendo 1024
  TIMSK0 = (1 << OCIE0A);             //Habilita las interrupciones en timer compare
}

void swept(void)
{
  switch (estadoActual1)
  {
  case estado_inicial:
  {
    if (multiplicador == 0)
    {
      estadoActual1 = led1;
      multiplicador = 25;
    }
  }
  break;

  case led1:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD7);
      estadoActual1 = led2;
      multiplicador = 25;
    }
  }
  break;
  case led2:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD6);
      estadoActual1 = led3;
      multiplicador = 25;
    }
  }
  break;
  case led3:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD5);
      estadoActual1 = led4;
      multiplicador = 25;
    }
  }
  break;
  case led4:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD4);
      estadoActual1 = led5;
      multiplicador = 25;
    }
  }
  break;
  case led5:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB3);
      estadoActual1 = led6;
      multiplicador = 25;
    }
  }
  break;
  case led6:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB2);
      estadoActual1 = led7;
      multiplicador = 25;
    }
  }
  break;
  case led7:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB1);
      estadoActual1 = led8;
      multiplicador = 25;
    }
  }
  break;
  case led8:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB0);
      estadoActual1 = led9;
      multiplicador = 25;
    }
  }
  break;
  case led9:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB1);
      estadoActual1 = led10;
      multiplicador = 25;
    }
  }
  break;
  case led10:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB2);
      estadoActual1 = led11;
      multiplicador = 25;
    }
  }
  break;
  case led11:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PB3);
      estadoActual1 = Led12;
      multiplicador = 25;
    }
  }
  break;
  case Led12:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD4);
      estadoActual1 = led13;
      multiplicador = 25;
    }
  }
  break;
  case led13:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD5);
      estadoActual1 = led14;
      multiplicador = 25;
    }
  }
  case led14:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD6);
      estadoActual1 = led15;
      multiplicador = 25;
    }
  }
  case led15:
  {
    if (multiplicador == 0)
    {
      ordenar_bits(1 << PD7);
      estadoActual1 = estado_inicial;
      multiplicador = 25;
    }
  }
  break;
  }
}

void secuencia1(void)
{
  switch (estadoActual2)
  {
  case estado1:
  {
    if (multiplicador == 0)
    {
      estadoActual2 = estado2;
      multiplicador = 25;
      ordenar_bits(0b11001100);
    }
  }
  break;
  case estado2:
  {
    if (multiplicador == 0)
    {
      estadoActual2 = estado1;
      multiplicador = 25;
      ordenar_bits(0b00110011);
    }
  }
  break;
  }
}

void secuencia2(void)
{
  switch (estadoActual2)
  {
  case estado1:
  {
    if (multiplicador == 0)
    {
      estadoActual2 = estado2;
      multiplicador = 25;
      ordenar_bits(0b10101010);
    }
  }
  break;
  case estado2:
  {
    if (multiplicador == 0)
    {
      estadoActual2 = estado1;
      multiplicador = 25;
      ordenar_bits(0b01010101);
    }
  }
  break;
  }
}

void antirrebote(void)
{
  switch (mi_pulsador1)
  {
  case PULSADOR_ARRIBA:

    if bit_is_clear (PINC, PC0)
    {
      mi_pulsador1 = PULSADOR_PRESIONADO;
      multiplicador = 50;
    }

    break;

  case PULSADOR_PRESIONADO:

    if (multiplicador == 0)
      mi_pulsador1 = PULSADOR_ABAJO;
    break;

  case PULSADOR_ABAJO:

    if (bit_is_clear(PINC, PC0))
    {
      mi_pulsador1 = PULSADOR_LIBERADO;
      multiplicador = 50;
      ctp++;
      if (ctp > 2)
      {
        ctp = 0;
      }
    }
    else if (bit_is_set(PINC, PC0))
    {
      mi_pulsador1 = PULSADOR_ARRIBA;
      ordenar_bits(0b00000000);
    }
    break;

  case PULSADOR_LIBERADO:
    mi_pulsador1 = PULSADOR_ARRIBA;
    break;

  default:
    break;
  }
}

int main(void)
{
  DDRD = (1 << DD7) | (1 << DD6) | (1 << DD5) | (1 << DD4);     // Configuro el PORTD como salida (4,5,6,7)
  DDRB = (1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0); // Configuro el PORTB como salida (0, 1, 2, 3)

  DDRC = DDRC & (~(1 << PC0));
  DDRC = DDRC & (~(1 << PC1));
  DDRC = DDRC & (~(1 << PC2));
  DDRC = DDRC & (~(1 << PC3));

  config_TIMER0();
  sei(); //Habilita interrupciones globales

  while (1)
  {
    antirrebote();
    if (ctp == 0)
    {
      swept();
    }
    if (ctp == 1)
    {
      secuencia1();
    }
    if (ctp == 2)
    {
      secuencia2();
    }
  }
  return 0;
}

ISR(TIMER0_COMPA_vect)
{
  if (multiplicador > 0)
  {
    multiplicador--; //si multiplicador es mayor a 0, se le va ir restando al multiplicador hasta que llegue a 0
  }
}