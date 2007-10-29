// generated 2007/10/28 18:51:11 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to login_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "login_dlg.hh"
#include "controller.h"
#include "std_errors.h"
extern Controller* useController();

void login_dlg::on_admin_psswrd_edit_box_editing_done()
{  
}

void login_dlg::on_previous_user_button_clicked()
{  
}

void login_dlg::on_admin_login_button_clicked()
{  
	std::string admin = "admin";
	int status;
	if ( m_error_count < 4 )
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
		if ( m_error_count > 3 )
		{
			admin_login_label->hide();
			admin_psswrd_edit_box->hide();
			secret_q_edit_box->show();
   			secret_a_edit_box->show();
   			secret_question_label->show();
   			secret_answer_label->show();			
			login_hint_label->set_text("\t\t\t\tYou must reset your password");
		}
		else login_hint_label->set_text("incorrect password");
		return;
	}
	hide();
}

void login_dlg::on_next_user_button_clicked()
{  
}

void login_dlg::on_user_icon_select_button_2_clicked()
{  
}

void login_dlg::on_user_icon_select_button_1_clicked()
{  
}

void login_dlg::on_user_icon_select_button_3_clicked()
{  
}