// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "../controls.extend/SMcListViewEx/SMCListViewEx.h"
#include "CAdapter.h"
#include "STileViewEx.h"

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
    m_bLayoutInited = FALSE;
    m_MainStyle = 0;
    m_LeftWndShow = TRUE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    SetMsgHandled(FALSE);
    return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
    m_bLayoutInited = TRUE;
    
    //多列listview
    SMCListView *pMcListView = FindChildByName2<SMCListView>("file_list_view");
    if(pMcListView)
    {
        IMcAdapter *pAdapter = new CTestMcAdapterFix;
        pMcListView->SetAdapter(pAdapter);
        pAdapter->Release();
    }
    //tileView
	STileViewEx *pTileView = FindChildByName2<STileViewEx>("file_tile_view");
    if(pTileView)
    {
        CTestTileAdapter *pAdapter = new CTestTileAdapter;
        pTileView->SetAdapter(pAdapter);
        pAdapter->Release();
    }
    
    return 0;
}

void CMainDlg::OnHideOrShowLeftWndClick()
{
    if(m_bLayoutInited)
    {
        SImageButton *pBtn = FindChildByName2<SImageButton>(L"btn_navi_left_wnd");
        SWindow *pLeftWnd = FindChildByName(L"wnd_left_file_type");
        m_LeftWndShow = !m_LeftWndShow;
        pLeftWnd->SetVisible(m_LeftWndShow);
        if(m_LeftWndShow)
        {
            pBtn->SetAttribute(L"skin", L"skin_navi_left_wnd");
        }
        else
        {
            pBtn->SetAttribute(L"skin", L"skin_navi_left_wnd_hide");
        }
    }
}

void CMainDlg::OnTabMainStyleClick()
{
    if(m_bLayoutInited)
    {
        SImageButton *pBtn = FindChildByName2<SImageButton>(L"btn_navi_tile");
        STabCtrl *pTab = FindChildByName2<STabCtrl>(L"tab_file");
        m_MainStyle = (m_MainStyle + 1) % 2;
        if(pTab)
        {
            pTab->SetCurSel(m_MainStyle);
        }
        if(0 == m_MainStyle)
        {
            pBtn->SetAttribute(L"skin", L"skin_navi_list");
        }
        else
        {
            pBtn->SetAttribute(L"skin", L"skin_navi_tile");
        }
    }
}

void CMainDlg::OnTabPageRadioSwitch(int nID)
{
    if(m_bLayoutInited)
    {
        STabCtrl *pTab = FindChildByName2<STabCtrl>(L"tab_main");
        if(pTab)
        {
            pTab->SetCurSel(nID - 10000);
        }
    }
}

const wchar_t *ft_str[] = { L"全部文件", L"图片", L"文档", L"视频", L"种子", L"音乐", L"应用", L"其它", L"我的分享" };
void CMainDlg::OnFileTypeRadioSwitch(int nID)
{
    SMessageBox(NULL, SStringT().Format(L"Change to %s", ft_str[nID - 20000]), L"File type", MB_OK);
}

void CMainDlg::OnSharePanelRadioSwitch(int nID)
{
    if(m_bLayoutInited)
    {
        STabCtrl *pTab = FindChildByName2<STabCtrl>(L"tab_share_panel");
        if(pTab)
        {
            pTab->SetCurSel(nID - 30000);
        }
    }
}

//TODO:消息映射
void CMainDlg::OnClose()
{
    CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
    SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
    SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
    SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
    SetMsgHandled(FALSE);
    if(!m_bLayoutInited)
    {
        return;
    }
    
    SWindow *pBtnMax = FindChildByName(L"btn_max");
    SWindow *pBtnRestore = FindChildByName(L"btn_restore");
    if(!pBtnMax || !pBtnRestore)
    {
        return;
    }
    
    if(nType == SIZE_MAXIMIZED)
    {
        pBtnRestore->SetVisible(TRUE);
        pBtnMax->SetVisible(FALSE);
    }
    else if(nType == SIZE_RESTORED)
    {
        pBtnRestore->SetVisible(FALSE);
        pBtnMax->SetVisible(TRUE);
    }
}

