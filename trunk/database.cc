/***************************************************************************
 *            database.cc
 *
 *  Fri Sep 28 11:54:13 2007
 *  Email pwightm@clemson.edu
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
 
 
 #include "database.h"
 
 Database::Database()
{
	// TODO: put constructor code here
	try {
		conn = tntdb::connect("sqlite:DigitalParentDB");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}


Database::~Database()
{
	// TODO: put destructor code here
}

Profile Database::getProfile(int diskID, int userID)
{
	Profile outProfile;
	
	return outProfile;
}

bool Database::storeProfile(Profile *profile)
{
	return true;
}

bool Database::removeProfile(Profile *profile)
{
	return true;
}

User Database::getUser(std::string& username, std::string& password)
{
	User outUser;
	
	return outUser;
	
}

bool Database::removeUser(User *user)
{
	return true;
}

bool Database::storeDisc(Disc *discInfo)
{
	return true;
}

Disc Database::getDisc(std::string& discName, int numChapters, long discLength)
{
	Disc outDisc;
	
	return outDisc;
}
