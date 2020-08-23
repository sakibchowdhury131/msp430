///TAR - 16BIT
TAR, increments or decrements (depending on mode of operation) with
each rising edge of the clock signal.TAR can be read or written with software.
Additionally, the timer can
generate an interrupt when it overflows.

TAR may be cleared by setting the TACLR bit.
Setting TACLR also clears the clock divider and count
direction for up/down mode.



NOTE: When the timer clock is asynchronous to the CPU clock, any read from TAR should occur
while the timer is not operating or the results may be unpredictable.

///Clock Source Select and Divider
The timer clock can be sourced from ACLK, SMCLK, or externally via TACLK or INCLK. The clock source
is selected with the TASSELx bits.

The selected clock source may be passed directly to the timer or
divided by 2, 4, or 8, using the IDx bits

NOTE: The timer clock divider is reset when TACLR is set.

///Starting the Timer
The timer counts when MCx > 0 and the clock source is active.
When the timer mode is either up or up/down, the timer may be stopped by writing 0 to TACCR0.

The
timer may then be restarted by writing a nonzero value to TACCR0.
In this scenario, the timer starts
incrementing in the up direction from zero.


///Timer Mode Control

MCx 		Mode 		Description
00 		Stop 		The timer is halted.
01 		Up 		The timer repeatedly counts from zero to the value of TACCR0.
10 		Continuous 	The timer repeatedly counts from zero to 0FFFFh.
11 		Up/down 	The timer repeatedly counts from zero up to the value of TACCR0 and back down to zero.

///Up Mode
The up mode is used if the timer period must be different from 0FFFFh counts.
The timer repeatedly
counts up to the value of compare register TACCR0,
The TACCR0 CCIFG interrupt flag is set when the timer counts to the TACCR0 value.


///Changing the Period Register TACCR0
When changing TACCR0 while the timer is running, if the new period is greater than or equal to the old
period, or greater than the current count value, the timer counts up to the new period. If the new period is
less than the current count value, the timer rolls to zero. However, one additional count may occur before
the counter rolls to zero.


///Continuous Mode
In the continuous mode, the timer repeatedly counts up to 0FFFFh and restarts from zero. The capture/compare register TACCR0 works the same way as the other capture/compare
registers.

NOTE: The TAIFG interrupt flag is set when the timer counts from 0FFFFh to zero.

///Up/Down Mode
The up/down mode is used if the timer period must be different from 0FFFFh counts, and if a symmetrical
pulse generation is needed. The timer repeatedly counts up to the value of compare register TACCR0 and
back down to zero, as shown in Figure 12-7. The period is twice the value in TACCR0.

The count direction is latched. This allows the timer to be stopped and then restarted in the same direction
it was counting before it was stopped. If this is not desired, the TACLR bit must be set to clear the
direction. The TACLR bit also clears the TAR value and the timer clock divider.

the TACCR0 CCIFG interrupt flag and the TAIFG interrupt flag are set only once during
a period, separated by 1/2 the timer period. The TACCR0 CCIFG interrupt flag is set when the timer
counts from TACCR0 – 1 to TACCR0, and TAIFG is set when the timer completes counting down from
0001h to 0000h.

/// Capture/Compare Blocks

Two or three identical capture/compare blocks, TACCRx, are present in Timer_A. Any of the blocks may
be used to capture the timer data, or to generate time intervals.


The capture mode is selected when CAP = 1.Capture mode is used to record time events. The capture inputs CCIxA and CCIxB are connected to
external pins or internal signals and are selected with the CCISx bits.The CMx bits select the capture
edge of the input signal as rising, falling, or both.

If a capture occurs:
• The timer value is copied into the TACCRx register
• The interrupt flag CCIFG is set

The input signal level can be read at any time via the CCI bit.

NOTE: The capture signal can be asynchronous to the timer clock and cause a race condition. Setting the SCS
bit will synchronize the capture with the next timer clock. Setting the SCS bit to synchronize the capture
signal with the timer clock is recommended
Overflow logic is provided in each capture/compare register to indicate if a second capture was performed
before the value from the first capture was read. Bit COV is set when this occurs. COV must be reset with software.



///Capture Initiated by Software
The CMx bits can be set for capture on both edges. Software then
sets CCIS1 = 1 and toggles bit CCIS0 to switch the capture signal between VCC and GND


///Compare Mode
The compare mode is selected when CAP = 0.The compare mode is used to generate PWM output
signals or interrupts at specific time intervals.When TAR counts to the value in a TACCRx:
•Interrupt flag CCIFG is set
•Internal signal EQUx = 1
•EQUx affects the output according to the output mode
•The input signal CCI is latched into SCCI

///Timer_A Interrupts
Two interrupt vectors are associated with the 16-bit Timer_A module:
• TACCR0 interrupt vector for TACCR0 CCIFG
• TAIV interrupt vector for all other CCIFG flags and TAIFG


In capture mode any CCIFG flag is set when a timer value is captured in the associated TACCRx register.
In compare mode, any CCIFG flag is set if TAR counts to the associated TACCRx value.
All CCIFG flags request an interrupt when their corresponding CCIE bit
and the GIE bit are set.

