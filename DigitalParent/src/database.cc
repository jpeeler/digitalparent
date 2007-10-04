/***************************************************************************
 *            database.cc
 *
 *  Fri Sep 28 11:54:13 2007
 *  Email pwightm@clemson.edu
 ****************************************************************************/

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
 
 
 #include "database.h"
 
 Database::Database()
{
	// TODO: put constructor code here
	try {
		conn = tntdb::connect("sqlite:DigitalParentDB");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}


Database::~Database()
{
	// TODO: put destructor code here
}

Profile Database::getProfile(int diskID, int userID)
{
	Profile outProfile;
	SkipTime skipTime;
	tntdb::Row row;
	
	tntdb::Statement query = conn.prepare("SELECT Profile_ID, User_ID, Disc_ID FROM Profiles WHERE Disc_ID = :v1 AND User_ID = :v2");
	
	query.setInt("v1", diskID).setInt("v2", userID);
	
	try {
		row = query.selectRow();
	}
	catch(tntdb::NotFound) {
		outProfile.setProfileID(0);
		return outProfile;
	}
	
	outProfile.setProfileID((int) row[0]);
	outProfile.setUserID((int) row[1]);
	outProfile.setDiscID((int) row[2]);
	
	//get the skipped chapters for this profile
	query = conn.prepare("SELECT Chapter_Number FROM Skip_Chapters WHERE Profile_ID = :v1 ORDER BY Chapter_Number ASC");
	
	query.setInt("v1", outProfile.getProfileID());
	
	for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	{
		row = *cursor;
		outProfile.addSkipChapter((int) row[0]);
	}
	
	//get skip times for this profile
	query = conn.prepare("SELECT Skip_Start, Skip_Stop, Audio_Only FROM Skip_Times WHERE Profile_ID = :v1 ORDER BY Skip_Start ASC");
	
	query.setInt("v1", outProfile.getProfileID());
	
	for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	{
		row = *cursor;
		skipTime.setSkipStart((int) row[0]);
		skipTime.setSkipStop((int) row[1]);
		skipTime.setAudioOnly(row[2]);
		
		outProfile.addSkipTime(skipTime);
	}
	
	return outProfile;
}

bool Database::storeProfile(Profile *profile)
{

	tntdb::Statement query;
	std::vector<SkipTime> skipTimes = (*profile).getSkipTimes();
	std::vector<int> skipChapters = (*profile).getSkipChapters();
	unsigned int index;
	
	if(0 != (*profile).getProfileID()) {
		//this is not a new profile, update database
		
		//update disc/user IDs
		query = conn.prepare("UPDATE Profiles SET User_ID = :v1, Disc_ID = :v2 WHERE Profile_ID = :v3");
		query.setInt("v1", (*profile).getUserID()).setInt("v2", (*profile).getDiscID()).setInt("v3", (*profile).getProfileID()).execute();
		
		//remove all skip chapters in database
		query = conn.prepare("DELETE FROM Skip_Chapters WHERE Profile_ID = :v1");
		query.setInt("v1", (*profile).getProfileID()).execute();
		
		//remove all skip times in database
		query = conn.prepare("DELETE FROM Skip_Times WHERE Profile_ID = :v1");
		query.setInt("v1", (*profile).getProfileID()).execute();
		
	}
	
	else {
		//profile does not exist, insert new
		query = conn.prepare("INSERT INTO Profiles (User_ID, Disc_ID) VALUES (:v1, :v2)");
		query.setInt("v1", (*profile).getUserID()).setInt("v2", (*profile).getDiscID()).execute();
		
		query = conn.prepare("SELECT Profile_ID FROM Profiles WHERE User_ID = :v1 AND Disc_ID = :v2");
		query.setInt("v1", (*profile).getUserID()).setInt("v2", (*profile).getDiscID());
		
		(*profile).setProfileID(query.selectValue());
	}
	
	//insert skip chapters
	query = conn.prepare("INSERT INTO Skip_Chapters (Chapter_Number, Profile_ID) VALUES (:v1, :v2)");
	
	for(index = 0; index < skipChapters.size(); index++)
	{
		query.setInt("v1", skipChapters[index]).setInt("v2", (*profile).getProfileID()).execute();
	}
	
	
	//insert skip times
	query = conn.prepare("INSERT INTO Skip_Times (Skip_Start, Skip_Stop, Audio_Only, Profile_ID) VALUES (:v1, :v2, :v3, :v4)");
	
	for(index = 0; index < skipTimes.size(); index++)
	{
		query.setInt("v1", (skipTimes[index]).getSkipStart()).setInt("v2", (skipTimes[index]).getSkipStop()).setBool("v3", (skipTimes[index]).getAudioOnly()).setInt("v4", (*profile).getProfileID()).execute();
	}
	
	
	return true;
}

bool Database::removeProfile(Profile *profile)
{
	tntdb::Statement query;
	
	query = conn.prepare("DELETE FROM Skip_Chapters WHERE Profile_ID = :v1");
	query.setInt("v1", (*profile).getProfileID()).execute();
	
	query = conn.prepare("DELETE FROM Skip_Times WHERE Profile_ID = :v1");
	query.setInt("v1", (*profile).getProfileID()).execute();
	
	query = conn.prepare("DELETE FROM Profiles WHERE Profile_ID = :v1");
	query.setInt("v1", (*profile).getProfileID()).execute();
	
	return true;
}

User Database::getUser(std::string& username, std::string& password)
{
	User outUser;
	tntdb::Statement query;
	tntdb::Row row;
	
	query = conn.prepare("SELECT User_ID, Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position FROM Users WHERE Username = :v1 AND Password = :v2");
	query.setString("v1", username).setString("v2", password);
	
	try
	{
		row = query.selectRow();
	}
	catch(tntdb::Error &e)
	{
		printf("\n\nError getting user\n\n");
		exit(1);
	}
	
	return outUser;
	
}

bool Database::storeUser(User *user)
{
	tntdb::Statement query;
	
	if(0 != (*user).getUserID())
	{
		//this user is already in database, update
		query = conn.prepare("UPDATE Users SET Username = :v1, Password = :v2, User_Icon = :v3, Can_Play_Unknown = :v4, Disc_Rating_ID = :v5, Last_Movie_ID = :v6, Last_Movie_Position = :v7 WHERE User_ID = :v8");
		query.setInt("v8", (*user).getUserID());
		query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash()).setString("v3", (*user).getUserIcon());
		query.setBool("v4", (*user).getPlayUnknownDisc()).setInt("v5", (*user).getMaxPlayLevel()).setInt("v6", (*user).getLastMovieID());
		query.setInt("v7", (*user).getLastMoviePos()).execute();
	
	}
	else
	{
		query = conn.prepare("INSERT INTO Users (Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position) VALUES (:v1, :v2, :v3, :v4, :v5, :v6, :v7)");
		query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash()).setString("v3", (*user).getUserIcon());
		query.setBool("v4", (*user).getPlayUnknownDisc()).setInt("v5", (*user).getMaxPlayLevel()).setInt("v6", (*user).getLastMovieID());
		query.setInt("v7", (*user).getLastMoviePos()).execute();
	
		query = conn.prepare("SELECT User_ID FROM Users WHERE Username = :v1 AND Password = :v2");
		query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash());
		
		(*user).setUserID(query.selectValue());
	}
		
	
	
	return true;
}

bool Database::removeUser(User *user)
{
	return true;
}

bool Database::storeDisc(Disc *discInfo)
{
	return true;
}

Disc Database::getDisc(std::string& discName, int numChapters, long discLength)
{
	Disc outDisc;
	
	return outDisc;
}
