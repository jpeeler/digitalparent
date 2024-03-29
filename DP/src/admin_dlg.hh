// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _ADMIN_DLG_HH
#  include "admin_dlg_glade.hh"
#include "controller.h"
#include "data_structure.h"
#include <vector>
#include <string>
#  define _ADMIN_DLG_HH

using namespace std;

extern Controller *useController();
//extern Controller g_img_dir;

typedef enum {	
	AD_SETTINGS,
	AD_CHOOSE_EDIT,	
	AD_USER_SETTINGS,
	AD_ADD_USER,
	AD_EDIT_USER,
	AD_DELETE_USER	
} AD_STATE;

enum {
	USER_ICONS,
	ALL_ICONS
}; 

class admin_dlg : public admin_dlg_glade
{  
        void on_logout_button_clicked();        
        void on_add_user_button_clicked(); 	
		void on_screen_movies_button_clicked();		
        void on_user_save_button_clicked();       
        void on_pw_checkbox_toggled();
        void on_cf_checkbox_toggled();
        void on_sq_checkbox_toggled();
        void on_sa_checkbox_toggled();
		void onIconButtonClicked();
		void on_change_icon_clicked();
		void on_edit_user_button_clicked();
		void on_admin_settings_button_clicked();
		void on_remove_user_button_clicked();
		void on_media_player_button_clicked();
		void on_confirm_delete_button_clicked();
		void on_cancel_delete_button_clicked();
		void start_delete_confirm();	
		void stop_delete_confirm();
		bool on_admin_dlg_delete_event(GdkEventAny *ev);
		vector<class Gtk::Image*> m_image_list;					
		vector<class Gtk::Button*> m_button_list;
		vector<string> m_icon_list;	
		vector<string> m_user_list;		
			
	public:
		void oninit_admin();
		void oninit_user();
		void oninit_icons();
		void reset_frame3(const User *a_user);
		void reset_frame1(const User *a_user);
		void fill_image_button_scroller(int mode);
		void clear_user_icon();
		void set_user_icon(string user, string file_name);
		vector<string> m_file_list;
		AD_STATE ad_state;
		
	private:		
		const User *m_user;
		const User *m_admin;
		string m_user_image;
		
		
};
#endif
