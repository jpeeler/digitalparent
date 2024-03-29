// generated 2007/10/15 10:20:36 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to digitalparent.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm/main.h>
#include <glib/gi18n.h>
#include <iostream>

#include "login_dlg.hh"
#include "media_player_dlg.hh"
#include "welcome_dlg.hh"
#include "admin_dlg.hh"
#include "controller.h"
#include "std_errors.h"

#define RUN_WINDOW true
#define TEST_CONTROLLER false
#define TEST_DATABASE false
#define TEST_DATA_STRUCTURE false
#define TEST_WINDOWS false
#define SHOW_WELCOME false
#define TEST_USERS true //this tests a heavy load of users

// the one and only controller
Controller m_control;

// global function to allow all objects to access controller
Controller* useController()
{
	return &m_control;
}

using namespace std;

void fillWithUsers();

int main(int argc, char **argv)
{
   #if DEB_MODE
     // for creating debs
     useController()->img_dir = "/usr/share/DigitalParent/";
     useController()->pixmaps_dir = "/usr/share/pixmaps/";
   #else
     // the globally accessed hard coded paths
     useController()->img_dir = "/Projects/DP/data/";   
     useController()->pixmaps_dir = "/Projects/DP/pixmaps/";
   #endif
	
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS   

#if RUN_WINDOW
   Gtk::Main m(&argc, &argv);
   useController()->dp_state = DP_START;
   welcome_dlg *welcome_dlg;   
   admin_dlg *admin_dlg;   
   login_dlg *login_dlg;   
   media_player_dlg *media_player_dlg;
	
   
#if TEST_USERS
	fillWithUsers();
#endif	   
	
   while ( useController()->dp_state != DP_STOP )
   {
	   switch ( useController()->dp_state )
	   {
		   case DP_START:
		   {
			   std::string password = "";							   
			   std::string admin = "admin";	   
			   int status = 
			   		useController()->loadCurrentUser(admin,password);
		   	   switch( status )
			   {
				   case DB_UNKNOWN_USER:
					   useController()->dp_state = DP_RUNONCE;
				   break;
				   case DB_BAD_PASSWORD:
					   useController()->dp_state = DP_LOGIN;
				   break;				   
				   default:
					   useController()->dp_state = DP_STOP;
				   		// figure this out later
				   break;
			   }		   			   
		   break;
		   }		   
		   case DP_RUNONCE:
		   {
			   welcome_dlg = new class welcome_dlg();
				   welcome_dlg->oninit();
				   m.run(*welcome_dlg);
			   delete welcome_dlg;
			   std::string password = "";							   
			   std::string admin = "admin";
			   int status = 
			   		useController()->loadCurrentUser(admin,password);
			   if ( status == DB_UNKNOWN_USER ) exit(0);
			   useController()->dp_state = DP_ADMIN_PANEL;
		   break;
		   }			   
		   case DP_LOGIN:
		   {
			   login_dlg =  new class login_dlg();
				login_dlg->oninit(0);				   
				   m.run(*login_dlg);
			   delete login_dlg;		   							   
		   break;
		   }		   
		   case DP_USER_PANEL:
		   {			   
			   admin_dlg = new class admin_dlg();
				   admin_dlg->oninit_icons();
				   admin_dlg->oninit_user();
				   m.run(*admin_dlg);
			   delete admin_dlg;			   
		   break;
		   }			   
		   case DP_ADMIN_PANEL:
			   admin_dlg = new class admin_dlg();
			   		admin_dlg->oninit_icons();	
			   		admin_dlg->oninit_admin();  			       		   	   
			   		m.run(*admin_dlg);
			   delete admin_dlg;			   		   			   
		   break;		   
		   case DP_USER_PLAY:
		   {
			  media_player_dlg = new class media_player_dlg();
					media_player_dlg->init();  
			  		m.run(*media_player_dlg);
			  delete media_player_dlg;			  		   	
		   break;
		   }		     
		   case DP_ADMIN_PLAY:
		   {
			   media_player_dlg = new class media_player_dlg();
				   media_player_dlg->init();  
				   m.run(*media_player_dlg);
			   delete media_player_dlg;
			   useController()->dp_state = DP_ADMIN_PANEL;
		   break;
		   }		   	   
	   	   default:
			   //do nothing, should exit while loop
		   break;
	   }
   }   


#endif
   
#if TEST_WINDOWS
   Gtk::Main m(&argc, &argv);
  //  welcome_dlg *welcome_dlg = new class welcome_dlg();
//	 m.run(*welcome_dlg);	
 //delete welcome_dlg;
	

//~ login_dlg *login_dlg = new class login_dlg();
	//~ m.run(*login_dlg);	
//~ delete login_dlg;

//psswrd_prompt_dlg *psswrd_prompt_dlg = new class psswrd_prompt_dlg();
//	m.run(*psswrd_prompt_dlg);
//delete psswrd_prompt_dlg;	

   admin_dlg *admin_dlg = new class admin_dlg();
	   m.run(*admin_dlg);
   delete admin_dlg;	

/*   
media_player_dlg *media_player_dlg = new class media_player_dlg();
   m.run(*media_player_dlg);
delete media_player_dlg;
*/

#endif

  
#if TEST_CONTROLLER
	printf("\n------ Begin Controller Test ------\n\n");
	TestController::do_test();
	printf("\n------- End Controller Test -------\n\n");
#endif
	
#if TEST_DATABASE
	printf("\n------ Begin Database Test ------\n\n");
	DBTest::do_DBTest();
	printf("\n------- End Database Test -------\n\n");
#endif
	
#if TEST_DATA_STRUCTURE
	printf("\n------ Begin Data Structure Test ------\n\n");
	DataTest::do_test();
	printf("\n------- End Data Structure Test -------\n\n");
#endif

#if SHOW_WELCOME
	Gtk::Main m(&argc, &argv);
	welcome_dlg *welcome_dlg = new class welcome_dlg();
		m.run(*welcome_dlg);
	delete welcome_dlg;
	
	const User *auser = useController()->c_getUserLoggedIn();
	printf("%s",auser->getPasswordHash().c_str());	
#endif
	
    return 0;
}

void fillWithUsers()
{
	// setup user Jeremy
	useController()->c_setCurrentUser(std::string("Jeremy"));
	useController()->c_setCurrentUserPasswordHash(std::string("jeremys_password"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("one"));
	useController()->c_setCurrentUserIcon(useController()->img_dir + "tired_smile.png");
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(NR);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Jeff
	useController()->c_setCurrentUser(std::string("Jeff"));
	useController()->c_setCurrentUserPasswordHash(std::string(""));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("two"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "pirate.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(X);//someone has to test x, sorry
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Chris
	useController()->c_setCurrentUser(std::string("Chris"));
	useController()->c_setCurrentUserPasswordHash(std::string(""));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("three"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "roswell_smile.png"));
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(R);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Paul
	useController()->c_setCurrentUser(std::string("Paul"));
	useController()->c_setCurrentUserPasswordHash(std::string("pauls_password"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("four"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "full_matrix.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(G);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Cindy
	useController()->c_setCurrentUser(std::string("Cindy"));
	useController()->c_setCurrentUserPasswordHash(std::string("candy"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("five"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "butterfly.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(G);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Marsha
	useController()->c_setCurrentUser(std::string("Marsha"));
	useController()->c_setCurrentUserPasswordHash(std::string("boys"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("six"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "sun.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(NC17);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user OtherBradyGirl
	useController()->c_setCurrentUser(std::string("OtherBradyGirl"));
	useController()->c_setCurrentUserPasswordHash(std::string("straightjacket"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("seven"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "weird.png"));
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(PG13);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Alice
	useController()->c_setCurrentUser(std::string("Alice"));
	useController()->c_setCurrentUserPasswordHash(std::string("sam"));
	useController()->c_setCurrentUserSecretQuestion(string("number?"));
	useController()->c_setCurrentUserSecretAnswerHash(string("eight"));
	useController()->c_setCurrentUserIcon(std::string(useController()->img_dir + "foxy_smile.png"));
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(R);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();	
	
}
