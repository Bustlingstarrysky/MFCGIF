#include "pch.h"
#include "changetheme.hpp"

// 现在还得加主题 笑死了
std::map<std::string, std::map<std::string, std::unique_ptr<WE::THEME::THEME>>> Map;

//你要写一个主题把,不然很难直接插入

void WE::THEME::ThemeMapInsert__(std::string theme, std::string& str, THEME* _CLA) {
	Map[theme].insert(std::map<std::string, std::unique_ptr<WE::THEME::THEME>>::value_type(str, _CLA));//你还得加主题
}
//得先插入类型把

void WE::SetInsertTheme(std::string str) {
	Map.insert(decltype(Map)::value_type(str, std::map<std::string, std::unique_ptr<WE::THEME::THEME>>()));//把它插入进去
}

std::map<std::string, std::unique_ptr<WE::THEME::THEME>>& WE::GetTheme(std::string str) {
	return Map[str];//直接去加主题
}