// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
using namespace Gdiplus;
using namespace roverlib;


class CMainDlg : public CDialogImpl<CMainDlg, CHTMLayoutCtrl>,
	public CHTMLayoutHost<CMainDlg>,
	public htmlayout::event_handler
{
private:

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
	enum { IDD = IDD_MAINDLG1 };

	BEGIN_MSG_MAP(CMainDlg)
		COMMAND_ID_HANDLER(IDC_BUTTON1, OnButton1)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()


	CMainDlg(bool builtinDD = true) : event_handler( unsigned(-1) /*handle all event groups*/ ) 
	{
		m_nCurIndex = -1;
		m_supportDD = builtinDD;
	}

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		SetCallback();
		SetEventHandler(this);

		::DragAcceptFiles(m_hWnd,TRUE);
		LoadHtmlResource(L"EMPTY");

		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
	
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{		
		WTL::CPaintDC dc(m_hWnd);
		Graphics g(dc.m_hDC);
		DrawPic(dc.m_hDC, L"img\\png-0070.png");		

		return 0;
	}

	LRESULT OnButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		return 0;
	}

};
