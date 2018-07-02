//////////////////////TRANSMISSOR

#include <main.h>

void main()
{
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_tris_b(0b11111110);
   while(TRUE)
   {
      set_adc_channel(0);
      delay_us(100);
      printf("%lu ",read_adc());
      set_adc_channel(1);
      delay_us(100);
      printf("%lu\n\r",read_adc());
      output_b(0b00100000);
      delay_us(100);
      output_b(0b00000000);
   }

}
