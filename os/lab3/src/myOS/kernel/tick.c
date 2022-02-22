#include "../kernel/wallClock.h"

static unsigned long int TickCount = 0;

//��ȡ����
int getTickCount()
{
	return TickCount;
}

//ÿ�뱻����100�εļ�������
void tick(void)
{
	TickCount += 1;
	//�ﵽ100�������ʱ��
	if (TickCount >= 100)
	{
		int h, m, s;
		getWallClock(&h, &m, &s);
		setWallClock(h, m, s + (TickCount / 100));
		TickCount %= 100;
	}
	//����ʱ�Ӻ���
	setms(TickCount * 10);
}