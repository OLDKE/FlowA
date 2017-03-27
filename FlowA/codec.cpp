#include "codec.h"

Codec::Codec()
{

}

int Codec::code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
	{
		return -1;
	}
	memset(outbuf, 0, strlen(outbuf));
	if (iconv(cd, (const char **)pin, (unsigned int *)&inlen, pout, (unsigned int *)&outlen) == -1)
	{
		return -1;
		iconv_close(cd);
	}
	return 0;
}

char* Codec::utf8togb2312(char *inbuf)
{
	int nOutlen = 2 * strlen(inbuf) - 1;
	char *szOut = (char *)malloc(nOutlen);
	if (-1 == code_convert("utf-8", "gb2312", inbuf, strlen(inbuf), szOut, nOutlen))
	{
		free(szOut);
		szOut = NULL;
	}
	return szOut;
}

char* Codec::gb2312toutf8(char *inbuf)
{
	int nOutlen = 2 * strlen(inbuf) - 1;
	char *szOut = (char *)malloc(nOutlen);
	if (-1 == code_convert("gb2312", "utf-8", inbuf, strlen(inbuf), szOut, nOutlen))
	{
		free(szOut);
		szOut = NULL;
	}
	return szOut;
}

bool Codec::u2g(char *inbuf, char *outbuf)
{
	if (NULL == inbuf || outbuf == NULL)
		return false;
	char *pout = NULL;
	pout = utf8togb2312(inbuf);
	if (NULL == pout)
		return false;
	strcpy(outbuf, pout); //strcpy is not safe
	free(pout);
	return true;
}

bool Codec::g2u(char *inbuf, char *outbuf)
{
	if (NULL == inbuf || outbuf == NULL)
		return false;
	char *pout = NULL;
	pout = gb2312toutf8(inbuf);
	if (NULL == pout)
		return false;
	strcpy(outbuf, pout); //strcpy is not safe, consider use snprintf 
	free(pout);
	return true;
}

