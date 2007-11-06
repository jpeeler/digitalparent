// generated 2007/10/28 18:51:11 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to login_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DP_LOGIN_DLG_HH
#  include "login_dlg_glade.hh"
#include "controller.h"
#include <string>
#include <vector>

using namespace std;

typedef enum
{
	LG_ADMIN,
	LG_ADMIN_START,	
	LG_B1_LOST_PASSWORD,
	LG_B2_LOST_PASSWORD,
	LG_B3_LOST_PASSWORD,
	LG_ADMIN_LOST_PASSWORD
} LG_STATE;

#  define _DP_LOGIN_DLG_HH
class login_dlg : public login_dlg_glade
{          
        void on_admin_psswrd_edit_box_editing_done();
        void on_previous_user_button_clicked();
        void on_admin_login_button_clicked();
        void on_next_user_button_clicked();
        void on_user_icon_select_button_2_clicked();
        void on_user_icon_select_button_1_clicked();
        void on_user_icon_select_button_3_clicked();
		void on_back_button_clicked();
		bool on_login_dlg_delete_event(GdkEventAny *ev);
		bool on_secret_a_edit_box_key_press_event(GdkEventKey *ev);
        bool on_icon1_password_edit_box_key_press_event(GdkEventKey *ev);
        bool on_icon2_password_edit_box_key_press_event(GdkEventKey *ev);
        bool on_icon3_password_edit_box_key_press_event(GdkEventKey *ev);
	bool on_admin_psswrd_edit_box_key_press_event(GdkEventKey *ev);
	public:
		void oninit(int shifted);
	private:
		vector<string> m_user_list;
		vector<string> m_icon_list;
		int m_status;
		int m_shifted;
		int m_ad_error_count;
		int m_b1_error_count;
		int m_b2_error_count;
		int m_b3_error_count;
		LG_STATE lg_state;		
		string m_admin;
		void setupButton1(const string filename, const string username);
		void setupButton2(const string filename, const string username);
		void setupButton3(const string filename, const string username);
		void setupAdminButton(const string filename, const string username);
		void userLoginInit();
		void setupButtons();
		void hideUserLogin();
		void loginWithAnswer(string username);
		void tooManyErrors(string username);
		
		
};
#endif
