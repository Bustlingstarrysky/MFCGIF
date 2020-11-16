#include "pch.h"

#include "changetheme.hpp"
#include "TheamName.h"

std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> Theme1;//这个是主题1的内容
std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> Theme2;//这个是主题1的内容
//还有一套路劲
//我去,还有这种操作
bool Is = false;
unsigned  int  Num = 1;
//std::vector<std::string> Theme3;
//首先,是名字,其次是路径

//主题1,主题二
std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>* WE::GetThemeName() {
	//push个锤子啊,

	switch (Num) {
	case 1: return &Theme1;  // NOLINT(bugprone-branch-clone)
	case 2: return &Theme2;
	}
	return nullptr;
}

std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>* WE::GetThemeNameNum(unsigned i) {
	switch (i) {
	case 1: return &Theme1;  // NOLINT(bugprone-branch-clone)
	case 2: return &Theme2;
	}
	return nullptr;
}

void WE::InsertVectorThemeName() {
	if (Is == false) {
		//每一个类不要用指针,而是直接去用
		SSS::__InSertThemeName1();
		SSS::__InSertThemeName2();
	}
}

void WE::ChangeNumTheme(unsigned i) {
	Num = i;
	ResertRun();
}

void WE::ResertRun() {
	//可惜我不是,所以就要这么做

	for (int i = 0; i < GetThemeName()->second.first.size(); ++i) {
		GetTheme(GetThemeName()->first)[GetThemeName()->second.first[i]]->run();// 没错,就是我吊打 //懂了,没有其他的东西
	}
}

//通过一个全局遍历.然后我们用函数去改这个变量

void WE::SSS::__InSertThemeName1() {
	WE::SetInsertTheme("主题1");
	Theme1.first = ("主题1");
	Theme1.second.first.clear();
	Theme1.second.second.clear();

	Theme1.second.first.push_back("主窗口");//标题,路径 //它是按照顺序的
	Theme1.second.second.push_back("picture/流星.gif");//标题,路径 //它是按照顺序的

	Theme1.second.first.push_back("背景窗口");//标题,路径 //它是按照顺序的
	Theme1.second.second.push_back("picture/主窗口背景.jpg");

	Theme1.second.first.push_back("控制面板_上箭头");
	Theme1.second.second.push_back("picture/jiantoutop.jpg");

	Theme1.second.first.push_back("控制面板_下箭头");
	Theme1.second.second.push_back("picture/jiantoudown.jpg");

	Theme1.second.first.push_back("控制面板_左箭头");
	Theme1.second.second.push_back("picture/jiantouleft.jpg");

	Theme1.second.first.push_back("控制面板_右箭头");
	Theme1.second.second.push_back("picture/jiantouright.jpg");

	Theme1.second.first.push_back("控制面板__上箭头");
	Theme1.second.second.push_back("picture/jiantoutopblue.jpg");

	Theme1.second.first.push_back("控制面板__下箭头");
	Theme1.second.second.push_back("picture/jiantoudownblue.jpg");

	Theme1.second.first.push_back("控制面板__左箭头");
	Theme1.second.second.push_back("picture/jiantouleftblue.jpg");

	Theme1.second.first.push_back("控制面板__右箭头");
	Theme1.second.second.push_back("picture/jiantourightblue.jpg");

	//Theme1.second.first.push_back("相片背景");
	//Theme1.second.second.push_back("picture/黑色.jpg");
}

void WE::SSS::__InSertThemeName2() {
	WE::SetInsertTheme("主题2");//然后只是告诉他们我们要怎么做,没错 没错,主题二还要搞 //查的是函数,没有关系的

	Theme2.first = ("主题2");
	Theme2.second.first.clear();
	Theme2.second.second.clear();

	Theme2.second.first.push_back("主窗口");//标题,路径 //它是按照顺序的
	Theme2.second.second.push_back("picture/下雨.gif");//标题,路径 //它是按照顺序的

	Theme2.second.first.push_back("背景窗口");//标题,路径 //它是按照顺序的
	Theme2.second.second.push_back("picture/浅蓝渐变色.jpg");

	Theme2.second.first.push_back("控制面板_上箭头");
	Theme2.second.second.push_back("picture/jiantoutop.jpg");

	Theme2.second.first.push_back("控制面板_下箭头");
	Theme2.second.second.push_back("picture/jiantoudown.jpg");

	Theme2.second.first.push_back("控制面板_左箭头");
	Theme2.second.second.push_back("picture/jiantouleft.jpg");

	Theme2.second.first.push_back("控制面板_右箭头");
	Theme2.second.second.push_back("picture/jiantouright.jpg");

	Theme2.second.first.push_back("控制面板__上箭头");
	Theme2.second.second.push_back("picture/jiantoutopblue.jpg");

	Theme2.second.first.push_back("控制面板__下箭头");
	Theme2.second.second.push_back("picture/jiantoudownblue.jpg");

	Theme2.second.first.push_back("控制面板__左箭头");
	Theme2.second.second.push_back("picture/jiantouleftblue.jpg");

	Theme2.second.first.push_back("控制面板__右箭头");
	Theme2.second.second.push_back("picture/jiantourightblue.jpg");

	//Theme2.second.first.push_back("相片背景");
	//Theme2.second.second.push_back("picture/白色.jpg");
}