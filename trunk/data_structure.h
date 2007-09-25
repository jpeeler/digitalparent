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
 
#include <string>
#include <vector>

// TODO: add constructor methods, optionally with ID parameter

class Disc
{
public:
	void setDiscID(int ID);
	int getDiscID();

	void setDiscName(std::string& name);
	std::string& getDiscName();

	void setDiscLength(long length);
	long getDiscLength();

	void setDiscChapterNum(int chapters);
	int getDiscChapterNum();

	void setDiscRating(int rating);
	int getDiscRating();

private:
	int m_discID;
	std::string m_disc_name;
	long m_disc_length;
	int m_disc_chapters;
	int m_disc_rating; // using 1:G, 2:PG, 3:PG-13, 4:R, 5:NC-17, 6:X, 7:NR

};

class User
{
public:
	void setUserID(int ID);
	int getUserID();

	void setUser(std::string& username); // const?
	std::string& getUser();

	void setPasswordHash(std::string& hash);
	std::string& getPasswordHash();

	void setIconfile(std::string& file);
	std::string& getIconfile();

	void setPlayUnknownDisc(bool flag);
	bool getPlayUnknownDisc();

	void setMaxPlayLevel(int level);
	int getMaxPlayLevel();

	void setLastMovieID(int ID);
	int getLastMovieID();

	void setLastMoviePos(long position);
	long getLastMoviePos();

private:
	int m_userID;
	std::string m_username;
	std::string m_iconfile;
	std::string m_password;
	bool m_play_unknown;
	int m_max_play_level;
	int m_last_movie_ID;
	long m_last_movie_pos;
};

class SkipTime
{
public:
	void setSkipStart(long start);
	long getSkipStart();

	void setSkipStop(long stop);
	long getSkipStop();

	void setAudioOnly(bool isAudio);
	bool getAudioOnly();

	bool operator==(const SkipTime& other);
	
private:
	long m_start_time;
	long m_stop_time;
	bool m_audio_only;
};


class Profile
{
public:
	void setProfileID(int ID);
	int getProfileID();

	void setUserID(int ID);
	int getUserID();

	void setDiscID(int ID);
	int getDiscID();

	void addSkipChapter(int chapter);
	void removeSkipChapter(int chapter);
	std::vector<int>& getSkipChapters();

	// TODO: perhaps make a addSkipTimePair method?
	// void addSkipTimingPair(long start, long stop);
	void addSkipTime(SkipTime skip_time);
	void removeSkipTime(SkipTime skip_time);
	std::vector<SkipTime>& getSkipTimes();

private:
	int m_profileID;
	int m_userID;
	int m_discID;
	std::vector<SkipTime> m_skip_times; // start & stop time pairings to skip
	std::vector<int> m_skip_chapters; // chapters marked for skipping
};

class DataStructure
{
public:
	Disc* getDisc();
	User* getUser();
	Profile* getProfile();

private:
	User m_user;
	Disc m_disc;
	Profile m_profile;	
};
