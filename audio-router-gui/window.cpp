#include "window.h"

telemetry* telemetry_m = NULL;

window::window(bootstrapper* bootstrap) : dlg_main_b(true)/*, license(NULL)*/, bootstrap(bootstrap)
{
    this->dlg_main = new dialog_main(*this);
    this->form_view = new formview(*this);
}

window::~window()
{
    if(this->dlg_main_b)
        delete this->dlg_main;
    delete this->form_view;

    delete telemetry_m;
    telemetry_m = NULL;
}

int window::OnCreate(LPCREATESTRUCT lpcs)
{
    telemetry_m = new telemetry;

    /*this->license = new dialog_licensing(*this);*/

    this->m_hWndClient = this->dlg_main->Create(this->m_hWnd);
    this->dlg_main->ShowWindow(SW_SHOW);

    return 0;
}
LRESULT window::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{

    if (m_NotifyIconData.cbSize)
    {
        Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
    }

    return 0;
}

LRESULT window::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == SC_MINIMIZE || IsWindowVisible() && wParam == SC_CLOSE)
    {
        /* for(dialog_main::dialog_arrays_t::iterator it = this->dlg_main->dialog_arrays.begin();
             it != this->dlg_main->dialog_arrays.end();
             it++)
         {
             for(dialog_array::dialog_controls_t::iterator jt = (*it)->dialog_controls.begin();
                 jt != (*it)->dialog_controls.end();
                 jt++)
             {
                 (*jt)->set_display_name(false, true);
             }
         }*/

        if (!m_NotifyIconData.cbSize)
        {
            m_NotifyIconData.cbSize = NOTIFYICONDATAA_V1_SIZE;
            m_NotifyIconData.hWnd = m_hWnd;
            m_NotifyIconData.uID = 1;
            m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            m_NotifyIconData.uCallbackMessage = WM_SYSTEMTRAYICON;
            m_NotifyIconData.hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON));
            ATL::CString sWindowText;
            GetWindowText(sWindowText);
            _tcscpy_s(m_NotifyIconData.szTip, sWindowText);
        }
        
        Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);
        ShowWindow(SW_HIDE);

        bHandled = TRUE;
        return 0;
    }
    else if(wParam == SC_RESTORE)
    {
        /*for(dialog_main::dialog_arrays_t::iterator it = this->dlg_main->dialog_arrays.begin();
            it != this->dlg_main->dialog_arrays.end();
            it++)
        {
            for(dialog_array::dialog_controls_t::iterator jt = (*it)->dialog_controls.begin();
                jt != (*it)->dialog_controls.end();
                jt++)
            {
                (*jt)->set_display_name(false, false);
            }
        }*/

    }

    bHandled = FALSE;
    return 0;
}

LRESULT window::OnSystemTrayIcon(UINT, WPARAM wParam, LPARAM lParam) {

    ATLASSERT(wParam == 1);
    switch (lParam)
    {
		case WM_LBUTTONDBLCLK:
			SendMessage(WM_COMMAND, SC_RESTORE);
			break;

		case WM_RBUTTONUP:
		{
			SetForegroundWindow(m_hWnd);

			CPoint pos;
			ATLVERIFY(GetCursorPos(&pos));

			CMenu menu;
			menu.LoadMenuW(IDR_SYSTRAY_MENU);
			CMenuHandle popupMenu = menu.GetSubMenu(0);

			popupMenu.TrackPopupMenu(TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pos.x, pos.y, this->m_hWnd);
		}
		break;
    }
    return 0;
}

LRESULT window::OnSystemTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    SendMessage(WM_SYSCOMMAND, SC_CLOSE);
    return 0;
}

LRESULT window::OnFileRefreshlist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if(!this->dlg_main_b)
    {
        this->form_view->refresh_list();
    }
    return 0;
}


LRESULT window::OnAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    this->MessageBoxW(
        L"Audio Router version 0.10.2.\n" \
        L"\nIf you come across any bugs(especially relating to routing or duplicating), " \
        L"or just have an idea for a new feature, " \
        L"please send a PM to the developer on reddit: reddit.com/user/audiorouterdev/", 
        L"About", MB_ICONINFORMATION);
    return 0;
}


LRESULT window::OnFileSwitchview(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    RECT rc;
    this->GetClientRect(&rc);

    if(this->dlg_main_b)
    {
        this->dlg_main->DestroyWindow();
        delete this->dlg_main;

        this->m_hWndClient = this->form_view->Create(*this);
        //this->form_view->ShowWindow(SW_SHOW);
        this->form_view->SetWindowPos(NULL, &rc, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    else
    {
        this->form_view->DestroyWindow();

        this->dlg_main = new dialog_main(*this);
        this->m_hWndClient = this->dlg_main->Create(*this);
        //this->dlg_main->ShowWindow(SW_SHOW);
        this->dlg_main->SetWindowPos(NULL, &rc, SWP_NOZORDER | SWP_SHOWWINDOW);
    }

    this->dlg_main_b = !this->dlg_main_b;

    return 0;
}

LRESULT window::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return HTCLOSE;
}


LRESULT window::OnRestore(UINT, INT, HWND)
{
    if (m_NotifyIconData.cbSize)
    {
        Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
    }

    ShowWindow(SW_SHOW);
    BringWindowToTop();

    return 0;
}