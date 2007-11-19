// generated 2007/11/19 11:53:10 EST by ctemple@Barf.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/media_player_dlg.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (GETTEXT_PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "media_player_dlg_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/adjustment.h>
#include <gdkmm/pixbufloader.h>

static const unsigned char audio_volume_high_png_data[] = 
{       	137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
	0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,
	97,0,0,2,166,73,68,65,84,120,156,98,100,192,15,24,
	25,24,24,148,160,236,123,12,12,12,255,209,21,0,0,0,
	0,255,255,98,194,163,153,153,129,129,193,187,173,173,173,130,
	129,129,65,151,129,129,129,21,77,158,141,129,129,161,13,0,
	0,0,255,255,194,167,217,175,166,166,102,249,187,119,239,254,
	51,48,48,164,48,48,48,112,161,169,145,102,96,96,56,5,
	0,0,0,255,255,194,169,185,186,186,122,197,221,187,119,255,
	67,13,40,98,96,96,224,65,179,217,156,129,129,225,5,0,
	0,0,255,255,98,97,96,96,80,101,128,248,19,230,29,246,
	234,234,234,136,164,164,164,112,36,67,89,144,216,162,12,12,
	12,46,12,12,12,71,25,24,24,152,0,0,0,0,255,255,
	98,97,96,96,48,220,189,123,247,202,61,123,246,48,184,184,
	184,48,184,186,186,110,72,74,74,10,120,255,254,61,186,203,
	96,54,111,100,96,96,144,99,96,96,96,103,96,96,96,0,
	0,0,0,255,255,98,98,96,96,16,55,54,54,102,120,244,
	232,17,131,177,177,49,131,146,146,82,192,189,123,247,24,222,
	191,127,207,128,102,8,63,212,102,17,168,62,38,6,6,6,
	6,0,0,0,0,255,255,60,141,161,17,0,32,16,195,34,
	48,21,12,215,125,187,66,87,226,48,60,81,49,185,44,64,
	73,176,77,18,0,218,254,74,210,232,126,231,225,0,92,0,
	0,0,255,255,76,208,161,13,0,32,16,4,193,9,9,14,
	115,242,251,253,110,105,2,5,65,172,29,177,3,146,232,110,
	73,64,85,189,214,186,239,76,236,15,24,112,0,0,0,255,
	255,98,97,96,96,96,80,82,82,98,16,19,19,99,80,82,
	82,98,184,119,239,222,125,41,41,41,197,207,159,63,163,135,
	193,111,6,6,134,243,208,176,128,187,0,0,0,0,255,255,
	52,206,161,17,128,64,12,0,176,8,108,37,3,112,85,172,
	212,137,24,3,213,177,24,0,139,129,87,168,95,32,151,5,
	87,102,158,88,51,243,195,232,238,183,170,118,136,136,9,60,
	56,176,225,158,131,31,0,0,255,255,98,97,128,36,134,23,
	12,144,120,254,205,192,192,192,58,127,254,124,31,6,6,6,
	6,152,33,80,240,17,234,5,94,6,6,134,115,48,23,0,
	0,0,0,255,255,98,129,106,126,195,128,72,7,92,12,12,
	12,159,78,156,56,193,207,192,192,192,88,83,83,163,1,21,
	255,197,192,192,240,133,129,129,225,9,178,75,0,0,0,0,
	255,255,98,129,74,252,66,178,233,59,3,3,195,255,235,215,
	175,207,186,126,253,250,39,14,14,142,247,12,12,12,127,144,
	228,95,67,93,195,203,192,192,112,14,0,0,0,255,255,98,
	68,15,41,40,96,97,96,96,16,100,96,96,80,102,96,96,
	208,102,96,96,120,206,192,192,112,128,129,129,225,27,146,26,
	105,6,6,6,126,0,0,0,0,255,255,194,101,0,3,3,
	36,79,240,50,64,194,230,23,3,3,195,7,52,151,178,49,
	48,48,176,1,0,0,0,255,255,3,0,131,117,133,34,6,
	71,133,122,0,0,0,0,73,69,78,68,174,66,96,130,

};

media_player_dlg_glade::media_player_dlg_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  media_player_dlg = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::Adjustment *volume_slider_adj = Gtk::manage(new class Gtk::Adjustment(0, 0, 20, 0, 0, 0));
   volume_slider = Gtk::manage(new class Gtk::HScale(*volume_slider_adj));
   image5 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-previous"), Gtk::IconSize(4)));
   previous_button = Gtk::manage(new class Gtk::Button());
   image7 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-rewind"), Gtk::IconSize(4)));
   rewind_button = Gtk::manage(new class Gtk::Button());
   image4 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-stop"), Gtk::IconSize(4)));
   stop_button = Gtk::manage(new class Gtk::Button());
   image1 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-pause"), Gtk::IconSize(4)));
   pause_button = Gtk::manage(new class Gtk::Button());
   image2 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-play"), Gtk::IconSize(4)));
   play_button = Gtk::manage(new class Gtk::Button());
   image6 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-forward"), Gtk::IconSize(4)));
   fastforward_button = Gtk::manage(new class Gtk::Button());
   image3 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-media-next"), Gtk::IconSize(4)));
   next_button = Gtk::manage(new class Gtk::Button());
   image12 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-quit"), Gtk::IconSize(4)));
   label4 = Gtk::manage(new class Gtk::Label(_("Logout")));
   hbox4 = Gtk::manage(new class Gtk::HBox(false, 2));
   alignment4 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 0, 0));
   Logout = Gtk::manage(new class Gtk::Button());
   image9 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-index"), Gtk::IconSize(4)));
   playlist_button = Gtk::manage(new class Gtk::ToggleButton());
   
   Glib::RefPtr<Gdk::PixbufLoader> _sound_loader=Gdk::PixbufLoader::create();
   _sound_loader->write(audio_volume_high_png_data, sizeof audio_volume_high_png_data);
   _sound_loader->close();
   sound = Gtk::manage(new class Gtk::Image(_sound_loader->get_pixbuf()));
   _sound_loader=Glib::RefPtr<Gdk::PixbufLoader>();
   mute_button = Gtk::manage(new class Gtk::ToggleButton());
   open_media_button = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cdrom")));
   currentUser = Gtk::manage(new class Gtk::Label(_("User:")));
   media = Gtk::manage(new class Gtk::Label(_("Now Playing")));
   
   Gtk::Adjustment *time_slider_adj = Gtk::manage(new class Gtk::Adjustment(0, 0, 100, 1, 0, 0));
   time_slider = Gtk::manage(new class Gtk::HScale(*time_slider_adj));
   image13 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-fullscreen"), Gtk::IconSize(4)));
   label11 = Gtk::manage(new class Gtk::Label(_("Fullscreen")));
   hbox6 = Gtk::manage(new class Gtk::HBox(false, 2));
   alignment8 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 0, 0));
   fullscreen = Gtk::manage(new class Gtk::Button());
   image11 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-cut"), Gtk::IconSize(4)));
   label3 = Gtk::manage(new class Gtk::Label(_("Video")));
   hbox3 = Gtk::manage(new class Gtk::HBox(false, 2));
   alignment3 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 0, 0));
   cut_video = Gtk::manage(new class Gtk::ToggleButton());
   fixed1 = Gtk::manage(new class Gtk::Fixed());
   volume_slider->set_size_request(88,16);
   volume_slider->set_flags(Gtk::CAN_FOCUS);
   volume_slider->set_update_policy(Gtk::UPDATE_CONTINUOUS);
   volume_slider->set_inverted(false);
   volume_slider->set_digits(1);
   volume_slider->set_draw_value(false);
   volume_slider->set_value_pos(Gtk::POS_BOTTOM);
   image5->set_alignment(0.5,0.5);
   image5->set_padding(0,0);
   previous_button->set_size_request(72,32);
   previous_button->set_flags(Gtk::CAN_FOCUS);
   previous_button->set_relief(Gtk::RELIEF_NORMAL);
   previous_button->add(*image5);
   image7->set_alignment(0.5,0.5);
   image7->set_padding(0,0);
   rewind_button->set_size_request(72,32);
   rewind_button->set_flags(Gtk::CAN_FOCUS);
   rewind_button->set_relief(Gtk::RELIEF_NORMAL);
   rewind_button->add(*image7);
   image4->set_alignment(0.5,0.5);
   image4->set_padding(0,0);
   stop_button->set_size_request(72,32);
   stop_button->set_flags(Gtk::CAN_FOCUS);
   stop_button->set_relief(Gtk::RELIEF_NORMAL);
   stop_button->add(*image4);
   image1->set_alignment(0.5,0.5);
   image1->set_padding(0,0);
   pause_button->set_size_request(72,32);
   pause_button->set_flags(Gtk::CAN_FOCUS);
   pause_button->set_relief(Gtk::RELIEF_NORMAL);
   pause_button->add(*image1);
   image2->set_alignment(0.5,0.5);
   image2->set_padding(0,0);
   play_button->set_size_request(70,32);
   play_button->set_flags(Gtk::CAN_FOCUS);
   play_button->set_relief(Gtk::RELIEF_NORMAL);
   play_button->add(*image2);
   image6->set_alignment(0.5,0.5);
   image6->set_padding(0,0);
   fastforward_button->set_size_request(72,32);
   fastforward_button->set_flags(Gtk::CAN_FOCUS);
   fastforward_button->set_relief(Gtk::RELIEF_NORMAL);
   fastforward_button->add(*image6);
   image3->set_alignment(0.5,0.5);
   image3->set_padding(0,0);
   next_button->set_size_request(70,32);
   next_button->set_flags(Gtk::CAN_FOCUS);
   next_button->set_relief(Gtk::RELIEF_NORMAL);
   next_button->add(*image3);
   image12->set_alignment(0.5,0.5);
   image12->set_padding(0,0);
   label4->set_alignment(0.5,0.5);
   label4->set_padding(0,0);
   label4->set_justify(Gtk::JUSTIFY_LEFT);
   label4->set_line_wrap(false);
   label4->set_use_markup(false);
   label4->set_selectable(false);
   hbox4->pack_start(*image12, Gtk::PACK_SHRINK, 0);
   hbox4->pack_start(*label4, Gtk::PACK_SHRINK, 0);
   alignment4->add(*hbox4);
   Logout->set_size_request(96,32);
   Logout->set_flags(Gtk::CAN_FOCUS);
   Logout->set_relief(Gtk::RELIEF_NORMAL);
   Logout->add(*alignment4);
   image9->set_alignment(0.5,0.5);
   image9->set_padding(0,0);
   playlist_button->set_size_request(72,32);
   playlist_button->set_flags(Gtk::CAN_FOCUS);
   playlist_button->set_relief(Gtk::RELIEF_NORMAL);
   playlist_button->set_active(false);
   playlist_button->add(*image9);
   sound->set_alignment(0.5,0.5);
   sound->set_padding(0,0);
   mute_button->set_size_request(48,27);
   mute_button->set_flags(Gtk::CAN_FOCUS);
   mute_button->set_relief(Gtk::RELIEF_NORMAL);
   mute_button->set_active(false);
   mute_button->add(*sound);
   open_media_button->set_size_request(96,32);
   open_media_button->set_flags(Gtk::CAN_FOCUS);
   open_media_button->set_relief(Gtk::RELIEF_NORMAL);
   currentUser->set_size_request(128,16);
   currentUser->set_alignment(0.5,0.5);
   currentUser->set_padding(0,0);
   currentUser->set_justify(Gtk::JUSTIFY_LEFT);
   currentUser->set_line_wrap(true);
   currentUser->set_use_markup(false);
   currentUser->set_selectable(false);
   media->set_size_request(304,16);
   media->set_alignment(0.5,0.5);
   media->set_padding(0,0);
   media->set_justify(Gtk::JUSTIFY_LEFT);
   media->set_line_wrap(true);
   media->set_use_markup(false);
   media->set_selectable(false);
   time_slider->set_size_request(360,16);
   time_slider->set_flags(Gtk::CAN_FOCUS);
   time_slider->set_update_policy(Gtk::UPDATE_CONTINUOUS);
   time_slider->set_inverted(false);
   time_slider->set_digits(0);
   time_slider->set_draw_value(false);
   time_slider->set_value_pos(Gtk::POS_TOP);
   image13->set_alignment(0.5,0.5);
   image13->set_padding(0,0);
   label11->set_alignment(0.5,0.5);
   label11->set_padding(0,0);
   label11->set_justify(Gtk::JUSTIFY_LEFT);
   label11->set_line_wrap(false);
   label11->set_use_markup(false);
   label11->set_selectable(false);
   hbox6->pack_start(*image13, Gtk::PACK_SHRINK, 0);
   hbox6->pack_start(*label11, Gtk::PACK_SHRINK, 0);
   alignment8->add(*hbox6);
   fullscreen->set_size_request(96,32);
   fullscreen->set_flags(Gtk::CAN_FOCUS);
   fullscreen->set_relief(Gtk::RELIEF_NORMAL);
   fullscreen->add(*alignment8);
   image11->set_alignment(0.5,0.5);
   image11->set_padding(0,0);
   label3->set_alignment(0.5,0.5);
   label3->set_padding(0,0);
   label3->set_justify(Gtk::JUSTIFY_LEFT);
   label3->set_line_wrap(false);
   label3->set_use_markup(false);
   label3->set_selectable(false);
   hbox3->pack_start(*image11, Gtk::PACK_SHRINK, 0);
   hbox3->pack_start(*label3, Gtk::PACK_SHRINK, 0);
   alignment3->add(*hbox3);
   cut_video->set_size_request(96,32);
   cut_video->set_flags(Gtk::CAN_FOCUS);
   cut_video->set_relief(Gtk::RELIEF_NORMAL);
   cut_video->set_active(false);
   cut_video->add(*alignment3);
   fixed1->put(*volume_slider, 0, 72);
   fixed1->put(*previous_button, 72, 88);
   fixed1->put(*rewind_button, 144, 88);
   fixed1->put(*stop_button, 216, 88);
   fixed1->put(*pause_button, 288, 88);
   fixed1->put(*play_button, 360, 88);
   fixed1->put(*fastforward_button, 432, 88);
   fixed1->put(*next_button, 504, 88);
   fixed1->put(*Logout, 0, 0);
   fixed1->put(*playlist_button, 592, 88);
   fixed1->put(*mute_button, 8, 88);
   fixed1->put(*open_media_button, 0, 32);
   fixed1->put(*currentUser, 104, 8);
   fixed1->put(*media, 248, 8);
   fixed1->put(*time_slider, 144, 48);
   fixed1->put(*fullscreen, 568, 0);
   fixed1->put(*cut_video, 568, 32);
   media_player_dlg->set_title(_("Digital Parent"));
   media_player_dlg->set_default_size(800,600);
   media_player_dlg->set_modal(false);
   media_player_dlg->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   media_player_dlg->set_resizable(false);
   media_player_dlg->property_destroy_with_parent().set_value(false);
   media_player_dlg->add(*fixed1);
   volume_slider->show();
   image5->show();
   previous_button->show();
   image7->show();
   rewind_button->show();
   image4->show();
   stop_button->show();
   image1->show();
   pause_button->show();
   image2->show();
   play_button->show();
   image6->show();
   fastforward_button->show();
   image3->show();
   next_button->show();
   image12->show();
   label4->show();
   hbox4->show();
   alignment4->show();
   Logout->show();
   image9->show();
   playlist_button->show();
   sound->show();
   mute_button->show();
   open_media_button->show();
   currentUser->show();
   media->show();
   time_slider->show();
   image13->show();
   label11->show();
   hbox6->show();
   alignment8->show();
   fullscreen->show();
   image11->show();
   label3->show();
   hbox3->show();
   alignment3->show();
   cut_video->show();
   fixed1->show();
   media_player_dlg->show();
   volume_slider->signal_value_changed().connect(SigC::slot(*this, &media_player_dlg_glade::on_volume_slider_value_changed), false);
   previous_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_previous_button_clicked), false);
   rewind_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_rewind_button_clicked), false);
   stop_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_stop_button_clicked), false);
   pause_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_pause_button_clicked), false);
   play_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_play_button_clicked), false);
   fastforward_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_fastforward_button_clicked), false);
   next_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_next_button_clicked), false);
   Logout->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_Logout_clicked), false);
   playlist_button->signal_toggled().connect(SigC::slot(*this, &media_player_dlg_glade::on_playlist_button_toggled), false);
   mute_button->signal_toggled().connect(SigC::slot(*this, &media_player_dlg_glade::on_mute_button_toggled), false);
   open_media_button->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_open_media_button_clicked), false);
   time_slider->signal_value_changed().connect(SigC::slot(*this, &media_player_dlg_glade::on_time_slider_value_changed), false);
   time_slider->signal_button_press_event().connect(SigC::slot(*this, &media_player_dlg_glade::on_time_slider_button_press), false);
   time_slider->signal_button_release_event().connect(SigC::slot(*this, &media_player_dlg_glade::on_time_slider_button_release_event), false);
   fullscreen->signal_clicked().connect(SigC::slot(*this, &media_player_dlg_glade::on_fullscreen_clicked), false);
   cut_video->signal_toggled().connect(SigC::slot(*this, &media_player_dlg_glade::on_cut_video_toggled), false);
}

media_player_dlg_glade::~media_player_dlg_glade()
{  delete gmm_data;
}
