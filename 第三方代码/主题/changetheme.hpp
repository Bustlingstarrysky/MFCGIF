#pragma once

//这个比较难受,重新来吧//统一规定,主题使用相同类型
#include <tuple>
#include<map>
#include <memory>
#include <string>

namespace WE {
	namespace THEME {
		//这里面都是禁忌,不能动的
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
		}//弄完了,包装器,接下来就是函数和函数指针

		template<typename T, typename ... Args>
		THEME* THEME_Fartory(T func, Args...args) {
			return new THEMERUN<T, Args...>(func, args...);
		}
	}

	//这个也是一个模板

	//接下来就是确定的

	//用map吧
	namespace THEME {
		void ThemeMapInsert__(std::string, std::string&, THEME*);//是吗,插入这么难 //把指针传入,然后扔进去
	}

	template<typename T, typename ...Args>
	void THEMEMapInsert(std::string theme, std::string str, T func, Args... args) {
		ThemeMapInsert__(theme, str, THEME::THEME_Fartory(func, args...));
	}
	void SetInsertTheme(std::string);//主题名字
	std::map<std::string, std::unique_ptr<THEME::THEME>>& GetTheme(std::string);//第一个,返回这个map,怎么操作怎么来
}