/***************************************************************************
 *            login_dlg.c
 *
 *  Tue Oct  9 23:39:25 2007
 *  Copyright  2007  User
 *  Email
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "login_dlg.h"
#include "data_structure.h"

LoginDlg::LoginDlg()
{
	
}

LoginDlg::~LoginDlg()
{
	
}

int LoginDlg::GetLogin(const std::vector<User> *users)
{	
	m_users = users;
	int temp = 1;
	return temp;
}

bool LoginDlg::Hide()
{
	return true;
}

std::string LoginDlg::GetPassword()
{
	std::string psswrd = "";
	return psswrd;
}
