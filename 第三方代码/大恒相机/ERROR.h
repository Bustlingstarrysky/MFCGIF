#pragma once
#ifndef ERROR_R_R_R_
#define ERROR_R_R_R_

#define MY_ERROR__0 "�ɹ�"
#define MY_ERROR__1 "��������������"
#define MY_ERROR__2 "�Ҳ���TL��"
#define MY_ERROR__3 "�Ҳ����豸"
#define MY_ERROR__4 "��ǰ�豸Ϊ�����豸"
#define MY_ERROR__5 "��Ч����"

#define MY_ERROR__6 "��Ч���"
#define MY_ERROR__7 "��Ч�Ľӿڵ���"
#define MY_ERROR__8 "���ܵ�ǰ���ɷ��ʻ��豸���ʴ���"
#define MY_ERROR__9 "�û�buffer����"
#define MY_ERROR__10 "Feature���ʹ���,������IntFeature�������㹦��"
#define MY_ERROR__11 "д��ֵԽ��"

#define MY_ERROR__12 "��֧�ֵĹ���"
#define MY_ERROR__13 "û�е��ó�ʼ���ӿ�"
#define MY_ERROR__14 "��ʱ����"

#define MY_ERROR__ "�Ǵ���������Ĵ���"
//�ӹ����еĴ�����,ֱ�Ӻ궨��Ҳ��,���Ǻ�Ҳ��,�������ǽӹ�
//�ӹܴ���

#define MY_ERROR_TRY(_1)\
	try{  \
	  _1();\
	} \
	catch (CGalaxyException& e)\
	{\
	WE::MY_MFC_ERROR TRY;	\
	TRY.MyError(e.GetErrorCode()); \
	\
};\//����������

namespace WE {
	class MY_ERROR
	{
	public:
		virtual void MyError(int i) = 0;
	};
	class MY_MFC_ERROR : public MY_ERROR
	{
	public:
		virtual void MyError(int i) override;
	};
}

#endif
