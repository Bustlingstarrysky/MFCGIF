#include "pch.h"
#include "RunMessage.hpp"

std::map<int, std::unique_ptr< WE::__LL::____FATHER>> TABLE{};

std::map<int, std::unique_ptr<WE::__LL::____FATHER>>& WE::GetMap() {
	return TABLE;
}

void WE::RUNTIMING(int ID) {
	if (!TABLE.count(ID)) {
		AfxMessageBox(L"û�д����������");
	}
	else {
		TABLE[ID]->run();
	}

	//AfxMessageBox(L"û�д���Ϣ/û��Ϊ�����Ϣ��������"
}