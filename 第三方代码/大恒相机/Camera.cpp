#include"pch.h"
#include"Camera.h"

#include"ERROR.h"
WE::DAHENG::DAHENG() {
	IGXFactory::GetInstance().Init();
}
//�Ҳ�����������ά��,��������̫����
//���ҵķ�����ʵ�ְ�,һ���԰����еĶ���ȫ������,Ȼ��ÿ�ζ��þ�ȫ����ʾ,�Ҹ����벻����ʲô�취����list����ӿؼ�
//�ܳ��İ취,�Ҳ��Ի�ؼ�,лл , ��ֻ����ӳ��,û��,��ֻ����ӳ��,Ȼ��ѿؼ���ʾ����
WE::DAHENG::~DAHENG() {
	IGXFactory::GetInstance().Uninit();;
}

void WE::FindCamera(GxIAPICPP::gxdeviceinfo_vector& vector) {
	//WE::DAHENG ces;
	//IGXFactory::GetInstance().Init();
	IGXFactory::GetInstance().UpdateAllDeviceList(1000, vector);
	//IGXFactory::GetInstance().Uninit();;
	//����������ص�ֵ���������Ϣ
}