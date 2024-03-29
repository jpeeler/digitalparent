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
#include "database.h"

#include <string>

typedef enum {
	DP_STOP,
	DP_START,
	DP_RUNONCE,
	DP_LOGIN,
	DP_ADMIN_PANEL,
	DP_USER_PANEL,
	DP_USER_PLAY,
	DP_ADMIN_PLAY
} DP_STATE;


class Controller
{
public:
	int loadCurrentUser(std::string username, std::string password);
	int loadCurrentUserWithAnswer(std::string username, std::string answer);
	int storeCurrentUser();
	int storeOtherUser();
	int deleteOtherUser();

	int loadProfile();
	int storeProfile();
	int deleteProfile();
	
	int loadDisc();
	int storeDisc();

	int populateUserInfo(std::string username);

	std::vector <std::string> getUserList();
	std::vector <std::string> getIconList();

	// in this case, reference to string input required
	bool hashString(std::string& input);

	DP_STATE dp_state;
	std::string img_dir;
	std::string pixmaps_dir;

	// controller disc wrapper methods
	void c_setDiscID(int ID);
	void c_setDiscName(std::string name);
	void c_setDiscSerial(std::string serial);
	void c_setDiscLength(long length);
	void c_setDiscChapterNum(int chapters);
	void c_setDiscRating(int rating);
	
	// controller user wrapper methods
	void c_setCurrentUserID(int ID);
	void c_setCurrentUser(std::string username);
	void c_setCurrentUserPasswordHash(std::string hash);
	void c_setCurrentUserSecretQuestion(std::string question);
	void c_setCurrentUserSecretAnswerHash(std::string answer);
	void c_setCurrentUserIcon(std::string file);
	void c_setCurrentUserCanPlayUnknown(bool flag);
	void c_setCurrentUserMaxPlayLevel(int level);
	void c_setCurrentUserLastMovieID(int ID);
	void c_setCurrentUserLastMoviePos(long position);
	
	// controller other user wrapper methods
	void c_setOtherUserID(int ID);
	void c_setOtherUser(std::string username);
	void c_setOtherUserPasswordHash(std::string hash);
	void c_setOtherUserSecretQuestion(std::string question);
	void c_setOtherUserSecretAnswerHash(std::string answer);
	void c_setOtherUserIcon(std::string file);
	void c_setOtherUserCanPlayUnknown(bool flag);
	void c_setOtherUserMaxPlayLevel(int level);
	void c_setOtherUserLastMovieID(int ID);
	void c_setOtherUserLastMoviePos(long position);
	
	// controller profile wrapper methods
	void c_setProfileID(int ID);
	void c_profileSetUserID(int ID);
	void c_profileSetDiscID(int ID);
	void c_addSkipChapter(int chapter);
	void c_removeSkipChapter(int chapter);
	void c_clearSkipVectors();
	
	// data structure class wrapper methods
	const Disc* c_getDisc() const;
	void c_clearDisc();
	const User* c_getUserLoggedIn() const;
	void c_clearUserLoggedIn();
	const User* c_getUserOther() const;
	void c_clearUserOther();
	const Profile* c_getProfile() const;
	void c_clearProfile();
	
	// replaced by non-wrapper method
	/*
	void c_setSkipStart(long start);
	void c_setSkipStop(long stop);
	void c_setAudioOnly(bool isAudio); // rename?
	
	void c_addSkipTime(Profile *profile, SkipTime skip_time); // yes, not a pointer
	void c_removeSkipTime(Profile *profile, SkipTime skip_time);
	*/
	
	// controller skip method (not wrapper) PROBABLY BETTER?
	void c_addSkipTiming(long start, long stop/*, bool onlyAudio*/);
	
	friend class TestController; // (allows access to m_data in test class)
	
private:
	DataStructure m_data;
	Database m_database; 
	void dvd_read_info(char *name, char *serial, long *length, int *numChapters);
};

class TestController
{
public:
	static void do_test();
};

#endif
