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
		printf("connected\n");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}


Database::~Database()
{
	// TODO: put destructor code here
}

int Database::getProfile(Profile *profile)
{
	SkipTime skipTime;
	tntdb::Row row;
   int id;
	
	tntdb::Statement query = conn.prepare("SELECT Profile_ID FROM Profiles WHERE Disc_ID = :v1 AND User_ID = :v2");
	
	query.setInt("v1", (*profile).getDiscID()).setInt("v2", (*profile).getUserID());
	
	try {
      id = query.selectValue();
		(*profile).setProfileID(id);
	}
	catch(tntdb::Error &e) {
		(*profile).setProfileID(0);
      
      if(0 == strcmp("not found", e.what()))
		   return DB_UNKNOWN_PROFILE;
      else
         return DB_GEN_ERROR;
	}
	
	
	//get the skipped chapters for this profile
	query = conn.prepare("SELECT Chapter_Number FROM Skip_Chapters WHERE Profile_ID = :v1 ORDER BY Chapter_Number ASC");
	
	query.setInt("v1", (*profile).getProfileID());
	
   try {
	   for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	   {
		   row = *cursor;
		   (*profile).addSkipChapter((int) row[0]);
	   }
   }
   catch(tntdb::Error &e) {
      if(0 != strcmp("not found", e.what()))
         return DB_GEN_ERROR;
      
      //'not found' indicates no skip chapters for this profile
      //not an error condition
   }
	
	//get skip times for this profile
	query = conn.prepare("SELECT Skip_Start, Skip_Stop, Audio_Only FROM Skip_Times WHERE Profile_ID = :v1 ORDER BY Skip_Start ASC");
	
	query.setInt("v1", (*profile).getProfileID());
	
   try {
	   for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	   {
		   row = *cursor;
		   skipTime.setSkipStart((int) row[0]);
		   skipTime.setSkipStop((int) row[1]);
		   //skipTime.setAudioOnly(row[2]);
		
		   (*profile).addSkipTime(skipTime);
	   }
   }
   catch(tntdb::Error &e) {
      if(0 != strcmp("not found", e.what()))
         return DB_GEN_ERROR;
      
      //'not found' indicates no skip times for this profile
      //not an error condition
   }
	
	return SUCCESS;
}

int Database::storeProfile(Profile *profile)
{	

	tntdb::Statement query;
	std::vector<SkipTime> skipTimes = (*profile).getSkipTimes();
	std::vector<int> skipChapters = (*profile).getSkipChapters();
	unsigned int index;
	
	if(0 != (*profile).getProfileID()) {
		//this is not a new profile, update database
		
      try {
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
      catch(tntdb::Error &e) {
         return DB_GEN_ERROR;
      }
		
	}
	
	else {
      try {
		   //profile does not exist, insert new
		   query = conn.prepare("INSERT INTO Profiles (User_ID, Disc_ID) VALUES (:v1, :v2)");
		   query.setInt("v1", (*profile).getUserID()).setInt("v2", (*profile).getDiscID()).execute();
		
		   query = conn.prepare("SELECT Profile_ID FROM Profiles WHERE User_ID = :v1 AND Disc_ID = :v2");
		   query.setInt("v1", (*profile).getUserID()).setInt("v2", (*profile).getDiscID());
		
		   (*profile).setProfileID(query.selectValue());
      }
      catch(tntdb::Error &e) {
         return DB_GEN_ERROR;
      }
	}
	
	//insert skip chaptersprintf("\n%s",m_user_image.c_str());	
	query = conn.prepare("INSERT INTO Skip_Chapters (Chapter_Number, Profile_ID) VALUES (:v1, :v2)");
	
	for(index = 0; index < skipChapters.size(); index++)
	{
      try {
         query.setInt("v1", skipChapters[index]).setInt("v2", (*profile).getProfileID()).execute();
      }
      catch(tntdb::Error &e) {
         return DB_GEN_ERROR;
      }
	}
	
	
	//insert skip times
	query = conn.prepare("INSERT INTO Skip_Times (Skip_Start, Skip_Stop, Audio_Only, Profile_ID) VALUES (:v1, :v2, :v3, :v4)");
	
	for(index = 0; index < skipTimes.size(); index++)
	{
      try {
		   query.setInt("v1", (skipTimes[index]).getSkipStart()).setInt("v2", (skipTimes[index]).getSkipStop())./*setBool("v3", (skipTimes[index]).getAudioOnly()).*/setInt("v4", (*profile).getProfileID()).execute();
      }
      catch(tntdb::Error &e) {
         return DB_GEN_ERROR;
      }
	}
	
	
	return SUCCESS;
}

int Database::deleteProfile(Profile *profile)
{
	tntdb::Statement query;
	
   try {
	   query = conn.prepare("DELETE FROM Skip_Chapters WHERE Profile_ID = :v1");
	   query.setInt("v1", (*profile).getProfileID()).execute();
	
	   query = conn.prepare("DELETE FROM Skip_Times WHERE Profile_ID = :v1");
	   query.setInt("v1", (*profile).getProfileID()).execute();
	
	   query = conn.prepare("DELETE FROM Profiles WHERE Profile_ID = :v1");
	   query.setInt("v1", (*profile).getProfileID()).execute();
   }
   catch(tntdb::Error &e) {
      return DB_GEN_ERROR;
   }
	
	//set profile_id to 0 in case they try to store it again
	(*profile).setProfileID(0);
	
	return SUCCESS;
}

int Database::getUser(User *user)
{
	tntdb::Statement query;
	tntdb::Row row;
	std::string returnIcon, returnQuestion;
    int userStatus; //used in determining  if user exists
	
	query = conn.prepare("SELECT User_ID, Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position, Secret_Question, Secret_Answer FROM Users WHERE Username = :v1 AND Password = :v2");
	query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash());
	
	try
	{
		row = query.selectRow();
	}
	catch(tntdb::Error &e)
	{
		if(0 == strcmp("not found", e.what())) {
         
         //see if username exists
         userStatus = userExists(user);
         
         switch(userStatus) {
            case DB_UNKNOWN_USER:
                  //username doesn't exist
                  return DB_UNKNOWN_USER;
                  break;
            case DB_USERNAME_IN_USE:
                  //user exists, must be bad password
				  //fill in secret question
				  if(SUCCESS != fillSecretQuestionAndIcon(user)) {
					  //something failed in getting the question
					  return DB_GEN_ERROR;
				  }
				  else {
                  	return DB_BAD_PASSWORD;
				  }
                  break;
            default:
                  return DB_GEN_ERROR;
                  break;
         }
      }
      else
         return DB_GEN_ERROR;
	}
	
	//user was successfully retrieved, fill object
	returnIcon = (row[3]).getString();
	returnQuestion = (row[8]).getString();
	
	(*user).setUserID(row[0]);
	(*user).setUserIcon(returnIcon);
	(*user).setPlayUnknownDisc(row[4]);
	(*user).setMaxPlayLevel(row[5]);
	(*user).setLastMovieID(row[6]);
	(*user).setLastMoviePos((int) row[7]);
	(*user).setQuestion(returnQuestion);
	
	return SUCCESS;
	
}

int Database::getUserUsingAnswer(User *user) {
	tntdb::Statement query;
	tntdb::Row row;
	std::string returnIcon, returnPassword, returnQuestion, returnAnswer;
    int userStatus; //used in determining  if user exists
	
	query = conn.prepare("SELECT User_ID, Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position, Secret_Question, Secret_Answer FROM Users WHERE Username = :v1 AND Secret_Answer = :v2");
	query.setString("v1", (*user).getUser()).setString("v2", (*user).getAnswer());
	
	try
	{
		row = query.selectRow();
	}
	catch(tntdb::Error &e)
	{
		if(0 == strcmp("not found", e.what())) {
         
         //see if username exists
         userStatus = userExists(user);
         
         switch(userStatus) {
            case DB_UNKNOWN_USER:
                  //username doesn't exist
                  return DB_UNKNOWN_USER;
                  break;
            case DB_USERNAME_IN_USE:
                  //user exists, must be bad password
                  return DB_BAD_PASSWORD;
                  break;
            default:
                  return DB_GEN_ERROR;
                  break;
         }
      }
      else
         return DB_GEN_ERROR;
	}
	
	//user was successfully retrieved, fill object
	returnIcon = (row[3]).getString();
	returnQuestion = (row[8]).getString();
	
	(*user).setUserID(row[0]);
	(*user).setUserIcon(returnIcon);
	(*user).setPlayUnknownDisc(row[4]);
	(*user).setMaxPlayLevel(row[5]);
	(*user).setLastMovieID(row[6]);
	(*user).setLastMoviePos((int) row[7]);
	(*user).setQuestion(returnQuestion);
	
	return SUCCESS;
	
}

int Database::getUserForEdit(User *user) {
	tntdb::Statement query;
	tntdb::Row row;
	std::string returnIcon, returnPassword, returnQuestion, returnAnswer;
    int userStatus; //used in determining  if user exists
	
	query = conn.prepare("SELECT User_ID, Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position, Secret_Question, Secret_Answer FROM Users WHERE Username = :v1");
	query.setString("v1", (*user).getUser());
	
	try
	{
		row = query.selectRow();
	}
	catch(tntdb::Error &e)
	{
		if(0 == strcmp("not found", e.what())) {
         
         //see if username exists
         userStatus = userExists(user);
         
         switch(userStatus) {
            case DB_UNKNOWN_USER:
                  //username doesn't exist
                  return DB_UNKNOWN_USER;
                  break;
            case DB_USERNAME_IN_USE:
                  //user exists, must be bad password
                  return DB_BAD_PASSWORD;
                  break;
            default:
                  return DB_GEN_ERROR;
                  break;
         }
      }
      else
         return DB_GEN_ERROR;
	}
	
	//user was successfully retrieved, fill object
	returnPassword = (row[2]).getString();
	returnIcon = (row[3]).getString();
	returnQuestion = (row[8]).getString();
	returnAnswer = (row[9]).getString();
	
	(*user).setUserID(row[0]);
	(*user).setPasswordHash(returnPassword);
	(*user).setUserIcon(returnIcon);
	(*user).setPlayUnknownDisc(row[4]);
	(*user).setMaxPlayLevel(row[5]);
	(*user).setLastMovieID(row[6]);
	(*user).setLastMoviePos((int) row[7]);
	(*user).setQuestion(returnQuestion);
	(*user).setAnswer(returnAnswer);
	
	return SUCCESS;
	
}

int Database::storeUser(User *user)
{
	tntdb::Statement query;
   int userStatus; //used to determine if user exists
	
	if(0 != (*user).getUserID())
	{
      try {
		   //this user is already in database, update
		   query = conn.prepare("UPDATE Users SET Username = :v1, Password = :v2, User_Icon = :v3, Can_Play_Unknown = :v4, Disc_Rating_ID = :v5, Last_Movie_ID = :v6, Last_Movie_Position = :v7, Secret_Question = :v8, Secret_Answer = :v9 WHERE User_ID = :v10");
		   query.setInt("v10", (*user).getUserID());
		   query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash()).setString("v3", (*user).getUserIcon());
		   query.setBool("v4", (*user).getPlayUnknownDisc()).setInt("v5", (*user).getMaxPlayLevel()).setInt("v6", (*user).getLastMovieID());
		   query.setInt("v7", (*user).getLastMoviePos());
		   query.setString("v8", (*user).getQuestion()).setString("v9", (*user).getAnswer()).execute();
      }
      catch(tntdb::Error &e) {
         //printErrorMessage(DB_GEN_ERROR);
         return DB_GEN_ERROR;
      }
	}
	else
	{
      //user should be inserted
      userStatus = userExists(user);
      
      //first check if username is already in use
      if(DB_UNKNOWN_USER == userStatus) {   
         //username does not exist, insert this user
         try {
            printf("User does not exist, inserting\n");
		      query = conn.prepare("INSERT INTO Users (Username, Password, User_Icon, Can_Play_Unknown, Disc_Rating_ID, Last_Movie_ID, Last_Movie_Position, Secret_Question, Secret_Answer) VALUES (:v1, :v2, :v3, :v4, :v5, :v6, :v7, :v8, :v9)");
		      query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash()).setString("v3", (*user).getUserIcon());
		      query.setBool("v4", (*user).getPlayUnknownDisc()).setInt("v5", (*user).getMaxPlayLevel()).setInt("v6", (*user).getLastMovieID());
		      query.setInt("v7", (*user).getLastMoviePos());
			  query.setString("v8", (*user).getQuestion()).setString("v9", (*user).getAnswer()).execute();
	
		      query = conn.prepare("SELECT User_ID FROM Users WHERE Username = :v1 AND Password = :v2");
		      query.setString("v1", (*user).getUser()).setString("v2", (*user).getPasswordHash());
		
		      (*user).setUserID(query.selectValue());
         }
         catch(tntdb::Error &e) {
            return DB_GEN_ERROR;
         }
      }
      else {
         printErrorMessage(userStatus);
         return userStatus;
      }
	}
		
	return SUCCESS;
}

int Database::deleteUser(User *user)
{
	tntdb::Statement query;
	tntdb::Statement removeTimesQuery;
	tntdb::Statement removeChaptersQuery;
	tntdb::Row row;
	
	//need to remove all data for this user, including profiles
	//get list of profiles for this userID
	query = conn.prepare("SELECT Profile_ID FROM Profiles WHERE User_ID = :v1");
	query.setInt("v1", (*user).getUserID());
	
	removeTimesQuery = conn.prepare("DELETE FROM Skip_Times WHERE Profile_ID = :v1");
	removeChaptersQuery = conn.prepare("DELETE FROM Skip_Chapters WHERE Profile_ID = :v1");
	
   try {
   	for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	   {
		   //for each profile, remove skip chapters and skip times
		   row = *cursor;
		   removeTimesQuery.setInt("v1", row[0]).execute();
		   removeChaptersQuery.setInt("v1", row[0]).execute();
	   }
   }
   catch(tntdb::Error &e) {
      return DB_GEN_ERROR;
   }
	
   try {
	//all skip chapters/times removed, delete Profile entries
	query = conn.prepare("DELETE FROM Profiles WHERE User_ID = :v1");
	query.setInt("v1", (*user).getUserID()).execute();
	}
   catch(tntdb::Error &e) {
      return DB_GEN_ERROR;
   }
   
   try {
	   //Profiles gone, remove Users entry
	   query = conn.prepare("DELETE FROM Users WHERE User_ID = :v1");
	   query.setInt("v1", (*user).getUserID()).execute();
	}
   catch(tntdb::Error &e) {
      return DB_GEN_ERROR;
   }
   
	//(*user).setUserID(0);
    (*user).clear();
	
	return SUCCESS;
}

std::vector <std::string> Database::getUserList()
{
	std::vector <std::string> returnList;
	tntdb::Statement query;
	tntdb::Row row;
	
	query = conn.prepare("SELECT Username FROM Users WHERE Username = 'admin'");	

	try
	{
	   row = query.selectRow();
	   returnList.push_back(row[0]);
	}
	catch(tntdb::Error &e)
	{
		if(0 != strcmp("not found", e.what())) {
			returnList.clear();
			return returnList;
		}
	}
	
	query = conn.prepare("SELECT Username FROM Users WHERE Username NOT LIKE 'admin' ORDER BY Username ASC");	

	try
	{
		for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	   {
		   //for each user, add user icon to return vector
		   row = *cursor;
		   returnList.push_back(row[0]);
	   }
	}
	catch(tntdb::Error &e)
	{
		if(0 != strcmp("not found", e.what()))
			returnList.clear();
	}
	
	
	return returnList;
}

std::vector <std::string> Database::getIconList()
{
	std::vector <std::string> returnList;
	tntdb::Statement query;
	tntdb::Row row;

    if(!conn) printf("No DB Connection!!!!\n");
	query = conn.prepare("SELECT User_Icon, Username FROM Users WHERE Username = 'admin'");	

	try
	{
	   row = query.selectRow();
	   returnList.push_back(row[0]);			
	}
	catch(tntdb::Error &e)
	{
		if(0 != strcmp("not found", e.what())) {
			returnList.clear();
			return returnList;
		}
	}
	
	query = conn.prepare("SELECT User_Icon, Username FROM Users WHERE Username NOT LIKE 'admin' ORDER BY Username ASC");	

	try
	{
		for(tntdb::Statement::const_iterator cursor = query.begin();
			cursor != query.end(); ++cursor)
	   {
		   //for each user, add username to return vector
		   row = *cursor;
		   returnList.push_back(row[0]);		   
	   }
	} 
	catch(tntdb::Error &e)
	{
		if(0 != strcmp("not found", e.what()))
			returnList.clear();
	}
	
	return returnList;
}

int Database::storeDisc(Disc *discInfo)
{
	tntdb::Statement query;
	tntdb::Row row;
	std::string discname, serial;

	discname = (*discInfo).getDiscName();
	serial = (*discInfo).getDiscSerial();
	
	query = conn.prepare("SELECT Disc_ID, Disc_Rating_ID FROM Disc WHERE Disc_Name = :v1 AND Disc_Length = :v2 AND Disc_NumChapters = :v3 AND Disc_Serial = :v4");
	query.setString("v1", discname).setInt("v2", (*discInfo).getDiscLength()).setInt("v3", (*discInfo).getDiscChapterNum()).setString("v4", serial);
	
	try {
		row = query.selectRow();
		
		//if error was not thrown, this disc is already in database;
		//set Disc ID and rating
		(*discInfo).setDiscID(row[0]);
		(*discInfo).setDiscRating(row[1]);
	}
	catch(tntdb::Error &e) {
      if(0 == strcmp("not found", e.what())) {
		   //if error thrown is tntdb::NotFound, this disc does not exist so insert
		   query = conn.prepare("INSERT INTO Disc (Disc_Name, Disc_Length, Disc_NumChapters, Disc_Rating_ID, Disc_Serial) VALUES (:v1, :v2, :v3, :v4, :v5)");
		   query.setString("v1", discname).setInt("v2", (*discInfo).getDiscLength()).setInt("v3", (*discInfo).getDiscChapterNum()).setInt("v4", (*discInfo).getDiscRating());
		   query.setString("v5", serial);
         
         try {
		      query.execute();
			 
			  query = conn.prepare("SELECT Disc_ID FROM Disc WHERE Disc_Name = :v1 AND Disc_Length = :v2 AND Disc_NumChapters = :v3 AND Disc_Serial = :v4");
			  query.setString("v1", discname).setInt("v2", (*discInfo).getDiscLength()).setInt("v3", (*discInfo).getDiscChapterNum()).setString("v4", serial);
			 
			  (*discInfo).setDiscID(query.selectValue());
	
         }
         catch(tntdb::Error &e) {
            return DB_GEN_ERROR;
         }
      }
      else
         return DB_GEN_ERROR;
		
		//get ID for this discID
		getDisc(discInfo);
	}
	
	return SUCCESS;
}

int Database::getDisc(Disc *disc)
{
	tntdb::Statement query;
	tntdb::Row row;
	std::string discname = (*disc).getDiscName();
	std::string serial = (*disc).getDiscSerial();
	
	query = conn.prepare("SELECT Disc_ID, Disc_Rating_ID FROM Disc WHERE Disc_Name = :v1 AND Disc_Length = :v2 AND Disc_NumChapters = :v3 AND Disc_Serial = :v4");
	query.setString("v1", discname).setInt("v2", (*disc).getDiscLength());
	query.setInt("v3", (*disc).getDiscChapterNum()).setString("v4", serial);
	
	try {
		row = query.selectRow();
		
		(*disc).setDiscID(row[0]);
		(*disc).setDiscRating(row[1]);
	}
	catch(tntdb::Error &e) {
      if(0 == strcmp("not found", e.what())) {
		   //this disc does not exist, return false
		   return DB_UNKNOWN_DISC;
      }
      else
         return DB_GEN_ERROR;
	}
	
	return SUCCESS;
}

void Database::printErrorMessage(int errorNumber) {
   
   char *errorMessage;
   
   switch(errorNumber) {
      
      case DB_GEN_ERROR:
            errorMessage = "Unknown general DB error likely caused by SQL syntax.";
            break;
      case DB_DATABASE_NOT_FOUND:
            errorMessage = "Could not find database to open.";
            break;
      case DB_UNKNOWN_USER:
            errorMessage = "Username not found in database.";
            break;
      case DB_UNKNOWN_DISC:
            errorMessage = "Disc not found in database.";
            break;
      case DB_UNKNOWN_PROFILE:
            errorMessage = "Profile not found in database.";
            break;
      case DB_BAD_PASSWORD:
            errorMessage = "Invalid password given for user.";
            break;
      case DB_USERNAME_IN_USE:
            errorMessage = "Username in use by another user.";
            break;
      case SUCCESS:
            errorMessage = "SUCCESS";
            break;
      default:
            errorMessage = "Unspecified Error!!";
            break;
   }
   
   printf("\n%s\n", errorMessage);
}

int Database::userExists(User *user) {
   
   tntdb::Statement query;
   int id;
   
   query = conn.prepare("SELECT User_ID FROM Users WHERE Username = :v1");
	query.setString("v1", (*user).getUser());
   
   //see if username exists
   try {          
      id = query.selectValue();
   }
   catch(tntdb::Error &d) {
      if(0 == strcmp("not found", d.what())) {
         //user does not exist
         return DB_UNKNOWN_USER;
      }
      else
        return DB_GEN_ERROR;
   }
   
   //if exception was not thrown, username exists
   if(id != (*user).getUserID()) {
      //username in use by another user
      return DB_USERNAME_IN_USE;
   }
   else
      return SUCCESS;
}

int Database::fillSecretQuestionAndIcon(User *user)
{
	tntdb::Statement query;
	tntdb::Row row;
	std::string returnQuestion, returnIcon;
	
	query = conn.prepare("SELECT User_ID, Username, Secret_Question, User_Icon FROM Users WHERE Username = :v1");
	query.setString("v1", (*user).getUser());
	
	try
	{
		row = query.selectRow();
	}
	catch(tntdb::Error &e)
	{
		//calling function has already ensured user exists
		//any error must be DB error
		return DB_GEN_ERROR;
	}
	
	//fill secret question
	returnQuestion = (std::string) row[2];
	returnIcon = (std::string) row[3];
	(*user).setQuestion(returnQuestion);
	(*user).setUserIcon(returnIcon);
	
	return SUCCESS;
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
**/

#define TEST_USER true
#define TEST_DISC true
#define TEST_PROFILE true
#define DELETE_PROFILE true
#define DELETE_USER true

void DBTest::do_DBTest()
{
	Database db;
   	Disc sampleDisc, returnDisc;
   	Profile sampleProfile, returnProfile;
   	User sampleUser, returnUser;
   	SkipTime skip1, skip2;
	std::vector <std::string> userList;
	std::vector <std::string> iconList;
	
 
   	std::string discname = "We Were Soldiers";
   	std::string username = "aUser2";
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

   skip1.setSkipStart(2100);
   skip1.setSkipStop(2203);
   //skip1.setAudioOnly(false);

   skip2.setSkipStart(1200);
   skip2.setSkipStop(1303);
   //skip2.setAudioOnly(true);

   //note: will need to set userID, discID once User and Disc
   //are inserted and IDs assigned
   sampleProfile.addSkipChapter(12);
   sampleProfile.addSkipChapter(2);
   sampleProfile.addSkipChapter(5);
   sampleProfile.addSkipTime(skip1);
   sampleProfile.addSkipTime(skip2);

   /**
    * Use objects to insert data into database.
   **/

   if(SUCCESS != db.storeDisc(&sampleDisc)) {
      printf("\nInsert Disc\n");
      exit(1);
   }

	
   if(SUCCESS != db.storeUser(&sampleUser)) {
      printf("\nInsert User\n");
      exit(1);
   }

   sampleProfile.setUserID(sampleUser.getUserID());
   sampleProfile.setDiscID(sampleDisc.getDiscID());

   if(SUCCESS != db.storeProfile(&sampleProfile)) {
      printf("\nInsert Profile\n");
      exit(1);
   }
   
   //enter second user
   username = "Jimmy";
   pwdhash = "pwdGoesHere";
   iconfile = "/home/jimmy/icon";
   sampleUser.setUser(username);
   sampleUser.setPasswordHash(pwdhash);
   sampleUser.setUserIcon(iconfile);
   sampleUser.setPlayUnknownDisc(true);
   sampleUser.setMaxPlayLevel(5);
   sampleUser.setLastMoviePos(3321);
   sampleUser.setUserID(0);
   
   if(SUCCESS != db.storeUser(&sampleUser)) {
      printf("\nInsert User 2\n");
      exit(1);
   }
   
   //try getting user and icon lists
   userList = db.getUserList();
   iconList = db.getIconList();
   
   if(userList.size() != 3 || 0 != (userList[0]).compare("admin")) {
	   printf("\nUser List %s\n", (userList[0]).c_str());
	   exit(1);
   }
   if(iconList.size() != 3) {
	   printf("\nIcon List\n");
	   exit(1);
   }
   
   
   
   //set up necessary info in return objects for get* functions
   returnUser.setUser(username);
   returnUser.setPasswordHash(pwdhash);
   
   returnProfile.setDiscID(sampleProfile.getDiscID());
   returnProfile.setUserID(sampleProfile.getUserID());
   
   returnDisc.setDiscLength(sampleDisc.getDiscLength());
   returnDisc.setDiscName(discname);
   returnDisc.setDiscChapterNum(sampleDisc.getDiscChapterNum());

   /**
    * Get data from database to compare with sample data.
   **/
	if(TEST_USER) {
   		db.getUser(&returnUser);
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
	   
	   
   
	}

	if(TEST_DISC) {
	   db.getDisc(&returnDisc);
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
	   db.getProfile(&returnProfile);
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
	   if(!(sampleProfile.getSkipChapters() == returnProfile.getSkipChapters())) {
		   printf("\nProfile Skip Chapters\n");
		   exit(1);
	   }
	   
	   std::vector<SkipTime> sampleSkips = sampleProfile.getSkipTimes();
	   std::vector<SkipTime> returnSkips = returnProfile.getSkipTimes();
	   
	   if(sampleSkips.size() != returnSkips.size()) {
		   printf("\nProfile Skip Times\n");
		   exit(1);
	   }
	   else {
		   for(unsigned int i = 0; i < sampleSkips.size(); i++) {
			   if(!(sampleSkips[i] == returnSkips[i])) {
				   printf("\nProfile Skip Times\n");
				   exit(1);
			   }
		   }
	   }
	
	   //if we've gotten this far, the Profile is correct
	   printf("\nProfile good!\n");
	   
	   
	 
	}
	
	
	if(DELETE_PROFILE) {
		if(SUCCESS != db.deleteProfile(&returnProfile)) {
			printf("\nDelete Profile\n");
			exit(1);
		}
	}
		
	if(DELETE_USER)
	{
		if(SUCCESS != db.deleteUser(&returnUser)) {
			printf("\nDelete User\n");
			exit(1);
		}
	}
}
