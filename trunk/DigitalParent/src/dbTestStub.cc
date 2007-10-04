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

#define TEST_USER false
#define TEST_DISC false
#define TEST_PROFILE true
#define DELETE_PROFILE false
#define DELETE_USER false

#include "database.h"
#include <string>
#include <stdio.h> // for perror

int main(void) {

	Database db;
   	Disc sampleDisc, returnDisc;
   	Profile sampleProfile, returnProfile;
   	User sampleUser, returnUser;
   	SkipTime skip1, skip2;
   	//int userID, discID, profileID;
	
 
   	std::string discname = "We Were Soldiers";
   	std::string username = "TestUser2";
   	std::string pwdhash = "#PWDHasH!";
   	std::string iconfile = "/filename";
   	/**
     * Create objects with sample data for inserts.
   	**/
   	//sampleDisc = new Disc();
   	sampleDisc.setDiscName(discname);
   	sampleDisc.setDiscLength(123456789);
   	sampleDisc.setDiscChapterNum(12);
   	sampleDisc.setDiscRating(1);

   //note: need to set lastMovieID after Disc object is in database
   //sampleUser = new User();
   sampleUser.setUserID(0);
   sampleUser.setUser(username);
   sampleUser.setPasswordHash(pwdhash);
   sampleUser.setUserIcon(iconfile);
   sampleUser.setPlayUnknownDisc(false);
   sampleUser.setMaxPlayLevel(2);
   sampleUser.setLastMoviePos(4321);

   //skip1 = new Skip_Time();
   skip1.setSkipStart(1300);
   skip1.setSkipStop(1403);
   skip1.setAudioOnly(false);

   //skip2 = new Skip_Time();
   skip2.setSkipStart(2100);
   skip2.setSkipStop(2403);
   skip2.setAudioOnly(true);

   //note: will need to set userID, discID once User and Disc
   //are inserted and IDs assigned
   //sampleProfile = new Profile();
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
      perror("Insert Disc");
      exit(1);
   }
*/
	//returnUser = db.getUser(username, pwdhash);
	
   if(!db.storeUser(&sampleUser)) {
      perror("Insert User");
      exit(1);
   }

   sampleProfile.setUserID(sampleUser.getUserID());
   sampleProfile.setDiscID(2);//sampleDisc.getDiscID());
   //sampleProfile.getDiscID(); // check
   sampleProfile.setProfileID(0);

   if(!db.storeProfile(&sampleProfile)) {
      perror("Insert Profile");
      exit(1);
   }

   /**
    * Get data from database to compare with sample data.
   **/
if(TEST_USER) {
   returnUser = db.getUser((std::string&) sampleUser.getUser(), (std::string&) sampleUser.getPasswordHash());
   if(0 == returnUser.getUserID()) {
      perror("Get User");
      exit(1);
   }
   
   if(sampleUser.getUserID() != returnUser.getUserID()) {
      perror("User ID");
      exit(1);
   }
   if(sampleUser.getUser() != returnUser.getUser()) {
      perror("Username");
      exit(1);
   }
   if(sampleUser.getPasswordHash() != returnUser.getPasswordHash()) {
      perror("Password Hash");
      exit(1);
   }
   if(sampleUser.getUserIcon() != returnUser.getUserIcon()) {
      perror("User Icon");
      exit(1);
   }
   if(sampleUser.getPlayUnknownDisc() != returnUser.getPlayUnknownDisc()) {
      perror("User Unknown Discs");
      exit(1);
   }
   if(sampleUser.getMaxPlayLevel() != returnUser.getMaxPlayLevel()) {
      perror("User Max Play Level");
      exit(1);
   }
   if(sampleUser.getLastMovieID() != returnUser.getLastMovieID()) {
      perror("User Last Movie ID");
      exit(1);
   }
   if(sampleUser.getLastMoviePos() != returnUser.getLastMoviePos()) {
      perror("User Last Movie Position");
      exit(1);
   }
   
   //if we've gotten this far, the User is correct
   printf("\nUser good!\n");
   
   if(DELETE_USER)
   {
   		if(!db.removeUser(&returnUser)) {
      		perror("Delete User");
      		exit(1);
		}
   }
   
}

if(TEST_DISC) {
   returnDisc = db.getDisc((std::string&) sampleDisc.getDiscName(), sampleDisc.getDiscChapterNum(), sampleDisc.getDiscLength());
   if(0 == returnDisc.getDiscID()) {
      perror("Get Disc");
      exit(1);
   }
   
   if(sampleDisc.getDiscID() != returnDisc.getDiscID()) {
      perror("Disc ID");
      exit(1);
   }
   if(sampleDisc.getDiscName() != returnDisc.getDiscName()) {
      perror("Disc Name");
      exit(1);
   }
   if(sampleDisc.getDiscLength() != returnDisc.getDiscLength()) {
      perror("Disc Length");
      exit(1);
   }
   if(sampleDisc.getDiscChapterNum() != returnDisc.getDiscChapterNum()) {
      perror("Disc NumChapters");
      exit(1);
   }
   if(sampleDisc.getDiscRating() != returnDisc.getDiscRating()) {
      perror("Disc Rating");
      exit(1);
   }
   
   //if we've gotten this far, the Disc is correct
   printf("\nDisc good!\n");
   
}

if(TEST_PROFILE) {
   returnProfile = db.getProfile(sampleProfile.getDiscID(), sampleProfile.getUserID());
   if(0 == returnProfile.getProfileID()) {
      perror("Get Profile");
      exit(1);
   }
   
   if(sampleProfile.getProfileID() != returnProfile.getProfileID()) {
      printf("Profile ID");
      exit(1);
   }
   if(sampleProfile.getUserID() != returnProfile.getUserID()) {
      printf("Profile User ID");
      exit(1);
   }
   if(sampleProfile.getDiscID() != returnProfile.getDiscID()) {
      printf("Profile Disc ID");
      exit(1);
   }
   
   //add checks for skipped chapters and skipped times

   //if we've gotten this far, the Profile is correct
   printf("\nProfile good!\n");
   
   if(DELETE_PROFILE) {
		if(!db.removeProfile(&returnProfile)) {
      		perror("Delete Profile");
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
