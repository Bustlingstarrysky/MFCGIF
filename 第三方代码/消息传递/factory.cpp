#include "pch.h"
#include "RunMessage.hpp"

std::map<int, std::unique_ptr< WE::__LL::____FATHER>> TABLE{};

std::map<int, std::unique_ptr<WE::__LL::____FATHER>>& WE::GetMap() {
	return TABLE;
}

void WE::RUNTIMING(int ID) {
	if (!TABLE.count(ID)) {
		AfxMessageBox(L"没有存在这个函数");
	}
	else {
		TABLE[ID]->run();
	}

	//AfxMessageBox(L"没有此消息/没有为这个消息建立函数"
}