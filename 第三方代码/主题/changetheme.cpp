#include "pch.h"
#include "changetheme.hpp"

// ���ڻ��ü����� Ц����
std::map<std::string, std::map<std::string, std::unique_ptr<WE::THEME::THEME>>> Map;

//��Ҫдһ�������,��Ȼ����ֱ�Ӳ���

void WE::THEME::ThemeMapInsert__(std::string theme, std::string& str, THEME* _CLA) {
	Map[theme].insert(std::map<std::string, std::unique_ptr<WE::THEME::THEME>>::value_type(str, _CLA));//�㻹�ü�����
}
//���Ȳ������Ͱ�

void WE::SetInsertTheme(std::string str) {
	Map.insert(decltype(Map)::value_type(str, std::map<std::string, std::unique_ptr<WE::THEME::THEME>>()));//���������ȥ
}

std::map<std::string, std::unique_ptr<WE::THEME::THEME>>& WE::GetTheme(std::string str) {
	return Map[str];//ֱ��ȥ������
}