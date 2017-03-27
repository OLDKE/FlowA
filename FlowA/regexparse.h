#ifndef __REGEXPARSE_H__
#define __REGEXPARSE_H__

class RegexPaser
{
public:
	RegexPaser(wchar_t* m_pattern = (wchar_t*)0);
	virtual ~RegexPaser();
public:
	/*
	˵��������������ʽ���죬���������
	��Σ�������ʽ�ַ���
	����ֵ������ģʽ���ɵ����������
	*/
	RegexPaser *compile(wchar_t* pattern);
	/*
	˵�����ַ���ƥ����ԣ�ֻ��ȫƥ��ʱ�򣬲ŷ����棬���򷵻ؼ�
	��Σ�str ��Ҫƥ����ַ���
	��Σ�pattern ƥ��ģʽ�ַ���
	����ֵ��	���ģʽƥ���ַ����ɹ����� true ���򷵻�false
	*/
	bool match(wchar_t*str, wchar_t* pattern = (wchar_t*)0);
	/*
	˵������ָ���ַ������У�����������ʽ��ָ�������ݣ��˺�����װ�򵥣�ֻ֧�ֻ�ȡһ���������
	��Σ�str Ҫƥ����ַ���
	��Σ�pattern ƥ��ģʽ
	���Σ�out ƥ�䵽���Ӵ�
	����ֵ:���ƥ��ɹ����򷵻�true ���򷵻� false
	*/
	//bool search(wchar_t*str, wchar_t*out, wchar_t* pattern = (wchar_t*)0);
	bool search(char*str, char*out, char* pattern = (char*)0);
private:
	wchar_t* m_pattern;
};

#endif