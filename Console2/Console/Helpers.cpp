#include "StdAfx.h"
#include "Helpers.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void Helpers::GetMonitorRect(HWND hWnd, CRect& rectMonitor) {

	HMONITOR hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	GetMonitorRect(hMonitor, true, rectMonitor);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void Helpers::GetDesktopRect(HWND hWnd, CRect& rectDesktop) {

	HMONITOR hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	GetMonitorRect(hMonitor, false, rectDesktop);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void Helpers::GetDesktopRect(const CPoint& point, CRect& rectDesktop) {

	HMONITOR hMonitor = ::MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
	GetMonitorRect(hMonitor, false, rectDesktop);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void Helpers::GetMonitorRect(HMONITOR hMonitor, bool bIgnoreTaskbar, CRect& rectDesktop) {

	::ZeroMemory(&rectDesktop, sizeof(CRect));

	MONITORINFO		mi;

	::ZeroMemory(&mi, sizeof(MONITORINFO));
	mi.cbSize = sizeof(MONITORINFO);

	::GetMonitorInfo(hMonitor, &mi);
	rectDesktop = mi.rcMonitor;

	if (!bIgnoreTaskbar) {

		HWND hWndTaskbar = ::FindWindow(L"Shell_TrayWnd", L"");

		if (hWndTaskbar) {
			CRect rectTaskbar(0, 0, 0, 0);
			::GetWindowRect(hWndTaskbar, &rectTaskbar);
			rectDesktop.SubtractRect(&(mi.rcMonitor), rectTaskbar);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
