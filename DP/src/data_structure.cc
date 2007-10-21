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

// -----------------------------------------------------------------------------
// Disc class

void Disc::clear()
{
	m_discID = 0;
	m_disc_name = "";
	m_disc_length = 0;
	m_disc_chapters = 0;
    m_disc_rating = 0;
}

void Disc::setDiscID(int ID)
{
	m_discID = ID;
}

const int Disc::getDiscID() const
{
	return m_discID;
}

void Disc::setDiscName(std::string& name)
{
	m_disc_name = name;
}

const std::string& Disc::getDiscName() const
{
	return m_disc_name;
}

void Disc::setDiscLength(long length)
{
	m_disc_length = length;
}

const long Disc::getDiscLength() const
{
	return m_disc_length;
}

void Disc::setDiscChapterNum(int chapters)
{
	m_disc_chapters = chapters;
}

const int Disc::getDiscChapterNum() const
{
	return m_disc_chapters;
}

void Disc::setDiscRating(int rating)
{
	m_disc_rating = rating;
}

const int Disc::getDiscRating() const
{
	return m_disc_rating;
}

// -----------------------------------------------------------------------------
// User class

void User::clear()
{
	m_userID =0;
    m_username = "";
	m_iconfile = "";
	m_password = "";
    m_play_unknown = false;
	m_max_play_level = 0;
    m_last_movie_ID = 0;
    m_last_movie_pos = 0;
}

void User::setUserID(int ID)
{
	m_userID = ID;
}

const int User::getUserID() const
{
	return m_userID;
}

void User::setUser(std::string& username)
{
	m_username = username;
}

const std::string& User::getUser() const
{
	return m_username;
}

void User::setPasswordHash(std::string& hash)
{
	m_password = hash;
}

const std::string& User::getPasswordHash() const
{
	return m_password;
}

void User::setUserIcon(std::string& file)
{
	m_iconfile = file;
}

const std::string& User::getUserIcon() const
{
	return m_iconfile;
}

void User::setPlayUnknownDisc(bool flag)
{
	m_play_unknown = flag;
}

const bool User::getPlayUnknownDisc() const
{
	return m_play_unknown;
}

void User::setMaxPlayLevel(int level)
{
	m_max_play_level = level;
}

const int User::getMaxPlayLevel() const
{
	return m_max_play_level;
}

void User::setLastMovieID(int ID)
{
	m_last_movie_ID = ID;
}

const int User::getLastMovieID() const
{
	return m_last_movie_ID;
}

void User::setLastMoviePos(long position)
{
	m_last_movie_pos = position;
}

const long User::getLastMoviePos() const
{
	return m_last_movie_pos;
}

// -----------------------------------------------------------------------------
// class SkipTime

void SkipTime::clear()
{
	m_start_time = 0;
    m_stop_time = 0;
    m_audio_only = false;
}

void SkipTime::setSkipStart(long start)
{
	m_start_time = start;
}

const long SkipTime::getSkipStart() const
{
	return m_start_time;
}

void SkipTime::setSkipStop(long stop)
{
	// TODO:
	//if (m_stop_time > m_start_time)
		m_stop_time = stop;
}

const long SkipTime::getSkipStop() const
{
	return m_stop_time;
}

void SkipTime::setAudioOnly(bool isAudio)
{
	m_audio_only = isAudio;
}

const bool SkipTime::getAudioOnly() const
{
	return m_audio_only;
}

// -----------------------------------------------------------------------------
// Profile class

void Profile::clear()
{
	m_profileID = 0;
	m_userID = 0;
    m_discID = 0;
	m_skip_times.clear(); // empties vector of SkipTime objects
	m_skip_chapters.clear(); // empties vector of ints
}

void Profile::setProfileID(int ID)
{
	m_profileID = ID;
}

const int Profile::getProfileID() const
{
	return m_profileID;
}

void Profile::setUserID(int ID)
{
	m_userID = ID;
}

const int Profile::getUserID() const
{
	return m_userID;
}

void Profile::setDiscID(int ID)
{
	m_discID = ID;
}

const int Profile::getDiscID() const
{
	return m_discID;
}

void Profile::addSkipChapter(int chapter)
{
	m_skip_chapters.push_back(chapter);
}

void Profile::removeSkipChapter(int chapter)
{
	std::vector<int>::iterator location;
 	location = find(m_skip_chapters.begin(), m_skip_chapters.end(), chapter);
	
	if(location != m_skip_chapters.end())
	{
		m_skip_chapters.erase(location);
	}
	
}
		
const std::vector<int>& Profile::getSkipChapters() const
{
	return m_skip_chapters;
}

void Profile::addSkipTime(SkipTime skip_time)
{
	m_skip_times.push_back(skip_time);
}

void Profile::removeSkipTime(SkipTime skip_time)
{
	std::vector<SkipTime>::iterator location;	
	location = find(m_skip_times.begin(), m_skip_times.end(), skip_time);
	
	if (location != m_skip_times.end())
	{
		m_skip_times.erase(location);
	}
	
	// traverse the vector yourself... remove later, just for reference
	/*
	for (std::vector<SkipTime>::iterator it=m_skip_times.begin(); it!=m_skip_times.end(); ++it)
	{
		if (skip_time == *it)
			m_skip_times.erase(it);		
	}
	*/
	
}

const std::vector<SkipTime>& Profile::getSkipTimes() const
{
	return m_skip_times;
}

bool SkipTime::operator==(const SkipTime& other)
{
	if (m_start_time == other.m_start_time &&
		m_stop_time == other.m_stop_time &&
		m_audio_only == other.m_audio_only)
		return true;
	else
		return false;
}

// -----------------------------------------------------------------------------
// DataStructure class
Disc* DataStructure::getDisc()
{
	return &m_disc;
}

const Disc* DataStructure::getDisc() const
{
	return &m_disc;
}

void DataStructure::clearDisc()
{
	m_disc.clear();
}

User* DataStructure::getUserLoggedIn()
{
	return &m_userLoggedIn;
}

const User* DataStructure::getUserLoggedIn() const
{
	return &m_userLoggedIn;
}

void DataStructure::clearUserLoggedIn()
{
	m_userLoggedIn.clear();
}

User* DataStructure::getUserOther()
{
	return &m_userOther;
}

const User* DataStructure::getUserOther() const
{
	return &m_userOther;
}

void DataStructure::clearUserOther()
{
	m_userOther.clear();
}

Profile* DataStructure::getProfile()
{
	return &m_profile;
}

const Profile* DataStructure::getProfile() const
{
	return &m_profile;
}

void DataStructure::clearProfile()
{
	m_profile.clear();
}
// -----------------------------------------------------------------------------
// DataTest testbench
/* 9/22/07 - At this point most of the data structure operations are simply
	setting instance variables. Future testing to be added once further
	development is done: integration with database, extensive error checking,
	and adding const methods.
*/
void DataTest::do_test()
{	
	const int anumber = 4;
	std::string astring = "Jeff";
	std::string ahash = "a123456789";
	long alongnum = 12312984;
	long alongnum2 = 18888888;
	long alongnum3 = 99999999;
	int size;
	
	// Test disc object ----------------
	Disc atest;
	if (atest.getDiscID() != 0)
		puts("DEBUG: disc ID not initialized to zero!");
	
	// Test user object ----------------
	User auser;
	auser.setUserID(anumber);
	if (auser.getUserID() != anumber)
		puts("DEBUG: problem with UserID");
	
	auser.setUser(astring);
	if (auser.getUser() != astring)
		puts("DEBUG: problem with User");
	
	auser.setPasswordHash(ahash);
	if (auser.getPasswordHash() != ahash)
		puts("DEBUG: problem with password");
	
	// Test Profile object ------------
	SkipTime askiptime;
	askiptime.setSkipStart(alongnum);
	askiptime.setSkipStop(alongnum2);
	askiptime.setAudioOnly(false);
	
	SkipTime askiptime2;
	askiptime2.setSkipStart(alongnum2);
	askiptime2.setSkipStop(alongnum3);
	askiptime2.setAudioOnly(false);
	
	Profile aprofile;
	aprofile.addSkipTime(askiptime);
	
	// since this time was never added, shouldn't effect anything
	aprofile.removeSkipTime(askiptime2);
	
	size = aprofile.getSkipTimes().size();
	if (size != 1)
		puts("DEBUG: problem with profile");
	
	// check out the vector
	for (std::vector<SkipTime>::const_iterator it = aprofile.getSkipTimes().begin();
		it!=aprofile.getSkipTimes().end(); ++it)
	{
		printf("%s\n", "A skiptime object:");
		printf("skipstart: %ld\n",it->getSkipStart());
		printf("skipstop: %ld\n",it->getSkipStop());
		printf("audio only: %s\n\n", it->getAudioOnly() ? "true" : "false");
	}
	
	aprofile.removeSkipTime(askiptime);
	size = aprofile.getSkipTimes().size();
	if (size != 0)
		puts("DEBUG: problem with profile");
	
}
