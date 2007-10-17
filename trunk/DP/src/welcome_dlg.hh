// generated 2007/10/17 13:39:21 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to welcome_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WELCOME_DLG_HH
#  include "welcome_dlg_glade.hh"
#  define _WELCOME_DLG_HH
class welcome_dlg : public welcome_dlg_glade
{  
        
        void on_init_password_edit_box_editing_done();
        void on_repeat_password_edit_box_editing_done();
        void on_secret_q_edit_box_editing_done();
        void on_secret_a_edit_box_editing_done();
        void on_welcome_next_button_clicked();
};
#endif
