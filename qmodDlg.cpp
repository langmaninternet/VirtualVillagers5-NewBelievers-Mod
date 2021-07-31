// qmodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qmod.h"
#include "qmodDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CQmodDlg dialog

CQmodDlg::CQmodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQmodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQmodDlg)
	m_food = 0;
	m_tech = 0;
	mainTimerID = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CQmodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQmodDlg)
	DDX_Text(pDX, IDC_FOOD, m_food);
	DDX_Text(pDX, IDC_TECH, m_tech);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQmodDlg, CDialog)
	//{{AFX_MSG_MAP(CQmodDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQmodDlg message handlers


BOOL		CQmodDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//	CMenu* pSysMenu = GetSystemMenu(FALSE);
	//	if (pSysMenu != NULL)
	//	{
	//		CString strAboutMenu;
	//		strAboutMenu.LoadString(IDS_ABOUTBOX);
	//		if (!strAboutMenu.IsEmpty())
	//		{
	//			pSysMenu->AppendMenu(MF_SEPARATOR);
	//			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//		}
	//	}



	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	mainTimerID = SetTimer(1, 2000, NULL);



	return TRUE;  // return TRUE  unless you set the focus to a control
}
void		CQmodDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}
void		CQmodDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

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
HCURSOR		CQmodDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}
HBRUSH		CQmodDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_TACGIA:pDC->SetTextColor(RGB(0, 0, 255)); break;
	case IDC_TRANGWEB:pDC->SetTextColor(RGB(255, 0, 0)); break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void		CQmodDlg::OnOK()
{
}





/************************************************************************/
/*                                                                      */
/************************************************************************/


void	GhiDuLieu0(
	DWORD pid,
	HANDLE hProcess,
	DWORD baseoffset /*= 0x380DAD*/,
	unsigned char* membuffer/*{0x90,0x90,0x90} = nop */,
	int membufferLength /*= 3*/);


void CQmodDlg::OnTimer(UINT_PTR nIdEvent)
{
	if (mainTimerID == nIdEvent)
	{


		HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
		if (!hwnd) return;

		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		if (pid == 0) return;

		HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pid);
		if (handle == 0) return;





		char bufferText[100] = { 0 };
		int* address = NULL;



		/************************************************************************/
		/*                                                                      */
		/************************************************************************/


		// Virtual Villagers - New Believers.exe+2D0D0 - 29 B3 587D0100        - sub [ebx+00017D58],esi
		// --> Virtual Villagers - New Believers.exe+2D0D0 - 01 B3 587D0100        - add [ebx+00017D58],esi
		unsigned char noniCheat[1] = { 0x01 };
		GhiDuLieu0(pid, handle, 0x2D0D0, noniCheat, 1);


		unsigned char fastSkillData[2] = { 0x90,0x90 };
		GhiDuLieu0(pid, handle, 0x3578A, fastSkillData, 2);


		//Virtual Villagers - New Believers.exe+5A9E3 - 29 86 647D0100        - sub [esi+00017D64],eax
		unsigned char infManaData[1] = { 0x01 };
		GhiDuLieu0(pid, handle, 0x5A9E3, infManaData, 1);


		unsigned char maxManaData[2] = { 0x90,0x90 };
		GhiDuLieu0(pid, handle, 0x5AAD6, maxManaData, 2);








		/************************************************************************/
		/* Food and Tech                                                        */
		/************************************************************************/
		address = (int*)0x7A7730;
		ReadProcessMemory(handle, address, &m_food, 4, 0);
		if (m_food < 99989)
		{
			m_food += 10;
			WriteProcessMemory(handle, address, &m_food, 4, 0);
		}

		address = (int*)0x7A79E0;
		ReadProcessMemory(handle, address, &m_tech, 4, 0);
		if (m_tech < 999899 && m_tech > 100)
		{
			m_tech += 100;
			WriteProcessMemory(handle, address, &m_tech, 4, 0);
		}
		else if (m_tech < 90)
		{
			if (m_tech < 1) m_tech = 1;
			m_tech++;
			WriteProcessMemory(handle, address, &m_tech, 4, 0);
		}

		UpdateData(FALSE);



		/************************************************************************/
		/* House                                                                */
		/************************************************************************/

		//mausoleum
		address = (int*)0x7EE4BC;
		float mausoleum = 0.0;
		ReadProcessMemory(handle, address, &mausoleum, 4, 0);
		if (mausoleum > 200.0)
		{
			mausoleum -= 100.0;
			mausoleum = (float)floor(mausoleum);
		}
		else if (mausoleum > 20.0)
		{
			mausoleum -= 10.0;
			mausoleum = (float)floor(mausoleum);
		}
		else if (mausoleum > 2.0)
		{
			mausoleum--;
			mausoleum = (float)floor(mausoleum);
		}
		WriteProcessMemory(handle, address, &mausoleum, 4, 0);
		sprintf_s(bufferText, "Mausoleum - %0.1f", mausoleum);
		GetDlgItem(IDC_MAUSOLEUM)->SetWindowTextA(bufferText);

		address = (int*)0x7EE3B8;
		short int houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "House 1 - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "House 1 - Full");
		else sprintf_s(bufferText, "House 1 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE)->SetWindowTextA(bufferText);
		//	temp = 1;
		//	address = (int*)0x7EE7C4;
		//	GhiDuLieu(address, &temp, 1);




		address = (int*)0x7EE3C0;
		houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "House 2 - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "House 2 - Full");
		else sprintf_s(bufferText, "House 2 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE2)->SetWindowTextA(bufferText);
		//	temp = 1;
		//	address = (int*)0x7EE7C4;
		//	GhiDuLieu(address, &temp, 1);




		address = (int*)0x7EE3C8;
		houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "House 3 - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "House 3 - Full");
		else sprintf_s(bufferText, "House 3 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE3)->SetWindowTextA(bufferText);
		//	temp = 1;
		//	address = (int*)0x7EE7C4;
		//	GhiDuLieu(address, &temp, 1);




		address = (int*)0x7EE3D0;
		houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "Wear - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "Wear - Full");
		else sprintf_s(bufferText, "Wear - %d/2000", houseValue);
		GetDlgItem(IDC_WEAR)->SetWindowTextA(bufferText);
		//	temp = 1;
		//	address = (int*)0x7EE7DC;
		//	GhiDuLieu(address, &temp, 1);




		address = (int*)0x7EE3E0;
		houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "School - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "School - Full");
		else sprintf_s(bufferText, "School - %d/2000", houseValue);
		GetDlgItem(IDC_SCHOOL)->SetWindowTextA(bufferText);
		//	temp = 1;
		//	address = (int*)0x7EE7D0;
		//	GhiDuLieu(address, &temp, 1);




		address = (int*)0x7EE3D8;
		houseValue = 0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1 && houseValue < 1980)
		{
			houseValue += 10;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		else if (houseValue > 1 && houseValue < 1998)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		if (houseValue == 0) sprintf_s(bufferText, "LoveShark - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "LoveShark - Full");
		else sprintf_s(bufferText, "LoveShark - %d/2000", houseValue);
		GetDlgItem(IDC_LOVESHARK)->SetWindowTextA(bufferText);





		//Tribute
		address = (int*)0x7EDC74;
		houseValue = 0;
		//float houseTributeValue = 0.0;
		ReadProcessMemory(handle, address, &houseValue, 2, 0);
		if (houseValue > 1)
		{
			houseValue += 1;
			WriteProcessMemory(handle, address, &houseValue, 2, 0);
		}
		//	if (houseValue > 1 && houseValue < 15)
		//	{
		//		houseValue += 1;
		//		WriteProcessMemory(handle, address, &houseValue, 2, 0);
		//	}
		//	else if (houseValue > 1 && houseValue < 190)
		//	{
		//		houseValue += 10;
		//		WriteProcessMemory(handle, address, &houseValue, 2, 0);
		//	}
		if (houseValue == 0) sprintf_s(bufferText, "Tribute - Auto");
		else if (houseValue >= 2000) sprintf_s(bufferText, "Tribute - Full");
		else sprintf_s(bufferText, "Tribute - %d/2000", houseValue);
		GetDlgItem(IDC_TRIBUTE)->SetWindowTextA(bufferText);



		/************************************************************************/
		/* Collection                                                           */
		/************************************************************************/
		address = (int*)0x7E93D0;
		int collectionArray[48] = { 0 };
		ReadProcessMemory(handle, address, collectionArray, 48 * 4, 0);
		int countScientificItems = 0;
		int countRelicItems = 0;
		for (int i = 0; i < 24; i++)
		{
			if (collectionArray[i])
			{
				countScientificItems++;
			}
		}
		for (int i = 24; i < 48; i++)
		{
			if (collectionArray[i])
			{
				countRelicItems++;
			}
		}
		if (countScientificItems < 24)
		{
			char collectionData = 1;
			for (int i = 0; i < 24; i++)
			{
				WriteProcessMemory(handle, address + i, &collectionData, 1, 0);

				if (collectionArray[i] == 0)
				{
					WriteProcessMemory(handle, address + i, &collectionData, 1, 0);
					//soft break;
					i = 99;
				}
			}
		}
		else if (countRelicItems < 24)
		{
			char collectionData = 1;
			for (int i = 24; i < 48; i++)
			{
				if (collectionArray[i] == 0)
				{
					WriteProcessMemory(handle, address + i, &collectionData, 1, 0);
					//soft break;
					i = 99;
				}
			}
		}

		if (countScientificItems + countRelicItems < 48)
		{
			sprintf_s(bufferText, "Collection - %d+%d/48", countScientificItems, countRelicItems);
		}
		else if (countScientificItems + countRelicItems == 48)
		{
			sprintf_s(bufferText, "Collection - Full");
		}
		else
		{
			sprintf_s(bufferText, "Collection - Auto");
		}
		GetDlgItem(IDC_COLLECTION)->SetWindowTextA(bufferText);


		/************************************************************************/
		/* Trophies                                                             */
		/************************************************************************/
		int trophies = 0;
		//food   1000
		address = (int*)0x7EE57C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999)
		{
			trophies = 999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//food   10000
		address = (int*)0x7EE588;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9999)
		{
			trophies = 9999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//food  100000
		address = (int*)0x7EE594;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99999)
		{
			trophies = 99999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//food  1000000
		address = (int*)0x7EE5A0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999999)
		{
			trophies = 999999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//tech  1000
		address = (int*)0x7EE5AC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999)
		{
			trophies = 999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//tech   10000
		address = (int*)0x7EE5B8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9999)
		{
			trophies = 9999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//tech  100000
		address = (int*)0x7EE5C4;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99999)
		{
			trophies = 99999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//tech   1000000
		address = (int*)0x7EE5D0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999999)
		{
			trophies = 999999;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//mushroom 25;
		address = (int*)0x7EE5DC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 24)
		{
			trophies = 24;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//mushroom 100;
		address = (int*)0x7EE5E8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//mushroom 500;
		address = (int*)0x7EE5F4;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 499)
		{
			trophies = 499;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//rare mushroom  5;
		address = (int*)0x7EE600;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 4)
		{
			trophies = 4;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//rare mushroom  25;
		address = (int*)0x7EE60C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 24)
		{
			trophies = 24;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//rare mushroom  100;
		address = (int*)0x7EE618;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//Relics
		address = (int*)0x7EE624;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies != countRelicItems)
		{
			trophies = countRelicItems;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//Science items
		address = (int*)0x7EE630;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies != countScientificItems)
		{
			trophies = countScientificItems;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}

		//		//Master collector
		//		address = (int*)0x7EE63C;
		//		ReadProcessMemory(handle, address, &trophies, 4, 0);
		//		if (trophies < 2)
		//		{
		//			trophies = 2;
		//			WriteProcessMemory(handle, address, &trophies, 4, 0);
		//		}


		//Heathens 3
		address = (int*)0x7EE660;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 2)
		{
			trophies = 2;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//Heathens 10
		address = (int*)0x7EE66C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}


		//		//buom bay
		//		temp = 15;
		//		address = (int*)0x7EE684;
		//		WriteProcessMemory(handle, address, &trophies, 4, 0);


		//baby girl
		address = (int*)0x7EE6CC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//baby boy
		address = (int*)0x7EE6D8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}




		//		//master skill
		//		temp = 10;
		//		address = (int*)0x7EE750;
		//		WriteProcessMemory(handle, address, &trophies, 4, 0);
		//		
		//		


		//event 10;
		address = (int*)0x7EE7B0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//event 50;
		address = (int*)0x7EE7BC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}


		//		//3house
		//		temp = 1;
		//		address = (int*)0x7EE7C4;
		//		GhiDuLieu(address, &temp, 1);
		//		
		//		//school
		//		temp = 1;
		//		address = (int*)0x7EE7D0;
		//		GhiDuLieu(address, &temp, 1);
		//		
		//		// wear
		//		temp = 1;
		//		address = (int*)0x7EE7DC;
		//		GhiDuLieu(address, &temp, 1);
		//		


		//cured = 10;
		address = (int*)0x7EE7EC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//cured = 50;
		address = (int*)0x7EE7F8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//cured = 100;
		address = (int*)0x7EE804;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//dot lua 50
		address = (int*)0x7EE810;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//dot lua time
		address = (int*)0x7EE81C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}
		//100 bo quan ao
		address = (int*)0x7EE834;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			WriteProcessMemory(handle, address, &trophies, 4, 0);
		}




		//		temp = 10;
		//		address = (int*)0x7EE84C;
		//		WriteProcessMemory(handle, address, &trophies, 4, 0);
		//		
		//		
		//		temp = 10;
		//		address = (int*)0x7EE87C;
		//		WriteProcessMemory(handle, address, &trophies, 4, 0);
		//		
		//		temp = 50;
		//		address = (int*)0x7EE888;
		//		WriteProcessMemory(handle, address, &trophies, 4, 0);




		CloseHandle(handle);
	}
}








#include "tlhelp32.h"
DWORD	GetModuleExeBase(HWND hwnd, char* lpModuleName)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwnd, &dwProcessId);


	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);


	if (!hSnapShot)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
	while (bModule)
	{
		if (!strcmp(lpModuleEntry.szModule, lpModuleName))
		{
			CloseHandle(hSnapShot);
			return (DWORD)lpModuleEntry.modBaseAddr;
		}
		bModule = Module32Next(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return NULL;
}
DWORD	GetModuleExeBase(DWORD th32ProcessID, wchar_t* lpModuleName)
{
	MODULEENTRY32W lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, th32ProcessID);
	if (!hSnapShot) return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32FirstW(hSnapShot, &lpModuleEntry);
	while (bModule)
	{
		if (!wcscmp(lpModuleEntry.szModule, lpModuleName))
		{
			CloseHandle(hSnapShot);
			return (DWORD)lpModuleEntry.modBaseAddr;
		}
		bModule = Module32NextW(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return NULL;
}





void GhiDuLieu(int* address, void* value, int size)
{
	HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
	if (!hwnd) return;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	WriteProcessMemory(handle, address, value, size, 0);
	CloseHandle(handle);
}






/************************************************************************/
/* For module name is same as excute file name                          */
/* "Virtual Villagers - New Believers.exe"+5AAD6                        */
/************************************************************************/
void	GhiDuLieu0(
	DWORD pid,
	HANDLE hProcess,
	DWORD baseoffset /*= 0x380DAD*/,
	unsigned char* membuffer/*{0x90,0x90,0x90} = nop */,
	int membufferLength /*= 3*/)
{
	if (!pid) return;
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32FirstW(snapshot, &entry) == TRUE)
	{
		while (Process32NextW(snapshot, &entry) == TRUE)
		{
			if (entry.th32ProcessID == pid)
			{
				DWORD baseaddress = GetModuleExeBase(entry.th32ProcessID, entry.szExeFile);
				if (baseaddress)
				{
					DWORD address = baseaddress + baseoffset;
					if (address)
					{
						WriteProcessMemory(hProcess, (void*)address, membuffer, membufferLength, 0);
					}
				}
			}
		}
	}
	CloseHandle(snapshot);
}



void	GhiDuLieu1(
	const wchar_t* className /*= L"Virtual Villagers - New Believers WndCls"*/,
	const wchar_t* windowName /*= L"Virtual Villagers - New Believers"*/,
	wchar_t* moduleName /*= L"Virtual Villagers - New Believers.exe" , NULL is excute file name*/,
	DWORD baseoffset /*= 0x380DAD*/,
	unsigned char* membuffer/*{0x90,0x90,0x90} = nop */,
	int membufferLength /*= 3*/)
{
	HWND hwnd = ::FindWindowW(className, windowName);
	if (!hwnd) return;

	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (!pid) return;

	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32FirstW(snapshot, &entry) == TRUE)
	{
		while (Process32NextW(snapshot, &entry) == TRUE)
		{
			if (entry.th32ProcessID == pid)
			{
				if (moduleName == NULL) moduleName = entry.szExeFile;
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, entry.th32ProcessID);
				DWORD baseaddress = GetModuleExeBase(entry.th32ProcessID, moduleName);
				if (baseaddress)
				{
					DWORD address = baseaddress + baseoffset;
					if (address)
					{
						WriteProcessMemory(hProcess, (void*)address, membuffer, membufferLength, 0);
					}
				}
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
}



void	GhiDuLieu2(
	wchar_t* executeName /*= L"stritz.exe"*/,
	wchar_t* moduleName /*= L"stritz.exe"*/,
	DWORD baseoffset /*= 0x380DAD*/,
	char* membuffer/*{0x90,0x90,0x90} = nop */,
	int membufferLength /*= 3*/)
{
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32FirstW(snapshot, &entry) == TRUE)
	{
		while (Process32NextW(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, executeName) == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, entry.th32ProcessID);
				DWORD baseaddress = GetModuleExeBase(entry.th32ProcessID, moduleName);
				DWORD address = baseaddress + baseoffset;
				WriteProcessMemory(hProcess, (void*)address, membuffer, membufferLength, 0);
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
}






