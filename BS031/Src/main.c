
/*说明*/
/*AE006 测试板程序*/

/*头文件*/
#include "stm8s.h"

/*变量*/
uint16_t DelayTimes = 0; //延时时间 ms级

/*宏定义配置*/
/*LED1配置*/
#define LEDPort GPIOC
#define LED1Pin GPIO_PIN_7
#define LED1ON GPIO_WriteHigh(LEDPort, LED1Pin)
#define LED1OFF GPIO_WriteLow(LEDPort, LED1Pin)
/*LED2配置*/
#define LED2Pin GPIO_PIN_6
#define LED2ON GPIO_WriteHigh(LEDPort, LED2Pin)
#define LED2OFF GPIO_WriteLow(LEDPort, LED2Pin)
/*LED2配置*/
#define LED3Pin GPIO_PIN_5
#define LED3ON GPIO_WriteHigh(LEDPort, LED3Pin)
#define LED3OFF GPIO_WriteLow(LEDPort, LED3Pin)
/*蜂鸣器配置*/
#define BeepPort GPIOC
#define BeepPin GPIO_PIN_4
#define BeepON GPIO_WriteHigh(BeepPort, BeepPin)
#define BeepOFF GPIO_WriteLow(BeepPort, BeepPin)
/*温度检测配置*/
#define TempSWPort GPIOC
#define TempSWPin GPIO_PIN_3
#define TempSWON GPIO_WriteHigh(TempSWPort, TempSWPin)
#define TempSWOFF GPIO_WriteLow(TempSWPort, TempSWPin)
/* 过压触发1 */
#define OV_CHECK_1_PORT GPIOD
#define OV_CHECK_1_PIN GPIO_PIN_3
#define OV_CHECK_1_ON GPIO_WriteHigh(OV_CHECK_1_PORT, OV_CHECK_1_PIN)
#define OV_CHECK_1_OFF GPIO_WriteLow(OV_CHECK_1_PORT, OV_CHECK_1_PIN)
/* 过压触发2 */
#define OV_CHECK_2_PORT GPIOC
#define OV_CHECK_2_PIN GPIO_PIN_3
#define OV_CHECK_2_ON GPIO_WriteHigh(OV_CHECK_2_PORT, OV_CHECK_2_PIN)
#define OV_CHECK_2_OFF GPIO_WriteLow(OV_CHECK_2_PORT, OV_CHECK_2_PIN)
/* 欠压触发 */
#define UV_CHECK_PORT GPIOD
#define UV_CHECK_PIN GPIO_PIN_2
#define UV_CHECK_ON GPIO_WriteHigh(UV_CHECK_PORT, UV_CHECK_PIN)
#define UV_CHECK_OFF GPIO_WriteLow(UV_CHECK_PORT, UV_CHECK_PIN)
/*按键配置*/
#define ButPort GPIOA
#define ButPin GPIO_PIN_3
/*ADC通道*/
#define RT1 ADC1_CHANNEL_5

#define PIN_S ADC1_CHANNEL_6
/*函数声明*/
static void CLK_Config(void);
static void ADC_Init(void);
static void GPIO_Conf(void);
static uint16_t ReadADCValue(ADC1_Channel_TypeDef Channel);
static void TIM4_INI(void);
static void DelayMs(uint16_t xms);
static void BeepFlash(uint8_t times, uint16_t delayms);

/**
  * @brief 时钟配置 主系统时钟配置 必要外设时钟配置.
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);

  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
}
/**
  * @brief 主函数.
  * @param  None
  * @retval None
  */
void main()
{

  uint32_t ADValue = 0;
  CLK_Config();
  GPIO_Conf();
  ADC_Init();
  TIM4_INI();
  TempSWOFF;
  LED1OFF;
  LED2OFF;
  LED3OFF;
  OV_CHECK_1_OFF;
  OV_CHECK_2_OFF;

  while (1)
  {
  Next: //循环
    if (GPIO_ReadInputPin(GPIOA, GPIO_PIN_3) == 0)
    {
      DelayMs(100);
      if (GPIO_ReadInputPin(GPIOA, GPIO_PIN_3) == 0)
      {
        //按键按下所有输出关闭
        LED1OFF;
        LED2OFF;
        LED3OFF;
        OV_CHECK_1_OFF;
        OV_CHECK_2_OFF;
        //TempSWON;
        //蜂鸣器长响一声
        BeepON;
        DelayMs(1300);
        BeepOFF;
        DelayMs(500);

        //测试NTC
        ADValue = 0;
        ADValue = ReadADCValue(RT1);
        ADValue = ADValue * 5000 / 1024;
        //电压在2400和2600之间  NTC测试通过  蜂鸣器短响两声 LED1亮
        if ((ADValue > 2800) && (ADValue < 3730)) //NTC正常
        {
          BeepFlash(2, 300);
          LED1ON;
        }
        else
        {
          BeepFlash(5, 700);
          LED1OFF;
          LED2OFF;
          goto Next; //跳出循环
        }
        //NTC测试通过

        //计算S口电压 正常状态下 2300 -2500
        ADValue = 0;
        ADValue = ReadADCValue(PIN_S);
        ADValue = ADValue * 5000 / 1024;
        if ((ADValue > 2300) && (ADValue < 2500))
        {
          ;
          // BeepFlash(2, 300);
          // LED2ON;
        }
        else
        {
          BeepFlash(5, 700);
          LED2OFF;
          LED1OFF;
          goto Next; //跳出循环
        }
        //正常状态测试通过

        /* 第三步 测过充 */
        OV_CHECK_1_ON;
        DelayMs(3000);
        ADValue = ReadADCValue(PIN_S);
        ADValue = ADValue * 5000 / 1024;
        if (ADValue < 100)
        {
          ;
        }
        else
        {
          BeepFlash(5, 700);
          LED2OFF;
          LED1OFF;
          goto Next; //跳出循环
        }

        OV_CHECK_1_OFF;
        DelayMs(3000);
        ADValue = ReadADCValue(PIN_S);
        ADValue = ADValue * 5000 / 1024;
        if ((ADValue > 2300) && (ADValue < 2500))
        {
          BeepFlash(2, 300);
          LED2ON;
        }
        else
        {
          BeepFlash(5, 700);
          LED2OFF;
          LED1OFF;
          goto Next; //跳出循环
        }

        /* 第4步 测欠压 */
        UV_CHECK_ON;
        DelayMs(3000);
        ADValue = ReadADCValue(PIN_S);
        ADValue = ADValue * 5000 / 1024;
        if (ADValue < 100)
        {
          ;
        }
        else
        {
          BeepFlash(5, 700);
          LED2OFF;
          LED1OFF;
          goto Next; //跳出循环
        }
        UV_CHECK_OFF;
        DelayMs(3000);
        ADValue = ReadADCValue(PIN_S);
        ADValue = ADValue * 5000 / 1024;
        if ((ADValue > 2300) && (ADValue < 2500))
        {
          BeepFlash(2, 300);
          LED3ON;
        }
        else
        {
          BeepFlash(5, 700);
          LED2OFF;
          LED1OFF;
          goto Next; //跳出循环
        }
        //整板测试通过
      }
    }
  }
}

/**
  * @brief  GPIO相关初始化
  * @param  None
  * @retval None
  */
static void GPIO_Conf(void)
{

  GPIO_Init(LEDPort, LED1Pin, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(LEDPort, LED2Pin, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(LEDPort, LED3Pin, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(BeepPort, BeepPin, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(OV_CHECK_1_PORT, OV_CHECK_1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(UV_CHECK_PORT, UV_CHECK_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(OV_CHECK_2_PORT, OV_CHECK_2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(TempSWPort, TempSWPin, GPIO_MODE_OUT_PP_LOW_FAST);

  GPIO_Init(ButPort, ButPin, GPIO_MODE_IN_PU_NO_IT);
}
/**
  * @brief ADC初始化.
  * @param  None
  * @retval None
  */
static void ADC_Init(void)
{

  //ADC1_DeInit();

  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_5, ADC1_PRESSEL_FCPU_D8, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL5, DISABLE);
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_6, ADC1_PRESSEL_FCPU_D8, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL6, DISABLE);
  ADC1_Cmd(ENABLE);
}
/**
  * @brief  获取某通道的ADC数值
  * @param  channel  //所需的ADC通道
  * @retval Val       //ADC转换值
  */
uint16_t ReadADCValue(ADC1_Channel_TypeDef Channel)
{
  uint16_t Val = 0;

  ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, Channel, ADC1_ALIGN_RIGHT);
  //平均值滤波
  for (uint8_t index = 0; index < 20; index++)
  {
    ADC1_ClearFlag(ADC1_FLAG_EOC);
    ADC1_StartConversion();
    while (!ADC1_GetFlagStatus(ADC1_FLAG_EOC))
      ;
    Val += ADC1_GetConversionValue();
  }
  return Val / 20;
}

/**
  * @brief 定时器4初始化
  * @param  None
  * @retval None
  */
void TIM4_INI(void)
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 125); //TIM4时钟是主频128分频 计数周期125  16M/128 =0.125M    (125+1)/0.125M ≈ 1ms
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  enableInterrupts();
}
/**
  * @brief 延时函数  使用TIME4 实现.
  * @param  xms      //期望延时的时间长度 单位 毫秒
  * @retval None
  */
void DelayMs(uint16_t xms)
{

  TIM4_Cmd(ENABLE);
  while (DelayTimes != xms)
  {
    ;
  }
  TIM4_Cmd(DISABLE);
  DelayTimes = 0;
  TIM4_SetCounter(0);
}
/**
  * @brief 蜂鸣器开关.
  * @param  times  //期望蜂鸣器响声次数
  * @retval None    //期望蜂鸣器响声持续时间
  */
void BeepFlash(uint8_t times, uint16_t delayms)
{
  uint8_t index = 2 * times;

  for (uint8_t i = 0; i < index; i++)
  {
    GPIO_WriteReverse(BeepPort, BeepPin);
    DelayMs(delayms);
  }
}

/*end of file*/
