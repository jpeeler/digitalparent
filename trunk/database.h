/**
 * Header file for database / SQLite interface module.
**/
#ifndef DATABASE_H
#define DATABASE_H

#include "data_structure.h"

Profile getProfile(int diskID, int userID);
bool storeProfile(Profile *profile);
bool removeProfile(Profile *profile);
User getUser(std::string& username, std::string& password);
bool storeUser(User *user);
bool removeUser(User *user);
bool storeDisc(Disc *discInfo);
Disc getDisc(std::string& discName, int numChapters, long discLength);

#endif
