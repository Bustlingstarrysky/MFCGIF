#pragma once

#ifndef LUCENCY_H_
#define LUCENCY_H

//可选什么颜色为透明,透明度不可以选

namespace WE {
	void lucency(UINT8 r, UINT8 g, UINT8 b, CDialogEx* dlg);

	void changelucency(UINT8 i, CDialogEx* dlg);
}

#endif
