/**
 * Header file for database / SQLite interface module.
**/

#include "data_structure.h"

Profile getProfile(int diskID, int userID);
bool storeProfile(Profile *profile);
bool deleteProfile(Profile *profile);
User getUser(std::string username, std::string password);
bool storeUser(User *user);
bool deleteUser(User *user);
bool storeDisc(Disc *discInfo);
Disc getDisc(std::string discName, int numChapters, long discLength);
