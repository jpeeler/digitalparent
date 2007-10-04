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
User* Controller::loadUser(std::string& username, std::string& password)
{
	// call database methods to fetch info, change this
	User *auser = new User();
	auser->setUserID(1);
	auser->setPasswordHash(password);
	auser->setUser(username);	
	return auser;
}

void Controller::storeUser(User *user)
{
	
}

void Controller::removeUser(User *user)
{
	
}

bool Controller::deleteUser(User *user)
{
	
}
// -------------------------------------
Profile* Controller::loadProfile(int userID, int discID)
{
	
}

void Controller::storeProfile(Profile *profile)
{
	
}

void Controller::removeProfile(Profile *profile)
{
	
}

bool Controller::deleteProfile(Profile *profile)
{
	
}
// -------------------------------------
Disc* Controller::loadDisc(std::string& discName, long discLength, int numChapters)
{
	
}

void Controller::storeDisc(Disc *disc)
{
	
}

bool Controller::deleteDisc(Disc *disc)
{
	
}
// -------------------------------------
// wrappers of data structures
void Controller::c_setDiscName(Disc *disc, std::string& name)
{
	disc->setDiscName(name);
}

void Controller::c_setDiscLength(Disc *disc, long length)
{
	disc->setDiscLength(length);
}

void Controller::c_setDiscChapterNum(Disc *disc, int chapters)
{
	disc->setDiscChapterNum(chapters);
}

void Controller::c_setDiscRating(Disc *disc, int rating)
{
	disc->setDiscRating(rating);
}

void Controller::c_setUserID(User *user, int ID)
{
	user->setUserID(ID);
}

void Controller::c_setUser(User *user, std::string& username)
{
	user->setUser(username);
}

void Controller::c_setUserPasswordHash(User *user, std::string& hash)
{
	user->setPasswordHash(hash);
}

void Controller::c_setUserIcon(User *user, std::string& file)
{
	user->setUserIcon(file);
}

void Controller::c_setUserCanPlayUnknown(User *user, bool flag)
{
	user->setPlayUnknownDisc(flag);
}

void Controller::c_setUserMaxPlayLevel(User *user, int level)
{
	user->setMaxPlayLevel(level);
}

void Controller::c_setUserLastMovieID(User *user, int ID)
{
	user->setLastMovieID(ID);
}

void Controller::c_setUserLastMoviePos(User *user, long position)
{
	user->setLastMoviePos(position);
}

// controller profile wrapper methods
void Controller::c_setProfileID(Profile *profile, int ID)
{
	profile->setProfileID(ID);
}

void Controller::c_profileSetUserID(Profile *profile, int ID)
{
	profile->setUserID(ID);
}

void Controller::c_profileSetDiscID(Profile *profile, int ID)
{
	profile->setDiscID(ID);
}

void Controller::c_addSkipChapter(Profile *profile, int chapter)
{
	profile->addSkipChapter(chapter);
}

void Controller::c_removeSkipChapter(Profile *profile, int chapter)
{
	profile->removeSkipChapter(chapter);
}

// controller skip method (not wrapper) PROBABLY BETTER?
void Controller::addSkipTiming(Profile *profile, long start, long stop, bool onlyAudio)
{
	SkipTime askiptime;
	askiptime.setSkipStart(start);
	askiptime.setSkipStop(stop);
	askiptime.setAudioOnly(onlyAudio);
	
	profile->addSkipTime(askiptime);
}

// TODO: make testbench an object
int c_testbench()
{
	Controller theController;
	std::string usern="test";
	std::string passw="pass";
	User* auser = theController.loadUser(usern,passw);
	theController.c_setUserID(auser, 3);
	//auser->setUserID(5);
	printf("%d",auser->getUserID());
	printf("%s",auser->getUser().c_str());
	delete(auser);
	
	return 0;
}
