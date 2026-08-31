
#include "USART_Driver.h"
#include "GPIO_Driver.h"
#include "RCC_Driver.h"
/*USART Driver function declaration*/

/*this function initialize to the usart peripheral in the passed USART_ID*/
void USART_Init(USART_EN_ID *USART_Config);
{
    uint8_t Over8Val;
    float USARTDIV,fraction;
    uint32_t Mantissa;
    USART_TypeDef *pUsart;
    pUsart = USART_Config->USARTinstant;

    /*insert the GPIO conofiguration for the usart ID*/    
    USART_GPIOConfig(USART_Config->usart_ID);

    /*UASRT enable RCC */
    /*Enable the clock for the corresponding USART peripheral based on the USART_ID*/
    switch(USART_Config->usart_ID)
    {
        case USART1_ID:
            RCC->APB2ENR |= (1 << 14);
            break;
        case USART2_ID:
            RCC->APB1ENR |= (1 << 17);
            break;
        case USART3_ID:
            RCC->APB1ENR |= (1 << 18);
            break;
        case USART4_ID:
            RCC->APB1ENR |= (1 << 19);
            break;
        case USART5_ID:
            RCC->APB1ENR |= (1 << 20);
            break;
        case USART6_ID:
            RCC->APB2ENR |= (1 << 5);
            break;
        default:
            // Handle invalid USART ID
            break;
    }
    RCC->APB2ENR &= ~(0 << 14);
   
    /*Enable PARTY for USART*/
    
    if(USART_Config->PARTY == USART_PARTY 0);
    {
        pUsart->CR1 &= ~(0 << 9);
    }
    else
    {
        pUsart->CR1 |= (1 << 9);
    }

    /*USART ENABLE WORDLENGTH*/

    if (USART_Config->WORDLENGTH == USART_WORD_LENGTH 8);
    {
        pUsart->CR1 &= ~(0 << 28);
    }
    else (USART_Config->WORDLENGTH == USART_WORD_LENGTH 9);
    {
        pUsart->CR1 |= (1 << 28);
    }
    /*USART Enable STOPBITS*/

    if (USART_Config->STOPBITS == USART_STOPBIT 1);
    {
        pUsart->CR2 &= ~(0b00 << 12);
    }
    else(USART_Config->STOPBITS == USART_STOPBIT 1);
    {
        pUsart->CR2 |= (0b10 << 12);
    }

    /*USART SET OVERSAMPLING */
    if (USART_Config->OVERSAMPLING == USART_OVERSAMPLING 8);
    {
        pUsart->CR1 |= (1 << 15);
        Over8Val =1;
    }
    else (USART_Config->OVERSAMPLING == USART_OVERSAMPLING 8);
    {
        pUsart->CR1 &= ~(0 << 15);
        Over8Val =0;
    }


    /*USART set bandrate*/

    //USARTDIV =FClk /(8 x (2 - Over8) x Baud Rate )
    float USARTDIV,fraction;
    uint32_t = Mantissa

    USARTDIV = USART_PeripheralClockFreq /(8 * x (2 -Over8Val) x *USART_Config->BaudRate);
    Mantissa = (uint32_t)USARTDIV;
    fraction = USARTDIV - Mantissa;

      // Convert fraction to register format
    if (Over8Val == 0) {
        // 16x oversampling: 4-bit fraction
        fractional_part = (uint8_t)(fraction * 16) & 0x0F;
    } else {
        // 8x oversampling: 3-bit fraction
        fractional_part = (uint8_t)(fraction * 8) & 0x07;
    }

    // Combine into BRR register value
    BRR_value = (Mantissa << 4) | fractional_part;

    // Write to BRR register
    pUsart->BRR = BRR_value;
}

// Usage:
    USART_SetBaudRate(USART1, 72000000, 9600, 0);  // 72MHz, 9600 baud, 16x oversampling

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



    /*USART ENABLE TX,RX */
    
    if (USART_Config->TE == USART_enable_TX);
    {
        pUsart->CR1 &= ~(0 == 3);  /*disable Tranmiton enable*/
        pUsart->CR1 |= (1 == 3);  /*enable Tranmition enable */
    }
    else (USART_Config->TE == USART_enable_TX);
    {
        pUsart->CR1 &= ~(0 == 2); /*disable Receiver disable*/
        pUsart->CR1 |= (1 == 2); /*enable Receiver enable*/

    }

/*----------------------------------------------------------------------------------------------------------------------------*/


/*this function transmit the data to the usart peripheral in the passed USART_ID*/
void USART_Transmit(USART_EN_ID USART_ID uint8_t *data, uint32_t length);
{ 
     
    {

    for(uint32_t i=0; i<length; i++);
        
        {
            while (!(pUsart->SR & USART_SR_TXE 0)); /*wait until TXE is set*/

            /*Transmit data */
            pUsart->DR = data[i];
        }

    /*Check for Transission check*/
    while (!(pUsart->SR & USART_SR_TC )); /*wait until TC is set*/
    }   
}


/*------------------------------------------------------------------------------------------------------------------------------*/


/*this function receive the data from the buffer as the passed USART_ID*/
void USART_Receive(USART_EN_ID USART_ID uint8_t *data, uint32_t length);
{  
{
    for(uint32_t i=0; i<length; i++);
    {
    //check the RXNE flag is SR
    While(!(pUsart->SR & USART_SR_RXNE)); /*wait until RXNE is set*/      
    }
    switch(USART_Config->USART_ID)
    
        {
        //Read the data from the DR register
        data[] = pUsart->DR;   
        }
              
}
}
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*this function enable the usart peripheral in the passed USART_ID*/
void USART_enable(USART_EN_ID USART_ID);
{   if(usartID == USART1_ID)
    {
        USARTx = USART1;
    }
    else if(usartID == USART2_ID)
    {
        USARTx = USART2;
    }
    else if(usartID == USART3_ID)
    {
        USARTx = USART3;
    }
    else if(usartID == USART4_ID)
    {
        USARTx = USART4;
    }
    else if(usartID == USART5_ID)
    {
        USARTx = USART5;
    }
    else if(usartID == USART6_ID)
    {
        USARTx = USART6;
    }
    USARTx->CR1 |= USART_CR1_UE; /*Enable USART peripheral*/
}
/*this function disable the usart peripheral in the given USART_ID*/
void USART_disable(USART_EN_ID USART_ID);   
{   if(usartID == USART1_ID)
    {
        USARTx = USART1;
    }
    else if(usartID == USART2_ID)
    {
        USARTx = USART2;
    }
    else if(usartID == USART3_ID)
    {
        USARTx = USART3;
    }
    else if(usartID == USART4_ID)
    {
        USARTx = USART4;
    }
    else if(usartID == USART5_ID)
    {
        USARTx = USART5;
    }
    else if(usartID == USART6_ID)
    {
        USARTx = USART6;
    }
    USARTx->CR1 &= ~USART_CR1_UE; /*Disable USART peripheral*/
    
}

/*this function configure GPIO Pinsthe usart peripheral in the given USART_ID*/
void USART_GPIOConfig(USART_EN_ID USART_ID);
{
   GPIO_InitTypeDef USART_GPIOConfig = {
        .Pin = 0,
        .Mode = GPIO_MODE_AF,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_NO_PULL
        .alternate=0
    };

/*the GPIO configuration for the USART peripheral is based on the specific USART_ID. The following code configures the GPIO pins for each USART peripheral.*/

/*GPIO UART1 pinconfiguration*/

    if(USART_ID == USART1_ID){
     /*PA 2 and PA 3 for rx and tx in USART_ID and AF1 */

    USART_GPIOConfig.pin=2
    USART_GPIOConfig.alternate=1
    GPIO_InitTypeDef(GPIOA, & USART_GPIOConfig)

    USART_GPIOConfig.pin=3
    USART_GPIOConfig.alternate=1
    GPIO_InitTypeDef(GPIOA, & USART)
    RCC_EnableGPIO(GPIOA)

    }

/*GPIO UART2 pinconfiguration*/
    else if(USART_ID == USART2_ID){ 
    /*PA 2 and PA 3 for rx and tx in USART_ID and AF1 */
    
    USART_GPIOConfig.pin=2
    USART_GPIOConfig.alternate=1
    GPIO_InitTypeDef(GPIOA, & USART_GPIOConfig)

    USART_GPIOConfig.pin=3
    USART_GPIOConfig.alternate=1
    GPIO_InitTypeDef(GPIOA, & USART)
    RCC_EnableGPIO(GPIOA)    

    }
/*GPIO UART3 pinconfiguration*/
    else if(USART_ID == USART2_ID){ 
    /*PB 10 and PB 11 for rx and tx in USART_ID and AF4 */

    USART_GPIOConfig.pin=10
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOB, & USART_GPIOConfig)

    USART_GPIOConfig.pin=11
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOB, & USART)
    RCC_EnableGPIO(GPIOB)

    }

/*GPIO UART4 pinconfiguration*/
    else if(USART_ID == USART2_ID){ 
    /*PA 0 and PA 1 for rx and tx in USART_ID and AF4 */

    USART_GPIOConfig.pin=0
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOA, & USART_GPIOConfig)

    USART_GPIOConfig.pin=1
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOA, & USART)
    RCC_EnableGPIO(GPIOA)
     
    }

/*GPIO UART5 pinconfiguration*/
    else if(USART_ID == USART2_ID){ 
    /*PB 3 and PB 4 for rx and tx in USART_ID and AF4 */
    
    USART_GPIOConfig.pin=3
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOB, & USART_GPIOConfig)

    USART_GPIOConfig.pin=4
    USART_GPIOConfig.alternate=4
    GPIO_InitTypeDef(GPIOB, & USART)
    RCC_EnableGPIO(GPIOB)
     
    }

/*GPIO UART6 pinconfiguration*/
    else if(USART_ID == UASRT6_ID){
    /*PA 4 and PA 5 for RX and TX in USART_ID and AF5*/

    USART_GPIOConfig.pin=4
    USART_GPIOConfig.alternate=5
    GPIO_InitTypeDef(GPIOA, & USART_GPIOConfig)

    USART_GPIOConfig.pin=5
    USART_GPIOConfig.alternate=5
    GPIO_InitTypeDef(GPIOA, & USART)
    RCC_EnableGPIO(GPIOA)    

    }
}

