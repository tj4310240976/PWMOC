#include "./TIME_PWMOC/My_TIME_PWMOC.h"
TIM_HandleTypeDef My_TIME_PWMOC_init_struct;
void My_TIME_PWMOC_init(void)
{
    GPIO_InitTypeDef GPIO_init_struct;
    TIM_OC_InitTypeDef OC_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    My_TIME_PWMOC_init_struct.Instance=TIM2;
    My_TIME_PWMOC_init_struct.Init.Period=100;
    My_TIME_PWMOC_init_struct.Init.Prescaler=720-1;
    My_TIME_PWMOC_init_struct.Init.CounterMode=TIM_COUNTERMODE_UP;
    HAL_TIM_PWM_Init(&My_TIME_PWMOC_init_struct);
    
        
    GPIO_init_struct.Mode=GPIO_MODE_AF_PP;
    GPIO_init_struct.Pin=GPIO_PIN_0;
    GPIO_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&GPIO_init_struct);
    
    
    OC_init_struct.OCMode=TIM_OCMODE_PWM1;
    OC_init_struct.Pulse=0;
    OC_init_struct.OCPolarity=TIM_OCPOLARITY_HIGH;    
    HAL_TIM_PWM_ConfigChannel(&My_TIME_PWMOC_init_struct,&OC_init_struct,TIM_CHANNEL_1);
    
    
    HAL_TIM_PWM_Start(&My_TIME_PWMOC_init_struct,TIM_CHANNEL_1);
}

void My_PWMOC_MSPinit(void)
{
    for(int i=0;i<100;i++)
    {
        __HAL_TIM_SET_COMPARE(&My_TIME_PWMOC_init_struct, TIM_CHANNEL_1, i);
        HAL_Delay(10);
    }
    for(int i=0;i<100;i++)
    {
        __HAL_TIM_SET_COMPARE(&My_TIME_PWMOC_init_struct, TIM_CHANNEL_1, 100-i);
        HAL_Delay(10);
    }
}
