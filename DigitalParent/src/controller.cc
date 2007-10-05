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
 
#include "controller.h"
#include <string>
#include "database.h"

// wrappers to database methods
int Controller::loadCurrentUser(std::string& username, std::string& password)
{
	// call database methods to fetch info, change this
	User* user = m_data.getUserLoggedIn();
	user->setUserID(1);
	user->setPasswordHash(password);
	user->setUser(username);	
	return 0;
}

bool Controller::storeCurrentUser()
{
	return true;
}

bool Controller::deleteCurrentUser()
{
	return true;
}
// -------------------------------------
int Controller::loadProfile(int userID, int discID)
{
	return 0;
}

bool Controller::storeProfile()
{
	return true;
}

bool Controller::deleteProfile()
{
	return true;
}
// -------------------------------------
int Controller::loadDisc(std::string& discName, long discLength, int numChapters)
{
	return 0;
}

bool Controller::storeDisc()
{
	return true;
}

bool Controller::deleteDisc()
{
	return true;
}
// -------------------------------------
// wrappers of data structures
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

void Controller::c_setCurrentUserID(int ID)
{
	User* user = m_data.getUserLoggedIn();
	user->setUserID(ID);
}

void Controller::c_setCurrentUser(std::string& username)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
}

void Controller::c_setCurrentUserPasswordHash(std::string& hash)
{
	User* user = m_data.getUserLoggedIn();
	user->setPasswordHash(hash);
}

void Controller::c_setCurrentUserIcon(std::string& file)
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
void Controller::addSkipTiming(long start, long stop, bool onlyAudio)
{
	Profile* profile = m_data.getProfile();
	
	SkipTime askiptime;
	askiptime.setSkipStart(start);
	askiptime.setSkipStop(stop);
	askiptime.setAudioOnly(onlyAudio);
	
	profile->addSkipTime(askiptime);
}

void TestController::do_test()
{
	Controller theController;
	const User* constUser = theController.m_data.getUserLoggedIn();
	std::string usern="test";
	std::string passw="pass";
	theController.loadCurrentUser(usern,passw);
	theController.c_setCurrentUserID(3);
	//using setter method with const pointer should fail
	//constUser->setUserID(5);
	printf("User ID = %d\n",constUser->getUserID());
	printf("Username = %s\n",constUser->getUser().c_str());
}
