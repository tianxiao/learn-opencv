#include "StdAfx.h"
#include "xtCharHelp.h"

#include <Windows.h>

xtCharHelp::xtCharHelp(void)
{
}


xtCharHelp::~xtCharHelp(void)
{
}

char *xtCharHelp::WCharToCharPtr(_TCHAR *tstr)
{
	unsigned int tcharnum = _tcslen( tstr );
	unsigned int buffersize = 100;
	char *newchar = new char[buffersize];
	unsigned int convertedChars = 0;
	wcstombs_s(&convertedChars, newchar,tcharnum+1, tstr,buffersize);

	return newchar;
}
