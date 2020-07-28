#include <uart.h>

//variable
u8 Rx_flag = 0;
u8 RxCounter1 = 0;
u8 RxBuffer1[30];

//function
void uart_init()
{

    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART2_IRQHandler(void)
{
    u8 temp;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        /* Read one byte from the receive data register */
        temp = USART_ReceiveData(USART2);
        if (temp == '\n' || RxCounter1 == 20)
        {
            Rx_flag = 1;
            USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
        }
        else
            RxBuffer1[RxCounter1++] = temp;
    }
}

PUTCHAR_PROTOTYPE
{

    USART_SendData(USART2, (uint8_t)ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
    }

    return ch;
}
