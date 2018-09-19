// DeviceDmpDlg.h : header file
//

#pragma once
#include <setupapi.h>
#include "afxwin.h"
#include "afxcmn.h"

// CDeviceDmpDlg dialog
class CDeviceDmpDlg : public CDialog
{
// Construction
public:
	CDeviceDmpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DEVICEDMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	PBYTE CDeviceDmpDlg::GetDeviceRegistryProperty(IN HDEVINFO DeviceInfoSet, IN PSP_DEVINFO_DATA DeviceInfoData,
								IN DWORD Property, OUT PDWORD PropertyRegDataType);


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int BuildDevList(void);
	int DoInsertItem(CHeaderCtrl * pHeaderCtrl, int iInsertAfter, int nWidth, LPTSTR lpsz); 
public:
	
	CListCtrl m_list3;
};
