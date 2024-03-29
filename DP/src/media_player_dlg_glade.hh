// generated 2007/12/6 20:11:02 EST by ctemple@Barf.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/media_player_dlg.hh and./src/media_player_dlg.cc

#ifndef _MEDIA_PLAYER_DLG_GLADE_HH
#  define _MEDIA_PLAYER_DLG_GLADE_HH

// Since all your widgets were private I made them all public.
// To differentiate between accessable (e.g. entries, output labels)
// and unaccessible widgets (e.g. static labels, containers)
// you should use the 'visibility' property (only visible in C++ mode)


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/window.h>
#include <gtkmm/scale.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/fixed.h>

class media_player_dlg_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * media_player_dlg;
        class Gtk::HScale * volume_slider;
        class Gtk::Image * image5;
        class Gtk::Button * previous_button;
        class Gtk::Image * image7;
        class Gtk::Button * rewind_button;
        class Gtk::Image * image4;
        class Gtk::Button * stop_button;
        class Gtk::Image * image1;
        class Gtk::Button * pause_button;
        class Gtk::Image * image2;
        class Gtk::Button * play_button;
        class Gtk::Image * image6;
        class Gtk::Button * fastforward_button;
        class Gtk::Image * image3;
        class Gtk::Button * next_button;
        class Gtk::Image * image12;
        class Gtk::Label * label4;
        class Gtk::HBox * hbox4;
        class Gtk::Alignment * alignment4;
        class Gtk::Button * Logout;
        class Gtk::Image * sound;
        class Gtk::ToggleButton * mute_button;
        class Gtk::Label * currentUser;
        class Gtk::Label * media;
        class Gtk::HScale * time_slider;
        class Gtk::Image * image14;
        class Gtk::Label * label12;
        class Gtk::HBox * hbox7;
        class Gtk::Alignment * alignment9;
        class Gtk::Button * open_media_button;
        class Gtk::Image * image18;
        class Gtk::Label * label16;
        class Gtk::HBox * hbox11;
        class Gtk::Alignment * alignment13;
        class Gtk::Button * discRatingButton;
        class Gtk::Image * image9;
        class Gtk::ToggleButton * playlist_button;
        class Gtk::Image * image15;
        class Gtk::Label * label13;
        class Gtk::HBox * hbox8;
        class Gtk::Alignment * alignment10;
        class Gtk::ToggleButton * cut_video;
        class Gtk::Fixed * fixed1;
protected:
        
        media_player_dlg_glade();
        
        ~media_player_dlg_glade();
private:
        virtual void on_volume_slider_value_changed() = 0;
        virtual void on_previous_button_clicked() = 0;
        virtual void on_rewind_button_clicked() = 0;
        virtual void on_stop_button_clicked() = 0;
        virtual void on_pause_button_clicked() = 0;
        virtual void on_play_button_clicked() = 0;
        virtual void on_fastforward_button_clicked() = 0;
        virtual void on_next_button_clicked() = 0;
        virtual void on_Logout_clicked() = 0;
        virtual void on_mute_button_toggled() = 0;
        virtual void on_time_slider_value_changed() = 0;
        virtual bool on_time_slider_button_press(GdkEventButton *ev) = 0;
        virtual bool on_time_slider_button_release_event(GdkEventButton *ev) = 0;
        virtual void on_open_media_button_clicked() = 0;
        virtual void on_discRatingButton_clicked() = 0;
        virtual void on_playlist_button_toggled() = 0;
        virtual void on_cut_video_toggled() = 0;
};
#endif
