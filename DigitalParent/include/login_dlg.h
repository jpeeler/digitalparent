/***************************************************************************
 *            login_dlg.h
 *
 *  Tue Oct  9 23:39:07 2007
 *  Copyright  2007  Jeremy Morey
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
 

#include <vector>
#include <string>
#include "data_structure.h"

#ifndef __LOGINDLG__
#define __LOGINDLG__

class LoginDlg
{
	public:
		LoginDlg();	
		~LoginDlg();
	
		int GetLogin(const std::vector<User> *users);
		bool Hide();			
	
	private:		
		const std::vector<User> *m_users;
		std::string GetPassword();
};
	
	

#endif //__LOGINDLG__
