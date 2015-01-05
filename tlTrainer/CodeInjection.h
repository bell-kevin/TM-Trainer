#pragma once

#include "DllGlobals.h"
#include "cHack.h"
#include "Helper.h"

/*
CCodeInjection

Erstellt an einer Adresse einen Jmp zu einem neu allozierten Bereich mit neuem Code und springt 
anschlie�end zur�ck.
*/
class _declspec(dllexport) CCodeInjection : public CHelper
{
public:
	/*
	Konstruktor
	# setzt Standartwerte (Unwichtig f�r Endnutzer)
	*/
	CCodeInjection(void);

	/*
	Konstruktor
	# setzt Standartwerte und ruft danach direkt die Funktion "void Initialize(...)" auf
	*/
	CCodeInjection(cHack *pHack, UINT_PTR uiAddress, BYTE *pInject, SIZE_T nInjectSize, SIZE_T nOrigJmpSize);

	/*
	Destruktor
	# l�scht Pointer (Unwichtig f�r Endnutzer)
	*/
	~CCodeInjection(void);

	/*
	Initialisierung
	# *pHack		= das eigene Hackobjekt, damit der Codeinject sicher Read-/WriteProcessMemory nutzen kann
	# uiAddress		= an welcher Adresse zum Injected Code gesprungen werden soll
	# *pInject		= Array von Bytes die den Injected Code darstellen
					  WICHTIG: die letzten 5 Bytes m�ssen existieren und werden f�r den Backjump �berschrieben
	# nInjectSize	= Gr��e von pInject (sizeof Operatur nutzen)
	# nOrigJmpSize	= Gr��e des Originals. Mindestens 5. Bei 2+x Befehlen m�ssen beide Befehle im InjectedCode sein 
	*/
	void Initialize(cHack *pHack, UINT_PTR uiAddress, BYTE *pInject, SIZE_T nInjectSize, SIZE_T nOrigJmpSize);



	/*
	Gibt an ob im Moment der Inject aktiviert oder deaktiviert ist
	# return type bool
		- true	= aktiviert
		- false = deaktiviert
	*/
	bool IsInjected(void);

	UINT_PTR GetBaseAddress(void);

	void UpdateCode(BYTE *pbUpdatedCode);

private:
	/*
	Aktiviert den Inject
	# Nur m�glich wenn davor Initialize aufgerufen wurde
	*/
	virtual void EnableFeature(void);

	/*
	Deaktiviert den Inject
	# Nur m�glich wenn davor Initialize aufgerufen wurde
	*/
	virtual void DisableFeature(void);

	// Original zum wiederherstellen
	BYTE *m_pbOriginal;

	// Size of Original
	SIZE_T m_nOrigJmpSize;

	// Injected Code
	BYTE *m_pbInject;

	// Size of Injected Code
	SIZE_T m_nInjectSize;

	// StartAdresse des allozierten Bereichs
	UINT_PTR m_uiBase;

	// An welcher Adresse wird gesprungen
	UINT_PTR m_uiAddress;

	// Erstellt einen Jump-Opcode von einer Startadresse zu einer Endadresse
	void GetJmpOpCode(BYTE OpCodes[], UINT_PTR StartAddress, UINT_PTR EndAddress);
};

