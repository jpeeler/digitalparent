// generated 2007/10/17 13:39:21 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to welcome_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "welcome_dlg.hh"
#include "controller.h"
#include <string.h>
#include "std_errors.h"
extern Controller *useController();


void welcome_dlg::oninit()
{
	Tux_image->hide();	
	fixed7->remove(*Tux_image);
	Tux_image = Gtk::manage(new class Gtk::Image("/Projects/DP/images/tux.png"));
	fixed7->put(*Tux_image, 24, 24);;		
	Tux_image->show();
}

void welcome_dlg::on_welcome_next_button_clicked()
{  
	std::string password = init_password_edit_box->get_text();
	std::string confirm = repeat_password_edit_box->get_text();		
	
	if ( password != confirm || password == "" || confirm == "" )
	{
		welcome_hint_label->set_text("passwords do not match!");
		init_password_edit_box->set_text("");
		repeat_password_edit_box->set_text("");
		return;
	}
	
	if ( password.size() < 5 )
	{
		welcome_hint_label->set_text("your password is too short");
		init_password_edit_box->set_text("");
		repeat_password_edit_box->set_text("");
		return;
	}
	
	std::string question = secret_q_edit_box->get_text();
	std::string answer = secret_a_edit_box->get_text();
	
	if ( question == "" || answer == "" ) 
	{
		welcome_hint_label->set_text("question and answer must have at least one character!");
		return;	
	}	
	std::string user = "admin";	
	useController()->c_setCurrentUser( user );	
	useController()->c_setCurrentUserIcon(std::string("/Projects/DP/images/tux.png"));	
	useController()->c_setCurrentUserPasswordHash( password );
	useController()->c_setCurrentUserSecretQuestion( question );
	useController()->c_setCurrentUserSecretAnswerHash( answer );
	useController()->c_setCurrentUserCanPlayUnknown( true );
	useController()->c_setCurrentUserMaxPlayLevel( NR );
	if ( useController()->storeCurrentUser() != SUCCESS )
		welcome_hint_label->set_text("can't create user");
	hide();
}

bool welcome_dlg::on_repeat_password_edit_box_key_press_event(GdkEventKey *ev)
{  
	//65293 is the GDK value for the enter button...
	if ( ev->keyval == 65293 ) 
		on_welcome_next_button_clicked();
	return(0);
}

bool welcome_dlg::on_secret_a_edit_box_key_press_event(GdkEventKey *ev)
{  
	if ( ev->keyval == 65293 )
		on_welcome_next_button_clicked();
	return(0);
}

bool welcome_dlg::on_welcome_dlg_delete_event(GdkEventAny *ev)
{  
	useController()->dp_state = DP_STOP;
	hide();
	return 0;
}
