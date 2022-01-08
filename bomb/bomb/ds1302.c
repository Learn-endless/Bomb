#define _CRT_SECURE_NO_WARNINGS 1
/*ds1302.c*/
#include "reg52.h"
#include "i2c.h"
#include "absacc.h"

sfr AUXR = 0X8E;
unsigned char code tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff };
unsigned char dspbuf[8] = { 10,10,10,10,10,10,10,10 };
unsigned char dspcom = 0;
unsigned char intr;
bit adc_flag;
void display();
void cls_buzz(void)
{
    P2 = ((P2 & 0X1F) | 0XA0);
    P0 = 0X00;
    P2 &= 0X1F;
}
void cls_led(void)
{
    P2 = ((P2 & 0X1F) | 0X80);
    P0 = 0XFF;
    P2 &= 0X1F;
}


void main(void)
{
    unsigned char adc_value;
    cls_buzz();
    cls_led();
    P1 &= 0x7f;
    AUXR |= 0X80;
    TMOD &= 0XF0;
    TL0 = 0XCD;
    TH0 = 0XD4;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    init_pcf8591();
    while (1)
    {
        if (adc_flag)
        {
            adc_flag = 0;
            adc_value = adc_pcf8591();
            (adc_value >= 100) ? (dspbuf[5] = adc_value / 100) : (dspbuf[5] = 10);
            (adc_value >= 10) ? (dspbuf[6] = adc_value % 100 / 10) : (dspbuf[6] = 10);
            dspbuf[7] = adc_value % 10;
        }
    }

}

void isr_timer_0(void) interrupt 1
{
    if (++intr == 50)
    {
        intr = 0;
        adc_flag = 1;
    }
    display();
}



void display(void)
{
    P2 = ((P2 & 0X1F) | 0XE0);
    P0 = 0XFF;
    P2 &= 0X1F;


    P0 = 1 << dspcom;
    P2 = ((P2 & 0X1F) | 0XC0);
    P2 &= 0X1F;


    P0 = tab[dspbuf[dspcom]];
    P2 = ((P2 & 0X1F) | 0XE0);
    P2 = 0X1F;


    if (++dspcom == 8)
    {
        dspcom = 0;
    }
}