// generated 2007/12/6 11:38:13 EST by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/admin_dlg.cc


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
#include "admin_dlg_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/adjustment.h>
#include <gdkmm/pixbufloader.h>

static const unsigned char no_user_png_data[] = 
{       	137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
	0,0,0,89,0,0,0,89,8,2,0,0,0,218,105,31,
	248,0,0,0,4,103,65,77,65,0,0,177,143,11,252,97,
	5,0,0,2,5,73,68,65,84,120,94,237,156,237,118,131,
	32,16,68,211,55,247,209,250,104,77,14,61,72,217,101,25,
	173,96,140,215,127,241,3,97,152,185,2,49,249,90,150,229,
	193,150,20,120,106,193,150,20,248,213,226,251,246,27,90,172,
	22,64,11,180,240,128,128,47,240,5,190,136,31,149,100,132,
	140,144,17,50,162,14,168,225,5,188,128,23,240,2,94,168,
	10,192,11,120,1,47,212,180,48,190,128,23,240,2,94,192,
	11,85,1,120,1,47,224,133,154,150,33,227,139,252,69,117,
	174,133,221,163,86,112,226,121,104,49,152,157,248,98,21,184,
	171,69,245,182,71,153,131,242,144,27,177,116,194,136,232,156,
	144,145,74,169,178,109,246,141,152,212,230,64,187,3,69,57,
	83,139,170,123,93,141,210,57,115,208,123,130,22,173,126,110,
	189,38,245,225,90,88,231,199,13,190,176,47,108,207,91,40,
	84,114,184,92,200,87,93,91,139,24,120,226,115,36,3,229,
	242,90,28,72,248,57,69,13,97,231,156,170,31,126,23,180,
	24,60,6,63,188,199,230,20,136,47,240,133,231,52,124,129,
	47,186,190,232,206,181,231,48,172,172,134,56,202,10,78,19,
	75,120,54,237,79,70,208,98,253,205,196,155,104,225,46,237,
	196,150,156,237,139,216,186,238,50,76,44,110,119,229,198,78,
	94,255,115,73,86,179,44,164,148,120,67,70,148,245,5,59,
	233,106,41,168,148,86,105,161,92,18,87,192,157,64,103,57,
	246,104,97,167,219,226,146,84,224,172,174,100,129,71,244,67,
	65,61,183,177,51,46,200,93,128,40,119,230,26,87,201,215,
	173,228,154,60,205,235,183,118,134,187,104,48,220,23,214,150,
	214,86,173,44,4,251,247,29,138,159,175,245,184,211,205,164,
	94,123,87,111,219,111,110,110,211,181,138,46,129,149,118,240,
	34,221,180,206,72,224,243,216,135,113,47,185,90,40,109,222,
	97,254,110,61,91,62,245,181,168,242,124,159,143,204,205,214,
	190,70,11,180,240,146,143,47,240,5,190,136,159,137,100,132,
	140,144,17,50,162,142,156,225,5,188,128,23,240,2,94,168,
	10,192,11,120,1,47,212,180,48,190,128,23,240,2,94,192,
	11,85,1,120,1,47,224,133,154,22,198,23,240,2,94,192,
	139,237,188,120,253,37,244,237,183,31,231,54,55,164,158,120,
	155,253,0,0,0,0,73,69,78,68,174,66,96,130,

};

admin_dlg_glade::admin_dlg_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  admin_dlg = this;
   gmm_data = new GlademmData(get_accel_group());
   vseparator1 = Gtk::manage(new class Gtk::VSeparator());
   logout_button = Gtk::manage(new class Gtk::Button(_("<--  LOG OUT")));
   
   Gtk::RadioButton::Group _RadioBGroup_g_radio_button;
   g_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("G")));
   pg_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("PG")));
   pg13_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("PG13")));
   nc17_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("NC17")));
   r_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("R")));
   x_radio_button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_g_radio_button, _("X")));
   nr_checkbox = Gtk::manage(new class Gtk::CheckButton(_("NR")));
   screen_movies_button = Gtk::manage(new class Gtk::Button(_("Screen Movies")));
   vbox7 = Gtk::manage(new class Gtk::VBox(false, 0));
   alignment7 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   user_level_label = Gtk::manage(new class Gtk::Label(_("<b>Maximum User Level</b>")));
   frame3 = Gtk::manage(new class Gtk::Frame());
   add_user_button = Gtk::manage(new class Gtk::Button(_("Add User")));
   edit_user_button = Gtk::manage(new class Gtk::Button(_("Edit User")));
   remove_user_button = Gtk::manage(new class Gtk::Button(_("Remove User")));
   error_label = Gtk::manage(new class Gtk::Label(_("")));
   user_name_edit_box = Gtk::manage(new class Gtk::Entry());
   password_edit_box = Gtk::manage(new class Gtk::Entry());
   cf_checkbox = Gtk::manage(new class Gtk::CheckButton(_("hide")));
   sq_checkbox = Gtk::manage(new class Gtk::CheckButton(_("hide")));
   sa_checkbox = Gtk::manage(new class Gtk::CheckButton(_("hide")));
   confirm_edit_box = Gtk::manage(new class Gtk::Entry());
   sq_edit_box = Gtk::manage(new class Gtk::Entry());
   sa_edit_box = Gtk::manage(new class Gtk::Entry());
   user_save_button = Gtk::manage(new class Gtk::Button(_("Save User Settings")));
   pw_checkbox = Gtk::manage(new class Gtk::CheckButton(_("hide")));
   confirm_label = Gtk::manage(new class Gtk::Label(_("Confirm")));
   label10 = Gtk::manage(new class Gtk::Label(_("Password")));
   user_name_label = Gtk::manage(new class Gtk::Label(_("User Name")));
   sa_label = Gtk::manage(new class Gtk::Label(_("Secret Answer")));
   sq_label = Gtk::manage(new class Gtk::Label(_("Secret Question")));
   table1 = Gtk::manage(new class Gtk::Table(2, 2, false));
   vbox6 = Gtk::manage(new class Gtk::VBox(false, 0));
   vbox5 = Gtk::manage(new class Gtk::VBox(false, 0));
   alignment5 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 0.99));
   frame1 = Gtk::manage(new class Gtk::Frame());
   hbox5 = Gtk::manage(new class Gtk::HBox(false, 0));
   viewport1 = Gtk::manage(new class Gtk::Viewport(*manage(new Gtk::Adjustment(0,0,1)), *manage(new Gtk::Adjustment(0,0,1))));
   scrolledwindow1 = Gtk::manage(new class Gtk::ScrolledWindow());
   alignment6 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   icon_select_frame_label = Gtk::manage(new class Gtk::Label(_("<b>Select an icon</b>")));
   frame2 = Gtk::manage(new class Gtk::Frame());
   hseparator3 = Gtk::manage(new class Gtk::HSeparator());
   media_player_button = Gtk::manage(new class Gtk::Button(_("Media Player")));
   
   Glib::RefPtr<Gdk::PixbufLoader> _admin_icon_loader=Gdk::PixbufLoader::create();
   _admin_icon_loader->write(no_user_png_data, sizeof no_user_png_data);
   _admin_icon_loader->close();
   admin_icon = Gtk::manage(new class Gtk::Image(_admin_icon_loader->get_pixbuf()));
   _admin_icon_loader=Glib::RefPtr<Gdk::PixbufLoader>();
   admin_settings_button = Gtk::manage(new class Gtk::Button(_("Admin Settings")));
   change_icon_button = Gtk::manage(new class Gtk::Button(_("Change Icon")));
   confirm_delete_button = Gtk::manage(new class Gtk::Button(_("Confirm Delete")));
   user_label = Gtk::manage(new class Gtk::Label(_("USER")));
   hseparator2 = Gtk::manage(new class Gtk::HSeparator());
   cancel_delete_button = Gtk::manage(new class Gtk::Button(_("Cancel")));
   confirn_delete_label = Gtk::manage(new class Gtk::Label(_("<b>Delete this user?</b>")));
   fixed8 = Gtk::manage(new class Gtk::Fixed());
   vseparator1->set_size_request(16,184);
   logout_button->set_size_request(128,37);
   logout_button->set_flags(Gtk::CAN_FOCUS);
   logout_button->set_relief(Gtk::RELIEF_NORMAL);
   g_radio_button->set_flags(Gtk::CAN_FOCUS);
   g_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   g_radio_button->set_mode(true);
   g_radio_button->set_active(false);
   pg_radio_button->set_flags(Gtk::CAN_FOCUS);
   pg_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   pg_radio_button->set_mode(true);
   pg_radio_button->set_active(false);
   pg13_radio_button->set_flags(Gtk::CAN_FOCUS);
   pg13_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   pg13_radio_button->set_mode(true);
   pg13_radio_button->set_active(false);
   nc17_radio_button->set_flags(Gtk::CAN_FOCUS);
   nc17_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   nc17_radio_button->set_mode(true);
   nc17_radio_button->set_active(false);
   r_radio_button->set_flags(Gtk::CAN_FOCUS);
   r_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   r_radio_button->set_mode(true);
   r_radio_button->set_active(false);
   x_radio_button->set_flags(Gtk::CAN_FOCUS);
   x_radio_button->set_relief(Gtk::RELIEF_NORMAL);
   x_radio_button->set_mode(true);
   x_radio_button->set_active(false);
   nr_checkbox->set_flags(Gtk::CAN_FOCUS);
   nr_checkbox->set_relief(Gtk::RELIEF_NORMAL);
   nr_checkbox->set_mode(true);
   nr_checkbox->set_active(false);
   screen_movies_button->set_flags(Gtk::CAN_FOCUS);
   screen_movies_button->set_relief(Gtk::RELIEF_NORMAL);
   vbox7->pack_start(*g_radio_button);
   vbox7->pack_start(*pg_radio_button);
   vbox7->pack_start(*pg13_radio_button);
   vbox7->pack_start(*nc17_radio_button);
   vbox7->pack_start(*r_radio_button);
   vbox7->pack_start(*x_radio_button);
   vbox7->pack_start(*nr_checkbox);
   vbox7->pack_start(*screen_movies_button);
   alignment7->add(*vbox7);
   user_level_label->set_alignment(0.5,0.5);
   user_level_label->set_padding(0,0);
   user_level_label->set_justify(Gtk::JUSTIFY_LEFT);
   user_level_label->set_line_wrap(false);
   user_level_label->set_use_markup(true);
   user_level_label->set_selectable(false);
   frame3->set_size_request(168,280);
   frame3->set_shadow_type(Gtk::SHADOW_NONE);
   frame3->set_label_align(0,0.5);
   frame3->add(*alignment7);
   frame3->set_label_widget(*user_level_label);
   add_user_button->set_size_request(128,37);
   add_user_button->set_flags(Gtk::CAN_FOCUS);
   add_user_button->set_relief(Gtk::RELIEF_NORMAL);
   edit_user_button->set_size_request(128,37);
   edit_user_button->set_flags(Gtk::CAN_FOCUS);
   edit_user_button->set_relief(Gtk::RELIEF_NORMAL);
   remove_user_button->set_size_request(128,37);
   remove_user_button->set_flags(Gtk::CAN_FOCUS);
   remove_user_button->set_relief(Gtk::RELIEF_NORMAL);
   error_label->set_alignment(0.5,0.46);
   error_label->set_padding(0,0);
   error_label->set_justify(Gtk::JUSTIFY_LEFT);
   error_label->set_line_wrap(false);
   error_label->set_use_markup(false);
   error_label->set_selectable(false);
   user_name_edit_box->set_flags(Gtk::CAN_FOCUS);
   user_name_edit_box->set_visibility(true);
   user_name_edit_box->set_editable(true);
   user_name_edit_box->set_max_length(16);
   user_name_edit_box->set_text(_(""));
   user_name_edit_box->set_has_frame(true);
   user_name_edit_box->set_activates_default(false);
   password_edit_box->set_flags(Gtk::CAN_FOCUS);
   password_edit_box->set_visibility(false);
   password_edit_box->set_editable(true);
   password_edit_box->set_max_length(16);
   password_edit_box->set_text(_(""));
   password_edit_box->set_has_frame(true);
   password_edit_box->set_activates_default(false);
   cf_checkbox->set_flags(Gtk::CAN_FOCUS);
   cf_checkbox->set_relief(Gtk::RELIEF_NORMAL);
   cf_checkbox->set_mode(true);
   cf_checkbox->set_active(true);
   sq_checkbox->set_flags(Gtk::CAN_FOCUS);
   sq_checkbox->set_relief(Gtk::RELIEF_NORMAL);
   sq_checkbox->set_mode(true);
   sq_checkbox->set_active(true);
   sa_checkbox->set_flags(Gtk::CAN_FOCUS);
   sa_checkbox->set_relief(Gtk::RELIEF_NORMAL);
   sa_checkbox->set_mode(true);
   sa_checkbox->set_active(true);
   confirm_edit_box->set_flags(Gtk::CAN_FOCUS);
   confirm_edit_box->set_visibility(false);
   confirm_edit_box->set_editable(true);
   confirm_edit_box->set_max_length(16);
   confirm_edit_box->set_text(_(""));
   confirm_edit_box->set_has_frame(true);
   confirm_edit_box->set_activates_default(false);
   sq_edit_box->set_flags(Gtk::CAN_FOCUS);
   sq_edit_box->set_visibility(false);
   sq_edit_box->set_editable(true);
   sq_edit_box->set_max_length(16);
   sq_edit_box->set_text(_(""));
   sq_edit_box->set_has_frame(true);
   sq_edit_box->set_activates_default(false);
   sa_edit_box->set_flags(Gtk::CAN_FOCUS);
   sa_edit_box->set_visibility(false);
   sa_edit_box->set_editable(true);
   sa_edit_box->set_max_length(16);
   sa_edit_box->set_text(_(""));
   sa_edit_box->set_has_frame(true);
   sa_edit_box->set_activates_default(false);
   user_save_button->set_flags(Gtk::CAN_FOCUS);
   user_save_button->set_relief(Gtk::RELIEF_NORMAL);
   pw_checkbox->set_flags(Gtk::CAN_FOCUS);
   pw_checkbox->set_relief(Gtk::RELIEF_NORMAL);
   pw_checkbox->set_mode(true);
   pw_checkbox->set_active(true);
   confirm_label->set_alignment(0.01,0.5);
   confirm_label->set_padding(0,0);
   confirm_label->set_justify(Gtk::JUSTIFY_CENTER);
   confirm_label->set_line_wrap(false);
   confirm_label->set_use_markup(false);
   confirm_label->set_selectable(false);
   label10->set_alignment(0,0.5);
   label10->set_padding(0,0);
   label10->set_justify(Gtk::JUSTIFY_CENTER);
   label10->set_line_wrap(false);
   label10->set_use_markup(false);
   label10->set_selectable(false);
   user_name_label->set_alignment(0,0.5);
   user_name_label->set_padding(0,0);
   user_name_label->set_justify(Gtk::JUSTIFY_CENTER);
   user_name_label->set_line_wrap(false);
   user_name_label->set_use_markup(false);
   user_name_label->set_selectable(false);
   sa_label->set_alignment(0,0.5);
   sa_label->set_padding(0,0);
   sa_label->set_justify(Gtk::JUSTIFY_CENTER);
   sa_label->set_line_wrap(false);
   sa_label->set_use_markup(false);
   sa_label->set_selectable(false);
   sq_label->set_alignment(0,0.5);
   sq_label->set_padding(0,0);
   sq_label->set_justify(Gtk::JUSTIFY_CENTER);
   sq_label->set_line_wrap(false);
   sq_label->set_use_markup(false);
   sq_label->set_selectable(false);
   table1->set_row_spacings(0);
   table1->set_col_spacings(0);
   table1->attach(*user_name_edit_box, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 0, 0);
   table1->attach(*password_edit_box, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 0, 0);
   table1->attach(*cf_checkbox, 2, 3, 2, 3, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table1->attach(*sq_checkbox, 2, 3, 3, 4, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table1->attach(*sa_checkbox, 2, 3, 4, 5, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table1->attach(*confirm_edit_box, 1, 2, 2, 3, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 0, 0);
   table1->attach(*sq_edit_box, 1, 2, 3, 4, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 0, 0);
   table1->attach(*sa_edit_box, 1, 2, 4, 5, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 0, 0);
   table1->attach(*user_save_button, 1, 2, 5, 6, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   table1->attach(*pw_checkbox, 2, 3, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table1->attach(*confirm_label, 0, 1, 2, 3, Gtk::EXPAND, Gtk::AttachOptions(), 0, 0);
   table1->attach(*label10, 0, 1, 1, 2, Gtk::EXPAND, Gtk::AttachOptions(), 0, 0);
   table1->attach(*user_name_label, 0, 1, 0, 1, Gtk::EXPAND, Gtk::AttachOptions(), 0, 0);
   table1->attach(*sa_label, 0, 1, 4, 5, Gtk::EXPAND, Gtk::AttachOptions(), 0, 0);
   table1->attach(*sq_label, 0, 1, 3, 4, Gtk::EXPAND, Gtk::AttachOptions(), 0, 0);
   vbox6->pack_start(*error_label, Gtk::PACK_SHRINK, 0);
   vbox6->pack_start(*table1);
   vbox5->pack_start(*vbox6);
   alignment5->add(*vbox5);
   frame1->set_size_request(601,281);
   frame1->set_shadow_type(Gtk::SHADOW_IN);
   frame1->set_label_align(0,0.5);
   frame1->add(*alignment5);
   viewport1->set_shadow_type(Gtk::SHADOW_IN);
   viewport1->add(*hbox5);
   scrolledwindow1->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow1->set_shadow_type(Gtk::SHADOW_NONE);
   scrolledwindow1->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_NEVER);
   scrolledwindow1->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow1->add(*viewport1);
   alignment6->add(*scrolledwindow1);
   icon_select_frame_label->set_alignment(0.5,0.5);
   icon_select_frame_label->set_padding(0,0);
   icon_select_frame_label->set_justify(Gtk::JUSTIFY_LEFT);
   icon_select_frame_label->set_line_wrap(false);
   icon_select_frame_label->set_use_markup(true);
   icon_select_frame_label->set_selectable(false);
   frame2->set_size_request(600,184);
   frame2->set_shadow_type(Gtk::SHADOW_NONE);
   frame2->set_label_align(0,0.5);
   frame2->add(*alignment6);
   frame2->set_label_widget(*icon_select_frame_label);
   hseparator3->set_size_request(768,16);
   media_player_button->set_size_request(128,37);
   media_player_button->set_flags(Gtk::CAN_FOCUS);
   media_player_button->set_relief(Gtk::RELIEF_NORMAL);
   admin_icon->set_size_request(152,136);
   admin_icon->set_alignment(0.5,0.5);
   admin_icon->set_padding(0,0);
   admin_settings_button->set_size_request(128,37);
   admin_settings_button->set_flags(Gtk::CAN_FOCUS);
   admin_settings_button->set_relief(Gtk::RELIEF_NORMAL);
   change_icon_button->set_size_request(128,37);
   change_icon_button->set_flags(Gtk::CAN_FOCUS);
   change_icon_button->set_relief(Gtk::RELIEF_NORMAL);
   confirm_delete_button->set_size_request(110,32);
   confirm_delete_button->set_flags(Gtk::CAN_FOCUS);
   confirm_delete_button->set_relief(Gtk::RELIEF_NORMAL);
   user_label->set_size_request(160,16);
   user_label->set_alignment(0.5,0.5);
   user_label->set_padding(0,0);
   user_label->set_justify(Gtk::JUSTIFY_CENTER);
   user_label->set_line_wrap(false);
   user_label->set_use_markup(true);
   user_label->set_selectable(false);
   hseparator2->set_size_request(168,16);
   cancel_delete_button->set_size_request(110,32);
   cancel_delete_button->set_flags(Gtk::CAN_FOCUS);
   cancel_delete_button->set_relief(Gtk::RELIEF_NORMAL);
   confirn_delete_label->set_size_request(200,17);
   confirn_delete_label->set_alignment(0.5,0.52);
   confirn_delete_label->set_padding(0,0);
   confirn_delete_label->set_justify(Gtk::JUSTIFY_LEFT);
   confirn_delete_label->set_line_wrap(false);
   confirn_delete_label->set_use_markup(true);
   confirn_delete_label->set_selectable(false);
   fixed8->put(*vseparator1, 160, 40);
   fixed8->put(*logout_button, 0, 0);
   fixed8->put(*frame3, 0, 224);
   fixed8->put(*add_user_button, 384, 0);
   fixed8->put(*edit_user_button, 512, 0);
   fixed8->put(*remove_user_button, 640, 0);
   fixed8->put(*frame1, 167, 223);
   fixed8->put(*frame2, 168, 40);
   fixed8->put(*hseparator3, 0, 32);
   fixed8->put(*media_player_button, 128, 0);
   fixed8->put(*admin_icon, 8, 48);
   fixed8->put(*admin_settings_button, 256, 0);
   fixed8->put(*change_icon_button, 256, 0);
   fixed8->put(*confirm_delete_button, 248, 152);
   fixed8->put(*user_label, 0, 176);
   fixed8->put(*hseparator2, 0, 216);
   fixed8->put(*cancel_delete_button, 392, 152);
   fixed8->put(*confirn_delete_label, 280, 40);
   admin_dlg->set_title(_("Administration "));
   admin_dlg->set_modal(false);
   admin_dlg->property_window_position().set_value(Gtk::WIN_POS_NONE);
   admin_dlg->set_resizable(false);
   admin_dlg->property_destroy_with_parent().set_value(false);
   admin_dlg->add(*fixed8);
   logout_button->show();
   g_radio_button->show();
   pg_radio_button->show();
   pg13_radio_button->show();
   nc17_radio_button->show();
   r_radio_button->show();
   x_radio_button->show();
   nr_checkbox->show();
   screen_movies_button->show();
   vbox7->show();
   alignment7->show();
   user_level_label->show();
   frame3->show();
   add_user_button->show();
   edit_user_button->show();
   remove_user_button->show();
   error_label->show();
   user_name_edit_box->show();
   password_edit_box->show();
   cf_checkbox->show();
   sq_checkbox->show();
   sa_checkbox->show();
   confirm_edit_box->show();
   sq_edit_box->show();
   sa_edit_box->show();
   user_save_button->show();
   pw_checkbox->show();
   confirm_label->show();
   label10->show();
   user_name_label->show();
   sa_label->show();
   sq_label->show();
   table1->show();
   vbox6->show();
   vbox5->show();
   alignment5->show();
   hbox5->show();
   viewport1->show();
   scrolledwindow1->show();
   alignment6->show();
   hseparator3->show();
   media_player_button->show();
   admin_icon->show();
   admin_settings_button->show();
   change_icon_button->show();
   user_label->show();
   fixed8->show();
   admin_dlg->show();
   logout_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_logout_button_clicked), false);
   screen_movies_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_screen_movies_button_clicked), false);
   add_user_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_add_user_button_clicked), false);
   edit_user_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_edit_user_button_clicked), false);
   remove_user_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_remove_user_button_clicked), false);
   cf_checkbox->signal_toggled().connect(SigC::slot(*this, &admin_dlg_glade::on_cf_checkbox_toggled), false);
   sq_checkbox->signal_toggled().connect(SigC::slot(*this, &admin_dlg_glade::on_sq_checkbox_toggled), false);
   sa_checkbox->signal_toggled().connect(SigC::slot(*this, &admin_dlg_glade::on_sa_checkbox_toggled), false);
   user_save_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_user_save_button_clicked), false);
   pw_checkbox->signal_toggled().connect(SigC::slot(*this, &admin_dlg_glade::on_pw_checkbox_toggled), false);
   media_player_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_media_player_button_clicked), false);
   admin_settings_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_admin_settings_button_clicked), false);
   change_icon_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_change_icon_clicked), false);
   confirm_delete_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_confirm_delete_button_clicked), false);
   cancel_delete_button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::on_cancel_delete_button_clicked), false);
   admin_dlg->signal_delete_event().connect(SigC::slot(*this, &admin_dlg_glade::on_admin_dlg_delete_event), false);
}

admin_dlg_glade::~admin_dlg_glade()
{  delete gmm_data;
}
