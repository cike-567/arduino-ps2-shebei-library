/*
 *ps/2Э���豸�˵Ŀ⡣
 *Chris J.Kiick׫д��2008��1�·�������������
 *Gene E.Scogin���Σ�2008��8�·�������������
 *2022��2���ɼ�į��ŷ�ὴ�����޸����������ҵ�ϰ�ߣ�����ע�ͷ�������ˡ���������GitHub��
 */
#ifndef ps2shebei_h
#define ps2shebei_h
#include "Arduino.h"

class PS2SHEBEI
{
	public:
		PS2SHEBEI(int clock, int data);
		int write(unsigned char data);
		int read(unsigned char * data);
	private:
		int ps2clock;
		int ps2data;
		void low(int pin);
		void high(int pin);
};
#endif

