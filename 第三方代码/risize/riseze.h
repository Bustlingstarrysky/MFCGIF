#pragma once
#ifndef RESIZE_H_
#define RESIZE_H_

#define _RESIZERECT WE::Oldpoint(this,&Old);
#define _RESIZEOLD	POINT Old
#define _RESIZE 	WE::resize(this,&Old)

namespace WE {
	void resize(CDialogEx*, POINT*);
	void Oldpoint(CDialogEx*, POINT*);
}

#endif
