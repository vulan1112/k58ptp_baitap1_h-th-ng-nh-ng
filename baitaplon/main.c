#include <16F877A.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP      
#device ADC=10
#use delay(clock=20M)
#use I2C(MASTER, I2C1, SLOW = 100000, STREAM = DS1307_STREAM)
#include <DS1307.c>  
#define DATA_PIN_CHOT   PIN_C0
#define CLOCK_PIN_CHOT  PIN_C1 
#define LATCH_PIN_CHOT  PIN_C2
#define LED_COUNT  8 
RTC_Time *mytime;
unsigned int8 maphim,k,vonglap_1,vonglap_2;
signed int16 C;
unsigned int16 Gio,Phut,Giay,Ngay,Thang,Nam;
unsigned int16 Hour, Minute, Second, Day, Month, Year, Year_2;
unsigned int16 Nam1, Nam2, Thang1, Thang2, Ngay1, Ngay2, Gio1, Gio2, Phut1, Phut2, Giay1, Giay2;
unsigned char data1=0x00,data2=0x00,maled[10] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};
const unsigned int8 phim[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
void CHOT(unsigned char data1, unsigned char data2) {
  for (k = 0; k < 8; k++) {
    output_bit(DATA_PIN_CHOT, (data1 >> (7 - k)) & 1);
    output_high(CLOCK_PIN_CHOT);
    output_low(CLOCK_PIN_CHOT);
  }
  for (k = 0; k < 8; k++) {
    output_bit(DATA_PIN_CHOT, (data2 >> (7 - k)) & 1);
    output_high(CLOCK_PIN_CHOT);
    output_low(CLOCK_PIN_CHOT);
  }
  output_high(LATCH_PIN_CHOT);
  output_low(LATCH_PIN_CHOT);
}

unsigned int8 quet_phim()
{
   unsigned int8 hang, mp=0xff;
   unsigned int8 maquet[4]={0xFE, 0xFD, 0xFB, 0xF7};
   for(hang=0; hang<=3; hang++)
   {
      output_D(maquet[hang]);
      while(input(pin_D4)==0) mp=hang*3+1;
      while(input(pin_D5)==0) mp=hang*3+2; 
      while(input(pin_D6)==0) mp=hang*3+3;
   }
   return mp;
}

void hienthi_main()
{
    output_B(maled[Gio/10%10]);
    data1=0x01;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Gio%10]);
    data1=0x02;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Phut/10%10]);
    data1=0x04;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Phut%10]);
    data1=0x08;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Giay/10%10]);
    data1=0x10;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Giay%10]);
    data1=0x20;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[(C/ 10) % 10]);
    data1=0x40;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[C%10]);
    data1=0x80;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1); 
    
    output_B(maled[2]);
    data2=0x01;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[0]);
    data2=0x02;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Nam/10%10]);
    data2=0x04;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Nam%10]);
    data2=0x08;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    
    output_B(maled[Thang/10%10]);
    data2=0x10;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Thang%10]);
    data2=0x20;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);

    output_B(maled[Ngay/10%10]);
    data2=0x40;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Ngay%10]);
    data2=0x80;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
}

void hienthi()
{
    output_B(maled[Gio1]);
    data1=0x01;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Gio2]);
    data1=0x02;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Phut1]);
    data1=0x04;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Phut2]);
    data1=0x08;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Giay1]);
    data1=0x10;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[Giay2]);
    data1=0x20;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[(C/ 10) % 10]);
    data1=0x40;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1);
    output_B(maled[C%10]);
    data1=0x80;
    CHOT(data2,data1);
    delay_ms(1);
    data1=0x00;
    CHOT(data2,data1); 
    
    output_B(maled[2]);
    data2=0x01;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[0]);
    data2=0x02;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Nam1]);
    data2=0x04;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Nam2]);
    data2=0x08;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    
    output_B(maled[Thang1]);
    data2=0x10;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Thang2]);
    data2=0x20;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);

    output_B(maled[Ngay1]);
    data2=0x40;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
    output_B(maled[Ngay2]);
    data2=0x80;
    CHOT(data2,data1);
    delay_ms(1);
    data2=0x00;
    CHOT(data2,data1);
}

void main() {
  set_tris_C(0x18);
  set_tris_B(0x00);
  set_tris_D(0xF0);
  OSC_Enable();
  SQWE_Set(OUT_1Hz);
  setup_adc(ADC_CLOCK_INTERNAL);      
  setup_adc_ports(AN0); 
  set_adc_channel(0);
  while (true) 
  {
    mytime = RTC_Get();
    Gio = mytime->hours;
    Phut = mytime->minutes;
    Giay = mytime->seconds;
    Ngay = mytime->day;
    Thang = mytime->month;
    Nam = mytime->year;
    C = abs((read_adc() * 4.8875) / 10.0);
    hienthi_main();
    maphim=quet_phim();
    if (maphim!=0xff)
    {
         if (maphim == 12)
         {
            Nam1 = 0, Nam2 = 0, Thang1 = 0, Thang2 = 1, Ngay1 = 0, Ngay2 = 1;
            Gio1 = 0, Gio2 = 0, Phut1 = 0, Phut2 = 0, Giay1 = 0, Giay2 = 0;
            vonglap_1=1;
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=1&&maphim<=10)
                  {
                     Nam1=phim[maphim-1];
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=1&&maphim<=10)
                  {
                     Nam2=phim[maphim-1];
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                     year = Nam1*10 + Nam2;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim==1||maphim==10)
                  {
                     Thang1=phim[maphim-1];
                     if (Thang1==1)
                     {
                        Thang2=0;
                     }
                     else Thang2=1; 
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  
                  if (Thang1==1)
                  {
                     if (maphim==1||maphim==2||maphim==10)
                     {
                        Thang2=phim[maphim-1];
                     }
                  }
                  if (Thang1==0)
                  {
                     if (maphim>=1&&maphim<=9)
                     {
                        Thang2=phim[maphim-1];
                     }
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                     Month=Thang1*10+Thang2;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (Month==2)
                  {
                     if (maphim==1||maphim==2||maphim==10)
                     {
                        Ngay1=phim[maphim-1];
                     }
                  }
                  else
                  {
                     if (maphim==1||maphim==2||maphim==3||maphim==10)
                     {
                        Ngay1=phim[maphim-1];
                     }
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            Year_2=Year+2000;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (Month==1||Month==3||Month==5||Month==7||Month==8||Month==10||Month==12)
                  {
                     if (Ngay1==3)
                     {
                        if (maphim==1||maphim==10) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                     if (Ngay1==1||Ngay1==2)
                     {
                        if (maphim>=1&&maphim<=10) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                     if (Ngay1==0)
                     {
                        if (maphim>=1&&maphim<=9) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                  }
                  if (Month==4||Month==6||Month==9||Month==11)
                  {
                     if (Ngay1==3) Ngay2=0;
                     if (Ngay1==1||Ngay1==2)
                     {
                        if (maphim>=1&&maphim<=10) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                     if (Ngay1==0)
                     {
                        if (maphim>=1&&maphim<=9) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                  }
                  if (Month==2)
                  {
                     if (Ngay1==0)
                     {
                        if (maphim>=1||maphim<=9) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                     if (Ngay1==1)
                     {
                        if (maphim>=1&&maphim<=10) 
                        {
                           Ngay2=phim[maphim-1];
                        }
                     }
                     if (Ngay1==2)
                     {
                        if ((Year_2)%100!=0&&(Year_2)%4==0)
                        {
                           if (maphim>=1&&maphim<=10) 
                           {
                              Ngay2=phim[maphim-1];
                           }
                        }
                        else
                        {
                           if (maphim>=1&&maphim<=8) 
                           {
                              Ngay2=phim[maphim-1];
                           }
                           if (maphim==10) 
                           {
                              Ngay2=phim[maphim-1];
                           }
                        }
                     }
                  }
               
                  if (maphim==12)
                  {
                     vonglap_2=0;
                     Day=Ngay1*10+Ngay2;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            //Hours
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim==1||maphim==2||maphim==10)
                  {
                     Gio1=phim[maphim-1];
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (Gio1==2)
                  {
                     if (maphim==1||maphim==2||maphim==3||maphim==10)
                     {
                        Gio2=phim[maphim-1];
                     }
                  }
                  else
                  {
                     if (maphim>=1&&maphim<=10)
                     {
                        Gio2=phim[maphim-1];
                     }
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                     Hour = Gio1*10+Gio2;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=0&&maphim<=5)
                  {
                     Phut1=phim[maphim-1];
                  }
                  
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=0&&maphim<=10)
                  {
                     Phut2=phim[maphim-1];
                  }
                  if (maphim==12)
                  {
                     vonglap_2=0;
                     Minute = Phut1*10+Phut2;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=0&&maphim<=5)
                  {
                     Giay1=phim[maphim-1];
                  }
                  
                  if (maphim==12)
                  {
                     vonglap_2=0;
                  }
                  if (maphim==11)
                  {
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
            vonglap_2=1;
            if (vonglap_1==1)
            {
               while (vonglap_2==1)
               {
                  hienthi();
                  maphim=quet_phim();
                  if (maphim>=0&&maphim<=10){
                     Giay2=phim[maphim-1];
                  }
                  if (maphim==12){
                     vonglap_2=0;
                     Second = Giay1*10+Giay2;
                     mytime->hours = Hour;
                     mytime->minutes = Minute;
                     mytime->seconds = Second;
                     mytime->year = Year;
                     mytime->month = Month;
                     mytime->day = Day;
                     RTC_Set(mytime);
                  }
                  if (maphim==11){
                     vonglap_2=0;
                     vonglap_1=0;
                  }
               }
            }
         }
     }
  }
}


