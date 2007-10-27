// generated 2007/10/27 16:30:41 EDT by ctemple@Barf.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_chooser_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MEDIA_CHOOSER_DLG_HH
#  include "media_chooser_dlg_glade.hh"
#  define _MEDIA_CHOOSER_DLG_HH
class media_chooser_dlg : public media_chooser_dlg_glade
{  
public:
        
        media_chooser_dlg(GlademmData *gmm_data) : media_chooser_dlg_glade(gmm_data)
        {  
        }
private:
        
        void on_media_chooser_dlg_selection_changed();
};
#endif
