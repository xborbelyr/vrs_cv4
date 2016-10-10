#include <stddef.h>
#include "stm32l1xx.h"

void adc_init(void);
void delay(int time);

int main(void)
{

	uint32_t AD_value, pauza;

	adc_init();

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode=GPIO_Mode_OUT;
	gpioInitStruct.GPIO_OType=GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin=GPIO_Pin_5;
	gpioInitStruct.GPIO_Speed=GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);

	while(1){

		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
		AD_value=ADC_GetConversionValue(ADC1);


		if(AD_value>3920 && AD_value<3970){
			pauza=4000;
		}else if(AD_value>1980 && AD_value<2020){
			pauza=8000;
		}else if(AD_value>2880 && AD_value<2920){
			pauza=16000;
		}else if(AD_value>3440 && AD_value<3480){
			pauza=32000;
		}else if(AD_value>3640 && AD_value<3680){
			pauza=64000;
		}else if(AD_value>1680 && AD_value<1720){
			pauza=128000;
		}else if(AD_value>3200 && AD_value<3240){
			pauza=256000;
		}

		GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
		delay(pauza);
	}

	return 0;
}

void delay(int time){
	for(int i=0; i<time; i++){
		;
	}
}

void adc_init(void)
{

	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;

	 /* Enable GPIO clock */
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	 /* Configure ADCx Channel 2 as analog input */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable the HSI oscillator */
	 RCC_HSICmd(ENABLE);

	/* Check that HSI oscillator is ready */
	 while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	 /* Enable ADC clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	 /* Initialize ADC structure */
	 ADC_StructInit(&ADC_InitStructure);

	 /* ADC1 configuration */
	 ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	 ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	 ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	 ADC_InitStructure.ADC_NbrOfConversion = 1;
	 ADC_Init(ADC1, &ADC_InitStructure);

	/* ADCx regular channel8 configuration */
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_16Cycles);

	 /* Enable the ADC */
	 ADC_Cmd(ADC1, ENABLE);

	 /* Wait until the ADC1 is ready */
	 while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	 {
	 }

	 /* Start ADC Software Conversion */
	 ADC_SoftwareStartConv(ADC1);

}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
