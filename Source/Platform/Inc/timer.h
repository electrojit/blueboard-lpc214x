#ifndef _TIMER_H
#define _TIMER_H

#include "lpc_2148.h"
#include "hardware.h"

// Timer Interrupt Register Bit Definitions
#define TIR_MR0I    (1 << 0)            // Interrupt flag for match channel 0
#define TIR_MR1I    (1 << 1)            // Interrupt flag for match channel 1
#define TIR_MR2I    (1 << 2)            // Interrupt flag for match channel 2
#define TIR_MR3I    (1 << 3)            // Interrupt flag for match channel 3
#define TIR_CR0I    (1 << 4)            // Interrupt flag for capture channel 0 event
#define TIR_CR1I    (1 << 5)            // Interrupt flag for capture channel 1 event
#define TIR_CR2I    (1 << 6)            // Interrupt flag for capture channel 2 event
#define TIR_CR3I    (1 << 7)            // Interrupt flag for capture channel 3 event

// PWM Interrupt Register Bit Definitions
#define PWMIR_MR0I  (1 << 0)            // Interrupt flag for match channel 0
#define PWMIR_MR1I  (1 << 1)            // Interrupt flag for match channel 1
#define PWMIR_MR2I  (1 << 2)            // Interrupt flag for match channel 2
#define PWMIR_MR3I  (1 << 3)            // Interrupt flag for match channel 3
#define PWMIR_MR4I  (1 << 8)            // Interrupt flag for match channel 4
#define PWMIR_MR5I  (1 << 9)            // Interrupt flag for match channel 5
#define PWMIR_MR6I  (1 << 10)           // Interrupt flag for match channel 6
#define PWMIR_MASK  (0x070F)

// Timer Control Register Bit Definitions
#define TCR_ENABLE  (1 << 0)
#define TCR_RESET   (1 << 1)

// PWM Control Register Bit Definitions
#define PWMCR_ENABLE (1 << 0)
#define PWMCR_RESET (1 << 1)

// Timer Match Control Register Bit Definitions
#define TMCR_MR0_I  (1 << 0)            // Enable Interrupt when MR0 matches TC
#define TMCR_MR0_R  (1 << 1)            // Enable Reset of TC upon MR0 match
#define TMCR_MR0_S  (1 << 2)            // Enable Stop of TC upon MR0 match
#define TMCR_MR1_I  (1 << 3)            // Enable Interrupt when MR1 matches TC
#define TMCR_MR1_R  (1 << 4)            // Enable Reset of TC upon MR1 match
#define TMCR_MR1_S  (1 << 5)            // Enable Stop of TC upon MR1 match
#define TMCR_MR2_I  (1 << 6)            // Enable Interrupt when MR2 matches TC
#define TMCR_MR2_R  (1 << 7)            // Enable Reset of TC upon MR2 match
#define TMCR_MR2_S  (1 << 8)            // Enable Stop of TC upon MR2 match
#define TMCR_MR3_I  (1 << 9)            // Enable Interrupt when MR3 matches TC
#define TMCR_MR3_R  (1 << 10)           // Enable Reset of TC upon MR3 match
#define TMCR_MR3_S  (1 << 11)           // Enable Stop of TC upon MR3 match

// Timer Capture Control Register Bit Definitions
#define TCCR_CR0_R (1 << 0)            // Enable Rising edge on CAPn.0 will load TC to CR0
#define TCCR_CR0_F (1 << 1)            // Enable Falling edge on CAPn.0 will load TC to CR0
#define TCCR_CR0_I (1 << 2)            // Enable Interrupt on load of CR0
#define TCCR_CR1_R (1 << 3)            // Enable Rising edge on CAPn.1 will load TC to CR1
#define TCCR_CR1_F (1 << 4)            // Enable Falling edge on CAPn.1 will load TC to CR1
#define TCCR_CR1_I (1 << 5)            // Enable Interrupt on load of CR1
#define TCCR_CR2_R (1 << 6)            // Enable Rising edge on CAPn.2 will load TC to CR2
#define TCCR_CR2_F (1 << 7)            // Enable Falling edge on CAPn.2 will load TC to CR2
#define TCCR_CR2_I (1 << 8)            // Enable Interrupt on load of CR2
#define TCCR_CR3_R (1 << 9)            // Enable Rising edge on CAPn.3 will load TC to CR3
#define TCCR_CR3_F (1 << 10)           // Enable Falling edge on CAPn.3 will load TC to CR3
#define TCCR_CR3_I (1 << 11)           // Enable Interrupt on load of CR3

#define STOP_TIMER_0()    T0TCR = ~(TCR_ENABLE)
#define STOP_TIMER_1()    T1TCR = ~(TCR_ENABLE)

#define START_TIMER_0()   T0TCR = TCR_ENABLE
#define START_TIMER_1()   T1TCR = TCR_ENABLE

#define LOAD_TIMER_0(x)   T0MR0 = x
#define LOAD_TIMER_1(x)   T1MR0 = x

void init_timer0(void);
void init_timer1(void);
void tn_timer0_int_func(void);
void timer1_int_func(void);


#endif

