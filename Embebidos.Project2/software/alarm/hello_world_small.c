/* Alarm clock project */

/* LIBRARY INCLUDES */
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "system.h"

/* CONSTANTS */
#define TRUE 1;
#define FALSE 0;

#define SEC 2
#define MIN 3
#define HR 4

/* GLOBAL VARIABLES */

volatile alt_u32 alt_irq_active = 0;

/*
 * Number of available interrupts in internal interrupt controller.
 */
#define ALT_NIRQ 32 //NIOS2_NIRQ

/*
 * Used by alt_irq_disable_all() and alt_irq_enable_all().
 */
typedef int alt_irq_context;

/* ISR Prototype */
typedef void (*alt_isr_func)(void* isr_context, alt_u32 id);


// Pointers of the displays
volatile unsigned char *h1_ptr = (unsigned char*) H1_BASE;
volatile unsigned char *h0_ptr = (unsigned char*) H0_BASE;
volatile unsigned char *m1_ptr = (unsigned char*) M1_BASE;
volatile unsigned char *m0_ptr = (unsigned char*) M0_BASE;
volatile unsigned char *s1_ptr = (unsigned char*) S1_BASE;
volatile unsigned char *s0_ptr = (unsigned char*) S0_BASE;

// Pointers to interact with buttons
volatile unsigned char *set_clock = (unsigned char*) BTN_SET_BASE;
volatile unsigned char *up_ptr = (unsigned char*) BTN_UP_BASE;
volatile unsigned char *down_ptr = (unsigned char*) BTN_DOWN_BASE;
volatile unsigned char *swc_sel = (unsigned char*) SWC_SEL_BASE;
volatile unsigned char *swc_alarm = (unsigned char*) SWC_ALARM_BASE;


// Pointer for the alarm sound
volatile unsigned char *alarm_ptr = (unsigned char*) ALARM_BASE;

//Timer pointer
volatile unsigned char *timer_base_ptr = (unsigned char *) TIMER_BASE;

// Current alarm hour
unsigned short alarm[3] = {0, 0, 0};
// Current hour
unsigned short hour[3] = {0, 0, 0};
// To activate and deactivate the Alarm
short is_activated = FALSE;
short time_unit_sel = SEC;
unsigned char irqtimer_stall = FALSE;
unsigned char first = TRUE;
unsigned char ud_buttons_en = FALSE;
unsigned char up_pressed = FALSE;
unsigned char down_pressed = FALSE;
unsigned char set_pressed = FALSE;
unsigned char button_pressed = FALSE;

/* FUNCTIONS */
/*
 * alt_irq_disable_all()
 *
 * This routine inhibits all interrupts by negating the status register PIE
 * bit. It returns the previous contents of the CPU status register (IRQ
 * context) which can be used to restore the status register PIE bit to its
 * state before this routine was called.
 */
static ALT_INLINE alt_irq_context ALT_ALWAYS_INLINE
       alt_irq_disable_all (void)
{
  alt_irq_context context;

  do { context = __builtin_rdctl(0); } while (0);

  do { __builtin_wrctl(0, context & ~(0x00000001)); } while (0);

  return context;
}

/*
 * alt_irq_enable_all()
 *
 * Enable all interrupts that were previously disabled by alt_irq_disable_all()
 *
 * This routine accepts a context to restore the CPU status register PIE bit
 * to the state prior to a call to alt_irq_disable_all().
 * In the case of nested calls to alt_irq_disable_all()/alt_irq_enable_all(),
 * this means that alt_irq_enable_all() does not necessarily re-enable
 * interrupts.
 *
 * This routine will perform a read-modify-write sequence to restore only
 * status.PIE if the processor is configured with options that add additional
 * writeable status register bits. These include the MMU, MPU, the enhanced
 * interrupt controller port, and shadow registers. Otherwise, as a performance
 * enhancement, status is overwritten with the prior context.
 */
static ALT_INLINE void ALT_ALWAYS_INLINE
       alt_irq_enable_all (alt_irq_context context)
{
	do { __builtin_wrctl(0, context); } while (0);
}

/*
 * alt_irq_pending() returns a bit list of the current pending interrupts.
 * This is used by irq_handler() to determine which registered interrupt
 * handlers should be called.
 *
 * This routine is only available for the Nios II internal interrupt
 * controller.
 */
static ALT_INLINE alt_u32 ALT_ALWAYS_INLINE alt_irq_pending (void)
{
  alt_u32 active;

  do { active = __builtin_rdctl(4); } while (0);

  return active;
}


/*
 * A table describing each interrupt handler. The index into the array is the
 * interrupt id associated with the handler.
 *
 * When an interrupt occurs, the associated handler is called with
 * the argument stored in the context member.
 */
struct ALT_IRQ_HANDLER
{
  void (*handler)(void*, alt_u32);
  void *context;
} alt_irq[ALT_NIRQ];


void irq_handler (void)
{
  alt_u32 active;
  alt_u32 mask;
  alt_u32 i;

  /*
   * Obtain from the interrupt controller a bit list of pending interrupts,
   * and then process the highest priority interrupt. This process loops,
   * loading the active interrupt list on each pass until alt_irq_pending()
   * return zero.
   *
   * The maximum interrupt latency for the highest priority interrupt is
   * reduced by finding out which interrupts are pending as late as possible.
   * Consider the case where the high priority interupt is asserted during
   * the interrupt entry sequence for a lower priority interrupt to see why
   * this is the case.
   */

  active = alt_irq_pending ();

  do
  {
    i = 0;
    mask = 1;

    /*
     * Test each bit in turn looking for an active interrupt. Once one is
     * found, the interrupt handler asigned by a call to alt_irq_register() is
     * called to clear the interrupt condition.
     */

    do
    {
      if (active & mask)
      {
        alt_irq[i].handler(alt_irq[i].context, i);
        break;
      }
      mask <<= 1;
      i++;

    } while (1);

    active = alt_irq_pending ();

  } while (active);
}

/*
 * alt_irq_register() can be used to register an interrupt handler. If the
 * function is succesful, then the requested interrupt will be enabled upon
 * return.
 */
int alt_irq_register (alt_u32 id,
					 void*   context,
					 alt_isr_func handler);


/*
 * alt_irq_disable() disables the individual interrupt indicated by "id".
 */
static ALT_INLINE int ALT_ALWAYS_INLINE alt_irq_disable (alt_u32 id)
{
  alt_irq_context  status;

  status = alt_irq_disable_all ();

  alt_irq_active &= ~(1 << id);

  do { __builtin_wrctl(3, alt_irq_active); } while (0);

  alt_irq_enable_all(status);

  return 0;
}

/*
 * alt_irq_enable() enables the individual interrupt indicated by "id".
 */
static ALT_INLINE int ALT_ALWAYS_INLINE alt_irq_enable (alt_u32 id)
{
  alt_irq_context  status;

  status = alt_irq_disable_all ();

  alt_irq_active |= (1 << id);

  do { __builtin_wrctl(3, alt_irq_active); } while (0);

  alt_irq_enable_all(status);

  return 0;
}


/*
 * irq_handler() is called to register an interrupt handler. If the
 * function is succesful, then the requested interrupt will be enabled upon
 * return. Registering a NULL handler will disable the interrupt.
 *
 * The return value is 0 if the interrupt handler was registered and the
 * interrupt was enabled, otherwise it is negative.
 */
int alt_irq_register (alt_u32 id,
                      void* context,
                      alt_isr_func handler)
{
  int rc = -22;
  alt_irq_context status;

  if (id < ALT_NIRQ)
  {
    /*
     * interrupts are disabled while the handler tables are updated to ensure
     * that an interrupt doesn't occur while the tables are in an inconsistant
     * state.
     */

    status = alt_irq_disable_all ();

    alt_irq[id].handler = handler;
    alt_irq[id].context = context;

    rc = (handler) ? alt_irq_enable (id): alt_irq_disable (id);

    alt_irq_enable_all(status);
  }
  return rc;
}

/* FUNCTIONS FOR ALARM CLOCK */
/**
 * Handler for alarm set button interrupt.
 */
static void btn_set_respond(void* context, alt_u32 id) {

	up_pressed = FALSE;
	down_pressed = FALSE;
	*alarm_ptr = (unsigned char) 0;

	//logica del boton set_alarm.

	/* Acknowledge interrupt by clearing edge capture register */
	*(set_clock + 12) = 0;

	if (!set_pressed) {
		alt_putstr("Button set\n");
		set_pressed = TRUE;
		if (irqtimer_stall) {
			switch(time_unit_sel)
			{
			case SEC:
				time_unit_sel = MIN;
				break;
			case MIN:
				time_unit_sel = HR;
				break;
			case HR:
				time_unit_sel = SEC;
				irqtimer_stall = FALSE;
				alt_irq_enable(TIMER_IRQ);
				break;
			}
		} else {
			irqtimer_stall = TRUE;
			alt_irq_disable(TIMER_IRQ);
		}
	} else {
		alt_putstr("Button already set\n");
	}
}

/**
 * Handler for button up interrupt.
 */
static void btn_up_respond(void* context, alt_u32 id){
	//logica del boton up.

	/* Acknowledge interrupt by clearing edge capture register */
	*(up_ptr + 12) = 0;

	if (!up_pressed) {
		alt_putstr("Button up\n");
		up_pressed = TRUE;
	} else {
		alt_putstr("Button already set up\n");
	}
}

/**
 * Handler for button down interrupt.
 */
static void btn_down_respond(void* context, alt_u32 id) {
	//logica del boton down.

	/* Acknowledge interrupt by clearing edge capture register */
	*(down_ptr + 12) = 0;

	if (!down_pressed) {
		alt_putstr("Button down\n");
		down_pressed = TRUE;

	} else {
		alt_putstr("Button already set down\n");
	}
}

/**
 * Initialize the buttons to zero
 */
static void buttons_init(void){
	//Set alarm button:

	*(set_clock + 8) = 0x1;
	*(set_clock + 12) = 0x0;
	alt_irq_register(BTN_SET_IRQ, BTN_SET_BASE, btn_set_respond);

	//Up button:
	*(up_ptr + 8) = 0x1;
	*(up_ptr + 12) = 0x0;
	alt_irq_register(BTN_UP_IRQ, BTN_UP_BASE, btn_up_respond);

	//Down button:
	*(down_ptr + 8) = 0x1;
	*(down_ptr + 12) = 0x0;
	alt_irq_register(BTN_DOWN_IRQ, BTN_DOWN_BASE, btn_down_respond);
}

void numberToSeg7(int num, volatile unsigned char* seg7) {

  switch (num) {
    case 0:
      *seg7 = 0b1000000;
      break;

    case 1:
      *seg7 = 0b1111001;
      break;

    case 2:
      *seg7 = 0b0100100;
      break;

    case 3:
      *seg7 = 0b0110000;
      break;

    case 4:
      *seg7 = 0b0011001;
      break;

    case 5:
      *seg7 = 0b0010010;
      break;

    case 6:
      *seg7 = 0b0000010;
      break;

    case 7:
      *seg7 = 0b1111000;
      break;

    case 8:
      *seg7 = 0b0000000;
      break;

    case 9:
      *seg7 = 0b0011000;
      break;
  }

  return;

}

/**
 * Set values to the correct output.
 */
int set_value(unsigned short value, volatile unsigned char* seg1, volatile unsigned char* seg0)
{
	//*seg1 = (unsigned char) value / 10;
	//*seg0 = (unsigned char) value % 10;

	numberToSeg7(value / 10, seg1);
	numberToSeg7(value % 10, seg0);

	return 0;
}

/**
 * Update the value of a specific display
 */
void add_second()
{
//	if (sel == 0) {
	// Add a second
	hour[0]++;

	if (hour[0] == 60)
	{
		hour[0] = 0;
		hour[1]++;

		if (hour[1] == 60)
		{
			hour[1] = 0;
			hour[2]++;

			if (hour[2] == 24)
			{
				hour[2] = 0;
			}
		}
	}
}

void display_hour()
{
	alt_printf("%x %x : %x %x : %x %x\n", *h1_ptr, *h0_ptr, *m1_ptr, *m0_ptr,
									   *s1_ptr, *s0_ptr);
}

/**
 * Handler for timer interrupt.
 */
static void timer_respond(void* context){

	set_pressed = FALSE;
	ud_buttons_en = FALSE;

	alt_irq_disable(BTN_UP_IRQ);
	alt_irq_disable(BTN_DOWN_IRQ);

	/* Acknowledge interrupt by clearing status register */
	*timer_base_ptr = 0x0;

	add_second();

	if (*swc_alarm == 1 && hour[2] == alarm [2] &&
			hour[1] == alarm[1] && hour[0] < 30) {
		*alarm_ptr = (unsigned char) 1;
	} else {
		*alarm_ptr = (unsigned char) 0;
	}

	set_value(hour[0], s1_ptr, s0_ptr);
	set_value(hour[1], m1_ptr, m0_ptr);
	set_value(hour[2], h1_ptr, h0_ptr);

	display_hour();
}

/**
 * Timer init
 */
static void timer_init(void){
	//Start the values for the timer interrupt.
	*(timer_base_ptr + 4) = 0x1 | 0x4;
	//Init the handler for the timer interrupt.
	alt_irq_register(TIMER_IRQ, TIMER_BASE /*timer_base_ptr*/, timer_respond);
}

/**
 * Initialize the pointers to zero to avoid unexpected behaviour at the beggining
 */
void init_values(){
	// init all the pointers to zero
	*h1_ptr = 0;
	*h0_ptr = 0;
	*m1_ptr = 0;
	*m0_ptr = 0;
	*s1_ptr = 0;
	*s0_ptr = 0;

	// alarm sound set to zero
	*alarm_ptr = 0;
}

int main()
{ 
	alt_putstr("Welcome to the Alarm Clock\n");

	if (first) {
		init_values();
		first = FALSE;
	}

	buttons_init();

	alt_irq_disable(BTN_UP_IRQ);
	alt_irq_disable(BTN_DOWN_IRQ);

	// Timer interrupt
	timer_init();

	while (1)
	{

		hour[0]= 10;
		hour[1]=15;
		hour[2]=20;
		set_value(hour[0], s1_ptr, s0_ptr);
		set_value(hour[1], m1_ptr, m0_ptr);
		set_value(hour[2], h1_ptr, h0_ptr);
	}

	return 0;
}

