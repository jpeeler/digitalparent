// generated 2007/12/6 18:26:41 EST by ctemple@Barf.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to DiscRating.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "DiscRating.hh"
#include "controller.h"
#include "std_errors.h"
extern Controller* useController();

void DiscRating::on_saveButton_clicked()
{  
	if ( gButton->get_state() == true )
		useController()->c_setDiscRating(G);
	else if ( pgButton->get_state() == true )
		useController()->c_setDiscRating(PG);
	else if ( pg13Button->get_state() == true )
		useController()->c_setDiscRating(PG13);
	else if ( nc17Button->get_state() == true )
		useController()->c_setDiscRating(NC17);
	else if ( rButton->get_state() == true )
		useController()->c_setDiscRating(R);
	else if ( allButton->get_state() == true )
		useController()->c_setDiscRating(X);
	useController()->storeDisc();
	hide();
	
}
