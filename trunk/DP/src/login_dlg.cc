// generated 2007/10/28 18:51:11 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to login_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "login_dlg.hh"
#include "controller.h"
#include "std_errors.h"
#include "images.h"
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>

extern Controller* useController();

void login_dlg::on_admin_psswrd_edit_box_editing_done()
{  
}

void login_dlg::on_admin_login_button_clicked()
{  
	std::string admin = "admin";
	int status;
	if ( m_error_count < 3 )
	{
		std::string password = admin_psswrd_edit_box->get_text();	
		status = useController()->loadCurrentUser(admin,password);
	}
	else
	{
		std::string answer = secret_a_edit_box->get_text();
		status = useController()->loadCurrentUser(admin,answer);
	}
	if ( status == DB_BAD_PASSWORD )
	{
		admin_psswrd_edit_box->set_text("");
		m_error_count++;
		if ( m_error_count > 2 )
		{
			admin_login_label->hide();
			admin_psswrd_edit_box->hide();
			secret_q_edit_box->show();
   			secret_a_edit_box->show();
   			secret_question_label->show();
   			secret_answer_label->show();			
			login_hint_label->set_text("\t\t\t\tYou must reset your password");
		}
		else login_hint_label->set_text("Incorrect password");
		return;
	}
	hide();
}

void login_dlg::on_previous_user_button_clicked()
{
	admin_icon->hide();
	const std::string filename = "/Projects/DP/pixmaps/eye.png";
	admin_login_button->remove();
	admin_icon = Gtk::manage(new class Gtk::Image(filename));   
	admin_login_button->add(*admin_icon);
	admin_icon->show();	
}

void login_dlg::on_next_user_button_clicked()
{  
	//shift all user icons to left
}

void login_dlg::on_user_icon_select_button_1_clicked()
{  
	//if (status == DB_BAD_PASSWORD)
	//{
	icon1_password_edit_box->show();
	user_icon_select_button_2->hide();
	user_icon_select_button_3->hide();
	icon1_password_label->show();
	//}
}

void login_dlg::on_user_icon_select_button_2_clicked()
{  
	//if (status == DB_BAD_PASSWORD)
	//{
	icon2_password_edit_box->show();
	user_icon_select_button_1->hide();
	user_icon_select_button_3->hide();
	icon2_password_label->show();
	//}
}

void login_dlg::on_user_icon_select_button_3_clicked()
{  
	//if (status == DB_BAD_PASSWORD)
	//{
	icon3_password_edit_box->show();
	user_icon_select_button_1->hide();
	user_icon_select_button_2->hide();
	icon3_password_label->show();
	//}
}

void login_dlg::oninit()
{
	user_button1_icon->hide();
	const std::string filename = "/Projects/DP/pixmaps/eye.png";
	user_icon_select_button_1->remove();
	user_button1_icon = Gtk::manage(new class Gtk::Image(filename));   
	user_icon_select_button_1->add(*user_button1_icon);
	user_button1_icon->show();	
	
	user_button2_icon->hide();
	const std::string filename2 = "/Projects/DP/pixmaps/tired_smile.png";
	user_icon_select_button_2->remove();
	user_button2_icon = Gtk::manage(new class Gtk::Image(filename2));   
	user_icon_select_button_2->add(*user_button2_icon);
	user_button2_icon->show();	
	
	user_button3_icon->hide();
	const std::string filename3 = "/Projects/DP/pixmaps/truck.png";
	user_icon_select_button_3->remove();
	user_button3_icon = Gtk::manage(new class Gtk::Image(filename3));   
	user_icon_select_button_3->add(*user_button3_icon);
	user_button3_icon->show();	
}
