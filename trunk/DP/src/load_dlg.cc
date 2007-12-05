// generated 2007/12/5 8:23:26 EST by pwightm@pwightm-desktop3.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to load_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "load_dlg.hh"

void load_dlg::set_progress(float progress) {
   
  load_progress->set_fraction(progress);
  while(g_main_pending())
    	g_main_iteration(false);
}
