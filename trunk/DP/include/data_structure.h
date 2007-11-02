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
 
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include <vector>


class Disc
{
public:
	Disc() : m_discID(0),
             m_disc_name(""),
             m_disc_serial(""),
             m_disc_length(0),
             m_disc_chapters(0),
             m_disc_rating(0)
	{}
	~Disc() {}
		
	void clear(); // clears object member variables

	void setDiscID(int ID);
	const int getDiscID() const;

	void setDiscName(std::string& name);
	const std::string& getDiscName() const;
		
	void setDiscSerial(std::string& serial);
	const std::string& getDiscSerial() const;

	void setDiscLength(long length);
	const long getDiscLength() const;

	void setDiscChapterNum(int chapters);
	const int getDiscChapterNum() const;

	void setDiscRating(int rating);
	const int getDiscRating() const;

private:
	int m_discID;
	std::string m_disc_name;
	std::string m_disc_serial;
	long m_disc_length;
	int m_disc_chapters;
	int m_disc_rating; // using 1:G, 2:PG, 3:PG-13, 4:R, 5:NC-17, 6:X, 7:NR
};

class User
{
public:
	User() : m_userID(0),
             m_username(""),
             m_iconfile(""),
             m_password(""),
             m_question(""),
             m_answer(""),
             m_play_unknown(false),
             m_max_play_level(0),
             m_last_movie_ID(0),
             m_last_movie_pos(0)
	{}
	~User() {}
		
	void clear(); // clears object member variables

	void setUserID(int ID);
	const int getUserID() const;

	void setUser(std::string& username);
	const std::string& getUser() const;

	void setPasswordHash(std::string& hash);
	const std::string& getPasswordHash() const;

	void setUserIcon(std::string& file);
	const std::string& getUserIcon() const;

	void setPlayUnknownDisc(bool flag);
	const bool getPlayUnknownDisc() const;

	void setMaxPlayLevel(int level);
	const int getMaxPlayLevel() const;

	void setLastMovieID(int ID);
	const int getLastMovieID() const;

	void setLastMoviePos(long position);
	const long getLastMoviePos() const;
	
	void setQuestion(std::string& question);
	const std::string& getQuestion() const;
	
	void setAnswer(std::string& answer);
	const std::string& getAnswer() const;

private:
	int m_userID;
	std::string m_username;
	std::string m_iconfile;
	std::string m_password;
	std::string m_question;
	std::string m_answer;
	bool m_play_unknown;
	int m_max_play_level;
	int m_last_movie_ID;
	long m_last_movie_pos;
};

class SkipTime
{
public:
	
	SkipTime() : m_start_time(0),
                 m_stop_time(0)/*,
                 m_video_only(false)*/
	{}
	~SkipTime() {}
		
	void clear(); // clears object member variables

	void setSkipStart(long start);
	const long getSkipStart() const;

	void setSkipStop(long stop);
	const long getSkipStop() const;

	//taken out for now...
	//void setVideoOnly(bool isOnlyVideo);
	//const bool getVideoOnly() const;

	bool operator==(const SkipTime& other);
	
private:
	long m_start_time;
	long m_stop_time;
	//bool m_video_only;

};

struct skipSortAscending
{
	bool operator()(const SkipTime& rpStart, const SkipTime& rpEnd) const
   	{
		return (rpStart.getSkipStart() < rpEnd.getSkipStart() ||
				rpStart.getSkipStop() == 0);
   	}
};


class Profile
{
public:
	Profile() : m_profileID(0),
                m_userID(0),
                m_discID(0)
	{}
	~Profile() {}
		
	void clear(); // clears object member variables

	void setProfileID(int ID);
	const int getProfileID() const;

	void setUserID(int ID);
	const int getUserID() const;

	void setDiscID(int ID);
	const int getDiscID() const;

	void addSkipChapter(int chapter);
	void removeSkipChapter(int chapter);
	const std::vector<int>& getSkipChapters() const;

	void addSkipTime(SkipTime skip_time);
	void removeSkipTime(SkipTime skip_time);
	const std::vector<SkipTime>& getSkipTimes() const;
		

private:
	int m_profileID;
	int m_userID;
	int m_discID;
	std::vector<SkipTime> m_skip_times; // start & stop time pairings to skip
	std::vector<int> m_skip_chapters; // chapters marked for skipping
};


class DataTest
{
public:
	static void do_test();
};


class DataStructure
{
public:
	Disc* getDisc();
	const Disc* getDisc() const;
	void clearDisc();

	User* getUserLoggedIn();
	const User* getUserLoggedIn() const;
	void clearUserLoggedIn();

	User* getUserOther();
	const User* getUserOther() const;
	void clearUserOther();

	Profile* getProfile();
	const Profile* getProfile() const;
	void clearProfile();

private:
	User m_userLoggedIn;
	User m_userOther;
	Disc m_disc;
	Profile m_profile;
};


#endif
