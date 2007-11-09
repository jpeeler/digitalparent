// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "admin_dlg.hh"
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>
#include <iostream>

using namespace std;

void admin_dlg::on_logout_button_clicked()
{  
	useController()->dp_state = DP_LOGIN;
	useController()->c_clearUserLoggedIn();
	hide();
}

void admin_dlg::on_admin_settings_button_clicked()
{  
	ad_state = AD_SETTINGS;
}

void admin_dlg::fill_image_button_scroller( int mode )
{
	switch ( mode )
	{
		case ALL_ICONS:
		{
			m_icon_list = useController()->getIconList();					
			
			for ( unsigned int j = 0; j < m_file_list.size(); j++ )
			{
				bool user_icon = false;
				for ( unsigned int i = 0; i < m_icon_list.size(); i++ )
				{						
					if ( m_file_list.at(j) == m_icon_list.at(i) )											
						user_icon = true;
				}
				if ( user_icon )				
					m_button_list.at(j)->hide();					
				else
					m_button_list.at(j)->show();
			}

			frame2->show();		
		break;
		}
		
		case USER_ICONS:
		{
			m_icon_list = useController()->getIconList();
			m_user_list = useController()->getUserList();			
			
			for ( unsigned int j = 0; j < m_file_list.size(); j++ )
			{
				bool user_icon = false;
				for ( unsigned int i = 0; i < m_icon_list.size(); i++ )
				{						
					if ( m_file_list.at(j) == m_icon_list.at(i) )											
						user_icon = true;
				}
				if ( user_icon )				
					m_button_list.at(j)->show();					
				else
					m_button_list.at(j)->hide();
			}

			frame2->show();			
		break;
		}
	}
}

void admin_dlg::on_add_user_button_clicked()
{  	
	ad_state = AD_ADD_USER;
	fill_image_button_scroller(ALL_ICONS);
	m_user_image = "";
	
	hseparator2->show();
	vseparator1->show();
	frame2->show();
	icon_select_frame_label->show();
	frame1->show();
	
	user_label->set_text("");	
	user_name_edit_box->set_text("");
	user_name_edit_box->set_editable(true);	
	
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(string("/Projects/DP/pixmaps/no_user.png")));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();	
	
	password_edit_box->set_text("");
	password_edit_box->show();
	pw_checkbox->set_active(true);		
	confirm_edit_box->set_text("");
	cf_checkbox->set_active(true);	
	sq_edit_box->set_text("");	
	sq_checkbox->set_active(true);	
	sa_edit_box->set_text("");
	sa_checkbox->set_active(true);
	
	frame3->show();
	g_radio_button->set_active(true);	
	nr_checkbox->set_active(false);		
			
	user_save_button->show();
}

void admin_dlg::on_edit_user_button_clicked()
{  
	ad_state = AD_EDIT_USER;
	frame1->hide();
	frame3->hide();	
	fill_image_button_scroller(USER_ICONS);
	frame2->show();	
}

void admin_dlg::on_remove_user_button_clicked()
{  
	ad_state = AD_DELETE_USER;	
	frame1->hide();
	frame3->hide();	
	fill_image_button_scroller(USER_ICONS);
	frame2->show();
}

void admin_dlg::on_screen_movies_button_clicked()
{  
	if ( useController()->dp_state == DP_ADMIN_PANEL )
		useController()->dp_state = DP_ADMIN_PLAY;
	else useController()->dp_state = DP_USER_PLAY;
	hide();
}

void admin_dlg::oninit_admin()
{
	user_label->set_text("admin");
	
	frame3->hide();
	frame2->hide();
	frame1->hide();
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(string("/Projects/DP/pixmaps/tux.png")));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();

	m_admin = useController()->c_getUserLoggedIn();	
}

void admin_dlg::oninit_user()
{
	frame3->hide();
	frame2->hide();
	frame1->hide();
	edit_user_button->hide();
	add_user_button->hide();
	remove_user_button->hide();
	admin_settings_button->hide();
}

void admin_dlg::oninit_icons()
{
	system("ls /Projects/DP/images > pixmaps.dat");
	FILE *fp = fopen("pixmaps.dat","r");
	int c;
	string fname = useController()->img_dir;//"/Projects/DP/images/";
	c = fgetc(fp);
	class Gtk::Button *button;
	class Gtk::Image *image;
	m_icon_list = useController()->getIconList();
						
	while ( c != EOF )
	{
		if ( c == '\n' )
		{
														
			m_file_list.push_back(fname);
			image = Gtk::manage(new class Gtk::Image(fname)); 
			image->set_alignment(0.5,0.5);
   			image->set_padding(0,0);   
			m_image_list.push_back(image);				
			button = Gtk::manage(new class Gtk::Button());			
			button->set_flags(Gtk::CAN_FOCUS);
  			button->set_relief(Gtk::RELIEF_NORMAL);
			button->add(*image);
   			image->show();							
			button->show();				
			m_button_list.push_back(button);
			hbox5->pack_start(*button, Gtk::PACK_SHRINK, 0);
			button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::onIconButtonClicked), false);					
			fname = "/Projects/DP/images/";
		}
		else	fname+=c;
		c = fgetc(fp);
	}
}

void admin_dlg::on_user_save_button_clicked()
{  
	if ( m_user_image == "" )
	{
		error_label->set_text("Please choose an image");
		return;
	}
	
	string user = user_name_edit_box->get_text();
	
	if ( user == "" )
	{
		error_label->set_text("Please choose a name");
		return;
	}
	
	string password = password_edit_box->get_text();
	string confirm = confirm_edit_box->get_text();		
	
	if ( password != confirm || password == "" || confirm == "" )
	{		
		password_edit_box->set_text("");
		confirm_edit_box->set_text("");
		error_label->set_text("Password or Confirm error");
		return;
	}
	
	if ( password.size() < 5 )
	{		
		password_edit_box->set_text("");
		confirm_edit_box->set_text("");
		error_label->set_text("Password not long enough");
		return;
	}
	
	string question = sq_edit_box->get_text();
	string answer = sa_edit_box->get_text();
	
	if ( question == "" || answer == "" ) 
	{
		sq_edit_box->set_text("");
		sa_edit_box->set_text("");
		error_label->set_text("Q or A not filled in");
		return;	
	}
	
	bool unknown = nr_checkbox->get_state();
	int max_level = 0;
	if ( x_radio_button->get_state() == true )
		max_level = X;
	else if ( r_radio_button->get_state() == true )
		max_level = R;
	else if ( nc17_radio_button->get_state() == true )
		max_level = NC17;
	else if ( pg13_radio_button->get_state() == true )
		max_level = PG13;
	else if ( pg_radio_button->get_state() == true )
		max_level = PG;
	else if ( g_radio_button->get_state() == true )
		max_level = G;
	
	useController()->c_setOtherUser( user );
	useController()->c_setOtherUserIcon( m_user_image );
	useController()->c_setOtherUserPasswordHash( password );
	useController()->c_setOtherUserSecretQuestion( question );
	useController()->c_setOtherUserSecretAnswerHash( answer );
	useController()->c_setOtherUserCanPlayUnknown( unknown );
	useController()->c_setOtherUserMaxPlayLevel( max_level );
	if ( useController()->storeOtherUser() != SUCCESS )
		error_label->set_text("can't create user");
	else
	{
		error_label->set_text("User saved successfully");
		useController()->c_clearUserOther();
		for ( unsigned int i = 0; i < m_file_list.size(); i ++ )
		{
			if ( m_file_list.at(i) == m_user_image )
				m_button_list.at(i)->hide();
		}			
	}
}

void admin_dlg::on_un_checkbox_toggled()
{  
}

void admin_dlg::on_pw_checkbox_toggled()
{  
	bool visible = password_edit_box->get_visibility();
	if ( visible ) password_edit_box->set_visibility(false);
	else password_edit_box->set_visibility(true);
}

void admin_dlg::on_cf_checkbox_toggled()
{  
	bool visible = confirm_edit_box->get_visibility();
	if ( visible ) confirm_edit_box->set_visibility(false);
	else confirm_edit_box->set_visibility(true);
}

void admin_dlg::on_sq_checkbutton_toggled()
{  
	bool visible = sq_edit_box->get_visibility();
	if ( visible ) sq_edit_box->set_visibility(false);
	else sq_edit_box->set_visibility(true);
}

void admin_dlg::on_sa_checkbox_toggled()
{  
	bool visible = sa_edit_box->get_visibility();
	if ( visible ) sa_edit_box->set_visibility(false);
	else sa_edit_box->set_visibility(true);
}

void admin_dlg::onIconButtonClicked()
{
	for ( unsigned int i = 0; i < m_button_list.size(); i++ )
	{
		if ( get_focus() == m_button_list.at(i) )
		{			
			admin_icon->hide();	
			fixed8->remove(*admin_icon);
			m_user_image = m_file_list.at(i);
			admin_icon = Gtk::manage(new class Gtk::Image(m_file_list.at(i)));
			fixed8->put(*admin_icon, 0, 40);		
			admin_icon->show();
			return;
		}
	}
}