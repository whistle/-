//ȡ�ַ�����
int strlen(char* str)
{
	int n = 0;
	while (*str++) n++;
	return n;
}

//�ַ�������
int strcpy(char* src, char* dst)
{
	int n = 0;
	while (*src)
	{
		*dst++ = *src++;
		n++;
	}
	return n;
}

//�ַ����Ƚ�
int strcmp(char* str1, char* str2)
{
	char c1, c2;
	do
	{
		c1 = *str1++;
		c2 = *str2++;
		if (c1 != c2) return (c1 > c2) ? 1 : -1;
		if (c1 == '\0') break;
	} while (1);
	return 0;
}

//�ж��ַ��Ƿ�Ϊ�����ź�
int ischarempty(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\0') ? 1 : 0;
}

//�ж��ַ��Ƿ�Ϊȷ�������ź�
int ischarendline(char c)
{
	return (c == '\n' || c == '\r' || c == '\0') ? 1 : 0;
}