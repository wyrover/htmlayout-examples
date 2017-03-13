// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainFrame : 
	public CWindowImpl<CMainFrame, CHTMLayoutCtrl>, 
	public CHTMLayoutHost<CMainFrame>,	
	public htmlayout::event_handler,
	public CMessageFilter
{
	bool          m_probeMode;
	bool          m_supportDD;
	std::wstring  m_currentUrl;
	HELEMENT      m_mouseOver;
public:
	//used for recent file list
	std::list<std::wstring> m_recentList;

	//used for go back/forward
	std::vector<std::wstring> m_historyList;
	int m_nCurIndex;       
public:
	CMainFrame(bool builtinDD = true) : event_handler( unsigned(-1) /*handle all event groups*/ ) 
	{
		m_nCurIndex = -1;
		m_supportDD = builtinDD;
	}
public:
	DECLARE_WND_CLASS(::HTMLayoutClassNameT())

	

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	

	BEGIN_MSG_MAP(CMainFrame)
		//CHAIN_TO_HTMLAYOUT()
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)					
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
