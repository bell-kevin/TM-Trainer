#pragma once

#include "Globals.h"
#include "Setting.h"

class CPage
{
public:
	CPage(void);
	~CPage(void);

	std::vector<CSetting*> m_vecSettings;

	// ID der Seite
	int m_iID;
	// Welche der 3 Settings ist zurzeit ausgew�hlt
	int m_iCurrentSelection;

	// Select Arrow (Pfeil links vom Eintrag)
	HANDLE m_hSelectArrow;
	// NextPage Arrow
	HANDLE m_hNextArrow;
	// PrevPage Arrow
	HANDLE m_hPrevArrow;
	// Down Select Arrow
	HANDLE m_hDownArrow;
	// Action Circle
	HANDLE m_hCircleButton;

	// Leitet den Tastendruck weiter
	void DoAction(void);
	// F�gt ein Setting hinzu -> zur�ck: true wenn aufgenommen, false wenn abgewiesen
	bool AddSetting(HWND phHwndDlg, int iID, char* pszName);
	// wird aufgerufen wenn die Settings Selektion ge�ndert werden soll
	void SelectionChange(void);
};

