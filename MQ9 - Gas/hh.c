    /*******************************************************
    This program was created by the
    CodeWizardAVR V3.14 Advanced
    Automatic Program Generator
    © Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
    http://www.hpinfotech.com

    Project : 
    Version : 
    Date    : 5/20/2023
    Author  : 
    Company : 
    Comments: 


    Chip type               : ATmega32A
    Program type            : Application
    AVR Core Clock frequency: 8.000000 MHz
    Memory model            : Small
    External RAM size       : 0
    Data Stack size         : 512
    *******************************************************/

    #include <mega32a.h>
    #include <delay.h>
    #include <stdio.h>   
    #include <math.h>

    #define F_CPU 1000000UL


    #define USART_BAUDRATE 4800
    #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE*16UL)))-1)

    // Voltage Reference: AVCC pin
    #define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))   
    
    unsigned int _millis = 0;
    unsigned int millis(void){
    return _millis;    
    }  

    // Read the AD conversion result
    unsigned int read_adc(unsigned char adc_input){
        char adcHigh,adcLow;

        ADMUX=adc_input | ADC_VREF_TYPE;
            
        // Delay needed for the stabilization of the ADC input voltage
        delay_us(10);
            
        // Start the AD conversion
        ADCSRA|=(1<<ADSC);
            
        // Wait for the AD conversion to complete
        while (!(ADCSRA & (1<<ADIF)));
        ADCSRA|=(1<<ADIF);
            
        adcLow = ADCL;    
        adcHigh = ADCH;
            
        return (adcHigh << 8) + adcLow;
    }           
                                  
     
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
  //  PORTB.3 = 1; 
}

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
// Place your code here
  //  PORTB.3 = 0; 
}


// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
      _millis++;
}
 


    // Declare your global variables here


    void uart_transmit (char data){
        while( !(UCSRA & (1 << 5)) );
        UDR = data;
    }
    char uart_recieve (void) {
        while( !(UCSRA & (1 << 7)) );
        return UDR;
    }         
    
      
               
     void buzzer(){  
    int i = 0 ;
    for(i = 0;i < 300; i++)
    {     
                delay_us(50); 
                PORTD.4 = 1;   
                delay_us(50); 
                PORTC.0 = 0;   
               delay_us(50);   
                PORTD.4 = 0;  
                delay_us(50);
                  PORTC.0 = 1;  
    }
     }       
     
       
    float sensor_volt;           
    int t = 0;
    void main(void)
    {      
    
    unsigned int prevMillis = 0;
    unsigned int curMillis = 0;
    char ledState = 0;
    
    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: Off
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 1200
    UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
    UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
    UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
    UBRRL = BAUD_PRESCALE;
    UBRRH = (BAUD_PRESCALE>>8);    
    
   // Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 65.536 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;



// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

      // ADC initialization
        // ADC Clock frequency: 125.000 kHz
        // ADC Voltage Reference: AVCC pin
        // ADC Auto Trigger Source: Free Running
        ADMUX=ADC_VREF_TYPE;
        ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
        SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);  
        
        // Global enable interrupts
           #asm("sei")

    DDRC.5 = 1; 
    DDRB.0 = 1;
    DDRC.0 = 1;                              
    DDRC.1 = 1;           
    DDRD.6 = 0; 
    DDRD.5 = 0;  
    
     DDRB.3 = 1; 
       
      
    while (1)
          {  
      
          
           
                
          //calibre sensor.............................
          
//  float sensor_volt;  
//  float RS_air; //  Rs in clean air 
//  float R0;  // R0 in 1000 ppm LPG 
//  float sensorValue; 
// 
////Average  
//    int i; 
//    for( i = 0 ; i < 100 ; i++) 
//  { 
//    sensorValue = sensorValue + read_adc(0); 
//  } 
//  sensorValue = sensorValue/100.0; 
////-----------------------------------------------/ 
// 
//  sensor_volt = (sensorValue/1024)*5.0; 
//  RS_air = (5.0-sensor_volt)/sensor_volt; // Depend on RL on yor module 
//  R0 = RS_air/9.9; // According to MQ9 datasheet table 
//   
//
//    printf("sensor_volt = %f V \n\r",sensor_volt);
//  
//   
//    printf("R0 = %f \n\r",R0);
//    
//    delay_ms(1000); 
//////////////////////////////////////////////////////////////////////////////

             //Calculate volt,resistense,.........................
                        
              float sensor_volt; 
              float RS_gas; 
              float ratio; 
             //-Replace the name "R0" with the value of R0 in the demo of First Test -/ 
              float R0 = 0.75; 
             
              int sensorValue = read_adc(0); 
              sensor_volt = ((float)sensorValue / 1024) * 5.0; 
              RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module 
             
             
              ratio = RS_gas / R0; // ratio = RS/R0        
             //------------------------------------------------------------/   
            
             
             // PORTB.3 = 1;  
             // PORTC.1 = 1;    
    
            // printf(" %d   ",t++);  
            // printf(" %f  ",sensor_volt);     
            // printf("%f   ",ratio);    
            // printf("%f ",RS_gas);  
            // printf("\n\r");
                      
           
            
             
           float sensor_volt; 
           curMillis = millis();
          // printf("%d  \n\r",curMillis - prevMillis);   
         
           
           
       if(curMillis - prevMillis < 115){   
       //  OCR0=0xFF; 
          if(curMillis - prevMillis > 105 && curMillis - prevMillis < 115)
          { 
            int sensorValue = read_adc(0);
            sensor_volt = ((float)sensorValue / 1024) *  5.0; 
            sensor_volt = 1024 / sensor_volt;
            sensor_volt = 100 / sensor_volt; 
            printf(" %f PPM",sensor_volt); 
          }   
         
        PORTC.1 = 1;    
        }  
        
         else if(curMillis - prevMillis > 115 && curMillis - prevMillis < 287){
        // printf("co \n\r");         
         OCR0=0x49;
          if(curMillis - prevMillis > 272 && curMillis - prevMillis < 287)
          { 
            int sensorValue = read_adc(0);
            sensor_volt = ((float)sensorValue / 1024) * 1.4;  
             sensor_volt = 1024 / sensor_volt;
            sensor_volt = 100 / sensor_volt; 
            printf(" %f PPM",sensor_volt);
                
          }
             PORTC.1 = 0;        
               
        } 
     
         else if(curMillis - prevMillis > 287){
         prevMillis = curMillis;
        } 
       
         
           
           
          //Button  
          
                PORTD.6 = 1;
                 if(PIND.6 == 0)
             {        
              printf("Stop \n\r"); 
                 
             delay_ms(18000); 
             } 
              
                      
                    //Buzzer
                 if(PIND.5 == 0)
             {                     
             //  printf("gos ON \n\r");  
                  
               PORTB.0 = 1;
                 buzzer();
                  PORTB.0 = 0;  
              
             }   else{
             //  printf("Empty gas\n\r");  
                     PORTD.4 = 0;     
                  PORTC.0 = 0; 
             }
                  
             
          
             
             delay_ms(100);   
                
        //ADC Data 
           if(sensor_volt > 0.34 && ratio <20 && RS_gas < 15 )
             {       
           //  printf("gos ON \n\r");  
                  
              PORTC.1 = 1;
                buzzer();
                 PORTC.1 = 0;  
                 
           
             } else{  
        
                  PORTD.7 = 0;     
                  PORTC.0 = 0;  
                  
             }                             
             
             
       
            
             
          } 
          
    
      
                
              }
          