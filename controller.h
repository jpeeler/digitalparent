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
 
#include "data_structure.h"
 
class Controller
{
public:
	User* loadUser(std::string username, std::string password);
	void storeUser(User *user);
	void removeUser(User *user);

	Profile* loadProfile(int userID, int discID);
	void storeProfile(Profile *profile);
	void removeProfile(Profile *profile);
	
	Disc* loadDisc(std::string discName, long discLength, int numChapters);
	void storeDisc(Disc *disc);
	// TODO: should user be able to remove a disc from database?
	//void removeDisc(Disc *disc);
private:
	DataStructure m_data; // entire data structure
};
