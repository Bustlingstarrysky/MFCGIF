#pragma once

//����Ƚ�����,��������//ͳһ�涨,����ʹ����ͬ����
#include <tuple>
#include<map>
#include <memory>
#include <string>

namespace WE {
	namespace THEME {
		//�����涼�ǽ���,���ܶ���
		class THEME
		{
		public:
			virtual void run() = 0;
			virtual ~THEME() {};
		};

		//
		template<typename  T, typename ...Args>
		class THEMEPARAM
		{
		public:
			THEMEPARAM(T, Args...);

			virtual ~THEMEPARAM() {};
		protected:
			T func;
			std::tuple<Args...> Parma;
		};

		template <typename T, typename ... Args>
		THEMEPARAM<T, Args...>::THEMEPARAM(T _func, Args..._args) :func(_func), Parma(std::make_tuple(_args...)) {}

		template<typename T, typename ...Args>
		class THEMERUN :public THEME, public THEMEPARAM<T, Args...>
		{
		public:
			THEMERUN(T _func, Args... _args);

			virtual void run() override;
		};

		template <typename T, typename ... Args>
		THEMERUN<T, Args...>::THEMERUN(T _func, Args... _args) :THEMEPARAM(_func, _args...) {}

		template <typename T, typename ... Args>
		void THEMERUN<T, Args...>::run() {
			std::apply(THEMEPARAM<T, Args...>::func, THEMEPARAM<T, Args...>::Parma);
		}//Ū����,��װ��,���������Ǻ����ͺ���ָ��

		template<typename T, typename ... Args>
		THEME* THEME_Fartory(T func, Args...args) {
			return new THEMERUN<T, Args...>(func, args...);
		}
	}

	//���Ҳ��һ��ģ��

	//����������ȷ����

	//��map��
	namespace THEME {
		void ThemeMapInsert__(std::string, std::string&, THEME*);//����,������ô�� //��ָ�봫��,Ȼ���ӽ�ȥ
	}

	template<typename T, typename ...Args>
	void THEMEMapInsert(std::string theme, std::string str, T func, Args... args) {
		ThemeMapInsert__(theme, str, THEME::THEME_Fartory(func, args...));
	}
	void SetInsertTheme(std::string);//��������
	std::map<std::string, std::unique_ptr<THEME::THEME>>& GetTheme(std::string);//��һ��,�������map,��ô������ô��
}