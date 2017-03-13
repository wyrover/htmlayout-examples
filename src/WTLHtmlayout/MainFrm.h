// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

const int WM_UPDATE_PROGRESS = WM_USER + 2;
const int WM_SHNOTIFY = 0x401;

typedef struct tagUpdateInfo
{
	int id;
	int value;
	wchar_t message[256];

	tagUpdateInfo()
	{
		id = 0;
		value = 0;
		memset(message, 0, 256);
	};
}UpdateInfo;

typedef CWinTraits<WS_POPUP | WS_MINIMIZEBOX | WS_SYSMENU, WS_EX_LAYERED>		CHtmlayoutWinTraits;

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame, CHTMLayoutCtrl, CHtmlayoutWinTraits>, 
	public CHTMLayoutHost<CMainFrame>,	
	public htmlayout::event_handler,
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	CMainFrame() : event_handler(0xFFFFFFFF) 
	{
		
	}
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		
		
		CHAIN_TO_HTMLAYOUT()
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)	
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_UPDATE_PROGRESS, OnUpdateProgress)
		MESSAGE_HANDLER(WM_SHNOTIFY, OnShNotify)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		//CHAIN_MSG_MAP(CHTMLayoutCtrl<CMainFrame>)
		//CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);	
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUpdateProgress(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	std::wstring id_or_name_or_tag( HELEMENT he );
	virtual BOOL handle_mouse (HELEMENT he, MOUSE_PARAMS& params );	
	virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params );
	int hit_test(int x, int y);	
	bool is_minimized()const;
	bool is_maximized()const;
	void AddMessage(htmlayout::dom::element& root, const std::string& message, bool incoming);
	void ThreadPostValue();
	static UINT WINAPI _ThreadPostValueProc(LPVOID pParam);
	void LoadSkin();
private:
	dom::element button_min;
	dom::element button_max;
	dom::element button_menu;
	dom::element button_icon;
	dom::element button_close;
	dom::element caption;
	dom::element body;
	HANDLE		 m_hThread;
	DWORD        m_hSHNotify;
	LPITEMIDLIST m_pidlDesktop;
};
