#pragma once

#include<vector>
#include<string>

namespace WE {
	std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>* GetThemeName();//push个锤子啊,
	std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>* GetThemeNameNum(unsigned int i);//push个锤子啊
	void InsertVectorThemeName();
	void ChangeNumTheme(unsigned int i);
	void ResertRun();

	namespace SSS {
		void __InSertThemeName1();
		void __InSertThemeName2();
	}
}
