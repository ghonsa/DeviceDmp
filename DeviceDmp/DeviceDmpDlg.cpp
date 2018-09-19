// DeviceDmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeviceDmp.h"
#include "DeviceDmpDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDeviceDmpDlg dialog




CDeviceDmpDlg::CDeviceDmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceDmpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeviceDmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list3);
}

BEGIN_MESSAGE_MAP(CDeviceDmpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDeviceDmpDlg message handlers
DEFINE_GUID( GUID_DEVCLASS_PORTS,   0x4d36e978L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 );
//GUID portsGUID =                    {0x4d36e978,0xe325,0x11ce,0xbfc1,0x08,0x00,0x2b,0xe1,0x03,0x18};
BOOL CDeviceDmpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	m_list3.SetView(LV_VIEW_DETAILS);  //|LV_VIEW_TILE
	int rslt = m_list3.InsertColumn(0,_T("Desc"), LVCFMT_LEFT,200,1);
	rslt =m_list3.InsertColumn(1,_T("Dev Name"), LVCFMT_LEFT,200,2);
	rslt =m_list3.InsertColumn(2,_T("Name"), LVCFMT_LEFT,200,3);
	rslt =m_list3.InsertColumn(3,_T("Class"), LVCFMT_LEFT,200,4);
	rslt =m_list3.InsertColumn(4,_T("Guid"), LVCFMT_LEFT,200,5);
	
	
	

	// Sample code
#if 0
	{
		CString strText;
		int nColumnCount = m_list3.GetHeaderCtrl()->GetItemCount();
	
		// Insert 10 items in the list view control.
		for (int i = 0; i < 10; i++)
		{
			strText.Format(TEXT("item %d"), i);
			// Insert the item, select every other item.
			m_list3.InsertItem(LVIF_TEXT | LVIF_STATE, i, strText, 0, LVIS_SELECTED, 0, 0);

			// Initialize the text of the subitems.
			for (int j = 1; j < nColumnCount; j++)
			{
				strText.Format(TEXT("sub-item %d %d"), i, j);
				m_list3.SetItemText(i, j, strText);
			}
		}
	}
#endif
	// ____________________

	//m_list3.SetView(LV_VIEW_TILE );
	
	//m_list3.SetItemText(0,0,"item 0,0");
	//m_list3.SetItemText(0,1,"item 0,1");
	//m_list3.SetItemText(0,2,"item 0,2");

	//m_list3.InsertItem(0,"String 1 is some what long");
	//m_list3.InsertItem(1,"String 2 ");
	//m_list3.InsertItem(2,"String 3 ");
	BuildDevList();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDeviceDmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDeviceDmpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDeviceDmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CDeviceDmpDlg::BuildDevList(void)
{
   HDEVINFO DeviceInfoSet;
   HDEVINFO NewDeviceInfoSet;
   DWORD	devIndx = 0;
   DWORD	devPropType;

   SP_DEVINFO_DATA DeviceInfoData;
   TCHAR * LineBuffer = (TCHAR *)malloc(2048);
   if(!LineBuffer)
   {
	 	return -1;
   }
   memset(LineBuffer,0,1024);
   // Create a device information set that will be the container for 
   // the device interfaces.

   DeviceInfoSet = SetupDiCreateDeviceInfoList(NULL, NULL);
    
   if(DeviceInfoSet == INVALID_HANDLE_VALUE) 
   {
		
      return 0;
   }

   //HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
	#define MAX_KEY_LENGTH 255
	#define MAX_VALUE_NAME 16383

   {
	   HKEY hreg;
		//LONG lrslt = RegOpenKey(HKEY_LOCAL_MACHINE,"HARDWARE\\DEVICEMAP\\SERIALCOMM", &hreg);
	   	LONG lrslt = RegOpenKey(HKEY_LOCAL_MACHINE,_T("HARDWARE\\DEVICEMAP"), &hreg);
	    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys=0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 
 
		DWORD i, retCode; 

		TCHAR  achData[MAX_VALUE_NAME]; 
		DWORD cchData = MAX_VALUE_NAME; 

		TCHAR  achValue[MAX_VALUE_NAME]; 
		DWORD cchValue = MAX_VALUE_NAME; 
	
		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hreg,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 
 
		// Enumerate the subkeys, until RegEnumKeyEx fails.
    
		if (cSubKeys)
		{
			//printf( "\nNumber of subkeys: %d\n", cSubKeys);

			for (i=0; i<cSubKeys; i++) 
			{ 
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hreg, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
				if (retCode == ERROR_SUCCESS) 
				{
					
					_stprintf_s(LineBuffer,1024,("(%d) %s\n", i+1, achKey));
					//m_devList.AddString(LineBuffer);
 
				}
			}
		} 
 
		// Enumerate the key values. 

		if (cValues) 
		{
			printf( "\nNumber of values: %d\n", cValues);

			for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
			{ 
				cchValue = MAX_VALUE_NAME; 
				achValue[0] = '\0'; 
		        retCode = RegEnumValue(hreg, i, 
					achValue, 
					&cchValue, 
					NULL, 
					NULL,
					(LPBYTE)achData,
					&cchData);
 
				if (retCode == ERROR_SUCCESS ) 
				{ 
					
				} 
			}
		}	
	}


	   
	// Retrieve the device information set for the interface class.
//GUID_DEVCLASS_PORTS
   NewDeviceInfoSet = SetupDiGetClassDevsEx( NULL,		// &GUID_DEVCLASS_PORTS
      NULL,
      NULL,
      DIGCF_PRESENT  | DIGCF_DEVICEINTERFACE |DIGCF_ALLCLASSES,  //| DIGCF_ALLCLASSES,
      //DIGCF_PRESENT  ,
      DeviceInfoSet,
      NULL,
      NULL
    );

   if(NewDeviceInfoSet == INVALID_HANDLE_VALUE) 
   {
      printf( "SetupDiGetClassDevsEx failed: %d\n", GetLastError() );
      return 0;
   }
	while(1)
	{
		
		PBYTE pDataString;
		//memset((void *)&DeviceInfoData,0,sizeof( SP_DEVINFO_DATA));
		DeviceInfoData.cbSize = sizeof( SP_DEVINFO_DATA);
		

		if(!SetupDiEnumDeviceInfo(  NewDeviceInfoSet, devIndx++,&DeviceInfoData))
		{
			break;
		}
		pDataString = GetDeviceRegistryProperty(NewDeviceInfoSet, &DeviceInfoData,
							SPDRP_DEVICEDESC, &devPropType);
		
		int idx = m_list3.InsertItem(LVIF_TEXT | LVIF_STATE, devIndx, (LPCTSTR)pDataString, 0, LVIS_SELECTED, 0, 0);

		
		//sprintf_s((char *)LineBuffer,1024,"%s     :: ",pDataString);
	
		free(pDataString);

		pDataString = GetDeviceRegistryProperty(NewDeviceInfoSet,  &DeviceInfoData,
							SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,&devPropType);
		m_list3.SetItemText(idx, 1,(LPCTSTR) pDataString);
		
	
		//strcat_s((char *)LineBuffer,(1024-strlen(LineBuffer)),(char *)pDataString);			
		free(pDataString);

		pDataString = GetDeviceRegistryProperty(NewDeviceInfoSet,  &DeviceInfoData,
					SPDRP_FRIENDLYNAME,&devPropType);
		if(pDataString)
		{
			m_list3.SetItemText(idx,2,(LPCTSTR)pDataString);
			//strcat((char *)LineBuffer,"     ::");
			//strcat_s((char *)LineBuffer,(1024-strlen(LineBuffer)),(char *)pDataString);			
			free(pDataString);
		}
		pDataString = GetDeviceRegistryProperty(NewDeviceInfoSet,  &DeviceInfoData,
					SPDRP_CLASS,&devPropType);
		if(pDataString)
		{
			m_list3.SetItemText(idx,3,(LPCTSTR)pDataString);
			//strcat((char *)LineBuffer,"     ::");
			//strcat_s((char *)LineBuffer,(1024-strlen(LineBuffer)),(char *)pDataString);			
			free(pDataString);
		}
		pDataString = GetDeviceRegistryProperty(NewDeviceInfoSet,  &DeviceInfoData,
					SPDRP_CLASSGUID,&devPropType);
		if(pDataString)
		{
			m_list3.SetItemText(idx,4,(LPCTSTR)pDataString);
			//strcat((char *)LineBuffer,"     ::");
			//strcat_s((char *)LineBuffer,(1024-strlen(LineBuffer)),(char *)pDataString);			
			free(pDataString);
		}
	devIndx++;	
	
	}
	delete LineBuffer;
	SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);

	return 1;
}


PBYTE CDeviceDmpDlg::GetDeviceRegistryProperty(IN HDEVINFO DeviceInfoSet, IN PSP_DEVINFO_DATA DeviceInfoData,
							IN DWORD Property, OUT PDWORD PropertyRegDataType)
{
    DWORD length = 0;
    PBYTE buffer = NULL;
    // 1st call gets the required length of the buffer
    if( SetupDiGetDeviceRegistryProperty( DeviceInfoSet,DeviceInfoData,Property,NULL,   // registry data type
											NULL,  0,&length))
    {
        //printf("in GetDeviceRegistryProperty(): call SetupDiGetDeviceRegistryProperty did not fail? (%x)\n",GetLastError());
        return (NULL);
    }
    if( GetLastError() != ERROR_INSUFFICIENT_BUFFER )
    {
        // this means there are no upper filter drivers loaded, so we can just
        // return.
        return (NULL);
    }
	// alloc the buffer
    buffer = (PBYTE)malloc( length );
    if( buffer == NULL )
    {
        // no memory!
        return (NULL);
    }
    if( !SetupDiGetDeviceRegistryProperty( DeviceInfoSet, DeviceInfoData,Property,
                                           PropertyRegDataType,buffer,length,NULL))
    {
        //printf("in GetDeviceRegistryProperty(): couldn't get registry property! error: %i\n", GetLastError());
        free( buffer );
        return (NULL);
    }
    // ok, we are finally done, and can return the buffer
    return (buffer);
}

 

int CDeviceDmpDlg::DoInsertItem(CHeaderCtrl * pHeaderCtrl, int iInsertAfter, int nWidth, LPTSTR lpsz) 
{ 
    HDITEM hdi; 
    int index; 
 
    hdi.mask = HDI_TEXT | HDI_FORMAT | HDI_WIDTH; 
    hdi.pszText = lpsz; 
    hdi.cxy = nWidth; 
    hdi.cchTextMax = sizeof(hdi.pszText)/sizeof(hdi.pszText[0]); 
    hdi.fmt = HDF_LEFT | HDF_STRING; 
 
    index = pHeaderCtrl->InsertItem(iInsertAfter,&hdi);
		
		 
 
    return index; 
}
