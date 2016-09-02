# BLDC-Motor-Driver
This repository includes the code and schematics of my brushless DC motor controller. The controller **converts DC power into 3-phase AC power** to drive a brushless motor. Secondary features include **task prioritization**, **UART communication**, and **active temperature monitoring**. Some of my work includes:

- Reduced latency of key processes by implementing a multi-level queue scheduling algorithm
- Integrated an interrupt-driven control loop which leverages back-EMF detection to drive motor
- Synchronized UART hardware to device software using FIFO buffers, minimizing busy-wait delays  
- Designed controller’s circuitry, applying components including FETs, BJTs, op-amps, and thermistors
- Designed and implemented a two-stage temperature monitoring system which uses thermistors to actively monitor MOSFET temperatures, and triggers a hardware interrupt when a critical temperature is reached 
