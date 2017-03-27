#ifndef __CODEC_H__
#define __CODEC_H__

/*
说明：该类负责字符编码转换的处理
作者：任康
时间：2017/03/20
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
	说明：将utf8编码的字符串，转换为gb2312的字符串
	入参：inbuf 需要转换的utf8字符串
	出参：outbuf 转换后的字符串
	返回值：true转换成功， flase转换失败
	*/
	bool u2g(char *inbuf, char *outbuf);
	/*
	说明：将gb2312编码的字符串转化为utf-8编码的字符串
	入参：需要转换的字符串
	出参：转码后的字符串
	返回值：true转换成功， false转换失败
	*/
	bool g2u(char *inbuf, char *outbuf);
private:
	/*
	说明：编码转换
	入参：from_charset
	入参：to_charset
	入参：inbuf
	入参：inlen
	出参：outbuf
	出参：outlen
	返回值： -1 失败 0 成功
	*/
	int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
	char* utf8togb2312(char *inbuf);
	char* gb2312toutf8(char *inbuf);
};

#endif