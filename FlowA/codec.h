#ifndef __CODEC_H__
#define __CODEC_H__

/*
˵�������ฺ���ַ�����ת���Ĵ���
���ߣ��ο�
ʱ�䣺2017/03/20
*/
#ifdef __cplusplus
extern "C"
{
#include "include\iconv\iconv.h"
#include <stdio.h>
#include <string.h> //ANSI C HEADER
#include <stdlib.h>//ANSI C HEADER
#pragma comment(lib, ".\\libs\\iconv\\iconv.lib")
}
#endif

class Codec
{
public:
	Codec();
	/*
	˵������utf8������ַ�����ת��Ϊgb2312���ַ���
	��Σ�inbuf ��Ҫת����utf8�ַ���
	���Σ�outbuf ת������ַ���
	����ֵ��trueת���ɹ��� flaseת��ʧ��
	*/
	bool u2g(char *inbuf, char *outbuf);
	/*
	˵������gb2312������ַ���ת��Ϊutf-8������ַ���
	��Σ���Ҫת�����ַ���
	���Σ�ת�����ַ���
	����ֵ��trueת���ɹ��� falseת��ʧ��
	*/
	bool g2u(char *inbuf, char *outbuf);
private:
	/*
	˵��������ת��
	��Σ�from_charset
	��Σ�to_charset
	��Σ�inbuf
	��Σ�inlen
	���Σ�outbuf
	���Σ�outlen
	����ֵ�� -1 ʧ�� 0 �ɹ�
	*/
	int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
	char* utf8togb2312(char *inbuf);
	char* gb2312toutf8(char *inbuf);
};

#endif