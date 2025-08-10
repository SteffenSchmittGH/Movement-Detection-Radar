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
#include "cfar.h"
/*CA CFAR Parameter*/
#define BUFFERSIZE 15
#define SAMPLESIZE 512
float N = 512;
float NG = 1;
float NR = 10;
float PFA = 0;
float alpha = 0;
float summe = 0;
float fifo[BUFFERSIZE] = { };
float threshhold[SAMPLESIZE] = { };


void compute_magnitudes(int32 * fft_array, float* magnitudes, int samples) {
    for (int i = 0; i < samples; i++) {
        int32_t real = fft_array[2 * i];         // Real part
        int32_t imag = fft_array[2 * i + 1];     // Imaginary part
        magnitudes[i] = sqrt((float)(real * real + imag * imag));
    }
    return;
}

void init_fifo_buffer(int32 * fft_signal){
    for(int i = 0; i < BUFFERSIZE; i++){
           fifo[i] = (float)fft_signal[i];
    }
    return;   
}

void cfar_get_threshold(float *output, int32* fft_signal){
    PFA = pow(10, -6);
    alpha = N * (pow(PFA, -1.0 / N) - 1);
    for (int i = BUFFERSIZE; i < SAMPLESIZE; i++) {
        summe = 0;
        for (int j = 0; j < BUFFERSIZE; j++) {
            if (j == 7) {
                summe += 0;
            } else {
                summe += fifo[j];
            }
        }
        threshhold[i - 8] = alpha * summe / BUFFERSIZE;

        // Shift fifo buffer
        for (int j = 0; j < BUFFERSIZE - 1; j++) {
            fifo[j] = fifo[j + 1];
        }
        // Last FIFO Element
        fifo[BUFFERSIZE - 1] = (float)fft_signal[i];
    }
    for(int i = 0; i < SAMPLESIZE ; i++){
        output[i] = threshhold[i];   
    }
    return;
}
/* [] END OF FILE */
