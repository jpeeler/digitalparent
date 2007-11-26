// generated 2007/10/18 15:52:33 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_player_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MEDIA_PLAYER_DLG_HH
#  include "media_player_dlg_glade.hh"
#include <vlc/libvlc.h>
#include <dvdnav/dvdnav.h>
#  define _MEDIA_PLAYER_DLG_HH
class media_player_dlg : public media_player_dlg_glade
{          
        void on_volume_slider_value_changed();
        void on_previous_button_clicked();
        void on_rewind_button_clicked();
        void on_stop_button_clicked();
        void on_pause_button_clicked();
        void on_play_button_clicked();
        void on_fastforward_button_clicked();
        void on_next_button_clicked();
        void on_Logout_clicked();
        void on_playlist_button_toggled();
        void on_cut_video_toggled();
        void on_mute_button_toggled();
        void on_open_media_button_clicked();
        void on_time_slider_value_changed();
        void on_fullscreen_clicked();
        bool on_delete_event(GdkEventAny * event);
		bool update_slider();
		void dvd_read_name();
		void buildPlaylist();
		bool on_time_slider_button_press(GdkEventButton *ev);
		bool on_time_slider_button_release_event(GdkEventButton *ev);
		void on_time_slider_button_move_event();
		void on_save_button_clicked();
		void on_playlist_clicked();
		bool eraseFromSkipChapters(std::string toRemove);
		bool eraseFromSkipTimes(std::string toRemove);
		bool skipTimesContains(std::string toFind);
		bool skipChaptersContains(std::string toFind);
		int newSkipTime(int currentTime);
		
		int to_int(const std::string &str);
		template <class T>
inline std::string to_string (const T& t);
	public:
		void init();
	bool isAdmin;
	private:	
		libvlc_exception_t excp;
		libvlc_instance_t *inst;
	dvdnav_status_t status;
	dvdnav_t* dvdnav;
		SigC::Connection slider_signal;		
};
#endif
