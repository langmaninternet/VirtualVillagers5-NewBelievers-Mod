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
	ON_BN_CLICKED(IDC_COLLECTION, OnCollection)
	ON_EN_CHANGE(IDC_FOOD, OnChangeFood)
	ON_EN_SETFOCUS(IDC_FOOD, OnSetfocusFood)
	ON_EN_CHANGE(IDC_TECH, OnChangeTech)
	ON_EN_SETFOCUS(IDC_TECH, OnSetfocusTech)
	ON_BN_CLICKED(IDC_LOVESHARK, OnLoveshark)
	ON_BN_CLICKED(IDC_SCHOOL, OnSchool)
	ON_BN_CLICKED(IDC_WEAR, OnWear)
	ON_BN_CLICKED(IDC_HOUSE, OnHouse)
	ON_BN_CLICKED(IDC_HOUSE2, OnHouse2)
	ON_BN_CLICKED(IDC_HOUSE3, OnHouse3)
	ON_BN_CLICKED(IDC_TRIBUTE, OnTribute)
	ON_BN_CLICKED(IDC_TROPHIES, OnTrophies)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MAUSOLEUM, OnMausoleum)
	ON_BN_CLICKED(IDC_TRANGWEB, OnTrangweb)
	ON_BN_CLICKED(IDC_FASTSKILL, OnFastskill)
	ON_BN_CLICKED(IDC_MANA, OnMana)

	ON_WM_TIMER(OnTimer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQmodDlg message handlers

BOOL CQmodDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	mainTimerID = SetTimer(1, 2000, NULL);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void	GhiDuLieu1(
	const wchar_t* className /*= L"Virtual Villagers - New Believers WndCls"*/,
	const wchar_t* windowName /*= L"Virtual Villagers - New Believers"*/,
	wchar_t* moduleName /*= L"Virtual Villagers - New Believers.exe" , NULL is excute file name*/,
	DWORD baseoffset /*= 0x380DAD*/,
	unsigned char* membuffer/*{0x90,0x90,0x90} = nop */,
	int membufferLength /*= 3*/);

void CQmodDlg::OnTimer(UINT_PTR nIdEvent)
{
	if (mainTimerID == nIdEvent)
	{
		OnSetfocusFood();
		OnSetfocusTech();
		OnFastskill();
		OnMana();

		// Noni
		//Virtual Villagers - New Believers.exe+2D0D0 - 29 B3 587D0100        - sub [ebx+00017D58],esi
		// 
		// Virtual Villagers - New Believers.exe+2D0D0 - 01 B3 587D0100        - add [ebx+00017D58],esi
		unsigned char NoniCheat[1] = { 0x01 };
		GhiDuLieu1(L"Virtual Villagers - New Believers WndCls", L"Virtual Villagers - New Believers", NULL, 0x2D0D0, NoniCheat, 1);





		HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
		if (!hwnd) return;
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		if (pid == 0) return;
		HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pid);
		if (handle == 0) return;

		char bufferText[100] = { 0 };
		int* address = NULL;



		//mausoleum
		address = (int*)0x7EE4BC;
		float mausoleum = 0.0;
		ReadProcessMemory(handle, address, &mausoleum, 4, 0);
		if (mausoleum > 200.0)
		{
			mausoleum -= 100.0;
			mausoleum = floor(mausoleum);
		}
		else if (mausoleum > 20.0)
		{
			mausoleum -= 10.0;
			mausoleum = floor(mausoleum);
		}
		else if (mausoleum > 2.0)
		{
			mausoleum--;
			mausoleum = floor(mausoleum);
		}
		WriteProcessMemory(handle, address, &mausoleum, 4, 0);
		sprintf(bufferText, "Mausoleum - %0.1f", mausoleum);
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
		if (houseValue == 0) sprintf(bufferText, "House 1 - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "House 1 - Full");
		else sprintf(bufferText, "House 1 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE)->SetWindowTextA(bufferText);


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
		if (houseValue == 0) sprintf(bufferText, "House 2 - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "House 2 - Full");
		else sprintf(bufferText, "House 2 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE2)->SetWindowTextA(bufferText);


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
		if (houseValue == 0) sprintf(bufferText, "House 3 - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "House 3 - Full");
		else sprintf(bufferText, "House 3 - %d/2000", houseValue);
		GetDlgItem(IDC_HOUSE3)->SetWindowTextA(bufferText);





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
		if (houseValue == 0) sprintf(bufferText, "Wear - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "Wear - Full");
		else sprintf(bufferText, "Wear - %d/2000", houseValue);
		GetDlgItem(IDC_WEAR)->SetWindowTextA(bufferText);





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
		if (houseValue == 0) sprintf(bufferText, "School - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "School - Full");
		else sprintf(bufferText, "School - %d/2000", houseValue);
		GetDlgItem(IDC_SCHOOL)->SetWindowTextA(bufferText);





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
		if (houseValue == 0) sprintf(bufferText, "LoveShark - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "LoveShark - Full");
		else sprintf(bufferText, "LoveShark - %d/2000", houseValue);
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
		if (houseValue == 0) sprintf(bufferText, "Tribute - Auto");
		else if (houseValue >= 2000) sprintf(bufferText, "Tribute - Full");
		else sprintf(bufferText, "Tribute - %d/2000", houseValue);
		GetDlgItem(IDC_TRIBUTE)->SetWindowTextA(bufferText);


		int trophies = 0;


		//food   1000
		address = (int*)0x7EE57C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999)
		{
			trophies = 999;
			GhiDuLieu(address, &trophies, 4);
		}
		//food   10000
		address = (int*)0x7EE588;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9999)
		{
			trophies = 9999;
			GhiDuLieu(address, &trophies, 4);
		}
		//food  100000
		address = (int*)0x7EE594;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99999)
		{
			trophies = 99999;
			GhiDuLieu(address, &trophies, 4);
		}
		//food  1000000
		address = (int*)0x7EE5A0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999999)
		{
			trophies = 999999;
			GhiDuLieu(address, &trophies, 4);
		}



		//tech  1000
		address = (int*)0x7EE5AC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999)
		{
			trophies = 999;
			GhiDuLieu(address, &trophies, 4);
		}
		//tech   10000
		address = (int*)0x7EE5B8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9999)
		{
			trophies = 9999;
			GhiDuLieu(address, &trophies, 4);
		}
		//tech  100000
		address = (int*)0x7EE5C4;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99999)
		{
			trophies = 99999;
			GhiDuLieu(address, &trophies, 4);
		}
		//tech   1000000
		address = (int*)0x7EE5D0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 999999)
		{
			trophies = 999999;
			GhiDuLieu(address, &trophies, 4);
		}




		//mushroom  007EE5DC 007EE5E8   007EE5F4
		//mushroom 25;
		address = (int*)0x7EE5DC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 24)
		{
			trophies = 24;
			GhiDuLieu(address, &trophies, 4);
		}
		//mushroom 100;
		address = (int*)0x7EE5E8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			GhiDuLieu(address, &trophies, 4);
		}
		//mushroom 500;
		address = (int*)0x7EE5F4;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 499)
		{
			trophies = 499;
			GhiDuLieu(address, &trophies, 4);
		}



		//rare mushroom  5;
		address = (int*)0x7EE600;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 4)
		{
			trophies = 4;
			GhiDuLieu(address, &trophies, 4);
		}
		//rare mushroom  25;
		address = (int*)0x7EE60C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 24)
		{
			trophies = 24;
			GhiDuLieu(address, &trophies, 4);
		}
		//rare mushroom  100;
		address = (int*)0x7EE618;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			GhiDuLieu(address, &trophies, 4);
		}


		//Relics
		address = (int*)0x7EE624;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 24)
		{
			trophies = 24;
			GhiDuLieu(address, &trophies, 4);
		}

		//		//Science items
		//		address = (int*)0x7EE630;
		//		ReadProcessMemory(handle, address, &trophies, 4, 0);
		//		if (trophies < 25)
		//		{
		//			trophies = 25;
		//			GhiDuLieu(address, &trophies, 4);
		//		}
		//		
		//		//Master collector
		//		address = (int*)0x7EE63C;
		//		ReadProcessMemory(handle, address, &trophies, 4, 0);
		//		if (trophies < 2)
		//		{
		//			trophies = 2;
		//			GhiDuLieu(address, &trophies, 4);
		//		}


		//Heathens 3
		address = (int*)0x7EE660;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 2)
		{
			trophies = 2;
			GhiDuLieu(address, &trophies, 4);
		}

		//Heathens 10
		address = (int*)0x7EE66C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			GhiDuLieu(address, &trophies, 4);
		}


		//		//buom bay
		//		temp = 15;
		//		address = (int*)0x7EE684;
		//		GhiDuLieu(address, &temp, 4);


		//baby girl
		address = (int*)0x7EE6CC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			GhiDuLieu(address, &trophies, 4);
		}

		//baby boy
		address = (int*)0x7EE6D8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			GhiDuLieu(address, &trophies, 4);
		}




		//		//master skill
		//		temp = 10;
		//		address = (int*)0x7EE750;
		//		GhiDuLieu(address, &temp, 4);
		//		
		//		


		//event 10;
		address = (int*)0x7EE7B0;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 9)
		{
			trophies = 9;
			GhiDuLieu(address, &trophies, 4);
		}


		//event 50;
		address = (int*)0x7EE7BC;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			GhiDuLieu(address, &trophies, 4);
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
			GhiDuLieu(address, &trophies, 4);
		}


		//cured = 50;
		address = (int*)0x7EE7F8;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			GhiDuLieu(address, &trophies, 4);
		}


		//cured = 100;
		address = (int*)0x7EE804;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			GhiDuLieu(address, &trophies, 4);
		}



		//dot lua 50
		address = (int*)0x7EE810;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 49)
		{
			trophies = 49;
			GhiDuLieu(address, &trophies, 4);
		}



		//dot lua time
		address = (int*)0x7EE81C;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			GhiDuLieu(address, &trophies, 4);
		}





		//100 bo quan ao
		address = (int*)0x7EE834;
		ReadProcessMemory(handle, address, &trophies, 4, 0);
		if (trophies < 99)
		{
			trophies = 99;
			GhiDuLieu(address, &trophies, 4);
		}




		//		temp = 10;
		//		address = (int*)0x7EE84C;
		//		GhiDuLieu(address, &temp, 4);
		//		
		//		
		//		temp = 10;
		//		address = (int*)0x7EE87C;
		//		GhiDuLieu(address, &temp, 4);
		//		
		//		temp = 50;
		//		address = (int*)0x7EE888;
		//		GhiDuLieu(address, &temp, 4);





		CloseHandle(handle);
	}
}


void CQmodDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQmodDlg::OnPaint()
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQmodDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CQmodDlg::GhiDuLieu(int* address, void* value, int size)
{
	HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
	if (!hwnd) return;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	WriteProcessMemory(handle, address, value, size, 0);
	CloseHandle(handle);
}


void CQmodDlg::OnCollection()
{
	// TODO: Add your control notification handler code here
	HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
	if (!hwnd) return;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);

	int* address = (int*)0x7E93D0;
	char temp = 1;
	for (int i = 0; i < 48; i++, address++)
		WriteProcessMemory(handle, address, &temp, 1, 0);

	address = (int*)0x7EE620;
	GhiDuLieu(address, &temp, 1);

	address = (int*)0x7EE62C;
	GhiDuLieu(address, &temp, 1);

	address = (int*)0x7EE638;
	GhiDuLieu(address, &temp, 1);
}

void CQmodDlg::OnChangeFood()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int* address = (int*)0x7A7730;
	GhiDuLieu(address, &m_food, 4);
}

void CQmodDlg::OnSetfocusFood()
{
	// TODO: Add your control notification handler code here

	HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
	if (!hwnd) return;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, pid);

	int* address = (int*)0x7A7730;
	ReadProcessMemory(handle, address, &m_food, 4, 0);

	if (m_food < 99989)
	{
		m_food += 10;
		int* address = (int*)0x7A7730;
		GhiDuLieu(address, &m_food, 4);
	}
	CloseHandle(handle);

	UpdateData(FALSE);

}

void CQmodDlg::OnOK()
{
	// TODO: Add extra validation here

	//CDialog::OnOK();
}

void CQmodDlg::OnChangeTech()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int* address = (int*)0x7A79E0;
	GhiDuLieu(address, &m_tech, 4);
}

void CQmodDlg::OnSetfocusTech()
{
	// TODO: Add your control notification handler code here
	HWND hwnd = ::FindWindow("Virtual Villagers - New Believers WndCls", "Virtual Villagers - New Believers");
	if (!hwnd) return;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, pid);

	int* address = (int*)0x7A79E0;
	ReadProcessMemory(handle, address, &m_tech, 4, 0);
	if (m_tech < 999899 && m_tech > 100)
	{
		m_tech += 100;
		int* address = (int*)0x7A79E0;
		GhiDuLieu(address, &m_tech, 4);
	}
	else if (m_tech < 90)
	{
		if (m_tech < 1) m_tech = 1;
		m_tech++;
		int* address = (int*)0x7A79E0;
		GhiDuLieu(address, &m_tech, 4);
	}
	CloseHandle(handle);
	UpdateData(FALSE);
}

void CQmodDlg::OnLoveshark()
{
	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EE3D8;
	short int temp = 2000;
	GhiDuLieu(address, &temp, 2);
}

void CQmodDlg::OnSchool()
{
	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EE3E0;
	short int temp = 2000;
	GhiDuLieu(address, &temp, 2);
	temp = 1;
	address = (int*)0x7EE7D0;
	GhiDuLieu(address, &temp, 1);

}

void CQmodDlg::OnWear()
{
	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EE3D0;
	short int temp = 2000;

	GhiDuLieu(address, &temp, 2);
	temp = 1;
	address = (int*)0x7EE7DC;
	GhiDuLieu(address, &temp, 1);
}

void CQmodDlg::OnHouse()
{
	// TODO: Add your control notification handler code here

	int* address = (int*)0x7EE3B8;
	short int temp = 2000;

	GhiDuLieu(address, &temp, 2);
	temp = 1;
	address = (int*)0x7EE7C4;
	GhiDuLieu(address, &temp, 1);
}

void CQmodDlg::OnHouse2()
{
	// TODO: Add your control notification handler code here

	int* address = (int*)0x7EE3C0;
	short int temp = 2000;

	GhiDuLieu(address, &temp, 2);
	temp = 1;
	address = (int*)0x7EE7C4;
	GhiDuLieu(address, &temp, 1);
}

void CQmodDlg::OnHouse3()
{

	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EE3C8;
	short int temp = 2000;

	GhiDuLieu(address, &temp, 2);
	temp = 1;
	address = (int*)0x7EE7C4;
	GhiDuLieu(address, &temp, 1);
}


void CQmodDlg::OnTribute()
{
	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EDC74;
	short int temp = 2000;
	GhiDuLieu(address, &temp, 2);
}

void CQmodDlg::OnTrophies()
{
	// TODO: Add your control notification handler code here
	int* address;
	int temp;

	//food     007EE588   007EE594    007EE5A0 
	temp = 1000;
	address = (int*)0x7EE57C;
	GhiDuLieu(address, &temp, 4);

	temp = 10000;
	address = (int*)0x7EE588;
	GhiDuLieu(address, &temp, 4);

	temp = 100000;
	address = (int*)0x7EE594;
	GhiDuLieu(address, &temp, 4);

	temp = 1000000;
	address = (int*)0x7EE5A0;
	GhiDuLieu(address, &temp, 4);

	//tech     007EE588   007EE594    007EE5A0 
	temp = 1000;
	address = (int*)0x7EE5AC;
	GhiDuLieu(address, &temp, 4);

	temp = 10000;
	address = (int*)0x7EE5B8;
	GhiDuLieu(address, &temp, 4);

	temp = 100000;
	address = (int*)0x7EE5C4;
	GhiDuLieu(address, &temp, 4);

	temp = 1000000;
	address = (int*)0x7EE5D0;
	GhiDuLieu(address, &temp, 4);


	//mushroom  007EE5DC 007EE5E8   007EE5F4
	temp = 25;
	address = (int*)0x7EE5DC;
	GhiDuLieu(address, &temp, 4);

	temp = 100;
	address = (int*)0x7EE5E8;
	GhiDuLieu(address, &temp, 4);

	temp = 500;
	address = (int*)0x7EE5F4;
	GhiDuLieu(address, &temp, 4);


	//rare mushroom   007EE600   007EE60C  007EE618
	temp = 5;
	address = (int*)0x7EE600;
	GhiDuLieu(address, &temp, 4);

	temp = 25;
	address = (int*)0x7EE60C;
	GhiDuLieu(address, &temp, 4);

	temp = 100;
	address = (int*)0x7EE618;
	GhiDuLieu(address, &temp, 4);


	//Relics
	temp = 24;
	address = (int*)0x7EE624;
	GhiDuLieu(address, &temp, 4);

	temp = 24;
	address = (int*)0x7EE630;
	GhiDuLieu(address, &temp, 4);

	temp = 2;
	address = (int*)0x7EE63C;
	GhiDuLieu(address, &temp, 4);

	//heath
	temp = 3;
	address = (int*)0x7EE660;
	GhiDuLieu(address, &temp, 4);

	temp = 10;
	address = (int*)0x7EE66C;
	GhiDuLieu(address, &temp, 4);


	//buom bay
	temp = 15;
	address = (int*)0x7EE684;
	GhiDuLieu(address, &temp, 4);


	//baby girl
	temp = 10;
	address = (int*)0x7EE6CC;
	GhiDuLieu(address, &temp, 4);

	//baby boy
	temp = 10;
	address = (int*)0x7EE6D8;
	GhiDuLieu(address, &temp, 4);

	//master skill
	temp = 10;
	address = (int*)0x7EE750;
	GhiDuLieu(address, &temp, 4);


	//event  007EE7B0  007EE7BC   
	temp = 10;
	address = (int*)0x7EE7B0;
	GhiDuLieu(address, &temp, 4);

	temp = 50;
	address = (int*)0x7EE7BC;
	GhiDuLieu(address, &temp, 4);


	//3house
	temp = 1;
	address = (int*)0x7EE7C4;
	GhiDuLieu(address, &temp, 1);

	//school
	temp = 1;
	address = (int*)0x7EE7D0;
	GhiDuLieu(address, &temp, 1);

	// wear
	temp = 1;
	address = (int*)0x7EE7DC;
	GhiDuLieu(address, &temp, 1);

	//chua benh
	temp = 10;
	address = (int*)0x7EE7EC;
	GhiDuLieu(address, &temp, 4);

	temp = 50;
	address = (int*)0x7EE7F8;
	GhiDuLieu(address, &temp, 4);

	temp = 100;
	address = (int*)0x7EE804;
	GhiDuLieu(address, &temp, 4);

	//dot lua
	temp = 50;
	address = (int*)0x7EE810;
	GhiDuLieu(address, &temp, 4);

	//dot lua time
	temp = 100;
	address = (int*)0x7EE81C;
	GhiDuLieu(address, &temp, 4);

	//100 bo quan ao
	temp = 100;
	address = (int*)0x7EE834;
	GhiDuLieu(address, &temp, 4);

	temp = 10;
	address = (int*)0x7EE84C;
	GhiDuLieu(address, &temp, 4);


	temp = 10;
	address = (int*)0x7EE87C;
	GhiDuLieu(address, &temp, 4);

	temp = 50;
	address = (int*)0x7EE888;
	GhiDuLieu(address, &temp, 4);




}

HBRUSH CQmodDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CQmodDlg::OnMausoleum()
{
	// TODO: Add your control notification handler code here
	int* address = (int*)0x7EE4BC;
	float temp = 1.0f;
	GhiDuLieu(address, &temp, 4);
}

void CQmodDlg::OnTrangweb()
{
	// TODO: Add your control notification handler code here

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








void CQmodDlg::OnFastskill()
{
	//Virtual Villagers - New Believers.exe+3576D - D9 04 8E              - fld dword ptr [esi+ecx*4]
	//Virtual Villagers - New Believers.exe+35770 - D8 44 24 0C           - fadd dword ptr [esp+0C]

	//Virtual Villagers - New Believers.exe+3576D - C7 04 8E  0000C842    - mov [esi+ecx*4],42C80000
	unsigned char dataarr[18] = { 0xC7,0x04,0x8E,0x00,0x00,0xC8,0x42, 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
	GhiDuLieu1(L"Virtual Villagers - New Believers WndCls", L"Virtual Villagers - New Believers", NULL, 0x3576D, dataarr, 18);

}
void CQmodDlg::OnMana()
{
	//Virtual Villagers - New Believers.exe+5A9E3 - 29 86 647D0100        - sub [esi+00017D64],eax
	unsigned char dataarr[1] = { 0x01 };
	GhiDuLieu1(L"Virtual Villagers - New Believers WndCls", L"Virtual Villagers - New Believers", NULL, 0x5A9E3, dataarr, 1);
}
