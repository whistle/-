#include <stdarg.h>  
#define NULL 0  

static inline int isdigit(int ch)
{
	return (ch >= '0') && (ch <= '9'); //���ش��ַ�����ȡ0-9������  
}

//����ַ�����Ϊ���֣��򷵻�����   
static int skip_atoi(const char** s)
{
	int i = 0;

	while (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}

#define ZEROPAD 1       /* pad with zero */  
#define SIGN    2       /* unsigned/signed long */  
#define PLUS    4       /* show plus */  
#define SPACE   8       /* space if plus */  
#define LEFT    16      /* left justified */  
#define SMALL   32      /* Must be 32 == 0x20 */  
#define SPECIAL 64      /* 0x */  

//���������Ҫ����ʵ���ж���Ҫת����ʲô������   
int __do_div(int n, int base)
{
	int __res;
	__res = ((unsigned long)n) % (unsigned)base;
	n = ((unsigned long)n) / (unsigned)base;
	return __res;
}

void Number(char** str, int date, int base)
{
	if (date < 0)
	{
		*(*str++) = '-';
		date *= -1;
	}
	if (date == 0)
	{
		*(*str++) = '0';
		return;
	}
	int Array[100];
	int i = 0;
	while (date > 0)
	{
		Array[i] = date % base;
		i++;
		date /= base;
	}
	for (; i >= 1; i--)
	{
		if (Array[i - 1] < 10)
			** str = Array[i - 1] + '0';
		else
			**str = Array[i - 1] - '9' + 'A' - 1;
		(*str)++;
	}
}

static char* number(char* str, long num, int base, int size, int precision, int type)
{
	/*����ַ�����������0-15��16�����֣���ʱ��Ҫ��������ת��*/
	static const char digits[16] = "0123456789ABCDEF";

	char tmp[66];
	char c, sign, locase;
	int i;

	/*locase = 0 ���� 0x20 , ������locase��ͬ�����ֻ���ĸ��Ҳ����ĸ��Сд��*/
	locase = (type & SMALL);
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 36)
		return NULL;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN)
	{
		if (num < 0)
		{
			sign = '-';
			num = -num;
			size--;
		}
		else if (type & PLUS)
		{
			sign = '+';
			size--;
		}
		else if (type & SPACE)
		{
			sign = ' ';
			size--;
		}
	}
	//������������Ҫ2���ƻ���Ҫ8���ƻ���16����   
	if (type & SPECIAL)
	{
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
		while (num != 0)
			tmp[i++] = (digits[__do_div(num, base)] | locase);
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type & (ZEROPAD + LEFT)))
		while (size-- > 0)
			* str++ = ' ';
	if (sign)
		* str++ = sign;
	if (type & SPECIAL)
	{
		if (base == 8)
			* str++ = '0';
		else if (base == 16)
		{
			*str++ = '0';
			*str++ = ('X' | locase);
		}
	}
	if (!(type & LEFT))
		while (size-- > 0)
			* str++ = c;
	while (i < precision--)
		* str++ = '0';
	while (i-- > 0)
		* str++ = tmp[i];
	while (size-- > 0)
		* str++ = ' ';
	return str;
}

int vsprintf(char* buf, const char* fmt, va_list args)
{
	int len;
	unsigned long num;
	int i, base;
	char* str;
	const char* s;
	int flags;
	int field_width;    /*λ�����*/
	int precision;
	int qualifier;
	//�����жϣ�������ַ���fmt�в�����%������ţ���ô�ַ��������������   
	for (str = buf; *fmt; ++fmt)
	{
		if (*fmt != '%')
		{
			*str++ = *fmt;
			continue;
		}

		//�������ñ�־λ   
		flags = 0;
	repeat:
		++fmt;      /* this also skips first '%' */
		//��ʽ����   
		switch (*fmt)
		{
		case '-':
			flags |= LEFT;
			goto repeat;
		case '+':
			flags |= PLUS;
			goto repeat;
		case ' ':
			flags |= SPACE;
			goto repeat;
		case '#':
			flags |= SPECIAL;
			goto repeat;
		case '0':
			flags |= ZEROPAD;
			goto repeat;
		}

		//��ȡ��ȣ�������Ҫ��Ҫʵ��printf��λ�����   
		field_width = -1;
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*')
		{
			++fmt;
			field_width = va_arg(args, int);
			if (field_width < 0)
			{
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		precision = -1;
		if (*fmt == '.')
		{
			++fmt;
			if (isdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*')
			{
				++fmt;
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/*�õ���ת���޶���*/
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
		{
			qualifier = *fmt;
			++fmt;
		}

		/*Ĭ�Ͻ���Ϊ10����*/
		base = 10;
		//������Ҫ��Ҫʵ��printf�ĸ�ʽ��� ���磺%d , %c , %u ...�ȵ�   
		int date;
		switch (*fmt)
		{
		case 'c':  //���ַ���ʽ�������   
			if (!(flags & LEFT))
				while (--field_width > 0)
					* str++ = ' ';
			*str++ = (unsigned char)va_arg(args, int);
			while (--field_width > 0)
				* str++ = ' ';
			continue;

		case 's': //���ַ�����ʽ�������   
			s = va_arg(args, char*);

			//len = strnlen(s, precision);
			for (int len = 0; s[len] != '\0'; s++);

			if (!(flags & LEFT))
				while (len < field_width--)
					* str++ = ' ';
			for (i = 0; i < len; ++i)
				* str++ = *s++;
			while (len < field_width--)
				* str++ = ' ';
			continue;

		case 'p': //�Ե�ַ��ʽ�����Ҳ������16���������   
			if (field_width == -1)
			{
				field_width = 2 * sizeof(void*);
				flags |= ZEROPAD;
			}
			str = number(str,
				(unsigned long)va_arg(args, void*), 16,
				field_width, precision, flags);
			continue;

		case 'n':
			if (qualifier == 'l')
			{
				long* ip = va_arg(args, long*);
				*ip = (str - buf);
			}
			else
			{
				int* ip = va_arg(args, int*);
				*ip = (str - buf);
			}
			continue;

		case '%':     //�����ʾ�ַ����д���%������ַ�   
			*str++ = '%';
			continue;

			/* integer number formats - set up the flags and "break" */
		case 'o':     //%o ��ʾ8�������   
			base = 8;
			break;

		case 'x':     //%x����%X ��ʾ16�������   
			flags |= SMALL;
		case 'X':
			if (!(flags & LEFT))
				while (--field_width > 0)
					* str++ = ' ';
			date = va_arg(args, int);
			Number(&str, date, 16);
			while (--field_width > 0)
				* str++ = ' ';
			continue;
		case 'd':     //%d %i�����������%u�޷�������   
			if (!(flags & LEFT))
				while (--field_width > 0)
					* str++ = ' ';
			date = va_arg(args, int);
			Number(&str, date, 10);
			while (--field_width > 0)
				* str++ = ' ';
			continue;
		case 'i':
			flags |= SIGN;
		case 'u':
			break;

		default:
			*str++ = '%';
			if (*fmt)
				* str++ = *fmt;
			else
				--fmt;
			continue;
		}
		if (qualifier == 'l') //���޷��ų��������   
			num = va_arg(args, unsigned long);
		else if (qualifier == 'h')
		{
			num = (unsigned short)va_arg(args, int);
			if (flags & SIGN)
				num = (short)num;
		}
		else if (flags & SIGN)
			num = va_arg(args, int);
		else
			num = va_arg(args, unsigned int);
		str = number(str, num, base, field_width, precision, flags);
	}
	*str = '\0';   //�ַ�����������\0�ĵط���ֹͣ   
	return str - buf;
}
int myvsprintf(char* buf, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);
}
//#include <stdarg.h>  
//
//int vsprintf(char* buf, char* str, va_list args)
//{
//	int count = 0;
//	//�����ַ���
//	while (*str != '\0')
//	{
//		if (*str != '%')
//		{
//			buf[count] = *str;
//			count++;
//			str++;
//		}
//		else
//		{
//			int c;
//			str++;
//			switch (*str)
//			{
//			case 'd':
//				va_arg(args, c);
//				c = c + '0';
//				break;
//			case '%':
//				c = '%';
//				break;
//			default:
//				buf[count] = '%';
//				count++;
//				break;
//			}
//			buf[count] = c;
//			count++;
//			str++;
//		}
//	}
//	buf[count] = '\0';
//	return count;
//}
