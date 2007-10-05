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
 
#ifndef CONTROLLER_H
#define CONTROLLER_H
 
#include "data_structure.h"
 
class Controller
{
public:
	int loadCurrentUser(std::string& username, std::string& password);
	bool storeCurrentUser();
	bool deleteCurrentUser();

	int loadProfile(int userID, int discID);
	bool storeProfile();
	bool deleteProfile();
	
	int loadDisc(std::string& discName, long discLength, int numChapters);
	bool storeDisc();
	bool deleteDisc();
	// TODO: should user be able to remove a disc from database?
	//void removeDisc(Disc *disc);

	// controller disc wrapper methods
	void c_setDiscID(int ID);
	void c_setDiscName(std::string& name);
	void c_setDiscLength(long length);
	void c_setDiscChapterNum(int chapters);
	void c_setDiscRating(int rating);
	
	// controller user wrapper methods
	void c_setCurrentUserID(int ID);
	void c_setCurrentUser(std::string& username);
	void c_setCurrentUserPasswordHash(std::string& hash);
	void c_setCurrentUserIcon(std::string& file);
	void c_setCurrentUserCanPlayUnknown(bool flag);
	void c_setCurrentUserMaxPlayLevel(int level);
	void c_setCurrentUserLastMovieID(int ID);
	void c_setCurrentUserLastMoviePos(long position);
	
	// TODO: need to set options on other user object?
	
	// controller profile wrapper methods
	void c_setProfileID(int ID);
	void c_profileSetUserID(int ID);
	void c_profileSetDiscID(int ID);
	void c_addSkipChapter(int chapter);
	void c_removeSkipChapter(int chapter);
	
	// replaced by non-wrapper method
	/*
	void c_setSkipStart(long start);
	void c_setSkipStop(long stop);
	void c_setAudioOnly(bool isAudio); // rename?
	
	void c_addSkipTime(Profile *profile, SkipTime skip_time); // yes, not a pointer
	void c_removeSkipTime(Profile *profile, SkipTime skip_time);
	*/
	
	// controller skip method (not wrapper) PROBABLY BETTER?
	void addSkipTiming(long start, long stop, bool onlyAudio);
	
	friend class TestController; // (allows access to m_data in test class)
	
private:
	DataStructure m_data;
};

class TestController
{
public:
	static void do_test();
};

#endif
