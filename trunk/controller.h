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
	User* loadUser(std::string& username, std::string& password);
	void storeUser(User *user);
	void removeUser(User *user);
	bool deleteUser(User *user);

	Profile* loadProfile(int userID, int discID);
	void storeProfile(Profile *profile);
	void removeProfile(Profile *profile);
	bool deleteProfile(Profile *profile);
	
	Disc* loadDisc(std::string& discName, long discLength, int numChapters);
	void storeDisc(Disc *disc);
	bool deleteDisc(Disc *disc);
	// TODO: should user be able to remove a disc from database?
	//void removeDisc(Disc *disc);

	// controller disc wrapper methods
	void c_setDiscID(Disc *disc, int ID);
	void c_setDiscName(Disc *disc, std::string& name);
	void c_setDiscLength(Disc *disc, long length);
	void c_setDiscChapterNum(Disc *disc, int chapters);
	void c_setDiscRating(Disc *disc, int rating);
	
	// controller user wrapper methods
	void c_setUserID(User *user, int ID);
	void c_setUser(User *user, std::string& username);
	void c_setUserPasswordHash(User *user, std::string& hash);
	void c_setUserIcon(User *user, std::string& file);
	void c_setUserCanPlayUnknown(User *user, bool flag);
	void c_setUserMaxPlayLevel(User *user, int level);
	void c_setUserLastMovieID(User *user, int ID);
	void c_setUserLastMoviePos(User *user, long position);
	
	// controller skip wrapper methods - replaced by non-wrapper method
	/*
	void c_setSkipStart(long start);
	void c_setSkipStop(long stop);
	void c_setAudioOnly(bool isAudio); // rename?
	*/
	
	// controller profile wrapper methods
	void c_setProfileID(Profile *profile, int ID);
	void c_profileSetUserID(Profile *profile, int ID);
	void c_profileSetDiscID(Profile *profile, int ID);
	void c_addSkipChapter(Profile *profile, int chapter);
	void c_removeSkipChapter(Profile *profile, int chapter);
	// replaced by non-wrapper method
	/*
	void c_addSkipTime(Profile *profile, SkipTime skip_time); // yes, not a pointer
	void c_removeSkipTime(Profile *profile, SkipTime skip_time);
	*/
	
	// controller skip method (not wrapper) PROBABLY BETTER?
	void addSkipTiming(Profile *profile, long start, long stop, bool onlyAudio); 
	
/* if we were to know EXACTLY which objects we are going to create, this could work:
private:
	Disc *theDisc;
	User *userLoggedIn;
	User *otherUser; // what's the other user object for?
	Profile *theProfile;
*/
};

#endif
