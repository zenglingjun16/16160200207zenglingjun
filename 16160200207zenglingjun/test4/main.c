#include "LPC11XX.H"
#define LED1_ON()  (LPC_GPIO2->DATA &= ~(1<<0))
#define LED1_OFF() (LPC_GPIO2->DATA |= (1<<0))
#define LED2_ON()  (LPC_GPIO2->DATA &= ~(1<<1))
#define LED2_OFF() (LPC_GPIO2->DATA |= (1<<1))
#define KEY1_DOWN() ((LPC_GPIO3->DATA & (1<<0)) != (1<<0))
#define KEY2_DOWN() ((LPC_GPIO3->DATA & (1<<1))!=(1<<1))
/********************************************************************************
* FunctionName   : LEDInit()
* Description    : LED?????
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void LEDInit()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ??IOCON?? 
    LPC_IOCON->R_PIO1_0 &= ~0x07;    
    LPC_IOCON->R_PIO1_0 |= 0x01; //?P1.0????GPIO
    LPC_IOCON->R_PIO1_1 &= ~0x07;   
    LPC_IOCON->R_PIO1_1 |= 0x01; //?P1.1????GPIO
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ??IOCON??
    
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);  //??AHB???GPIO??    
    LPC_GPIO2->DIR |= (1<<0); // ?P1.0???????
    LPC_GPIO2->DATA |= (1<<0); // ?P1.0??????
    LPC_GPIO2->DIR |= (1<<1); // ?P1.1???????
    LPC_GPIO2->DATA |= (1<<1); // ?P1.1??????
}
/********************************************************************************
* FunctionName   : PIOINT1_IRQHandler()
* Description    : P1???????
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/

void PIOINT3_IRQHandler()
{
    if((LPC_GPIO3->MIS & (1<<0))==(1<<0)) // ???P1.9?????
    {
        LED1_ON();
        while(KEY1_DOWN());
        LED1_OFF();
        LPC_GPIO3->IC = (1<<0);  // ???
    }
    if((LPC_GPIO3->MIS & (1<<1))==(1<<1)) // ???P1.10?????
    {
        LED2_ON();
        while(KEY2_DOWN());
        LED2_OFF();
        LPC_GPIO3->IC = (1<<1);  // ???
    }
}
/********************************************************************************
* FunctionName   : main()
* Description    : ???
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
int main()
{
    LEDInit(); // ??LED
    
    LPC_IOCON->PIO3_0 &= ~(0x07);//?P1_9???GPIO
		LPC_GPIO3->DIR    &= ~(1<<0);//?P1_9?????
    LPC_IOCON->PIO3_1 &= ~(0x07);//?P1_10???GPIO
    LPC_GPIO3->DIR &= ~(1<<1);//?P1_10?????
    
    LPC_GPIO3->IE |= (1<<0); // ??P1.9??????
    LPC_GPIO3->IE |= (1<<1); // ??P1.10??????
    LPC_GPIO3->IS &= ~(1<<0); // ??P1.9???????
    LPC_GPIO3->IS &= ~(1<<1); // ??P1.10???????
    LPC_GPIO3->IEV &= ~(1<<0); // ??P1.9????????
    LPC_GPIO3->IEV &= ~(1<<1); // ??P1.10????????
    NVIC_EnableIRQ(EINT3_IRQn); // ??GPIO1??
    while(1)
    {
       ;
    }
}


