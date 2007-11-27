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

void admin_dlg::on_media_player_button_clicked()
{  	
	if ( useController()->dp_state == DP_ADMIN_PANEL )
		useController()->dp_state = DP_ADMIN_PLAY;
	else useController()->dp_state = DP_USER_PLAY;
	hide();
}

void admin_dlg::on_admin_settings_button_clicked()
{  	
	ad_state = AD_SETTINGS;
	oninit_admin();
}

void admin_dlg::on_change_icon_clicked()
{	
	fill_image_button_scroller(ALL_ICONS);
	frame2->show();
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
	
	clear_user_icon();
	user_name_edit_box->set_editable(true);
	
	reset_frame3(NULL);	
	frame3->show();
	
	g_radio_button->set_active(true);	
	nr_checkbox->set_active(false);		
	screen_movies_button->hide();		
	user_save_button->show();
}

void admin_dlg::on_remove_user_button_clicked()
{  	
	ad_state = AD_DELETE_USER;	
	frame1->hide();
	frame3->hide();	
	fill_image_button_scroller(USER_ICONS);
	frame2->show();
	clear_user_icon();
}

void admin_dlg::on_edit_user_button_clicked()
{  
	ad_state = AD_CHOOSE_EDIT;
	frame1->hide();
	frame3->hide();	
	fill_image_button_scroller(USER_ICONS);
	frame2->show();
	clear_user_icon();	
}

void admin_dlg::fill_image_button_scroller( int mode )
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
		if ( mode == ALL_ICONS && !user_icon )				
			m_button_list.at(j)->show();					
		else if ( mode == USER_ICONS && user_icon )
			m_button_list.at(j)->show();
		else m_button_list.at(j)->hide();
	}				
}

void admin_dlg::clear_user_icon()
{
	set_user_icon(string(""),string("/Projects/DP/pixmaps/no_user.png"));	
}

void admin_dlg::set_user_icon(string user, string file_name )
{
	user_label->set_text(user.c_str());	
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(file_name.c_str()));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();
}

void admin_dlg::onIconButtonClicked()
{
	unsigned int i;
	unsigned int j;	
	for ( i = 0; i < m_button_list.size(); i++ )
	{
		if ( get_focus() == m_button_list.at(i) )							
			break;				
	}
	
	set_user_icon(string(""),m_file_list.at(i));
	
	switch (ad_state)
	{			
		case AD_SETTINGS:
			// this case should not occur
			printf("\nIcon Buttons should not be clickable in state ADMIN_SETTINGS");
		break;			
		case AD_USER_SETTINGS:				
			user_label->set_text(m_user->getUser());
			useController()->c_setCurrentUserIcon(m_file_list.at(i));
			useController()->storeCurrentUser();
			fill_image_button_scroller(ALL_ICONS);
		break;
		case AD_ADD_USER:			
			m_user_image = m_file_list.at(i);
		break;
		case AD_EDIT_USER:
			
		break;
		case AD_CHOOSE_EDIT:			
			for ( j = 0; j < m_user_list.size(); j++ )
			{
				if ( m_file_list.at(i) == m_icon_list.at(j) )
					break;
			}
			user_label->set_text(m_user_list.at(j));
			useController()->populateUserInfo(m_user_list.at(j));
			m_user = useController()->c_getUserOther();			
			fill_image_button_scroller(ALL_ICONS);
			reset_frame3(m_user);
			frame1->show();
			frame3->show();
			ad_state = AD_EDIT_USER;
		break;
		case AD_DELETE_USER:
		{
			for ( j = 0; j < m_user_list.size(); j++ )
			{
				if ( m_file_list.at(i) == m_icon_list.at(j) )
					break;
			}
			user_label->set_text(m_user_list.at(j));			
			useController()->populateUserInfo(m_user_list.at(j));
			start_delete_confirm();								
		break;
		}
		case AD_DELETE_DLG:
			//do nothing
		break;
		default:
			
		break;
	}	
	return;
}

void admin_dlg::start_delete_confirm()
{
	frame2->hide();
	logout_button->hide();
	media_player_button->hide();
	admin_settings_button->hide();
	add_user_button->hide();
	edit_user_button->hide();
	remove_user_button->hide();
	cancel_delete_button->show();
	confirm_delete_button->show();
	confirn_delete_label->show();
}

void admin_dlg::stop_delete_confirm()
{
	frame2->show();
	logout_button->show();
	media_player_button->show();
	admin_settings_button->show();
	add_user_button->show();
	edit_user_button->show();
	remove_user_button->show();
	cancel_delete_button->hide();
	confirm_delete_button->hide();
	confirn_delete_label->hide();
}

void admin_dlg::on_confirm_delete_button_clicked()
{
	useController()->deleteOtherUser();
	fill_image_button_scroller(USER_ICONS);
	clear_user_icon();
	stop_delete_confirm();
}

void admin_dlg::on_cancel_delete_button_clicked()
{
	useController()->c_clearUserOther();
	clear_user_icon();
	stop_delete_confirm();
}

void admin_dlg::reset_frame3(const User *a_user)
{
	if ( a_user == NULL )
	{
		user_name_edit_box->set_editable(true);
		user_name_edit_box->set_text("");
		password_edit_box->set_text("");
		confirm_edit_box->set_text("");
		sq_edit_box->set_text("");	
		sa_edit_box->set_text("");		
	}
	else
	{
		user_name_edit_box->set_editable(false);
		printf("\n%s",a_user->getUser().c_str());
		user_name_edit_box->set_text(a_user->getUser().c_str());
		password_edit_box->set_text(a_user->getPasswordHash().c_str());
		confirm_edit_box->set_text(a_user->getPasswordHash().c_str());
		sq_edit_box->set_text(a_user->getQuestion().c_str());
		sa_edit_box->set_text(a_user->getAnswer().c_str());
		printf("\nTEST");
	}	
	
	pw_checkbox->set_active(true);
	password_edit_box->set_visibility(false);	
	cf_checkbox->set_active(true);	
	confirm_edit_box->set_visibility(false);	
	sq_checkbox->set_active(true);	
	sa_checkbox->set_active(true);
	sa_edit_box->set_visibility(false);	
}

void admin_dlg::on_screen_movies_button_clicked()
{  
	useController()->dp_state = DP_ADMIN_PLAY;	
	hide();
}

void admin_dlg::oninit_admin()
{		
	ad_state = AD_SETTINGS;
	// SHOW THE ADMIN ICON AND NAME
	set_user_icon(string("admin"),string("/Projects/DP/images/tux.png"));	
	
	// GET ALL OF THE USER NAMES AND ICONS
	m_user_list = useController()->getUserList();
	m_icon_list = useController()->getIconList();
	
	// SHOW ONLY APPROPRIATE BUTTONS ALONG TOP OF DIALOG
	m_user_list.size() == 0	? edit_user_button->hide() : edit_user_button->show(); 
	m_user_list.size() == 0 ? remove_user_button->hide() : remove_user_button->show(); 
	change_icon_button->hide();
	
	// GET THE ADMIN INFO AND FILL IT ALL IN
	m_admin = useController()->c_getUserLoggedIn();
	m_user_image = m_admin->getUserIcon();
	reset_frame3(m_admin);	
	
	// SHOW / HIDE FRAMES
	frame1->show();
	frame2->hide();
	frame3->hide();
	//user_save_button->show();
	user_name_edit_box->set_editable(false);	
}

void admin_dlg::oninit_user()
{
	ad_state = AD_USER_SETTINGS;
	frame3->hide();
	frame2->hide();
	frame1->hide();
	
	edit_user_button->hide();
	add_user_button->hide();
	remove_user_button->hide();
	admin_settings_button->hide();	
	change_icon_button->show();
	screen_movies_button->show();
	m_user = useController()->c_getUserLoggedIn();
	m_user_image = m_user->getUserIcon();
	set_user_icon(m_user->getUser(),m_user_image);
	user_name_edit_box->set_editable(false);
	screen_movies_button->hide();
	
	reset_frame3(m_user);
}

void admin_dlg::oninit_icons()
{
	system("ls /Projects/DP/images > pixmaps.dat");
	FILE *fp = fopen("pixmaps.dat","r");
	int c;
	string fname = useController()->img_dir;
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
	
	if ( password != confirm )
	{		
		password_edit_box->set_text("");
		confirm_edit_box->set_text("");
		error_label->set_text("Password and Confirm do not match");
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
	switch ( ad_state )
	{
		case AD_SETTINGS:
			useController()->c_setCurrentUserPasswordHash( password );
			useController()->c_setCurrentUserSecretQuestion( question );
			useController()->c_setCurrentUserSecretAnswerHash( answer );
			error_label->set_text("");
			on_admin_settings_button_clicked();			
		break;
		case AD_ADD_USER:
		case AD_EDIT_USER:
		{
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
			{				
				error_label->set_text("can't create user");	
				reset_frame3(NULL);
			}				
			else							
			{
				useController()->c_clearUserOther();
				error_label->set_text("");
				on_admin_settings_button_clicked();				
			}
		break;
		}
		case AD_USER_SETTINGS:
			
		break;
		default:
			
		break;			
	}
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

void admin_dlg::on_sq_checkbox_toggled()
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
