#pragma once
#define APP_DATA _T("FrameworkData")
#define APP_ROOT _T("FrameworkRoot")
#define DRIVE_WND _T("HIDATAWINDOW")


enum E_MACHINE_STATE{
	E_START=0,
	E_INIT,
	E_ADJUST,
	E_CALCULATION,
	E_SAVE,
	E_END
};
//#define STATE_STR(SW,STR,X) switch(SW){ case X:STR=_T(#X);}break;