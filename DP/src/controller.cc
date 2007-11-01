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

#include <mhash.h>
#include <string>
#include "controller.h"
#include "database.h"


// wrappers to database methods
int Controller::loadCurrentUser(std::string username, std::string password)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
	user->setPasswordHash(password);
	return(m_database.getUser(user));
}

int Controller::loadCurrentUserWithAnswer(std::string& username, std::string& answer)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
	user->setAnswer(answer);
	return(m_database.getUserUsingAnswer(user));
}

int Controller::storeCurrentUser()
{
	User* user = m_data.getUserLoggedIn();
	return (m_database.storeUser(user));
}

int Controller::deleteCurrentUser()
{
	User* user = m_data.getUserLoggedIn();
	return (m_database.deleteUser(user));
}
// -------------------------------------
int Controller::loadProfile(int userID, int discID)
{
	Profile* profile = m_data.getProfile();
	profile->setUserID(userID);
	profile->setDiscID(discID);
	return (m_database.getProfile(profile));
}

int Controller::storeProfile()
{
	Profile* profile = m_data.getProfile();
	return (m_database.storeProfile(profile));
}

int Controller::deleteProfile()
{
	Profile* profile = m_data.getProfile();
	return (m_database.deleteProfile(profile));
}

// -------------------------------------
int Controller::loadDisc(std::string& discName, long discLength, int numChapters)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscName(discName);
	disc->setDiscLength(discLength);
	disc->setDiscChapterNum(numChapters);
	return (m_database.getDisc(disc));
}

int Controller::storeDisc()
{
	Disc* disc = m_data.getDisc();
	return (m_database.storeDisc(disc));
}

int Controller::populateUserInfo(std::string& username)
{
	User* user = m_data.getUserOther();
	return (m_database.getUserForEdit(user));
}

std::vector <std::string> Controller::getUserList()
{
	return (m_database.getUserList());
}

std::vector <std::string> Controller::getIconList()
{
	return (m_database.getIconList());
}


bool hashString(std::string& input) 
{
	uint i;
	MHASH td;
	std::string output;
	unsigned char *hash;
	char *hashOut;

	td = mhash_init(MHASH_SHA1);

	if(td == MHASH_FAILED)
		return false;
	
	mhash(td, input.c_str(), input.size());

	hash = (unsigned char*) mhash_end(td);

	for (i = 0; i < mhash_get_block_size(MHASH_SHA1); i++) {
		sprintf(hashOut, "%.2x", hash[i]);
		output.append(hashOut);
	}

	input = output;

	return true;
}
// -------------------------------------
// wrappers of disc
void Controller::c_setDiscID(int ID)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscID(ID);
}

void Controller::c_setDiscName(std::string& name)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscName(name);
}

void Controller::c_setDiscLength(long length)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscLength(length);
}

void Controller::c_setDiscChapterNum(int chapters)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscChapterNum(chapters);
}

void Controller::c_setDiscRating(int rating)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscRating(rating);
}

// wrappers for user logged in
void Controller::c_setCurrentUserID(int ID)
{
	User* user = m_data.getUserLoggedIn();
	user->setUserID(ID);
}

void Controller::c_setCurrentUser(std::string username)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
}

void Controller::c_setCurrentUserPasswordHash(std::string hash)
{
	User* user = m_data.getUserLoggedIn();
	user->setPasswordHash(hash);
}

void Controller::c_setCurrentUserSecretQuestion(std::string question)
{
	User* user = m_data.getUserLoggedIn();
	user->setQuestion(question);
}

void Controller::c_setCurrentUserSecretAnswerHash(std::string answer)
{
	User* user = m_data.getUserLoggedIn();
	user->setAnswer(answer);
}

void Controller::c_setCurrentUserIcon(std::string file)
{
	User* user = m_data.getUserLoggedIn();
	user->setUserIcon(file);
}

void Controller::c_setCurrentUserCanPlayUnknown(bool flag)
{
	User* user = m_data.getUserLoggedIn();
	user->setPlayUnknownDisc(flag);
}

void Controller::c_setCurrentUserMaxPlayLevel(int level)
{
	User* user = m_data.getUserLoggedIn();
	user->setMaxPlayLevel(level);
}

void Controller::c_setCurrentUserLastMovieID(int ID)
{
	User* user = m_data.getUserLoggedIn();
	user->setLastMovieID(ID);
}

void Controller::c_setCurrentUserLastMoviePos(long position)
{
	User* user = m_data.getUserLoggedIn();
	user->setLastMoviePos(position);
}

// controller other user wrapper methods
void Controller::c_setOtherUserID(int ID)
{
	User* user = m_data.getUserLoggedIn();
	user->setUserID(ID);
}

void Controller::c_setOtherUser(std::string& username)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
}

void Controller::c_setOtherUserPasswordHash(std::string& hash)
{
	User* user = m_data.getUserLoggedIn();
	user->setPasswordHash(hash);
}

void Controller::c_setOtherUserIcon(std::string& file)
{
	User* user = m_data.getUserLoggedIn();
	user->setUserIcon(file);
}

void Controller::c_setOtherUserCanPlayUnknown(bool flag)
{
	User* user = m_data.getUserLoggedIn();
	user->setPlayUnknownDisc(flag);
}

void Controller::c_setOtherUserMaxPlayLevel(int level)
{
	User* user = m_data.getUserLoggedIn();
	user->setMaxPlayLevel(level);
}

void Controller::c_setOtherUserLastMovieID(int ID)
{
	User* user = m_data.getUserLoggedIn();
	user->setLastMovieID(ID);
}

void Controller::c_setOtherUserLastMoviePos(long position)
{
	User* user = m_data.getUserLoggedIn();
	user->setLastMoviePos(position);
}

// controller profile wrapper methods
void Controller::c_setProfileID(int ID)
{
	Profile* profile = m_data.getProfile();
	profile->setProfileID(ID);
}

void Controller::c_profileSetUserID(int ID)
{
	Profile* profile = m_data.getProfile();
	profile->setUserID(ID);
}

void Controller::c_profileSetDiscID(int ID)
{
	Profile* profile = m_data.getProfile();
	profile->setDiscID(ID);
}

void Controller::c_addSkipChapter(int chapter)
{
	Profile* profile = m_data.getProfile();
	profile->addSkipChapter(chapter);
}

void Controller::c_removeSkipChapter(int chapter)
{
	Profile* profile = m_data.getProfile();
	profile->removeSkipChapter(chapter);
}

// controller skip method (not wrapper) PROBABLY BETTER?
void Controller::addSkipTiming(long start, long stop/*, bool onlyAudio*/)
{
	Profile* profile = m_data.getProfile();
	
	SkipTime askiptime;
	askiptime.setSkipStart(start);
	askiptime.setSkipStop(stop);
	//askiptime.setAudioOnly(onlyAudio);
	
	profile->addSkipTime(askiptime);
}

//DataStructure wrapper methods
const Disc* Controller::c_getDisc() const
{
	return m_data.getDisc();
}

void Controller::c_clearDisc()
{
	Disc* disc = m_data.getDisc();
	disc->clear();
}
	
const User* Controller::c_getUserLoggedIn() const
{
	return m_data.getUserLoggedIn();
}

void Controller::c_clearUserLoggedIn()
{
	User* user = m_data.getUserLoggedIn();
	user->clear();
}

const User* Controller::c_getUserOther() const
{
	return m_data.getUserOther();
}

void Controller::c_clearUserOther()
{
	User *other = m_data.getUserOther();
	other->clear();
}

const Profile* Controller::c_getProfile() const
{
	return m_data.getProfile();
}

void Controller::c_clearProfile()
{
	Profile *profile = m_data.getProfile();
	profile->clear();
}

void TestController::do_test()
{
	Controller theController;
	//const User* constUser = theController.m_data.getUserLoggedIn();
	//using setter method with const pointer should fail
	//constUser->setUserID(5);
	std::string usern="testuser";
	std::string passw="testpass";
	std::string file="/dev/null";
	
	theController.c_setCurrentUser(usern);
	theController.c_setCurrentUserPasswordHash(passw);
	theController.c_setCurrentUserIcon(file);
	theController.c_setCurrentUserCanPlayUnknown(true);
	theController.c_setCurrentUserMaxPlayLevel(4);
	
	
	User *user = theController.m_data.getUserLoggedIn();
	theController.storeCurrentUser();
	
	printf("Before database load:\n");
	printf("User ID = %d\n",user->getUserID());
	printf("Username = %s\n",user->getUser().c_str());
	printf("Password = %s\n",user->getPasswordHash().c_str());
	printf("Icon file = %s\n",user->getUserIcon().c_str());
	printf("Play unknown? %d\n",user->getPlayUnknownDisc());
	printf("Max play level = %d\n",user->getMaxPlayLevel());
	printf("Last movie ID = %d\n",user->getLastMovieID());
	printf("Last movie position = %ld\n",user->getLastMoviePos());
	
	theController.loadCurrentUser(usern,passw);
	
	printf("\nAfter database load (should be identical):\n");
	printf("User ID = %d\n",user->getUserID());
	printf("Username = %s\n",user->getUser().c_str());
	printf("Password = %s\n",user->getPasswordHash().c_str());
	printf("Icon file = %s\n",user->getUserIcon().c_str());
	printf("Play unknown? %d\n",user->getPlayUnknownDisc());
	printf("Max play level = %d\n",user->getMaxPlayLevel());
	printf("Last movie ID = %d\n",user->getLastMovieID());
	printf("Last movie position = %ld\n",user->getLastMoviePos());	
	
}
