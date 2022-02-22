#include "../lib/color.h"
extern void append2screenAtpoint(int line, int column, char* str, int color);
extern int myvsprintf(char* buf, const char* format, ...);

int hh = 0, mm = 0, ss = 0, ms = 0;

//����hook���ƴ���ʱ������
void setWallClockHook(void (*func)(void))
{
	(*func)();
}

//����ʱ�ӵ���ʾ
void UpdateWallClock(void)
{
	char buf[9];
	myvsprintf(buf, "%t", hh, mm, ss);
	append2screenAtpoint(24, 71, buf, YELLOW);
}

//����ʱ��
void setWallClock(int h, int m, int s)
{
	//��λ����
	ss = s % 60;
	m += s / 60;
	mm = m % 60;
	h += m / 60;
	h = h % 24;
	setWallClockHook(UpdateWallClock);
}

//���ú���
void setms(int _ms)
{
	ms = _ms;
}

//��ȡʱ��
void getWallClock(int* h, int* m, int* s)
{
	*h = hh;
	*m = mm;
	*s = ss;
}