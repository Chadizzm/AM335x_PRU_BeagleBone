   /* Driver header file */
   #include <prussdrv.h>
   #include <pruss_intc_mapping.h>
   
   #define PRU_NUM 	0
   
   /* IRQ handler thread */
   void *pruevtout0_thread(void *arg) {
       do {
          prussdrv_pru_wait_event (PRU_EVTOUT_0);
          prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT);
       } while (1);
   }
   
   void main (void)
   {
       /* Initialize structure used by prussdrv_pruintc_intc   */
       /* PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h */
       tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
   
       /* Allocate and initialize memory */
       prussdrv_init ();		
       prussdrv_open (PRU_EVTOUT_0);
       
       /* Map PRU's INTC */
       prussdrv_pruintc_init(&pruss_intc_initdata);
       
       /* Load and execute binary on PRU */
       prussdrv_exec_program (PRU_NUM, "./blinker.bin");
       
       /* Wait for event completion from PRU */
       prussdrv_pru_wait_event (PRU_EVTOUT_0);  // This assumes the PRU generates an interrupt 
                                                // connected to event out 0 immediately before halting
   
       /* Disable PRU and close memory mappings */
       prussdrv_pru_disable(PRU_NUM); 
       prussdrv_exit ();
    }
