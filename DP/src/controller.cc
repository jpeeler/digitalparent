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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DVD_VIDEO_LB_LEN 2048
#define MSG_OUT stdout

// wrappers to database methods
int Controller::loadCurrentUser(std::string username, std::string password)
{
	User* user = m_data.getUserLoggedIn();
	user->setUser(username);
	user->setPasswordHash(password);
	return(m_database.getUser(user));
}

int Controller::loadCurrentUserWithAnswer(std::string username, std::string answer)
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

int Controller::storeOtherUser()
{
	User* user = m_data.getUserOther();
	return (m_database.storeUser(user));
}

int Controller::deleteOtherUser()
{
	User* user = m_data.getUserOther();
	return (m_database.deleteUser(user));
}
// -------------------------------------
int Controller::loadProfile()
{
	int userID;
	int discID;
	
	discID = m_data.getDisc()->getDiscID();
	
	if (m_data.getUserOther()->getUser() != "")
	{
		// other user object not null, so load profile for that user
		userID = m_data.getUserOther()->getUserID();
	}
	else
	{
		// other user object not used, load profile for current user
		userID = m_data.getUserLoggedIn()->getUserID();
	}
	
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

void Controller::dvd_read_info(char *name, char *serial, long *length, int *numChapters)
{
	const char *device = "/dev/dvd";
//end my code

    /* Because we are compiling with _FILE_OFFSET_BITS=64
     * all off_t are 64bit.
     */
    off_t off;
    int fd, i;
    //uint8_t data[DVD_VIDEO_LB_LEN];
	char data[DVD_VIDEO_LB_LEN];

    /* Read DVD name */
    fd = open(device, O_RDONLY);
    if (fd > 0) { 
      off = lseek( fd, 32 * (off_t) DVD_VIDEO_LB_LEN, SEEK_SET );
      if( off == ( 32 * (off_t) DVD_VIDEO_LB_LEN ) ) {
        off = read( fd, data, DVD_VIDEO_LB_LEN ); 
        close(fd);
        if (off == ( (off_t) DVD_VIDEO_LB_LEN )) {
          fprintf(MSG_OUT, "libdvdnav: DVD Title: ");
          for(i=25; i < 73; i++ ) {
            if((data[i] == 0)) break;
            if((data[i] > 32) && (data[i] < 127)) {
              fprintf(MSG_OUT, "%c", data[i]);
            } else {
              fprintf(MSG_OUT, " ");
            }
          }
          strncpy(name, &data[25], 48);
          name[48] = 0;
          fprintf(MSG_OUT, "\nlibdvdnav: DVD Serial Number: ");
          for(i=73; i < 89; i++ ) {
            if((data[i] == 0)) break;
            if((data[i] > 32) && (data[i] < 127)) {
              fprintf(MSG_OUT, "%c", data[i]);
            } else {
              fprintf(MSG_OUT, " ");
            } 
          }
//start my code
	  strncpy(serial, &data[73], 16);
          serial[16] = 0;
//end my code
          fprintf(MSG_OUT, "\nlibdvdnav: DVD Title (Alternative): ");
          for(i=89; i < 128; i++ ) {
            if((data[i] == 0)) break;
            if((data[i] > 32) && (data[i] < 127)) {
              fprintf(MSG_OUT, "%c", data[i]);
            } else {
              fprintf(MSG_OUT, " ");
            }
          }
          fprintf(MSG_OUT, "\n");
        } else {
          fprintf(MSG_OUT, "libdvdnav: Can't read name block. Probably not a DVD-ROM device.\n");
        }
      } else {
        fprintf(MSG_OUT, "libdvdnav: Can't seek to block %u\n", 32 );
      }
      close(fd);
    } else {
    fprintf(MSG_OUT, "NAME OPEN FAILED\n");
  }
  
  // get length and num chapters
  
	FILE *ptr;
	char lengthString[35];
	long hours, minutes, seconds, decimal;
	char buf[4];

	if((ptr = popen("lsdvd | grep -o -E \"Length: .* Chapters: [0-9]*,\"", "r")) != NULL) {
		fgets(lengthString, 35, ptr);
	}

	//do hours
	buf[0] = '0';
	buf[1] = lengthString[8];
	buf[2] = lengthString[9];
	buf[3] = '\0';
	hours = strtol(buf, NULL, 10);

	//do minutes
	buf[0] = '0';
	buf[1] = lengthString[11];
	buf[2] = lengthString[12];
	buf[3] = '\0';
	minutes = strtol(buf, NULL, 10);

	//do seconds
	buf[0] = '0';
	buf[1] = lengthString[14];
	buf[2] = lengthString[15];
	buf[3] = '\0';
	seconds = strtol(buf, NULL, 10);

	//do decimal
	buf[0] = lengthString[17];
	buf[1] = lengthString[18];
	buf[2] = lengthString[19];
	buf[3] = '\0';
	decimal = strtol(buf, NULL, 10);

	*length = decimal + 1000 * (seconds + 60 * minutes + 3600 * hours);

	//do chapters
	buf[0] = '0';
	buf[1] = lengthString[31];
	buf[2] = lengthString[32];
	buf[3] = '\0';
	*numChapters = strtol(buf, NULL, 10);

	printf("lsdvd: %s\n", lengthString);

  	pclose(ptr);  
}


// -------------------------------------
int Controller::loadDisc()
{// TODO: check first if disc is in drive
	// get the disc_name and disc_serial straight from the DVD
	char disc_name[50];
	char disc_serial[25];
	long discLength;
	int discNumChapters;
	
	dvd_read_info(disc_name, disc_serial, &discLength, &discNumChapters);
	
	// create C++ strings and set them in disc object
	std::string discName(disc_name);
	std::string discSerial(disc_serial);
	Disc* disc = m_data.getDisc();
	disc->setDiscName(discName);
	disc->setDiscSerial(discSerial);
	disc->setDiscLength(discLength);
	disc->setDiscChapterNum(discNumChapters);
	return (m_database.storeDisc(disc));
}

int Controller::storeDisc()
{
	Disc* disc = m_data.getDisc();
	return (m_database.storeDisc(disc));
}

int Controller::populateUserInfo(std::string username)
{
	User* user = m_data.getUserOther();
	user->setUser(username);
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
	char hashOut[40] = "";

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

void Controller::c_setDiscName(std::string name)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscName(name);
}

void Controller::c_setDiscSerial(std::string serial)
{
	Disc* disc = m_data.getDisc();
	disc->setDiscSerial(serial);
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
	User* user = m_data.getUserOther();
	user->setUserID(ID);
}

void Controller::c_setOtherUser(std::string username)
{
	User* user = m_data.getUserOther();
	user->setUser(username);
}

void Controller::c_setOtherUserPasswordHash(std::string hash)
{
	User* user = m_data.getUserOther();
	user->setPasswordHash(hash);
}

void Controller::c_setOtherUserSecretQuestion(std::string question)
{
	User* user = m_data.getUserOther();
	user->setQuestion(question);
}
	
void Controller::c_setOtherUserSecretAnswerHash(std::string answer)
{
	User* user = m_data.getUserOther();
	user->setAnswer(answer);
}

void Controller::c_setOtherUserIcon(std::string file)
{
	User* user = m_data.getUserOther();
	user->setUserIcon(file);
}

void Controller::c_setOtherUserCanPlayUnknown(bool flag)
{
	User* user = m_data.getUserOther();
	user->setPlayUnknownDisc(flag);
}

void Controller::c_setOtherUserMaxPlayLevel(int level)
{
	User* user = m_data.getUserOther();
	user->setMaxPlayLevel(level);
}

void Controller::c_setOtherUserLastMovieID(int ID)
{
	User* user = m_data.getUserOther();
	user->setLastMovieID(ID);
}

void Controller::c_setOtherUserLastMoviePos(long position)
{
	User* user = m_data.getUserOther();
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

void Controller::c_clearSkipVectors()
{
	Profile *profile = m_data.getProfile();
	profile->clearSkipVectors();
}

// controller skip method (not wrapper) PROBABLY BETTER?
void Controller::c_addSkipTiming(long start, long stop/*, bool onlyAudio*/)
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
	
	theController.c_addSkipTiming(1, 2);
	theController.c_addSkipTiming(17,18);
	theController.c_addSkipTiming(29,30);
	theController.c_addSkipTiming(12,13);
	theController.c_addSkipTiming(15,26);
	
	// get skip times from data structure (reference to skiptimes vector)
	const Profile *aprofile = theController.c_getProfile();
	const std::vector<SkipTime>& myvector = aprofile->getSkipTimes();
	
	// access all skiptimes	
	for (std::vector<SkipTime>::const_iterator it = myvector.begin();
		it!=myvector.end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	
	// access specific skiptimes
	printf("[%ld-%ld] ", myvector.at(3).getSkipStart(), myvector.at(3).getSkipStop());
}
