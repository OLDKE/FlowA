#include "adapter.h"
#include "ncrreadadapter.h"
#include "ncrformatadapter.h"
#include "ncrcontentadapter.h"
#include "ncrstoringadapter.h"

/*
说明：	根据atm厂商获取对应的文件读取适配器
参数：	入参 配置当中的atm厂商
返回值：	对应atm厂商的适配器
*/
ReadAdapter* Adapter::getReadAdapter(wchar_t* atmc)
{
	return new NCRReadAdapter();
}
/*
说明：	根据atm厂商获取对应的格式转换适配器
参数：	入参 配置当中的atm厂商
返回值：	对应atm厂商的适配器
*/
FormatAdapter* Adapter::getFormatAdapter(wchar_t* atmc)
{
	return new NCRFormatAdapter();
}
/*
说明：	根据atm厂商获取对应的报文处理适配器
参数：	入参 配置当中的atm厂商
返回值：	对应atm厂商的适配器
*/
ContentAdapter* Adapter::getContentAdapter(wchar_t* atmc)
{
	return new NCRContentAdapter();
}
/*
说明：	根据atm厂商获取对应的报文存储适配器
参数：	入参 配置当中的atm厂商
返回值：	对应atm厂商的适配器
*/
StoringAdapter* Adapter::getStoringAdapter(wchar_t* atmc)
{
	return new NCRStoringAdapter();
}