// generated 2007/10/28 18:51:11 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to login_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "login_dlg.hh"
#include "std_errors.h"
#include "math.h"
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>
#include <vector>
#include <string>

extern Controller* useController();

void login_dlg::on_admin_psswrd_edit_box_editing_done()
{  
	on_admin_login_button_clicked();	
}

void login_dlg::on_admin_login_button_clicked()
{  	
	switch ( m_login_mode )
	{
		case ADMIN_START:
			back_button->show();
			hideUserLogin();
			admin_login_label->show();
			admin_psswrd_edit_box->show();
			m_login_mode = ADMIN_OK;
		break;					
		case ADMIN_OK:
		{					
			string password = admin_psswrd_edit_box->get_text();		
			m_status = useController()->loadCurrentUser(m_admin,password);
			switch ( m_status )
			{
				case DB_GEN_ERROR:
					m_ad_error_count++;
					printf("general_error");//for testing
					admin_psswrd_edit_box->set_text("");
					login_hint_label->set_text("Incorrect password");
				break;
				case DB_BAD_PASSWORD:
					m_ad_error_count++;
					printf("\nbad password");//for testing
					admin_psswrd_edit_box->set_text("");
					login_hint_label->set_text("Incorrect password");
				break;
				case SUCCESS:
				{
					useController()->m_mode = ADMIN_PANEL;
					hide();
				break;
				}
				default:
					m_ad_error_count++;
					admin_psswrd_edit_box->set_text("");
				break;
			}
			if ( m_ad_error_count > 2 ) 
			{
				m_login_mode = ADMIN_LOST_PASSWORD;
				tooManyErrors(m_admin);				
			}
		break;
		}
		case ADMIN_LOST_PASSWORD:		
			loginWithAnswer(m_admin);					
		break;	
		case B1_LOST_PASSWORD:
			loginWithAnswer(m_user_list.at(1+m_shifted));					
		break;	
		case B2_LOST_PASSWORD:						
			loginWithAnswer(m_user_list.at(2+m_shifted));					
		break;		
		case B3_LOST_PASSWORD:
			loginWithAnswer(m_user_list.at(3+m_shifted));					
		break;	
		default:
			break;
	}	
}

void login_dlg::on_previous_user_button_clicked()
{
	m_shifted-=min(m_shifted,3);
	setupButtons();	
}

void login_dlg::on_next_user_button_clicked()
{  
	int remaining_icons = m_user_list.size() - m_shifted - 4;
	if ( remaining_icons < 1 ) return;
	m_shifted+=min(remaining_icons,3);			
	setupButtons();		
}

void login_dlg::on_user_icon_select_button_1_clicked()
{  
	back_button->show();
	admin_login_button->hide();
	admin_label->hide();
	string password = icon1_password_edit_box->get_text();
	int m_status = 
		useController()->loadCurrentUser(m_user_list.at(1+m_shifted),password);
	if (m_status == DB_BAD_PASSWORD)
	{
		if ( m_b1_error_count++ == 3 )
		{			
			tooManyErrors(m_user_list.at(1+m_shifted));
			m_login_mode = B1_LOST_PASSWORD;
			icon1_password_edit_box->hide();
			icon1_password_label->hide();
			return;
		}
		userLoginInit();
		icon1_password_edit_box->show();
		user_icon_select_button_2->hide();
		user_icon_select_button_3->hide();
		icon1_password_label->show();
		icon1_password_edit_box->set_text("");		
	}
	else 
	{
		useController()->m_mode = USER_PANEL;
		hide();
	}
}

void login_dlg::on_user_icon_select_button_2_clicked()
{  
	if ( m_user_list.size() < 2 ) return; //this is when there are no user yet
	admin_login_button->hide();
	admin_label->hide();
	back_button->show();
	string password = icon2_password_edit_box->get_text();
	login_hint_label->set_text(password);
	int status = 
		useController()->loadCurrentUser(m_user_list.at(2+m_shifted),password);
	if (status == DB_BAD_PASSWORD)
	{
		if ( m_b2_error_count++ == 3 )
		{			
			tooManyErrors(m_user_list.at(2+m_shifted));
			m_login_mode = B2_LOST_PASSWORD;
			icon2_password_edit_box->hide();
			icon2_password_label->hide();
			return;
		}
		userLoginInit();
		icon2_password_edit_box->show();
		user_icon_select_button_1->hide();
		user_icon_select_button_3->hide();
		icon2_password_label->show();
		icon2_password_edit_box->set_text("");		
	}
	else 
	{
		useController()->m_mode = USER_PANEL;
		hide();
	}
}

void login_dlg::on_user_icon_select_button_3_clicked()
{  
	back_button->show();
	admin_login_button->hide();
	admin_label->hide();
	string password = icon3_password_edit_box->get_text();
	int status = 
		useController()->loadCurrentUser(m_user_list.at(3+m_shifted),password);
	if (status == DB_BAD_PASSWORD)
	{
		if ( m_b1_error_count++ == 3 )
		{			
			tooManyErrors(m_user_list.at(3+m_shifted));
			m_login_mode = B3_LOST_PASSWORD;
			icon3_password_edit_box->hide();
			icon3_password_label->hide();
			return;
		}
		userLoginInit();
		icon3_password_edit_box->show();
		user_icon_select_button_1->hide();
		user_icon_select_button_2->hide();
		icon3_password_label->show();
		icon3_password_edit_box->set_text("");		
	}
	else 
	{
		useController()->m_mode = USER_PANEL;
		hide();
	}
}

void login_dlg::loginWithAnswer(string username)
{
	string answer = secret_a_edit_box->get_text();
	m_status = useController()->loadCurrentUserWithAnswer(username,answer);	
	if ( m_status == SUCCESS )
	{
		if ( username == "admin" )
			useController()->m_mode = ADMIN_PANEL;
		else 
			useController()->m_mode = USER_PANEL;
		hide();
	}
	else
	{
		login_hint_label->set_text("Incorrect answer");
		secret_a_edit_box->set_text("");
	}
}

void login_dlg::oninit(int shifted)
{
	m_shifted = 0 + shifted;
	m_ad_error_count = 0;
	m_b1_error_count = 0;
	m_b2_error_count = 0;
	m_b3_error_count = 0;
	m_login_mode = ADMIN_START;	
	m_icon_list = useController()->getIconList();
	m_user_list = useController()->getUserList();	
	m_admin = "admin";	
	
	icon1_password_edit_box->hide();
	icon2_password_edit_box->hide();
	icon3_password_edit_box->hide();
	icon1_password_label->hide();
	icon2_password_label->hide();
	icon3_password_label->hide();
	secret_a_edit_box->hide();
	secret_q_edit_box->set_text("");
	secret_q_edit_box->hide();
	secret_question_label->hide();
	secret_answer_label->hide();
	login_hint_label->set_text("");
	login_hint_label->hide();
	next_user_button->show();
	previous_user_button->show();
	back_button->hide();
	admin_login_label->hide();
	admin_psswrd_edit_box->hide();
	
	useController()->loadCurrentUser(m_admin,string(""));
	const User *a_user = useController()->c_getUserLoggedIn();
	const string filename = a_user->getUserIcon();
	setupAdminButton( filename, m_admin );
	
	if ( m_icon_list.size() > 3 )
	{
		setupButtons();	
		return;
	}
	
	user_icon_select_button_3->hide();

	if ( m_icon_list.size() > 2 )
	{
		setupButton2(m_icon_list.at(2),m_user_list.at(2));
		setupButton1(m_icon_list.at(1),m_user_list.at(1));	
		return;		
	}		
	
	if ( m_icon_list.size() > 1 )
	{	
		setupButton1(m_icon_list.at(1),m_user_list.at(1));	
		user_icon_select_button_2->hide();		
	}
	else 
	{
		user_icon_select_button_1->hide();
		next_user_button->hide();
		previous_user_button->hide();
		setupButton2(string("/Projects/DP/pixmaps/no_user.png"),string("NO USERS EXIST"));		
		return;
	}	
}

void login_dlg::setupButton1(const string filename, const string username)
{
	user_button1_icon->hide();
	user1_label->show();
	user1_label->set_text(username);	
	user_icon_select_button_1->remove();
	user_button1_icon = Gtk::manage(new class Gtk::Image(filename));   
	user_icon_select_button_1->add(*user_button1_icon);
	user_button1_icon->show();	
	user_icon_select_button_1->show();
}

void login_dlg::setupButton2(const string filename, const string username)
{
	user_button2_icon->hide();
	user2_label->show();
	user2_label->set_text(username);
	user_icon_select_button_2->remove();
	user_button2_icon = Gtk::manage(new class Gtk::Image(filename));   
	user_icon_select_button_2->add(*user_button2_icon);
	user_button2_icon->show();	
	user_icon_select_button_2->show();
}

void login_dlg::setupButton3(const string filename, const string username)
{
	user_button3_icon->hide();
	user3_label->show();
	user3_label->set_text(username);
	user_icon_select_button_3->remove();
	user_button3_icon = Gtk::manage(new class Gtk::Image(filename));   
	user_icon_select_button_3->add(*user_button3_icon);
	user_button3_icon->show();	
	user_icon_select_button_3->show();
}

void login_dlg::setupAdminButton(const string filename, const string username)
{
	admin_icon->hide();
	admin_login_button->remove();
	admin_label->set_text(username);
	admin_label->show();	
	admin_icon = Gtk::manage(new class Gtk::Image(filename));
	admin_login_button->add(*admin_icon);
	admin_icon->show();
	admin_login_button->show();
}

void login_dlg::userLoginInit()
{
	next_user_button->hide();
	previous_user_button->hide();
	user1_label->hide();
	user2_label->hide();
	user3_label->hide();	
}	

void login_dlg::setupButtons()
{
	setupButton1(m_icon_list.at(1+m_shifted),m_user_list.at(1+m_shifted));
	if ( m_user_list.size() > 2 )
		setupButton2(m_icon_list.at(2+m_shifted),m_user_list.at(2+m_shifted));	
	if ( m_user_list.size() > 3 )
		setupButton3(m_icon_list.at(3+m_shifted),m_user_list.at(3+m_shifted));	
}

void login_dlg::tooManyErrors(string username)
{
	hideUserLogin();
	admin_login_label->hide();
	admin_psswrd_edit_box->hide();
	secret_q_edit_box->show();
   	secret_a_edit_box->show();
   	secret_question_label->show();
   	secret_answer_label->show();	
	useController()->loadCurrentUser(username,string(""));
	const User *a_user = useController()->c_getUserLoggedIn();
	const string filename = a_user->getUserIcon();
	setupAdminButton(filename,username);	
	string question = a_user->getQuestion();			
	secret_q_edit_box->set_text(question);			
	login_hint_label->set_text("\t\t\t\tYou must reset your password");
	login_hint_label->show();
}

void login_dlg::hideUserLogin()
{
	user_icon_select_button_1->hide();	
	user_icon_select_button_2->hide();
	user_icon_select_button_3->hide();
	userLoginInit();
}

void login_dlg::on_back_button_clicked()
{  
	oninit(m_shifted);	
}

bool login_dlg::on_login_dlg_delete_event(GdkEventAny *ev)
{  
	exit(0);
}

bool login_dlg::on_admin_psswrd_edit_box_key_press_event(GdkEventKey *ev)
{  
	//by printf("\n%d",ev->keyval), you can figure out values
	//65293 is the GDK value for the enter button...
	if (ev->keyval == 65293) on_admin_login_button_clicked();		
	return 0;
}

bool login_dlg::on_secret_a_edit_box_key_press_event(GdkEventKey *ev)
{  
	if (ev->keyval == 65293) on_admin_login_button_clicked();
	return 0;
}

bool login_dlg::on_icon1_password_edit_box_key_press_event(GdkEventKey *ev)
{  
	if (ev->keyval == 65293) on_user_icon_select_button_1_clicked();
	return 0;
}

bool login_dlg::on_icon2_password_edit_box_key_press_event(GdkEventKey *ev)
{  
	if (ev->keyval == 65293) on_user_icon_select_button_2_clicked();
	return 0;
}

bool login_dlg::on_icon3_password_edit_box_key_press_event(GdkEventKey *ev)
{  
	
	if (ev->keyval == 65293) on_user_icon_select_button_3_clicked();
	return 0;
}
