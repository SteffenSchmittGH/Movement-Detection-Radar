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
#include "math.h"
void compute_magnitudes(int32 * fft_array, float* magnitudes, int samples);
void init_fifo_buffer(int32 * fft_signal);
void cfar_get_threshold(float *output,int32* fft_signal);
/* [] END OF FILE */
