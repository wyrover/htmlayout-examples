// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// engine needs tabs for TAB navigation

    if((pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP) && ::GetFocus() == m_hWnd)
    {
      if(pMsg->wParam == VK_TAB) // always need this
      {
        ::SendMessage(m_hWnd,pMsg->message,pMsg->wParam,pMsg->lParam);
        return TRUE;
      }
      /*if() // others - only when we are in focus
      {
        ::SendMessage(m_hWnd,pMsg->message,pMsg->wParam,pMsg->lParam);
        return TRUE;
      }*/
    }

	return FALSE;
        
	//return CHTMLayoutWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}


LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_probeMode = false;
	if( !m_supportDD )
		DefWindowProc(uMsg,WPARAM_DISCARD_BUILTIN_DD_SUPP0RT,lParam);
	else
		DefWindowProc(uMsg,wParam,lParam);

	// HTMLayout stuff
	SetCallback(); // reroute all notifications here
	SetEventHandler(this); // set this as a "zero level" event handler, all not handled HTML DOM events will go here

	//::DragAcceptFiles(m_hWnd,TRUE);

	LoadHtmlResource(L"EMPTY");

	// register object for message filtering and idle updates
// 	CMessageLoop* pLoop = _Module.GetMessageLoop();
// 	ATLASSERT(pLoop != NULL);
// 	pLoop->AddMessageFilter(this);


	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
// 	CMessageLoop* pLoop = _Module.GetMessageLoop();
// 	ATLASSERT(pLoop != NULL);
// 	pLoop->RemoveMessageFilter(this);


	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}
