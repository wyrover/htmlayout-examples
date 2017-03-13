// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"
using namespace roverlib;
using namespace std;



bool set_string(std::wstring &stupid_std_string, const wchar_t *str)
{
    if (!str)
        return false;
    stupid_std_string = str;
    return true;
}

BOOL CMainFrame::PreTranslateMessage(MSG *pMsg)
{
    return FALSE;
    //return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM
    /*lParam*/, BOOL & /*bHandled*/)
{
    // HTMLayout stuff
    SetCallback();
    SetEventHandler(this);

    //LoadHtmlResource(L"EMPTY");


    LoadSkin();


	CenterWindow(::GetDesktopWindow());


	
	m_hSHNotify = 0;
	SHNotify_Register(m_hWnd, m_hSHNotify, m_pidlDesktop);



    // register object for message filtering and idle updates
    CMessageLoop *pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM
    /*lParam*/, BOOL &bHandled)
{
    // unregister message filtering and idle updates
    CMessageLoop *pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);

	SHNotify_Unregister(m_hSHNotify, m_pidlDesktop);

    ::PostQuitMessage(1);

    bHandled = FALSE;
    return 1;
}


std::wstring CMainFrame::id_or_name_or_tag(HELEMENT he)
{
    if (!he)
        return L"(no element)";
    htmlayout::dom::element el = he;
    std::wstring name;
    if (set_string(name, el.get_attribute("id")))
        return name;
    if (set_string(name, el.get_attribute("name")))
        return name;
    name = aux::a2w(el.get_element_type());
    return name;
}




BOOL CMainFrame::handle_mouse(HELEMENT he, MOUSE_PARAMS &params)
{

    /*htmlayout::debug_output_console dc;
    switch (params.cmd)
    {
        case MOUSE_DOWN:
            dc.printf("MOUSE_DOWN: %S\n", id_or_name_or_tag(params.target)
                .c_str());
            break;
            case MOUSE_DOWN | HANDLED: dc.printf("MOUSE_DOWN*: %S\n",
                id_or_name_or_tag(params.target).c_str());
            break;
        case MOUSE_UP:
            dc.printf("MOUSE_UP: %S\n", id_or_name_or_tag(params.target).c_str()
                );
            break;
            case MOUSE_UP | HANDLED: dc.printf("MOUSE_UP*: %S\n",
                id_or_name_or_tag(params.target).c_str());
            break;
    }
	*/

	switch (params.cmd)
	{
	case MOUSE_UP:
		/*if (params.target == button_close)
		{
			::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			return TRUE;
		}
		else if (params.target == button_max)
		{
			if (is_maximized())
				::ShowWindow(m_hWnd, SW_RESTORE);
			else
				::ShowWindow(m_hWnd, SW_MAXIMIZE);
			return TRUE;
		}
		else if (params.target == button_min)
		{
			::ShowWindow(m_hWnd, SW_MINIMIZE);
			return TRUE;			
		}
		else if (params.target == button_menu)
		{
			::MessageBox(m_hWnd, L"你点击了菜单按钮", NULL, MB_OK);
			return TRUE;
		}*/
		break;
	}


    return FALSE;
}


BOOL CMainFrame::handle_event(HELEMENT he, BEHAVIOR_EVENT_PARAMS &params)
{	
	if (params.cmd == HYPERLINK_CLICK)
	{
		if (params.heTarget == button_close)
		{
			::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			return TRUE;
		}
		else if (params.heTarget == button_max)
		{
			if (is_maximized())
				::ShowWindow(m_hWnd, SW_RESTORE);
			else
				::ShowWindow(m_hWnd, SW_MAXIMIZE);
			return TRUE;
		}
		else if (params.heTarget == button_min)
		{
			::ShowWindow(m_hWnd, SW_MINIMIZE);
			return TRUE;			
		}
		else if (params.heTarget == button_menu)
		{			
			std::wcout << L"你点击了菜单按钮" << std::endl;
			return TRUE;
		}
		else if (params.heTarget == ((htmlayout::dom::element)this->GetRootElement()).get_element_by_id(L"addmessage"))
		{
			
			htmlayout::dom::element divchat =  ((htmlayout::dom::element)this->GetRootElement()).get_element_by_id(L"chat");
			for (int i = 0; i < 50; i++)
			{
				AddMessage(divchat, "test", rand() % 2 == 1);
			}
			return TRUE;
		}
		else if (params.heTarget == ((htmlayout::dom::element)this->GetRootElement()).get_element_by_id(L"update1"))
		{
			boost::function0<void> f = boost::bind(&CMainFrame::ThreadPostValue, this);  
			boost::thread thrd(f);  
			thrd.start_thread();
			//thrd.join();  

			/*
			unsigned int nTID = 0;
			m_hThread = (HANDLE) _beginthreadex( NULL, 0, _ThreadPostValue, this, CREATE_SUSPENDED,&nTID);           
			if (!m_hThread)
			{				
				return TRUE;
			} 
			else 
				ResumeThread(m_hThread);
			*/
			
			
		}
	}
	
    return FALSE;
}


void CMainFrame::AddMessage(htmlayout::dom::element& root, const std::string& message, bool incoming)
{
	std::wstring t;	
	std::wostringstream html;
	if (incoming)
		t = L"<img src=\"png-0070.png\" />阳朔";
	else
		t = L"<img src=\"png-0070.png\" />徽州";	

	html << L"<li><a href=\"#\">" << t << L"</a></li>";
	
	
	htmlayout::dom::element el = htmlayout::dom::element::create("li");	
	root.insert(el, 0x7FFFFFF);

	aux::w2utf utf8string = aux::w2utf(html.str());

	el.set_html(utf8string, utf8string.length(), SOH_REPLACE);

	
	
}




int CMainFrame::hit_test(int x, int y)
{

	POINT pt;
	pt.x = x;
	pt.y = y;
	::MapWindowPoints(HWND_DESKTOP, m_hWnd, &pt, 1);

	if (caption.is_valid() && caption.is_inside(pt))
		return HTCAPTION;	

	RECT body_rc = body.get_location(ROOT_RELATIVE | CONTENT_BOX);

	if (PtInRect(&body_rc, pt))
		return HTCLIENT;

	if (pt.y < body_rc.top + 10)
	{
		if (pt.x < body_rc.left + 10)
			return HTTOPLEFT;
		if (pt.x > body_rc.right - 10)
			return HTTOPRIGHT;
	}
	else if (pt.y > body_rc.bottom - 10)
	{
		if (pt.x < body_rc.left + 10)
			return HTBOTTOMLEFT;
		if (pt.x > body_rc.right - 10)
		{
			htmlayout::debug_output_console dc;
			dc.printf("HTBOTTOMRIGHT\n");

			return HTBOTTOMRIGHT;
		}
	}

	if (pt.y < body_rc.top)
		return HTTOP;
	if (pt.y > body_rc.bottom)
		return HTBOTTOM;
	if (pt.x < body_rc.left)
		return HTLEFT;
	if (pt.x > body_rc.right)
		return HTRIGHT;


	return HTCLIENT;

}

bool CMainFrame::is_minimized()const
{
	WINDOWPLACEMENT wp;
	::GetWindowPlacement(m_hWnd, &wp);
	return wp.showCmd == SW_SHOWMINIMIZED;
}

bool CMainFrame::is_maximized()const
{
	WINDOWPLACEMENT wp;
	::GetWindowPlacement(m_hWnd, &wp);
	return wp.showCmd == SW_SHOWMAXIMIZED;
}

LRESULT CMainFrame::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//CPoint point = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));	
	return this->hit_test(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	
}

LRESULT CMainFrame::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	

	LRESULT lr = ::DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
	MINMAXINFO *pmmi = (MINMAXINFO*)lParam;
	pmmi->ptMinTrackSize.x = ::HTMLayoutGetMinWidth(m_hWnd);
	RECT rc;
	::GetWindowRect(m_hWnd, &rc);
	pmmi->ptMinTrackSize.y = ::HTMLayoutGetMinHeight(m_hWnd,
		rc.right - rc.left);
	return lr;

	
}

LRESULT CMainFrame::OnUpdateProgress( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	

	boost::shared_ptr<UpdateInfo> *pp = (boost::shared_ptr<UpdateInfo>*)wParam;
	boost::shared_ptr<UpdateInfo> info(*pp);
	


	//UpdateInfo* info = (UpdateInfo*)wParam;
	std::wostringstream message;
	message << info->value;


	for (int i = 1; i <= 5; i++)
	{
		std::wostringstream woss;
		woss << L"progress" << i;
		htmlayout::dom::element el =((htmlayout::dom::element)this->GetRootElement()).get_element_by_id(woss.str().c_str());	

		el.set_attribute("value", message.str().c_str());
		//el.update(true);
	
	}
	


	bHandled = TRUE;

	delete pp; //no leak

	

	return 0;
	
}

UINT WINAPI CMainFrame::_ThreadPostValueProc( LPVOID pParam )
{
	ATLASSERT(pParam);
	CMainFrame* pMainFrame = reinterpret_cast<CMainFrame *> (pParam);
	pMainFrame->ThreadPostValue();

	return 0;
}

void CMainFrame::ThreadPostValue()
{
	boost::shared_ptr<UpdateInfo> pInfo = boost::make_shared<UpdateInfo>();
	for (int i = 0; i <= 100; i++)
	{	
		pInfo->id = 1;
		pInfo->value = i;		
		PostMessage(WM_UPDATE_PROGRESS, (WPARAM)new boost::shared_ptr<UpdateInfo>(pInfo), 0);		
		boost::this_thread::sleep(boost::posix_time::milliseconds(20));
	}
}

LRESULT CMainFrame::OnShNotify( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	std::wstring strEvent;
	wchar_t szBuf[MAX_PATH] = {0};
	std::wstring strPath1, strPath2;

	SHNOTIFYSTRUCT *pidlItem = PSHNOTIFYSTRUCT(wParam);
	SHGetPathFromIDListW(pidlItem->dwItem1, szBuf);
	strPath1 = std::wstring(szBuf);
	SHGetPathFromIDListW(pidlItem->dwItem2, szBuf);
	strPath2 = std::wstring(szBuf);

	std::wstring appdir;
	std::wstring filepath;

	switch(lParam)
	{
	case SHCNE_RENAMEITEM:
		strEvent = L"重命名文件: " + strPath1 + L" 为 " + strPath2;
		break;
	case SHCNE_CREATE:
		strEvent = L"建立文件, 文件名: " + strPath1 + strPath2;
		break;
	case SHCNE_DELETE:
		strEvent = L"删除文件, 文件名: " + strPath1;
		break;
	case SHCNE_MKDIR:
		strEvent = L"建立目录, 目录名: " + strPath1;
		break;
	case SHCNE_RMDIR:
		strEvent = L"删除目录,目录名: " + strPath1;
		break;
	case SHCNE_MEDIAINSERTED:
		strEvent = strPath1 + L" 中插入可移动存储介质";
		break;
	case SHCNE_MEDIAREMOVED:
		strEvent = strPath1 + L" 中移去可移动存储介质";
		break;
	case SHCNE_DRIVEREMOVED:
		strEvent = L"移去驱动器: " + strPath1;
		break;
	case SHCNE_DRIVEADD:
		strEvent = L"添加驱动器: " + strPath1;
		break;
	case SHCNE_NETSHARE:
		strEvent = L"改变目录 " + strPath1 + L" 的共享属性";
		break;
	case SHCNE_UPDATEDIR:
		strEvent = L"更新目录: " + strPath1;
		break;
	case SHCNE_UPDATEITEM:
		strEvent = L"更新文件, 文件名: " + strPath1;
		appdir = GetAppPath();
		filepath = ExtractFilePath(strPath1);
		if (appdir.compare(filepath) == 0)
		{
			std::wcout << GetAppPath() << std::endl;
			LoadSkin();
		}
		break;
	case SHCNE_SERVERDISCONNECT:
		strEvent = L"断开与服务器的连接: " + strPath1 + L" " + strPath2;
		break;
	case SHCNE_UPDATEIMAGE:
		strEvent = L"更新图标:" + strPath1 + L" " + strPath2;
		break;
	case SHCNE_DRIVEADDGUI:
		strEvent = L"添加并显示驱动器: " + strPath1;
		break;
	case SHCNE_RENAMEFOLDER:
		strEvent = L"重命名文件夹: " + strPath1 + L" 为 " + strPath2;
		break;
	case SHCNE_FREESPACE:
		strEvent = L"磁盘空间大小改变: " + strPath1 + strPath2;
		break;
	case SHCNE_ASSOCCHANGED:
		strEvent = L"改变文件关联: " + strPath1 + L" " + strPath2;
		break;
	default:
		strEvent = L"其他操作.";
		break;
	}

	std::wcout << strEvent << std::endl;
	
	return 0;
}

void CMainFrame::LoadSkin()
{
	std::wstring filename = GetAppPath();
	filename.append(L"skin\\index.html");
	HTMLayoutLoadFile(m_hWnd, filename.c_str());

	htmlayout::dom::element root = this->GetRootElement();
	button_close = root.get_element_by_id(L"close");
	button_min = root.get_element_by_id(L"min");
	button_max = root.get_element_by_id(L"max");
	button_menu = root.get_element_by_id(L"menu");
	caption = root.get_element_by_id(L"caption");
	body = root.find_first(L"body");
}
