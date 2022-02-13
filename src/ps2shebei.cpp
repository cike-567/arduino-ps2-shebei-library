/*
 *ps/2Э���������˺��豸�˲�����ȫһ���ģ���ͨѶʱ�в���豸��
 *������Ϊps/2���豸��ʹ�ã�Ҳ����ģ��һ��ps/2�豸��
 *����:��������żУ�����ʱ�������ݹ淶Ӳ���롣
 *���ݴ������ʲ����Ǻܿ죬���ܻ��кܴ���Ż��ռ䡣
 */
#include "ps2shebei.h"
//��������������ʱ�����ڵĳ��ȡ�
#define CLKFULL 40
//�ӽ׶ο�ʼ�����������ߵ�ʱ�䡣
#define CLKHALF 20

 //arduino����ȷ����ʱ�����ź��������ŵ�״̬����˲���Ҫ������������衣
PS2SHEBEI::PS2SHEBEI(int clock, int data)
{
  ps2clock = clock;
  ps2data = data;
  high(ps2clock);
  high(ps2data);
}

void PS2SHEBEI::high(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void PS2SHEBEI::low(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

//��ps/2����д��һ���ֽڡ�
int PS2SHEBEI::write(unsigned char data)
{
  unsigned char i;
  unsigned char parity = 1;

  if (digitalRead(ps2clock) != HIGH) {
    return -1;
  }
  if (digitalRead(ps2data) != HIGH) {
    return -2;
  }

  ////������ʼλ��
  low(ps2data);
  delayMicroseconds(CLKHALF);
  //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
  low(ps2clock);
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);

  for (i=0; i < 8; i++)
    {
      //��������λ��
      if (data & 0x01)
      {
        high(ps2data);
      } else
      {
        low(ps2data);
      }
      delayMicroseconds(CLKHALF);
      //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
      low(ps2clock);	
      delayMicroseconds(CLKFULL);
      high(ps2clock);
      delayMicroseconds(CLKHALF);

      parity = parity ^ (data & 0x01);
      data = data >> 1;
    }
  //������żУ��λ��
  if (parity)
    {
      high(ps2data);
    } else{
      low(ps2data);
      }
  delayMicroseconds(CLKHALF);
  //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
  low(ps2clock);	
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);

  //����ֹͣλ
  high(ps2data);
  delayMicroseconds(CLKHALF);
  //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
  low(ps2clock);	
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);

  delayMicroseconds(50);
  return 0;
}

//��ps2������ȡһ���ֽڵ����ݡ�����ֹͣλ��
int PS2SHEBEI::read(unsigned char * value)
{
  unsigned char data = 0x00;
  unsigned char i;
  unsigned char bit = 0x01;
  unsigned char parity = 1;
  
  //ps/2�������Ϳ�ʼλ
  //�ȴ�ps/2�������������ߵ�ƽ 
  while (digitalRead(ps2data) != LOW){
  } 
  //�ȴ�ps/2��������ʱ���ߵ�ƽ
  while (digitalRead(ps2clock) != HIGH){
  } 

  delayMicroseconds(CLKHALF);
  low(ps2clock);
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);

  //ps/2������������λ��
  for (i=0; i < 8; i++)
    {
      if (digitalRead(ps2data) != LOW){
        data = data | bit;
        }
        else{
        }

      bit = bit << 1;
      
      delayMicroseconds(CLKHALF);
      //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
      low(ps2clock);	
      delayMicroseconds(CLKFULL);
      high(ps2clock);
      delayMicroseconds(CLKHALF);
      
      //������һ��ѭ��������ʱ������żУ�顣
      parity = parity ^ (data & 0x01);
    }

  //��������żУ��λ
  delayMicroseconds(CLKHALF);
  low(ps2clock);	
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);
  
  //����ps/2����ͨѶ��������ֹͣλ��
  delayMicroseconds(CLKHALF);
  low(ps2data);
  
  //����ʱ���ߵ�ƽ���ȴ�һ��ʱ������ʱ���ߵ�ƽ��
  low(ps2clock);	
  delayMicroseconds(CLKFULL);
  high(ps2clock);
  delayMicroseconds(CLKHALF);

  //�ͷ�������
  high(ps2data);

  *value = data;
  
  return 0;
}

