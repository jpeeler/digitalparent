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
	catch(tntdb::Error &e) {
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
	
	//set profile_id to 0 in case they try to store it again
	(*profile).setProfileID(0);
	
	return true;
}

User Database::getUser(std::string& username, std::string& password)
{
	User outUser;
	tntdb::Statement query;
	tntdb::Row row;
	std::string returnName;
	std::string returnPassword;
	std::string returnIcon;
	
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
	
	//user was successfully retrieved, fill object
	returnName = (row[1]).getString();
	returnPassword = (row[2]).getString();
	returnIcon = (row[3]).getString();
	
	outUser.setUserID(row[0]);
	outUser.setUser(returnName);
	outUser.setPasswordHash(returnPassword);
	outUser.setUserIcon(returnIcon);
	outUser.setPlayUnknownDisc(row[4]);
	outUser.setMaxPlayLevel(row[5]);
	outUser.setLastMovieID(row[6]);
	outUser.setLastMoviePos((int) row[7]);
	
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
	//need to remove all data for this user, including profiles
	//get list of profiles for this userID
	
	//for each profile, remove skip chapters and skip times
	
	//all skip chapters/times removed, delete Profile entries
	
	//Profiles gone, remove Users entry
	
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

//--------------------------------------------------------------------------//

/**
 * 10/4/07 - Moved code from original dbTestStub.cc to DBTest class function
 *				below.  Need to add error checking.
**/

/**
 * Test stub for database / SQLite component of the DigitalParent product.
 *
 * Basic Approach:
 *    1) Create User, Profile, and Disc objects with sample data.
      2) Insert sample data into database using store*() methods.
 *    3) For each get*() method, ensure that the objects returned
 *       contain the proper sample data from the database.
 *    4) Remove sample data inserted in (2) using the remove*() commands.
 *    5) For each get*() method, attempt to read data not in the database
 *       (as if querying for information on a disc that has not been
 *       inserted yet).
 *    6) Test behavior in the event that the database file is unreadable.
**/

#define TEST_USER true
#define TEST_DISC false
#define TEST_PROFILE true
#define DELETE_PROFILE false
#define DELETE_USER false

void DBTest::do_DBTest()
{
	Database db;
   	Disc sampleDisc, returnDisc;
   	Profile sampleProfile, returnProfile;
   	User sampleUser, returnUser;
   	SkipTime skip1, skip2;
	
 
   	std::string discname = "We Were Soldiers";
   	std::string username = "TestUser2";
   	std::string pwdhash = "#PWDHasH!";
   	std::string iconfile = "/filename";
   	/**
     * Create objects with sample data for inserts.
   	**/
   	sampleDisc.setDiscName(discname);
   	sampleDisc.setDiscLength(123456789);
   	sampleDisc.setDiscChapterNum(12);
   	sampleDisc.setDiscRating(1);

   //note: need to set lastMovieID after Disc object is in database
   sampleUser.setUser(username);
   sampleUser.setPasswordHash(pwdhash);
   sampleUser.setUserIcon(iconfile);
   sampleUser.setPlayUnknownDisc(false);
   sampleUser.setMaxPlayLevel(2);
   sampleUser.setLastMoviePos(4321);

   skip1.setSkipStart(1300);
   skip1.setSkipStop(1403);
   skip1.setAudioOnly(false);

   skip2.setSkipStart(2100);
   skip2.setSkipStop(2403);
   skip2.setAudioOnly(true);

   //note: will need to set userID, discID once User and Disc
   //are inserted and IDs assigned
   sampleProfile.addSkipChapter(2);
   sampleProfile.addSkipChapter(5);
   sampleProfile.addSkipChapter(12);
   sampleProfile.addSkipTime(skip1);
   sampleProfile.addSkipTime(skip2);

   /**
    * Use objects to insert data into database.
   **/
/*
   if(!db.storeDisc(&sampleDisc)) {
      printf("\nInsert Disc\n");
      exit(1);
   }
*/
	//returnUser = db.getUser(username, pwdhash);
	
   if(!db.storeUser(&sampleUser)) {
      printf("\nInsert User\n");
      exit(1);
   }

   sampleProfile.setUserID(sampleUser.getUserID());
   sampleProfile.setDiscID(2);//sampleDisc.getDiscID());

   if(!db.storeProfile(&sampleProfile)) {
      printf("\nInsert Profile\n");
      exit(1);
   }

   /**
    * Get data from database to compare with sample data.
   **/
	if(TEST_USER) {
   		returnUser = db.getUser((std::string&) sampleUser.getUser(), (std::string&) sampleUser.getPasswordHash());
   		if(0 == returnUser.getUserID()) {
      		printf("\nGet User\n");
      		exit(1);
		}
	   
		if(sampleUser.getUserID() != returnUser.getUserID()) {
			printf("\nUser ID\n");
			exit(1);
		}
		if(sampleUser.getUser() != returnUser.getUser()) {
			printf("\nUsername\n");
			exit(1);
		}
		if(sampleUser.getPasswordHash() != returnUser.getPasswordHash()) {
			printf("\nPassword Hash\n");
			exit(1);
		}
		if(sampleUser.getUserIcon() != returnUser.getUserIcon()) {
			printf("\nUser Icon\n");
			exit(1);
		}
		if(sampleUser.getPlayUnknownDisc() != returnUser.getPlayUnknownDisc()) {
			printf("\nUser Unknown Discs\n");
			exit(1);
		}
		if(sampleUser.getMaxPlayLevel() != returnUser.getMaxPlayLevel()) {
			printf("\nUser Max Play Level\n");
			exit(1);
		}
		if(sampleUser.getLastMovieID() != returnUser.getLastMovieID()) {
			printf("\nUser Last Movie ID\n");
			exit(1);
		}
		if(sampleUser.getLastMoviePos() != returnUser.getLastMoviePos()) {
			printf("\nUser Last Movie Position\n");
			exit(1);
		}
	   
		//if we've gotten this far, the User is correct
		printf("\nUser good!\n");
	   
	   if(DELETE_USER)
	   {
			if(!db.removeUser(&returnUser)) {
				printf("\nDelete User\n");
				exit(1);
			}
	   }
   
	}

	if(TEST_DISC) {
	   returnDisc = db.getDisc((std::string&) sampleDisc.getDiscName(), sampleDisc.getDiscChapterNum(), sampleDisc.getDiscLength());
	   if(0 == returnDisc.getDiscID()) {
		  printf("\nGet Disc\n");
		  exit(1);
	   }
	   
	   if(sampleDisc.getDiscID() != returnDisc.getDiscID()) {
		  printf("\nDisc ID\n");
		  exit(1);
	   }
	   if(sampleDisc.getDiscName() != returnDisc.getDiscName()) {
		  printf("\nDisc Name\n");
		  exit(1);
	   }
	   if(sampleDisc.getDiscLength() != returnDisc.getDiscLength()) {
		  printf("\nDisc Length\n");
		  exit(1);
	   }
	   if(sampleDisc.getDiscChapterNum() != returnDisc.getDiscChapterNum()) {
		  printf("\nDisc NumChapters\n");
		  exit(1);
	   }
	   if(sampleDisc.getDiscRating() != returnDisc.getDiscRating()) {
		  printf("\nDisc Rating\n");
		  exit(1);
	   }
	   
	   //if we've gotten this far, the Disc is correct
	   printf("\nDisc good!\n");
	   
	}
	
	if(TEST_PROFILE) {
	   returnProfile = db.getProfile(sampleProfile.getDiscID(), sampleProfile.getUserID());
	   if(0 == returnProfile.getProfileID()) {
		  printf("\nGet Profile\n");
		  exit(1);
	   }
	   
	   if(sampleProfile.getProfileID() != returnProfile.getProfileID()) {
		  printf("\nProfile ID\n");
		  exit(1);
	   }
	   if(sampleProfile.getUserID() != returnProfile.getUserID()) {
		  printf("\nProfile User ID\n");
		  exit(1);
	   }
	   if(sampleProfile.getDiscID() != returnProfile.getDiscID()) {
		  printf("\nProfile Disc ID\n");
		  exit(1);
	   }
	   
	   //add checks for skipped chapters and skipped times
	
	   //if we've gotten this far, the Profile is correct
	   printf("\nProfile good!\n");
	   
	   if(DELETE_PROFILE) {
			if(!db.removeProfile(&returnProfile)) {
				printf("\nDelete Profile\n");
				exit(1);
			}
		}
	 
	}
   /**
    * For each element, compare to see if data is the same
   **/
   
   
   
   
   
   
   /**
    * Test what will happen if get*() is called with data that is
    * not in database.
    * Also test what happens when the database file cannot be accessed.
   **/

}
