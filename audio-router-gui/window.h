#pragma once

#include "dialog_main.h"
#include "formview.h"
#include "bootstrapper.h"
#include "licensing.h"
#include <memory>
#include <shellapi.h>

#define WIN_WIDTH 970//400
#define WIN_HEIGHT 670//360
#define GET(type, item) reinterpret_cast<type&>(this->GetDlgItem(item))

class window : public CFrameWindowImpl<window>
{
private:
    bool dlg_main_b;
    NOTIFYICONDATA m_NotifyIconData;
public:
    dialog_main* dlg_main;
    formview* form_view;
    /*dialog_licensing* license;*/
    bootstrapper* bootstrap;

    explicit window(bootstrapper*);
    ~window();

    DECLARE_FRAME_WND_CLASS(L"Audio Router", IDR_MAINFRAME);

    BEGIN_MSG_MAP(window)
        MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
        MSG_WM_CREATE(OnCreate)
        /*MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)*/
        MESSAGE_HANDLER_EX(WM_SYSTEMTRAYICON, OnSystemTrayIcon)
        CHAIN_MSG_MAP(CFrameWindowImpl<window>)
        COMMAND_ID_HANDLER(ID_FILE_REFRESHLIST, OnFileRefreshlist)
        COMMAND_ID_HANDLER(ID_ABOUT, OnAbout)
        COMMAND_ID_HANDLER(ID_FILE_SWITCHVIEW, OnFileSwitchview)
        COMMAND_ID_HANDLER(ID_SYSTRAY_EXIT, OnSystemTrayExit)
        COMMAND_ID_HANDLER_EX(SC_RESTORE, OnRestore)

        /*MSG_WM_NCHITTEST(OnNcHitTest)*/
    END_MSG_MAP()

    enum
    {
        WM_FIRST = WM_APP,
        WM_SYSTEMTRAYICON,
    };

    int OnCreate(LPCREATESTRUCT);
    LRESULT OnFileRefreshlist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnFileSwitchview(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSystemTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnSystemTrayIcon(UINT, WPARAM wParam, LPARAM lParam);
    LRESULT OnRestore(UINT, INT, HWND);
};