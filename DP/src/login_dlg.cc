// generated 2007/10/28 18:51:11 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to login_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "login_dlg.hh"
#include "controller.h"
#include "std_errors.h"
#include "math.h"
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>
#include <vector>
#include <string>

extern Controller* useController();

void login_dlg::on_admin_psswrd_edit_box_editing_done()
{  
}

void login_dlg::on_admin_login_button_clicked()
{  
	string admin = "admin";
	int status;
	if ( m_error_count < 3 )
	{
		string password = admin_psswrd_edit_box->get_text();		
		status = useController()->loadCurrentUser(admin,password);
		if ( status == DB_GEN_ERROR )
			printf("general_error");
	}
	else
	{
		string answer = secret_a_edit_box->get_text();
		status = useController()->loadCurrentUserWithAnswer(admin,answer);
	}
	if ( status == DB_BAD_PASSWORD )
	{
		printf("\nbad password");
		admin_psswrd_edit_box->set_text("");
		m_error_count++;
		if ( m_error_count > 2 )
		{
			const User *user_admin = useController()->c_getUserLoggedIn();
			string question = user_admin->getQuestion();		
			admin_login_label->hide();
			admin_psswrd_edit_box->hide();
			secret_q_edit_box->show();
   			secret_a_edit_box->show();
   			secret_question_label->show();
   			secret_answer_label->show();
			secret_q_edit_box->set_text(question);			
			login_hint_label->set_text("\t\t\t\tYou must reset your password");
		}
		else login_hint_label->set_text("Incorrect password");
		return;
	}
	hide();
}

void login_dlg::on_previous_user_button_clicked()
{
	shifted-=min(shifted,3);
	setupButton1(icon_list.at(1+shifted),user_list.at(1+shifted));
	setupButton2(icon_list.at(2+shifted),user_list.at(2+shifted));	
	setupButton3(icon_list.at(3+shifted),user_list.at(3+shifted));	
}

void login_dlg::on_next_user_button_clicked()
{  
	int remaining_icons = user_list.size() - shifted - 4;
	if ( remaining_icons < 1 ) return;
	shifted+=min(remaining_icons,3);			
	setupButton1(icon_list.at(1+shifted),user_list.at(1+shifted));
	setupButton2(icon_list.at(2+shifted),user_list.at(2+shifted));	
	setupButton3(icon_list.at(3+shifted),user_list.at(3+shifted));	
}

void login_dlg::on_user_icon_select_button_1_clicked()
{  
	string password = icon1_password_edit_box->get_text();
	int status = 
		useController()->loadCurrentUser(user_list.at(1+shifted),password);
	if (status == DB_BAD_PASSWORD)
	{
		next_user_button->hide();
		previous_user_button->hide();
		user1_label->hide();
		user2_label->hide();
		user3_label->hide();
		icon1_password_edit_box->show();
		user_icon_select_button_2->hide();
		user_icon_select_button_3->hide();
		icon1_password_label->show();
		icon1_password_edit_box->set_text("");		
	}
	else hide();
}

void login_dlg::on_user_icon_select_button_2_clicked()
{  
	if ( user_list.size() < 2 ) return;
	string password = icon2_password_edit_box->get_text();
	login_hint_label->set_text(password);
	int status = 
		useController()->loadCurrentUser(user_list.at(2+shifted),password);
	if (status == DB_BAD_PASSWORD)
	{
		next_user_button->hide();
		previous_user_button->hide();
		user1_label->hide();
		user2_label->hide();
		user3_label->hide();
		icon2_password_edit_box->show();
		user_icon_select_button_1->hide();
		user_icon_select_button_3->hide();
		icon2_password_label->show();
		icon2_password_edit_box->set_text("");		
	}
	else hide();
}

void login_dlg::on_user_icon_select_button_3_clicked()
{  
	string password = icon3_password_edit_box->get_text();
	int status = 
		useController()->loadCurrentUser(user_list.at(3+shifted),password);
	if (status == DB_BAD_PASSWORD)
	{
		next_user_button->hide();
		previous_user_button->hide();
		user1_label->hide();
		user2_label->hide();
		user3_label->hide();
		icon3_password_edit_box->show();
		user_icon_select_button_1->hide();
		user_icon_select_button_2->hide();
		icon3_password_label->show();
		icon3_password_edit_box->set_text("");		
	}
	else hide();
}

void login_dlg::oninit()
{
	shifted = 0;
	m_error_count = 0;
	icon_list = useController()->getIconList();
	user_list = useController()->getUserList();	
	
	if ( icon_list.size() > 1 )
	{	
		setupButton1(icon_list.at(1),user_list.at(1));		
	}
	else 
	{
		user_icon_select_button_1->hide();
		user_icon_select_button_3->hide();
		next_user_button->hide();
		previous_user_button->hide();
		setupButton2(string("/Projects/DP/pixmaps/no_user.png"),string("NO USERS EXIST"));		
		return;
	}
	
	if ( icon_list.size() > 2 )
	{
		setupButton2(icon_list.at(2),user_list.at(2));	
	}
	else user_icon_select_button_2->hide();
	
	if ( icon_list.size() > 3 )
	{
		setupButton3(icon_list.at(3),user_list.at(3));	
	}	
	else user_icon_select_button_3->hide();	
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
}

bool login_dlg::on_login_dlg_delete_event(GdkEventAny *ev)
{  
	exit(0);
}
