# Movement Detection with Radar Sensor
The project covers the following steps:

**Layout**

Complete schematic entry and footprints to start the layout process.
Submit the PCB layout and BOM and generate Gerber files.

**Software (State Machine, ADC, UART)** 

Write software code, assemble PCBs, and implement DFT.

**CFAR Algorithm & Start-Up**

Integrate the 24GHz radar sensor and finalize the software.

## PCB-Shematics
The following circuite is a Bandpass filter, which filters the wanted spectrum of the Radar Sensor, in order to detect movements.
![grafik](https://github.com/user-attachments/assets/d544a0fe-73ed-41a5-81a3-57d22a4c1be4)
**Layout:**
![grafik](https://github.com/user-attachments/assets/7432feee-305d-4e23-b275-334c19a5c968)
## Statemachine
![statemachine](https://github.com/user-attachments/assets/9dd233ec-b977-4545-8b8f-a49faaf0384d)

**IDLE State:**  

The system initializes with count = 0 and waits for a push button press to start sampling.  

**Sampling State:**  

The system collects 1024 x 16-bit samples (ADC to Array). If no "s" signal is received, it remains in this state.  

**UART Transfer State:**  

Once sampling is complete and "s" is received, data is transferred via UART, and count increments.  

