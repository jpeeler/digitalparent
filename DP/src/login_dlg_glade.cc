// generated 2007/10/23 10:33:53 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/login_dlg.cc


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
#include "login_dlg_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>

login_dlg_glade::login_dlg_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  login_dlg = this;
   gmm_data = new GlademmData(get_accel_group());
   drawingarea2 = Gtk::manage(new class Gtk::DrawingArea());
   admin_psswrd_edit_box = Gtk::manage(new class Gtk::Entry());
   previous_user_button = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-media-previous")));
   admin_login_label = Gtk::manage(new class Gtk::Label(_("Please enter the password to login as the administrator.")));
   next_user_button = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-media-next")));
   hseparator1 = Gtk::manage(new class Gtk::HSeparator());
   admin_login_button = Gtk::manage(new class Gtk::Button());
   user_icon_select_button2 = Gtk::manage(new class Gtk::Button());
   user_icon_select_button1 = Gtk::manage(new class Gtk::Button());
   user_icon_select_button3 = Gtk::manage(new class Gtk::Button());
   fixed5 = Gtk::manage(new class Gtk::Fixed());
   vbox1 = Gtk::manage(new class Gtk::VBox(false, 0));
   drawingarea2->set_size_request(784,16);
   admin_psswrd_edit_box->set_size_request(160,27);
   admin_psswrd_edit_box->set_flags(Gtk::CAN_FOCUS);
   admin_psswrd_edit_box->set_visibility(false);
   admin_psswrd_edit_box->set_editable(true);
   admin_psswrd_edit_box->set_max_length(16);
   admin_psswrd_edit_box->set_text(_(""));
   admin_psswrd_edit_box->set_has_frame(true);
   admin_psswrd_edit_box->set_activates_default(true);
   previous_user_button->set_size_request(96,40);
   previous_user_button->set_flags(Gtk::CAN_FOCUS);
   previous_user_button->set_relief(Gtk::RELIEF_NORMAL);
   admin_login_label->set_size_request(152,72);
   admin_login_label->set_alignment(0.5,0.5);
   admin_login_label->set_padding(0,0);
   admin_login_label->set_justify(Gtk::JUSTIFY_CENTER);
   admin_login_label->set_line_wrap(true);
   admin_login_label->set_use_markup(false);
   admin_login_label->set_selectable(false);
   next_user_button->set_size_request(96,40);
   next_user_button->set_flags(Gtk::CAN_FOCUS);
   next_user_button->set_relief(Gtk::RELIEF_NORMAL);
   hseparator1->set_size_request(760,16);
   admin_login_button->set_size_request(160,136);
   admin_login_button->set_flags(Gtk::CAN_FOCUS);
   admin_login_button->set_relief(Gtk::RELIEF_NORMAL);
   user_icon_select_button2->set_size_request(160,136);
   user_icon_select_button2->set_flags(Gtk::CAN_FOCUS);
   user_icon_select_button2->set_relief(Gtk::RELIEF_NORMAL);
   user_icon_select_button1->set_size_request(160,136);
   user_icon_select_button1->set_flags(Gtk::CAN_FOCUS);
   user_icon_select_button1->set_relief(Gtk::RELIEF_NORMAL);
   user_icon_select_button3->set_size_request(160,136);
   user_icon_select_button3->set_flags(Gtk::CAN_FOCUS);
   user_icon_select_button3->set_relief(Gtk::RELIEF_NORMAL);
   fixed5->put(*drawingarea2, 0, 344);
   fixed5->put(*admin_psswrd_edit_box, 208, 128);
   fixed5->put(*previous_user_button, 8, 288);
   fixed5->put(*admin_login_label, 216, 32);
   fixed5->put(*next_user_button, 680, 288);
   fixed5->put(*hseparator1, 16, 176);
   fixed5->put(*admin_login_button, 24, 24);
   fixed5->put(*user_icon_select_button2, 312, 208);
   fixed5->put(*user_icon_select_button1, 128, 208);
   fixed5->put(*user_icon_select_button3, 496, 208);
   vbox1->pack_start(*fixed5);
   login_dlg->set_title(_("Digital Parent - Login"));
   login_dlg->set_modal(false);
   login_dlg->property_window_position().set_value(Gtk::WIN_POS_NONE);
   login_dlg->set_resizable(true);
   login_dlg->property_destroy_with_parent().set_value(false);
   login_dlg->add(*vbox1);
   drawingarea2->show();
   admin_psswrd_edit_box->show();
   previous_user_button->show();
   admin_login_label->show();
   next_user_button->show();
   hseparator1->show();
   admin_login_button->show();
   user_icon_select_button2->show();
   user_icon_select_button1->show();
   user_icon_select_button3->show();
   fixed5->show();
   vbox1->show();
   login_dlg->show();
   admin_psswrd_edit_box->signal_editing_done().connect(SigC::slot(*this, &login_dlg_glade::on_admin_psswrd_edit_box_editing_done), false);
   previous_user_button->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_previous_user_button_clicked), false);
   next_user_button->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_next_user_button_clicked), false);
   admin_login_button->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_admin_login_button_clicked), false);
   user_icon_select_button2->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_user_icon_select_button2_clicked), false);
   user_icon_select_button1->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_user_icon_select_button1_clicked), false);
   user_icon_select_button3->signal_clicked().connect(SigC::slot(*this, &login_dlg_glade::on_user_icon_select_button3_clicked), false);
}

login_dlg_glade::~login_dlg_glade()
{  delete gmm_data;
}
