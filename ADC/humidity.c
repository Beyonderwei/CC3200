/*
 * humidity.c
 *
 *  Created on: 2019年3月19日
 *      Author: Beyonderwei
 */

#include "humidity.h"

/**
 * Function to initialize adc pins
 *  \param  none
 *  \return none
 */
void
adcInit(void)
{
    PinTypeADC(ADC_PIN,PIN_MODE_255);    //将 PIN_58 引脚 设置为ADC引脚功能
    ADCTimerConfig(ADC_BASE,2^17);  //adc 时钟初始化  定义一个时间戳获取 adc 数据样本
    ADCTimerEnable(ADC_BASE);   //使能 adc 时钟
    ADCEnable(ADC_BASE);    //使能 adc 模块
    ADCChannelEnable(ADC_BASE,CHANNEL);    //使能 adc 通道
}

/**
 * Function to obtain voltage value
 *  \param  none
 *  \return voltage value
 */
float
adcValueGet(void)
{
    float final_value_sum;
    int cnt; //采样计数值
    unsigned long adc_sample;    //adc 采样值

    for(cnt=0; cnt < CHANNEL_CNT ; cnt++)
        {
            if( ADCFIFOLvlGet (ADC_BASE, CHANNEL))
            {
                adc_sample = ADCFIFORead(ADC_BASE, CHANNEL);
                //例程采用下述方法计算的， 猜测右移两位的原因为：数据为16位，adc 为12位，最高和最低两位为0，所以需要右移两位
                final_value_sum += ((((float)((adc_sample >> 2 ) & 0x0FFF))*1.4)/4096);    //基准电压1.4V 12位->4096
            }
        }
    return (final_value_sum/CHANNEL_CNT);  //返回 CHANNEL_CNT 次测量的平均值
}


