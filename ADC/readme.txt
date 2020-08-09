ADC_operation
//stores result in ADC10MEM register
//2 programmable voltage levels Vr+ and Vr- to define the upper and lower limit of conversion
//The ADC10 core is configured by two control registers, ADC10CTL0 and ADC10CTL1.
//The core is enabled with the ADC10ON bit.
//the ADC10 control bits can only be modified when ENC = 0. ENC must be set to 1 before any conversion can take place.
//The ADC10 source clock is selected using the ADC10SSELx bits and can be divided from 1 to 8 using the ADC10DIVx bits.
//Parasitic current: 
The ADC10 external inputs Ax, VeREF+,and VREF- share terminals with general purpose I/O ports, which are
digital CMOS gates (see the device-specific data sheet). When analog signals are applied to digital CMOS
gates, parasitic current can flow from VCC to GND. This parasitic current occurs if the input voltage is
near the transition level of the gate. Disabling the port pin buffer eliminates the parasitic current flow and
therefore reduces overall current consumption. The ADC10AEx bits provide the ability to disable the port
pin input and output buffers.

//Auto Power-Down
The ADC10 is designed for low power applications. When the ADC10 is not actively converting, the core is
automatically disabled and is automatically re-enabled when needed. The ADC10OSC is also
automatically enabled when needed and disabled when not needed. When the core or oscillator is
disabled, it consumes no current.

//The ADC10 has four operating modes selected by the CONSEQx bits
Table 22-1. Conversion Mode Summary
CONSEQx 	Mode 					Operation
00 		Single channel single-conversion 	A single channel is converted once.
01 		Sequence-of-channels 			A sequence of channels is converted once.
10 		Repeat single channel 			A single channel is converted repeatedly.
11 		Repeat sequence-of-channels 		A sequence of channels is converted repeatedly.

//When MSC = 1 and CONSEQx > 0, the first rising edge
of the SHI signal triggers the first conversion. Successive conversions are triggered automatically as soon
as the prior conversion is completed.

//Stopping Conversions
1. Resetting ENC in single-channel single-conversion mode stops a conversion immediately and the
results are unpredictable. For correct results, poll the ADC10BUSY bit until reset before clearing ENC.
2. Resetting ENC during repeat-single-channel operation stops the converter at the end of the current
conversion.
3. Resetting ENC during a sequence or repeat sequence mode stops the converter at the end of the
sequence.
4. Any conversion mode may be stopped immediately by setting the CONSEQx = 0 and resetting the
ENC bit. Conversion data is unreliable.


//ADC10 Data Transfer Controller
The DTC is enabled by setting the ADC10DTC1 register
to a nonzero value.
A DTC transfer must not be initiated while the ADC10 is busy.

