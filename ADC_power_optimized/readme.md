# Coding Stuffs


# Analog Port Selection: 
Register Name: ADC10AE0 8 bit register. each bit configures port 1.0 to 1.7 as analog input respectively.

# Voltage Reference Generator:
The ADC10 module contains a built-in voltage reference with two selectable voltage levels.Setting REFON = 1 in ADC10CTL0 register enables the internal reference.
When REF2_5V = 1 in ADC10CTL0 register, the internal reference is 2.5 V. REF2_5V = 0 will result in internal reference voltage to be 1.5V.
REFOUT = 0 in ADC10CTL0 register will select internal reference voltage. If any device provides Vref pin, then external reference voltage can be used by
setting REFOUT. External references may be supplied for VR+ and VR- through pins A4 and A3 respectively. 
When When REFBURST = 1 the increased current consumption is limited to the sample and
conversion period. 

# Internal Reference Low-Power Features
The ADC10 internal reference generator is designed for low power applications. When REFON = 1, but no conversion is active, the buffer is automatically disabled and automatically reenabled
when needed. When the buffer is disabled, it consumes no current. In this case, the bandgap
voltage source remains enabled.When REFOUT = 1, the REFBURST bit controls the operation of the internal reference buffer. When
REFBURST = 0, the buffer is on continuously, allowing the reference voltage to be present outside the
device continuously. When REFBURST = 1, the buffer is automatically disabled when the ADC10 is not
actively converting and is automatically re-enabled when needed.


# Auto Power-Down
The ADC10 is designed for low power applications. When the ADC10 is not actively converting, the core is
automatically disabled and is automatically re-enabled when needed. The ADC10OSC is also
automatically enabled when needed and disabled when not needed. When the core or oscillator is
disabled, it consumes no current.

# Sample and Conversion Timing
Source signal for sample and convertion is selected by manipulating SHS_x bit in ADC10CTL1 register.
The SHTx bits in ADC10CTL1 register select the sample
period tsample to be 4, 8, 16, or 64 ADC10CLK cycles.
The sampling timer sets SAMPCON high for the
selected sample period after synchronization with ADC10CLK.The
high-to-low SAMPCON transition starts the analog-to-digital conversion, which requires 13 ADC10CLK
cycles.

# Conversion Modes:
The ADC10 has four operating modes selected by the CONSEQx bits
Table 22-1. Conversion Mode Summary
```sh
    CONSEQx 	Mode 					      Operation
    00 		Single channel single-conversion 	A single channel is converted once.
    01 		Sequence-of-channels 			A sequence of channels is converted once.
    10 		Repeat single channel 			A single channel is converted repeatedly.
    11 		Repeat sequence-of-channels 		A sequence of channels is converted repeatedly.
```
 #	Single-Channel Single-Conversion Mode
A single channel selected by INCHx is sampled and converted once. The ADC result is written to
ADC10MEM Register.


# Stopping Conversions
The recommended ways to stop an active
conversion or conversion sequence are:
1.	Resetting ENC in single-channel single-conversion mode stops a conversion immediately and the
	results are unpredictable. For correct results, poll the ADC10BUSY bit until reset before clearing ENC.
2.	Any conversion mode may be stopped immediately by setting the CONSEQx = 0 and resetting the
	ENC bit. Conversion data is unreliable.

# ADC10 Data Transfer Controller
The ADC10 includes a data transfer controller (DTC) to automatically transfer conversion results from
ADC10MEM to other on-chip memory locations.
The DTC is enabled by setting the ADC10DTC1 register to a nonzero value.
A DTC transfer must not be initiated while the ADC10 is busy.


# ADC10 Interrupts
When the DTC is not used (ADC10DTC1 = 0), ADC10IFG is set when conversion results are loaded into
ADC10MEM.When DTC is used (ADC10DTC1 > 0), ADC10IFG is set when a block transfer completes and the internal transfer counter n = 0.
If both the ADC10IE and the GIE bits are set, then the ADC10IFG
flag generates an interrupt request.The ADC10IFG flag is automatically reset when the interrupt request
is serviced, or it may be reset by software.
