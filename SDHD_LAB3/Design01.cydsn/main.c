/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "fft_application.h"
#include "cfar.h"
//Define Samples and FFT Array
#define SAMPLES 1024
int samplesABS = 1024;
//INTERRUPT PROTOTYPES
CY_ISR_PROTO(Pin_SW_Handler); /* Catch the Button Press via rising edge */
CY_ISR_PROTO(uart_interrupt);/*enables us to not miss any data during signal processing */
//GLOBAL VARIABLES
uint16_t state = 0; /*state variable to switch between states. state is in between [0,2]*/
uint8_t ch; /*variable to receive 's' or 'o' from Matlab*/
uint8_t sReceived = 0; /*Global flag to detect if an s was received*/
uint8_t oReceived = 0; /*Global flag to detect if an o was received*/
//INTERRUPT DEFINITION
CY_ISR(Pin_SW_Handler) /*switch state in switch case to sampling state*/
{
/* ISR Code here */
    state = 1;
    Pin_SW_ClearInterrupt();
}
CY_ISR(uart_interrupt)/*wait either for an s or o*/
{
/* ISR Code here */
    ch = UART_1_GetChar();
    if(ch == 's'){
        sReceived = 1;
    }
    if(ch == 'o'){
        oReceived = 1;
    }
}
//MAIN
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_button_StartEx(Pin_SW_Handler); /*start ISR Switch*/
    uart_interrupt_StartEx(uart_interrupt); /*start ISR UART*/
    WaveDAC8_1_Start(); /*Start Signal Generator*/
    ADC_Start(); /*Start ADC for Sampling*/
    UART_1_Start() ; /* Start UART for communication with Matlab */
    //CFAR Output
    float cfar_threshold[SAMPLES] = { };
    // definition of variables needed for the state machine
    int32 fft_array[2*SAMPLES] = { };
    int32 fft_array_abs[2*SAMPLES] = { };
    float fft_float[2*SAMPLES] = { };
    uint16_t samples[SAMPLES] = { }; /*Array with 1024 fields as a store for samples in one sample period */
    uint8_t sendSample_upper = 0; /*due to uint8 uart: store for upper bits*/
    uint8_t sendSample_lower = 0; /* due to uint8 uart: and store for lower bits */
    uint32_t count = 0; /*Variable to count the Matlab cycles*/
    /*Clear the LEDs*/
    LED_RED_Write(0);
    LED_YELLOW_Write(0);
    LED_Green_Write(0);
    for(;;)
    {
        /* Place your application code here. */
        switch(state)
        {
            case 0: count = 0; sReceived = 0; oReceived = 0; LED_RED_Write(1); LED_YELLOW_Write(0); LED_Green_Write(0);break; /*default values to start statemachine over and over*/
            case 1:
                    /*As long as no 's' received, sample the datas from PIN P15[4] (while). 
                      For loop ensures one whole sample period.
                      ADC_IsEndConversion, ensures to not grep values twice.
                      As a last step, change state to UART Transmit and reset the sReceived flag.*/
                    LED_RED_Write(0);
                    LED_YELLOW_Write(1);
                    LED_Green_Write(0);
                    ADC_StartConvert();  
                    do{
                        for(int i = 0; i < SAMPLES; i++){ 
                            while(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT) == 0){
                                //CY_NOP;
                            }
                            samples[i] = ADC_GetResult16();
                        }
                    }while(sReceived == 0);
                    /* FFT Calculation */
                    fft_app(samples, fft_array, SAMPLES);
                    compute_magnitudes(fft_array, fft_float, samplesABS); 
                    for(int i = 0; i < 1024; i++){
                        fft_array_abs[i] = (int32)fft_float[i];   
                    }
                    init_fifo_buffer(fft_array_abs);
                    cfar_get_threshold(cfar_threshold,fft_array_abs);
                    state = 2;
                    sReceived = 0;
                    break;
            case 2:
                    /*This part of the code sends the Sampled data to Matlab in the requested way.
                      The calculation samples[j]&0xFF ensures to send the lower 8 bit of the sampled uint16 samples[] array.
                      The calculation (samples[j] >> 8)&0xFF ensures to sample the upper 8 bit by shifting them into the range of the lower bits.
                      After wards wait for an 'o', reset global flag and change state.
                      if count == 10, switch to state 0.*/
                    LED_RED_Write(0);
                    LED_YELLOW_Write(0);
                    LED_Green_Write(1);
                    /* Send FFT Output to Matlab */
                    count++;
                    ADC_StopConvert();
                    for(int j = 0; j < 1024; j++){
                        /*UART*/
                        sendSample_lower = samples[j]&0xFF;
                        //sendSample_lower = ((uint16)cfar_threshold[j])&0xFF;
                        //sendSample_lower = (fft_array_shifted[j])&0xFF;
                        UART_1_PutChar(sendSample_lower);
                        sendSample_upper = (samples[j] >> 8)&0xFF;
                        //sendSample_upper = (((uint16)cfar_threshold) >> 8)&0xFF;
                        //sendSample_upper = (fft_array_shifted[j] >> 8)&0xFF;
                        UART_1_PutChar(sendSample_upper); 
                        /*CFAR FFT COMPARE*/
                        /*if(fft_array_abs[j] > cfar_threshold[j]){
                            LED_RED_Write(1);
                            LED_YELLOW_Write(0);
                            LED_Green_Write(0);
                        }else{
                            LED_RED_Write(0);
                            LED_YELLOW_Write(0);
                            LED_Green_Write(0);
                        }*/
                    }
            
                    while(oReceived != 1){ }
                    state = 1;
                    oReceived = 0;
                    if(count >= 10){
                        state = 0;
                    }
                    break;
            default: break;
        }

    }
}

/* [] END OF FILE */
