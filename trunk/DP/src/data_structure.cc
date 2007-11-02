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
	m_disc_serial = "";
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

void Disc::setDiscSerial(std::string& serial)
{
	m_disc_serial = serial;	
}

const std::string& Disc::getDiscSerial() const
{
	return m_disc_serial;
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
	m_question = "";
	m_answer = "";
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

void User::setQuestion(std::string& question)
{
	m_question = question;
}

const std::string& User::getQuestion() const
{
	return m_question;
}

void User::setAnswer(std::string& answer)
{
	m_answer = answer;
}

const std::string& User::getAnswer() const
{
	return m_answer;
}

// -----------------------------------------------------------------------------
// class SkipTime

void SkipTime::clear()
{
	m_start_time = 0;
    m_stop_time = 0;
    //m_video_only = false;
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

/*
void SkipTime::setVideoOnly(bool isOnlyVideo)
{
	m_video_only = isOnlyVideo;
}
*/
/*
const bool SkipTime::getVideoOnly() const
{
	return m_video_only;
}
*/
bool SkipTime::operator==(const SkipTime& other)
{
	if (m_start_time == other.m_start_time &&
		m_stop_time == other.m_stop_time /*&&
		m_video_only == other.m_video_only*/)
		return true;
	else
		return false;
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
	
	std::sort(m_skip_chapters.begin(), m_skip_chapters.end());
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

/* This method adds the SkipTime object to the vector of time ranges to 
 * skip. Methods returns on receipt of any negative values. Six possibilities
 * have been devised to compare the skip_time to be inserted versus
 * what already exists. A case by case basis is described below using
 * CAPS for new skip_time to be inserted.
 *
 * case 1: [START,STOP] [start,stop]
 *   skip_time occurs in a new separate block
 * case 2: [START start STOP stop]
 *   skip_time starts in empty space but stops in an existing range
 * case 3: [start START STOP stop]
 *   skip_time is a subset of an existing range, therefore is ignored
 * case 4: [start START stop STOP]
 *   skip_time starts in an existing range and can stop anywhere
 * case 5: [start stop] [START STOP]
 *   skip_time occurs in a new separate block
 * case 6: [START start stop STOP]
 *   skip_time starts before and after an existing skiptime range
 */
void Profile::addSkipTime(SkipTime skip_time)
{ 
	if (skip_time.getSkipStart() < 0 || skip_time.getSkipStop() < 0)
		return;
	
	std::vector<SkipTime>::iterator it=m_skip_times.begin();
	bool locate_stop = false;
	
	// find start of skip_time and handle if possible
	while(it!=m_skip_times.end())
	{
		// case 1 (handled here)
		if (skip_time.getSkipStop() < it->getSkipStart())
		{
			//printf("DEBUG: case 1 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
			m_skip_times.push_back(skip_time);
			break;
		}
		// case 5 (handled here), must wait until end to avoid false positive
		if (skip_time.getSkipStart() > it->getSkipStop() &&
			it == m_skip_times.end()-1)
		{
			//printf("DEBUG: case 5 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
			m_skip_times.push_back(skip_time);
			break;
		}
		// case 3 (handled here, nothing to do actually)
		else if (skip_time.getSkipStart() >= it->getSkipStart() &&
				skip_time.getSkipStop() <= it->getSkipStop())
		{
			//printf("DEBUG: case 3 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
			break;
		}
		// case 2 or 6 (may require further handling marked by locate_stop)
		else if (skip_time.getSkipStart() < it->getSkipStart() &&
				skip_time.getSkipStop() >= it->getSkipStart())
		{
			//printf("DEBUG: case 2/6 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
			if (skip_time.getSkipStop() <= it->getSkipStop())
			{
				skip_time.setSkipStop(it->getSkipStop()); // handled
				m_skip_times.push_back(skip_time);
			}
			else
				locate_stop = true;			
			it->clear();
			break;
		}
		// case 4 (requires further handling marked by locate_stop)
		else if (skip_time.getSkipStart() <= it->getSkipStop() &&
				skip_time.getSkipStart() >= it->getSkipStart() &&
				skip_time.getSkipStop() > it->getSkipStop())
		{
			//printf("DEBUG: case 4 for attempted [%ld,%ld] against [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop(),it->getSkipStart(),it->getSkipStop());
			// still don't know how far stop goes, so can't handle completely
			if (skip_time.getSkipStart() >= it->getSkipStart())
				skip_time.setSkipStart(it->getSkipStart());
			locate_stop = true;
			it->clear();
			break;			
		}
		it++;		
	}
	
	// find SkipTime stop relative to existing skiptimes
	if (locate_stop)
	{
		it++; // previous existing skip time already examined, move to next
		while(it!=m_skip_times.end())
		{
			if (skip_time.getSkipStop() < it->getSkipStart()) // nothing more
				break;
			// lands in middle of existing skip time
			else if (skip_time.getSkipStop() >= it->getSkipStart() &&
				skip_time.getSkipStop() <= it->getSkipStop())
				skip_time.setSkipStop(it->getSkipStop());
			
			// if not, skip_time must be greater than current existing range
			it->clear();
			it++;
		}
		m_skip_times.push_back(skip_time);
	}
	
	// insert first skiptime if none already exist, otherwise sort skiptimes
	if (m_skip_times.size() == 0)
		m_skip_times.push_back(skip_time);
	else
		std::sort(m_skip_times.begin(), m_skip_times.end(), skipSortAscending());
	
	// pops off all [0,0] elements (cleared) from head
	while (m_skip_times.at(0).getSkipStart() == 0 && m_skip_times.at(0).getSkipStop() == 0)
	{
		m_skip_times.erase(m_skip_times.begin());
	}
	/*
	
	// TODO: special case 4 testing required
	std::vector<SkipTime>::iterator it=m_skip_times.begin();
	std::vector<SkipTime *> affected_skips;

	// find first
	while (it!=m_skip_times.end())
	{
		if (it->getSkipStop() >= skip_time.getSkipStart())
		{
			affected_skips.push_back(&(*it));
			
			// passed in is subset of existing SkipTime
			//if (it->getSkipStop() >= skip_time.getSkipStop())
			//	affected_skips.push_back(&(*it));
			
			break;
		}
		it++;		
	}
	
	// find remaining
	while (it!=m_skip_times.end())
	{
		if (it->getSkipStart() <= skip_time.getSkipStop())
		{
			affected_skips.push_back(&(*it));
		}
		it++;
	}
	
	// no skip times effected, case 1, case 5
	if (affected_skips.size() == 0 ||
		skip_time.getSkipStop() < affected_skips.at(0)->getSkipStart() ||
		skip_time.getSkipStart() > affected_skips.back()->getSkipStop())
	{
		//printf("DEBUG: nothing effected for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
		m_skip_times.push_back(skip_time);
	}
	// case 6
	else if (skip_time.getSkipStart() <= affected_skips.at(0)->getSkipStart() &&
			skip_time.getSkipStop() >= affected_skips.back()->getSkipStop())
	{
		//printf("DEBUG: case 6 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
		
		// new skiptime bigger than all existing (or equal size which no-op is actually required)
		for (std::vector<SkipTime*>::iterator it=affected_skips.begin(); it!=affected_skips.end(); it++)
		{
			(*it)->clear();
		}
		m_skip_times.push_back(skip_time);
	}
	// case 2
	else if (skip_time.getSkipStart() < affected_skips.at(0)->getSkipStart())
	{
		//printf("DEBUG: case 2 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
		for (std::vector<SkipTime*>::iterator it=affected_skips.begin(); it!=affected_skips.end(); it++)
		{
			// if skip_time is bigger
			if (skip_time.getSkipStop() >= (*it)->getSkipStop())
				(*it)->clear();
			// if skip_time falls in middle or touches
			else if (skip_time.getSkipStop() < (*it)->getSkipStop() &&
				skip_time.getSkipStop() >= (*it)->getSkipStart())
			{
				skip_time.setSkipStop((*it)->getSkipStop());
				(*it)->clear();
			}
		}
		m_skip_times.push_back(skip_time);
	}
	// case 4
	else if (skip_time.getSkipStart() < affected_skips.back()->getSkipStop())
	{
		//printf("DEBUG: case 4 for attempted [%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop());
		for (std::vector<SkipTime*>::iterator it=affected_skips.begin(); it!=affected_skips.end(); it++)
		{
			// if skip_time needs expanding		
			if (skip_time.getSkipStop() < (*it)->getSkipStop() &&
				skip_time.getSkipStop() > (*it)->getSkipStart())
			{
				skip_time.setSkipStart((*it)->getSkipStart());
				(*it)->clear();
			}
			else if (skip_time.getSkipStart() >= (*it)->getSkipStart())
				(*it)->clear();
		}
		m_skip_times.push_back(skip_time);
	}
	// case 3
	else if (*(affected_skips.at(0)) == *(affected_skips.at(1)))
	{
		//printf("DEBUG: case 3 for attempted [%ld,%ld] affect1[%ld,%ld] affect2[%ld,%ld]\n",skip_time.getSkipStart(), skip_time.getSkipStop(),affected_skips.at(0)->getSkipStart(),affected_skips.at(0)->getSkipStop(),affected_skips.at(1)->getSkipStart(),affected_skips.at(1)->getSkipStop());
		// do nothing, skiptime subset of existing duration
	}		
	else
	{
		printf("DEBUG: unhandled\n");
	}
	
	std::sort(m_skip_times.begin(), m_skip_times.end(), skipSortAscending());
	
	// pops off all [0,0] elements from head
	while (m_skip_times.at(0).getSkipStart() == 0 && m_skip_times.at(0).getSkipStop() == 0)
	{
		m_skip_times.erase(m_skip_times.begin());
	}
	*/
}

void Profile::removeSkipTime(SkipTime skip_time)
{
	std::vector<SkipTime>::iterator location;	
	location = find(m_skip_times.begin(), m_skip_times.end(), skip_time);
	
	if (location != m_skip_times.end())
	{
		m_skip_times.erase(location);
	}	
}

const std::vector<SkipTime>& Profile::getSkipTimes() const
{
	return m_skip_times;
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
	std::string discname = "disc_name";
	std::string iconpath = "/tmp/iconfile.png";
	long alongnum = 12312984;
	long alongnum2 = 18888888;
	long alongnum3 = 99999999;
	int size;
	
	// Test disc object ----------------
	Disc adisc;
	adisc.setDiscID(5);
	adisc.setDiscName(discname);
	adisc.setDiscLength(alongnum);
	adisc.setDiscChapterNum(3);
	adisc.setDiscRating(1);
	
	if (adisc.getDiscID() != 5)
		puts("ERROR: adisc.getDiscID");
	if (adisc.getDiscName() != discname)
		puts("ERROR: atest.getDiscName");
	if (adisc.getDiscLength() != alongnum)
		puts("ERROR: atest.getDiscLength");
	if (adisc.getDiscChapterNum() != 3)
		puts("ERROR: atest.getDiscChapterNum");
	if (adisc.getDiscRating() != 1)
		puts("ERROR: atest.getDiscRating");
	
	adisc.clear(); // clear data structure
	if (adisc.getDiscID() != 0)
		puts("ERROR_C: adisc.getDiscID");
	if (adisc.getDiscName() != "")
		puts("ERROR_C: atest.getDiscName");
	if (adisc.getDiscLength() != 0)
		puts("ERROR_C: atest.getDiscLength");
	if (adisc.getDiscChapterNum() != 0)
		puts("ERROR_C: atest.getDiscChapterNum");
	if (adisc.getDiscRating() != 0)
		puts("ERROR_C: atest.getDiscRating");
	
	// Test user object ----------------
	User auser;
	auser.setUserID(anumber);
	auser.setUser(astring);
	auser.setPasswordHash(ahash);
	auser.setUserIcon(iconpath);
	auser.setPlayUnknownDisc(true);
	auser.setMaxPlayLevel(4);
	auser.setLastMovieID(345);
	auser.setLastMoviePos(2312343);
	
	if (auser.getUserID() != anumber)
		puts("ERROR: auser.getUserID");	
	if (auser.getUser() != astring)
		puts("ERROR: auser.getUser");	
	if (auser.getPasswordHash() != ahash)
		puts("ERROR: auser.getPasswordHash");
	if (auser.getUserIcon() != iconpath)
		puts("ERROR: auser.getUserIcon");
	if (auser.getPlayUnknownDisc() != true)
		puts("ERROR: auser.getPlayUnknownDisc");
	if (auser.getMaxPlayLevel() != 4)
		puts("ERROR: auser.getMaxPlayLevel");
	if (auser.getLastMovieID() != 345)
		puts("ERROR: auser.getLastMovieID");
	if (auser.getLastMoviePos() != 2312343)
		puts("ERROR: auser.getLastMoviePos");
	
	auser.clear();
	if (auser.getUserID() != 0)
		puts("ERROR_C: auser.getUserID");	
	if (auser.getUser() != "")
		puts("ERROR_C: auser.getUser");	
	if (auser.getPasswordHash() != "")
		puts("ERROR_C: auser.getPasswordHash");
	if (auser.getUserIcon() != "")
		puts("ERROR_C: auser.getUserIcon");
	if (auser.getPlayUnknownDisc() != false)
		puts("ERROR_C: auser.getPlayUnknownDisc");
	if (auser.getMaxPlayLevel() != 0)
		puts("ERROR_C: auser.getMaxPlayLevel");
	if (auser.getLastMovieID() != 0)
		puts("ERROR_C: auser.getLastMovieID");
	if (auser.getLastMoviePos() != 0)
		puts("ERROR_C: auser.getLastMoviePos");
	
	// Test SkipTime object ------------
	SkipTime askiptime;
	askiptime.setSkipStart(alongnum);
	askiptime.setSkipStop(alongnum2);
	//askiptime.setVideoOnly(false);
	
	if (askiptime.getSkipStart() != alongnum)
		puts("ERROR: askiptime.getSkipStart");
	if (askiptime.getSkipStop() != alongnum2)
		puts("ERROR: askiptime.getSkipStop");
	//if (askiptime.getVideoOnly() != false)
	//	puts("ERROR: askiptime.getVideoOnly");
	
	askiptime.clear();
	if (askiptime.getSkipStart() != 0)
		puts("ERROR_C: askiptime.getSkipStart");
	if (askiptime.getSkipStop() != 0)
		puts("ERROR_C: askiptime.getSkipStop");
	//if (askiptime.getVideoOnly() != false)
	//	puts("ERROR_C: askiptime.getVideoOnly");
	
	// Test Profile object ------------
	// set SkipTime object to something other than default values
	askiptime.setSkipStart(alongnum);
	askiptime.setSkipStop(alongnum2);
	//askiptime.setVideoOnly(false);
	
	// create another SkipTime object
	SkipTime askiptime2;
	askiptime2.setSkipStart(alongnum2);
	askiptime2.setSkipStop(alongnum3);
	//askiptime2.setVideoOnly(true);
	
	// add SkipTime object to newly created profile object
	Profile aprofile;
	aprofile.addSkipTime(askiptime);
	
	aprofile.setProfileID(345);
	aprofile.setUserID(543);
	aprofile.setDiscID(111);
	aprofile.addSkipChapter(9);
	
	if (aprofile.getProfileID() != 345)
		puts("ERROR: aprofile.getProfileID");
	if (aprofile.getUserID() != 543)
		puts("ERROR: aprofile.getUserID");
	if (aprofile.getDiscID() != 111)
		puts("ERROR: aprofile.getDiscID");
	if (aprofile.getSkipChapters().at(0) != 9)
		puts("ERROR: aprofile.getSkipChapters");
	if (aprofile.getSkipTimes().at(0).getSkipStart() != askiptime.getSkipStart() ||
		aprofile.getSkipTimes().at(0).getSkipStop() != askiptime.getSkipStop() /*||
		aprofile.getSkipTimes().at(0).getVideoOnly() != askiptime.getVideoOnly()*/)
		puts("ERROR: aprofile.getSkipTimes");
	aprofile.clear();
	if (aprofile.getProfileID() != 0)
		puts("ERROR_C: aprofile.getProfileID");
	if (aprofile.getUserID() != 0)
		puts("ERROR_C: aprofile.getUserID");
	if (aprofile.getDiscID() != 0)
		puts("ERROR_C: aprofile.getDiscID");
	if (aprofile.getSkipChapters().size() != 0)
		puts("ERROR_C: aprofile.getSkipChapters");
	if (aprofile.getSkipTimes().size() != 0)
		puts("ERROR_C: aprofile.getSkipTimes");
	
	// since this time was never added, shouldn't effect anything
	aprofile.removeSkipTime(askiptime2);
	
	// removed cleared SkipTime object
	aprofile.removeSkipTime(askiptime);
	
	// add valid non-cleared SkipTime object
	aprofile.addSkipTime(askiptime2);
	
	size = aprofile.getSkipTimes().size();
	if (size != 1)
		puts("ERROR: aprofile.getSkipTimes().size()");
	
	// remove valid non-cleared SkipTime object
	aprofile.removeSkipTime(askiptime2);
	size = aprofile.getSkipTimes().size();
	if (size != 0)
		puts("ERROR_C: aprofile.getSkipTimes().size()");	
	
	// intense test for addSkipTime:
	SkipTime existing_skiptime1;
	SkipTime existing_skiptime2;
	SkipTime existing_skiptime3;
	SkipTime existing_skiptime4;
	SkipTime existing_skiptime5;
	
	// existing ranges:
	// 4-10, 13-14, 16-19, 20-22, 23-28
	existing_skiptime1.setSkipStart(4); existing_skiptime1.setSkipStop(10);
	existing_skiptime2.setSkipStart(13); existing_skiptime2.setSkipStop(14);
	existing_skiptime3.setSkipStart(16); existing_skiptime3.setSkipStop(19);
	existing_skiptime4.setSkipStart(20); existing_skiptime4.setSkipStop(22);
	existing_skiptime5.setSkipStart(23); existing_skiptime5.setSkipStop(28);
	aprofile.addSkipTime(existing_skiptime2);
	aprofile.addSkipTime(existing_skiptime1);
	aprofile.addSkipTime(existing_skiptime3); // test sorting
	aprofile.addSkipTime(existing_skiptime5);
	aprofile.addSkipTime(existing_skiptime4);
	
	SkipTime newSkip1; // 0-1 (case 1)
	SkipTime newSkip3; // 17-18 (case 3)
	SkipTime newSkip5; // 29-30 (case 5)
	SkipTime newSkip2a; // 12-13 (case 2)
	SkipTime newSkip2b; // 15-26 (case 2)
	
	newSkip1.setSkipStart(1); newSkip1.setSkipStop(2);
	newSkip3.setSkipStart(17); newSkip3.setSkipStop(18);
	newSkip5.setSkipStart(29); newSkip5.setSkipStop(30);
	newSkip2a.setSkipStart(12); newSkip2a.setSkipStop(13);
	newSkip2b.setSkipStart(15); newSkip2b.setSkipStop(26);
	
	aprofile.addSkipTime(newSkip1);
	aprofile.addSkipTime(newSkip1); // tests special case 3 (exact match)
	aprofile.addSkipTime(newSkip3);
	aprofile.addSkipTime(newSkip5);
	aprofile.addSkipTime(newSkip2a);
	aprofile.addSkipTime(newSkip2b);
	
	// view vector contents
	puts("SkipTime objects in vector [start,stop]:");
	for (std::vector<SkipTime>::const_iterator it = aprofile.getSkipTimes().begin();
		it!=aprofile.getSkipTimes().end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	
	SkipTime newSkip4a; // test case 6 normal
	newSkip4a.setSkipStart(1); newSkip4a.setSkipStop(30);
	aprofile.addSkipTime(newSkip4a);
	
	puts("\nSkipTime objects in vector [start,stop]:");
	for (std::vector<SkipTime>::const_iterator it = aprofile.getSkipTimes().begin();
		it!=aprofile.getSkipTimes().end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	
	SkipTime newSkip4b;
	newSkip4b.setSkipStart(15); newSkip4b.setSkipStop(45);
	aprofile.addSkipTime(newSkip4b);
	
	puts("\nSkipTime objects in vector [start,stop]:");
	for (std::vector<SkipTime>::const_iterator it = aprofile.getSkipTimes().begin();
		it!=aprofile.getSkipTimes().end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	
	SkipTime newSkip6;
	newSkip6.setSkipStart(0); newSkip6.setSkipStop(100);
	aprofile.addSkipTime(newSkip6);
	
	SkipTime newSkip99; // tests negative skiptime
	newSkip99.setSkipStart(-1); newSkip99.setSkipStop(45);
	aprofile.addSkipTime(newSkip99);
	
	puts("\nSkipTime objects in vector [start,stop]:");
	for (std::vector<SkipTime>::const_iterator it = aprofile.getSkipTimes().begin();
		it!=aprofile.getSkipTimes().end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
}
