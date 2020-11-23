#include "pch.h"

#include "changetheme.hpp"
#include "TheamName.h"

std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> Theme1;//���������1������
std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> Theme2;//���������1������
//����һ��·��
//��ȥ,�������ֲ���
bool Is = false;
unsigned  int  Num = 1;
//std::vector<std::string> Theme3;
//����,������,�����·��

//����1,�����
std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>* WE::GetThemeName() {
	//push�����Ӱ�,

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
		//ÿһ���಻Ҫ��ָ��,����ֱ��ȥ��
		SSS::__InSertThemeName1();
		SSS::__InSertThemeName2();
	}
}

void WE::ChangeNumTheme(unsigned i) {
	Num = i;
	ResertRun();
}

void WE::ResertRun() {
	//��ϧ�Ҳ���,���Ծ�Ҫ��ô��

	for (int i = 0; i < GetThemeName()->second.first.size(); ++i) {
		GetTheme(GetThemeName()->first)[GetThemeName()->second.first[i]]->run();// û��,�����ҵ��� //����,û�������Ķ���
	}
}

//ͨ��һ��ȫ�ֱ���.Ȼ�������ú���ȥ���������

void WE::SSS::__InSertThemeName1() {
	WE::SetInsertTheme("����1");
	Theme1.first = ("����1");
	Theme1.second.first.clear();
	Theme1.second.second.clear();

	Theme1.second.first.push_back("������");//����,·�� //���ǰ���˳���
	Theme1.second.second.push_back("picture/����.gif");//����,·�� //���ǰ���˳���

	Theme1.second.first.push_back("��������");//����,·�� //���ǰ���˳���
	Theme1.second.second.push_back("picture/�����ڱ���.jpg");

	Theme1.second.first.push_back("�������_�ϼ�ͷ");
	Theme1.second.second.push_back("picture/jiantoutop.jpg");

	Theme1.second.first.push_back("�������_�¼�ͷ");
	Theme1.second.second.push_back("picture/jiantoudown.jpg");

	Theme1.second.first.push_back("�������_���ͷ");
	Theme1.second.second.push_back("picture/jiantouleft.jpg");

	Theme1.second.first.push_back("�������_�Ҽ�ͷ");
	Theme1.second.second.push_back("picture/jiantouright.jpg");

	Theme1.second.first.push_back("�������__�ϼ�ͷ");
	Theme1.second.second.push_back("picture/jiantoutopblue.jpg");

	Theme1.second.first.push_back("�������__�¼�ͷ");
	Theme1.second.second.push_back("picture/jiantoudownblue.jpg");

	Theme1.second.first.push_back("�������__���ͷ");
	Theme1.second.second.push_back("picture/jiantouleftblue.jpg");

	Theme1.second.first.push_back("�������__�Ҽ�ͷ");
	Theme1.second.second.push_back("picture/jiantourightblue.jpg");

	//Theme1.second.first.push_back("��Ƭ����");
	//Theme1.second.second.push_back("picture/��ɫ.jpg");
}

void WE::SSS::__InSertThemeName2() {
	WE::SetInsertTheme("����2");//Ȼ��ֻ�Ǹ�����������Ҫ��ô��,û�� û��,�������Ҫ�� //����Ǻ���,û�й�ϵ��

	Theme2.first = ("����2");
	Theme2.second.first.clear();
	Theme2.second.second.clear();

	Theme2.second.first.push_back("������");//����,·�� //���ǰ���˳���
	Theme2.second.second.push_back("picture/����.gif");//����,·�� //���ǰ���˳���

	Theme2.second.first.push_back("��������");//����,·�� //���ǰ���˳���
	Theme2.second.second.push_back("picture/ǳ������ɫ.jpg");

	Theme2.second.first.push_back("�������_�ϼ�ͷ");
	Theme2.second.second.push_back("picture/jiantoutop.jpg");

	Theme2.second.first.push_back("�������_�¼�ͷ");
	Theme2.second.second.push_back("picture/jiantoudown.jpg");

	Theme2.second.first.push_back("�������_���ͷ");
	Theme2.second.second.push_back("picture/jiantouleft.jpg");

	Theme2.second.first.push_back("�������_�Ҽ�ͷ");
	Theme2.second.second.push_back("picture/jiantouright.jpg");

	Theme2.second.first.push_back("�������__�ϼ�ͷ");
	Theme2.second.second.push_back("picture/jiantoutopblue.jpg");

	Theme2.second.first.push_back("�������__�¼�ͷ");
	Theme2.second.second.push_back("picture/jiantoudownblue.jpg");

	Theme2.second.first.push_back("�������__���ͷ");
	Theme2.second.second.push_back("picture/jiantouleftblue.jpg");

	Theme2.second.first.push_back("�������__�Ҽ�ͷ");
	Theme2.second.second.push_back("picture/jiantourightblue.jpg");

	//Theme2.second.first.push_back("��Ƭ����");
	//Theme2.second.second.push_back("picture/��ɫ.jpg");
}