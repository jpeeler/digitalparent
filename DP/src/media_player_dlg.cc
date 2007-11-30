// generated 2007/10/18 15:52:33 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_player_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "media_player_dlg.hh"
#include "playlist_dlg.hh"
#include "media_chooser_dlg.hh"
#include "controller.h"

#include <vlc/libvlc.h>
#include <gtkmm/checkbutton.h>
#include <dvdnav/dvdnav.h>

#include <sstream>


std::string filename= "/dev/dvd";
const char **dvdtitle;
//const char *playtimes[4]={":start-time=0",":stop-time=30",":start-time=45",":stop-time=60"};
//const char* playtimes[2]={":start-time=30",":stop-time=45"};
std::vector<SkipTime> skipTimes;
std::vector<int> skipChapters;
std::vector<Gtk::CheckButton*> skipButtons;
int item;
int id;
bool firstTime = true;
playlist_dlg *playlist_dlg;
media_chooser_dlg *media_chooser;
bool audioSkipped=false;
Gtk::CheckButton *checkbutton;
bool isAdmin;
long startTime;
long endTime;
int dvdLength;
int vlcSpeed;
Gtk::Button *saveProfile;



extern Controller* useController();



void media_player_dlg::init()
{	
		useController()->loadDisc();
	//returns c_disc_underscore_loaded
	//useController()->loadProfile();
	const Profile *aprofile = useController()->c_getProfile();
		useController()->loadProfile();
	
	skipChapters.clear();
	skipTimes.clear();
	skipTimes = aprofile->getSkipTimes();
	skipChapters = aprofile->getSkipChapters();
	//buildPlaylist();
	/*
	
	
	printf("Skip Times start\n");
	const char *times[playTimes.size()];
	for(uint i=0; i<playTimes.size(); i++){
		times[i]=playTimes.at(i).c_str();
		printf("times[%d]= %s\n",i,times[i]);
	}
	printf("Skip Times end\n");
	*/
	isAdmin = useController()->c_getUserLoggedIn()->getUser()=="admin";
	char **test =NULL;					//used for VLC only
	libvlc_exception_init(&excp);
  	inst = libvlc_new (0, test, &excp);
	id = libvlc_get_vlc_id(inst);
	//item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof playtimes/sizeof *playtimes,playtimes, &excp);
	/*
	libvlc_media_descriptor_t *md;
	vlc_int64_t len;
	libvlc_media_instance_t *mi;
	md = libvlc_media_descriptor_new(inst, filename, &excp);
	len = libvlc_media_descriptor_get_duration(md, &excp);
	mi = libvlc_media_instance_new_from_media_descriptor(mi, &excp);
	libvlc_media_instance_play(mi, &excp);
	*/
	//printf("Length: %d\n", len);
	
	/*
	if(playTimes.size()==0){
		const char *noTimes[1]={":start-time=0"};
		playTimes.push_back(":start-time=0");	
		item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof noTimes/sizeof *noTimes,noTimes, &excp);
	} else {
		item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof times/sizeof *times,times, &excp);
	}
	*/

	std::string option;
	std::string name;
	int chap;
	//the following line may be commented out if we don't want to show the menu
	//item = libvlc_playlist_add(inst, filename.c_str(), "Root Menu", &excp);
	if(isAdmin){
		for(chap = 1; chap <= useController()->c_getDisc()->getDiscChapterNum(); chap++) {
			option = "dvd:///dev/dvd@1:" + to_string(chap);
			name = "Chapter " + to_string(chap);
//skipChapters.push_back(chap);
			libvlc_playlist_add(inst, option.c_str(), name.c_str(), &excp);
		    //const char* options = ":auto-preparse";
			//libvlc_playlist_add_extended(inst, option.c_str(), name.c_str(), 1, &options, &excp);
		}
	} else {
		for(int i=1; i<=useController()->c_getDisc()->getDiscChapterNum();i++){
			if(!skipChaptersContains(to_string(i))){
				option = "dvd:///dev/dvd@1:" + to_string(chap);
				name = "Chapter " + to_string(chap);
				libvlc_playlist_add(inst, option.c_str(), name.c_str(), &excp);
			}
		}
	}
	
	libvlc_playlist_play(inst, 0, 0, NULL, &excp);
	vlcSpeed=0;

	
	
	currentUser->set_text("User: " +useController()->c_getUserLoggedIn()->getUser());
	media->set_text(useController()->c_getDisc()->getDiscName());
	if(!isAdmin){
		cut_video->hide();
	}
	saveProfile = new class Gtk::Button("Save Profile");
	playlist_dlg = new class playlist_dlg();
	playlist_dlg->vbox4->pack_end(*saveProfile, Gtk::PACK_EXPAND_WIDGET, 0);
	playlist_dlg->hide();						//hide the dlg
	
	volume_slider->set_value(libvlc_audio_get_volume(inst,&excp));
	time_slider->set_range(0,(useController()->c_getDisc()->getDiscLength())/1000);
	dvdLength = (useController()->c_getDisc()->getDiscLength())/1000;
	
	saveProfile->signal_clicked().connect(SigC::slot(*this, &media_player_dlg::on_save_button_clicked), false);
	slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));
	

}

void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_destroy(inst);
	firstTime = true;
	if(playlist_button->get_active()){
		playlist_button->set_active(false);
	}
	skipChapters.clear();
	skipTimes.clear();
	delete playlist_dlg;
	init();
/* 	if(inst==NULL){
 * 	printf("VLC set up\n");
 * 	init();
 * 	}
 * 	libvlc_destroy (inst);
 * 	inst = libvlc_new (0, test, &excp);
 * 	id = libvlc_get_vlc_id(inst);
 * 	item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof filename/sizeof *playtimes,playtimes, &excp);
 * 	media->set_text("Currently Playing: " + filename);
 * 	status = dvdnav_get_title_string(dvdnav, dvdtitle);
 * 	printf("DVD title: %s\n",dvdtitle);
 */
		
}

void media_player_dlg::on_stop_button_clicked()
{
  libvlc_playlist_stop(inst,&excp);
  
}

void media_player_dlg::on_previous_button_clicked()
{  
	libvlc_playlist_prev(inst,&excp);
}

void media_player_dlg::on_rewind_button_clicked()
{
	//VLC_SpeedSlower(id);   //adjusted functions
	//VLC_TimeSet(id,(int)time_slider->get_value()-10,false);
    set_playback_time((int)time_slider->get_value()-10, false);
	
}

void media_player_dlg::on_cut_video_toggled()
{
	
	if(cut_video->get_active()){
		startTime = (long)VLC_TimeGet(id);
		dvdLength = VLC_LengthGet(id);
		printf("Cut Video start time:  %ld\n",startTime);
	} else {
		endTime = (long)VLC_TimeGet(id);
		printf("Cut Video end time:  %ld\n",endTime);
	
		if(startTime < endTime && startTime >0){
			useController()->c_addSkipTiming(startTime,endTime);
			printf("Added skip time\tStart time: %ld\tEnd time: %ld\n",startTime, endTime);
			SkipTime newSkip;
			newSkip.setSkipStart(startTime);
			newSkip.setSkipStop(endTime);
			skipTimes.push_back(newSkip);
			firstTime=true;
		} else if(startTime ==-10){
			useController()->c_addSkipTiming(0,endTime);
			printf("Added skip time\tStart time: %d\tEnd time: %ld\n",0, endTime);
			SkipTime newSkip;
			newSkip.setSkipStart(0);
			newSkip.setSkipStop(endTime);
			skipTimes.push_back(newSkip);
			firstTime=true;
		} else if(startTime!=-20) {
			useController()->c_addSkipTiming(startTime,(long)dvdLength);
			printf("Length: %d\n",VLC_LengthGet(id));
			printf("Start time not smaller then end time\n");
			printf("Added skip time\tStart time: %ld\tEnd time: %d\n",startTime,dvdLength);
			SkipTime newSkip;
			newSkip.setSkipStart(startTime);
			newSkip.setSkipStop(dvdLength);
			skipTimes.push_back(newSkip);
			firstTime=true;
		}
			delete playlist_dlg;
	saveProfile = new class Gtk::Button("Save Profile");
	playlist_dlg = new class playlist_dlg();
	playlist_dlg->vbox4->pack_end(*saveProfile, Gtk::PACK_EXPAND_WIDGET, 0);
	on_playlist_button_toggled();
	}
}

void media_player_dlg::on_next_button_clicked()
{  
	libvlc_playlist_next(inst,&excp);
	
	/** this is how the skins controller does it:
	input_thread_t *p_input =
        (input_thread_t *)vlc_object_find( getIntf(), VLC_OBJECT_INPUT,
                                           FIND_ANYWHERE );
    if( p_input )
    {
        vlc_value_t val;
        val.b_bool = VLC_TRUE;
        var_Set( p_input, "next-chapter", val );
        vlc_object_release( p_input );
    }
	*/
}

void media_player_dlg::on_fastforward_button_clicked()
{
	VLC_SpeedFaster(id);
	if(vlcSpeed < 3){
		vlcSpeed++;
	}
	printf("VLC speed is %d\n",vlcSpeed);
}

void media_player_dlg::on_pause_button_clicked()
{  
	libvlc_playlist_pause(inst,&excp);
}

void media_player_dlg::on_play_button_clicked()
{
	//not using becuase it will restart playback if play is hit when paused
	//libvlc_playlist_play (inst, item, 0, NULL, &excp); 
	if(vlcSpeed==0){
		VLC_Play(id);
	} else {
		for(int i=vlcSpeed;i!=0;i--){
			VLC_SpeedSlower(id);
		}
		vlcSpeed=0;
		VLC_Play(id);
	}
	
}

bool media_player_dlg::set_playback_time(int curVal, bool moving)
{
   //int curVal = newSkipTime((int) time_slider->get_value());
    //int dvdLen = 0;
    int vlcVal;
	if(libvlc_playlist_isplaying(inst,&excp)){
	   vlcVal = VLC_TimeGet(id);
	   if(5 > (dvdLength - curVal)) {
		  VLC_TimeSet(id, dvdLength - 5, false);
	   }
	   else if(vlcVal < dvdLength && curVal < vlcVal) {
	      VLC_TimeSet(id, curVal, false);
	   }
	   else {
	      //printf("Debug: curVal = %d vlcVal = %d dvdLength = %d\n", curVal, vlcVal, dvdLength);
	      while(vlcVal < curVal || vlcVal > dvdLength) {
		     //printf("Debug: VLC: %d\n", vlcVal);
		   	 if(vlcVal < curVal - 1 && curVal < dvdLength) {// && vlcVal != curVal + 1) {
			    printf("Debug: set time to %d\n", curVal);
		      	VLC_TimeSet(id, curVal, false);
		   	 }
		   
		   	 while(0 > VLC_TimeGet(id) || dvdLength < VLC_TimeGet(id) || 1 >= abs(VLC_TimeGet(id) - curVal)) {
			    //printf("Debug: stall - %d curVal %d\n", VLC_TimeGet(id), curVal); //stall
			  	
			  	if(moving)
					return true;
				else
					usleep(25);
		   	 }//usleep(200); //stall to let VLC catch up
			  
		   	 vlcVal = VLC_TimeGet(id);
		   	 printf("Debug: end stall - %d curVal = %d\n", vlcVal, curVal);
		  }
	   }
	}   
    return true;
}

bool media_player_dlg::update_slider()
{
   int vlcTime = VLC_TimeGet(id);
   if(libvlc_playlist_isplaying(inst, &excp)) {
    	if(vlcTime <= 0 || vlcTime > dvdLength){
			//time_slider->set_value(newSkipTime(0));
		} else {
			if(newSkipTime(vlcTime) != vlcTime){
				//time_slider->set_value(newSkipTime(vlcTime));
				//VLC_TimeSet(id,newSkipTime(vlcTime),false);
			    set_playback_time(vlcTime, false);
			} else {
				time_slider->set_value(newSkipTime(vlcTime));
			}
		}
	   
	}
	
	usleep(50);
	return true;
}

void media_player_dlg::on_time_slider_value_changed()
{  
	//time_slider->set_range(0,VLC_LengthGet(id));	
	//VLC_TimeSet(id,(int)time_slider->get_value(),false);
}

void media_player_dlg::on_time_slider_button_move_event() {
	
   // libvlc_media_instance_t *mi;
    int newTime;
/*     long currentTime, maxTime, vlcTime;
 *    
 *     vlcTime = VLC_TimeGet(id);
 *     mi = libvlc_playlist_get_media_instance(inst, &excp);
 *     currentTime = libvlc_media_instance_get_time(mi, &excp);
 * 	maxTime = libvlc_media_instance_get_length(mi, &excp);
 *    
 *     printf("vlc: %d cT: %d mT: %d\n", vlcTime, currentTime, maxTime);
 *    
 */
    int currentTime;
    if(libvlc_playlist_isplaying(inst, &excp)) {
	   currentTime = VLC_TimeGet(id);
	   newTime = newSkipTime((int)time_slider->get_value());
	   set_playback_time(newTime, true);
	   //usleep(50);
/* 	   VLC_TimeSet(id,newSkipTime((int)time_slider->get_value()),false);
 * 	   usleep(50);
 * 	   if(currentTime < 0 || currentTime > useController()->c_getDisc()->getDiscLength()) {
 * 		  libvlc_playlist_next(inst, &excp);
 * 		  VLC_TimeSet(id,newSkipTime((int)time_slider->get_value()),false);
 * 	   }
 */
	   printf("New Time: %d, VLC Time %d, Playing %d\n", newTime, VLC_TimeGet(id), libvlc_playlist_isplaying(inst, &excp));
	}
	//VLC_TimeSet(id,(int)time_slider->get_value(),false);
	//usleep(50);
}

bool media_player_dlg::on_time_slider_button_press(GdkEventButton *ev)
{  
       slider_signal.disconnect();
	   //slider_signal = Glib::signal_timeout().connect(SigC::slot(*this, &media_player_dlg::on_time_slider_button_move_event), 500);
	   slider_signal = time_slider->signal_value_changed().connect(SigC::slot(*this, &media_player_dlg::on_time_slider_button_move_event), 500);
   printf("Slider clicked, VLC Time %d\n", VLC_TimeGet(id));
	   

       return 0;
}

bool media_player_dlg::on_time_slider_button_release_event(GdkEventButton *ev)
{
	   slider_signal.disconnect();
       set_playback_time((int)time_slider->get_value(), false);
	   //VLC_TimeSet(id,(int)time_slider->get_value(),false);
/*        while(VLC_TimeGet(id) == (int)time_slider->get_value()) ;
 * 	
 *        printf("Slider released int. 1, slider: %d VLC Time %d\n", (int)time_slider->get_value(), VLC_TimeGet(id));
 * 	
 *        if(VLC_TimeGet(id) < (int)time_slider->get_value()) {
 *    	      while(VLC_TimeGet(id) != (int)time_slider->get_value()) {
 * 		     if(VLC_TimeGet(id) < 0) {
 * 		        libvlc_playlist_next(inst, &excp);
 * 			    usleep(100);
 * 		     }
 * 		     VLC_TimeSet(id,newSkipTime((int)time_slider->get_value()),false);
 * 		     usleep(200);
 * 	   	     printf("Slider released int., slider: %d VLC Time %d\n", (int)time_slider->get_value(), VLC_TimeGet(id));
 * 	
 * 	      }
 * 	   }
 */
       slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));
	   printf("Slider released, slider: %d VLC Time %d\n", (int)time_slider->get_value(), VLC_TimeGet(id));
	
       return 0;
}

void media_player_dlg::on_save_button_clicked()
{
	if(isAdmin){
		useController()->c_clearSkipVectors();
		printf("save button clicked\n");
		printf("&&&&& Skip Chapters Start &&&&&\n");
		for(uint i=0;i<skipChapters.size();i++){
				printf("Chapter: %d\n",skipChapters.at(i));
				useController()->c_addSkipChapter(skipChapters.at(i));
		}
		printf("&&&&& Skip Chapters End &&&&&\n");
		printf("&&&&& Skip Times Start &&&&&\n");
		for(uint j =0;j<skipTimes.size();j++){		
			printf("Start: %ld - End: %ld\n",skipTimes.at(j).getSkipStart(),skipTimes.at(j).getSkipStop());
			useController()->c_addSkipTiming(skipTimes.at(j).getSkipStart(),skipTimes.at(j).getSkipStop());
		}
		printf("&&&&& Skip Times End &&&&&\n");
		useController()->storeProfile();
	} else {
		printf("save button clicked\n");
		printf("&&&&& Skip Chapters Start &&&&&\n");
		for(uint i =0;i<skipChapters.size();i++){
			printf("Chapter: %d\n",skipChapters.at(i));
		}
		printf("&&&&& Skip Chapters End &&&&&\n");
		printf("&&&&& Skip Times Start &&&&&\n");
		for(uint j =0;j<skipTimes.size();j++){		
			printf("Start: %ld - End: %ld\n",skipTimes.at(j).getSkipStart(),skipTimes.at(j).getSkipStop());
		}
	printf("&&&&& Skip Times End &&&&&\n");
}
	
	
}

void media_player_dlg::on_playlist_button_toggled()
{
	if(playlist_button->get_active()){
		if(firstTime){
			firstTime=false;
			skipButtons.clear();
			for(int chap = 1; chap <= useController()->c_getDisc()->getDiscChapterNum(); chap++) {

				if(isAdmin || !skipChaptersContains("Chapter" + to_string(chap))){
					checkbutton = new class Gtk::CheckButton("Chapter" + to_string(chap));
					skipButtons.push_back(checkbutton);
					if(isAdmin && skipChaptersContains("Chapter" +to_string(chap))){
						checkbutton->set_active(false);
					} else {
						checkbutton->set_active();
					}
					checkbutton->show();
					checkbutton->signal_toggled().connect(SigC::slot(*this, &media_player_dlg::on_playlist_clicked), false);				
					playlist_dlg->vbox4->pack_start(*checkbutton,Gtk::PACK_EXPAND_WIDGET,0);
				}
			}
			for(uint i=0; i< skipTimes.size(); i++){
				std::string start = "Start: ";
				std::string end = " - End: ";	
					if(isAdmin || !skipTimesContains(start + to_string(skipTimes.at(i).getSkipStart())+end + to_string(skipTimes.at(i).getSkipStop()))){
						checkbutton = new class Gtk::CheckButton();
						checkbutton->set_label(start + to_string(skipTimes.at(i).getSkipStart())+end + to_string(skipTimes.at(i).getSkipStop()));
						if(isAdmin && !skipTimesContains(start + to_string(skipTimes.at(i).getSkipStart())+end + to_string(skipTimes.at(i).getSkipStop()))){
							checkbutton->set_active(false);
						} else {
							checkbutton->set_active();
						}
						checkbutton->show();
						skipButtons.push_back(checkbutton);
						checkbutton->signal_toggled().connect(SigC::slot(*this, &media_player_dlg::on_playlist_clicked), false);
						playlist_dlg->vbox4->pack_start(*checkbutton, Gtk::PACK_EXPAND_WIDGET, 0);
				}
			}
		}
		playlist_dlg->show_all_children();
		playlist_dlg->show();
	}
	else{
		playlist_dlg->hide();
	}
}


void media_player_dlg::on_volume_slider_value_changed()
{  
	libvlc_audio_set_volume(inst,(int)volume_slider->get_value(),&excp);
}

void media_player_dlg::on_Logout_clicked()
{  
	if(inst!=NULL){
		libvlc_destroy (inst);
	}
	delete playlist_dlg;
	skipTimes.clear();
	skipChapters.clear();
	firstTime=true;
	if(isAdmin){			
		useController()->dp_state=DP_ADMIN_PANEL;
		hide();
	} else {
		useController()->dp_state=DP_USER_PANEL;
		hide();
	}

}

void media_player_dlg::on_fullscreen_clicked()
{  
	VLC_FullScreen(id);
}

void media_player_dlg::on_mute_button_toggled()
{  
	VLC_VolumeMute(id);
	if(mute_button->get_active()){	
		sound->hide();	
		fixed1->remove(*sound);
		sound = Gtk::manage(new class Gtk::Image(std::string("/Projects/DP/pixmaps/audio-volume-muted.png")));
		fixed1->put(*sound,22,93);
		sound->show();
	} else {
		sound->hide();	
		fixed1->remove(*sound);
		sound = Gtk::manage(new class Gtk::Image(std::string("/Projects/DP/pixmaps/audio-volume-high.png")));
		fixed1->put(*sound,22,93);
		sound->show();
	}
}


bool media_player_dlg::on_delete_event(GdkEventAny * event){
	//libvlc_destroy(inst);
	on_Logout_clicked();
	return true;
}



void media_player_dlg::buildPlaylist(){
	//~ const Profile *aprofile = useController()->c_getProfile();
	//~ const std::vector<SkipTime>& skipTimes = aprofile->getSkipTimes();
	std::vector<SkipTime> playList;
 	SkipTime askiptime0;
 	askiptime0.setSkipStart(0);
 	askiptime0.setSkipStop(10);
 	playList.push_back(askiptime0);
 	SkipTime askiptime1;
 	askiptime1.setSkipStart(30);
	askiptime1.setSkipStop(60);
	playList.push_back(askiptime1);
	SkipTime askiptime2;
 	askiptime2.setSkipStart(90);
	askiptime2.setSkipStop(100);
	playList.push_back(askiptime2);
	SkipTime askiptime3;
	askiptime3.setSkipStart(110);
 	askiptime3.setSkipStop(200);
	playList.push_back(askiptime3);
 

	
	printf("Correct Skip Times\n");
	for (std::vector<SkipTime>::const_iterator it = playList.begin();
		it!=playList.end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	//std::vector<std::string> tempPlayTimes;
	//~ std::string start = ":start-Time=";
	//~ std::string stop = ":stop-Time=";
	//~ for (uint i =0;i<playList.size();i++){
		//~ if(playList.at(0).getSkipStart()!=0 && i==0){
			//~ skipTimes.push_back(start + "0");			
		//~ } else if (playList.at(0).getSkipStart()==0 && i==mute0){
			//~ skipTimes.push_back(start + to_string(playList.at(0).getSkipStop()));
			//~ i++;
		//~ }
		//~ skipTimes.push_back(stop + to_string(playList.at(i).getSkipStart()));
		//~ skipTimes.push_back(start + to_string(playList.at(i).getSkipStop()));
	//~ }

}

void media_player_dlg::on_playlist_clicked()
{
	printf("***** Start Playlist clicked *****\n");
	for(uint i =0; i<skipButtons.size();i++){
		printf("I: %d\n",i);
//button is active so the chapter/time is to be played so remove it from the chapters/time not to be played
		if(skipButtons.at(i)->property_active()==1){	
			printf("Button active: %s\n",skipButtons.at(i)->get_label().c_str());
			if(!eraseFromSkipChapters(skipButtons.at(i)->get_label())){
				//eraseFromSkipTimes(skipButtons.at(i)->get_label());
				addToSkipTimes(skipButtons.at(i)->get_label());
			}//erased from lists
//button is not active so the chapter/time needs to be added to the times not to play
		} else {
			printf("Button not active %s\n",skipButtons.at(i)->get_label().c_str());
			if(!skipChaptersContains(skipButtons.at(i)->get_label())){
				if(!addToSkipChapters(skipButtons.at(i)->get_label())){
					if(skipTimesContains(skipButtons.at(i)->get_label())){
						//addToSkipTimes(skipButtons.at(i)->get_label());
						eraseFromSkipTimes(skipButtons.at(i)->get_label());
					}
				}
			}
		}
	}//i skipButtons
	printf("***** End Playlist clicked *****\n");
}


int media_player_dlg::newSkipTime(int currentTime){
	
	for(uint i=0;i<skipTimes.size();i++){
		if(currentTime>=skipTimes.at(i).getSkipStart() && currentTime<=skipTimes.at(i).getSkipStop()){
			return skipTimes.at(i).getSkipStop();
		}
	}
	return currentTime;
}

bool media_player_dlg::eraseFromSkipChapters(std::string toRemove){
	//printf("Removing From Skip Chapters %s\n",toRemove.c_str());
	std::vector<int>::iterator it;
		for(uint i=0;i<skipChapters.size();i++){
			//printf("SkipChapters[%d]: %d\n",i,skipChapters.at(i));
			//printf("Found string: ");
			std::string toCompare = "Chapter" +to_string(skipChapters.at(i));
			//bool temp = toCompare==toRemove;
			//printf(to_string(temp).c_str());
			//printf("\n");
			if(toCompare==toRemove){
				//printf("Size before %d\n",skipChapters.size());
				it=skipChapters.begin()+i;
				skipChapters.erase(it);
				printf("%s removed\n",toRemove.c_str());
				//printf("Size after %d\n",skipChapters.size());
				return true;
			}
		}
	return false;
}

bool media_player_dlg::eraseFromSkipTimes(std::string toRemove){
	//printf("Removing from Skip Times %s\n",toRemove.c_str());
	std::string toRemoveString;
	//printf("Size of toRemove: %d\n",toRemove.size());
	if(toRemove.find_first_of("C")==0){
		return false;
	}
	for(uint m =7;m<toRemove.find_first_of("-");m++){
			toRemoveString += toRemove.at(m);
	}
	//printf("toRemoveString Final: %s\n",toRemoveString.c_str());
	int start = to_int(toRemoveString);
	std::vector<SkipTime>::iterator it;
	for(uint i=0;i<skipTimes.size();i++){
		//printf("SkipTimes[%d]: [%ld - %ld]\n",i,skipTimes.at(i).getSkipStart(),skipTimes.at(i).getSkipStop());		
		//printf("Skiptimes Start: %s\n",toString.c_str());
		//printf("Found String %d\n",temp);
		if(skipTimes.at(i).getSkipStart() == start){	
			it=skipTimes.begin()+i;			
			skipTimes.erase(it);
			printf("%d removed\n",start);
			return true;
		}
	}
	return false;
}

bool media_player_dlg::skipChaptersContains(std::string toFind){
	std::string chapterString;
	//printf("Checking for %s in SkipChapters\n",toFind.c_str());
	if(toFind.find_first_of("S")==0){
		//printf("Wrong string for Skip Chapter\n");
		return false;
	} else {	
		for(uint i=7;i<toFind.size();i++){
			chapterString +=toFind.at(i);
		}
		//printf("Chapter String: '%s'\n",chapterString.c_str());
	}
	int chapter = to_int(chapterString);
	for(uint i=0;i<skipChapters.size();i++){
		if(skipChapters.at(i)==chapter){	
			printf("Found string in SkipChapters\n");
			return true;
		}
	}
	//printf("String not found in SkipChapters\n");
	return false;
}

bool media_player_dlg::skipTimesContains(std::string toFind){
	//printf("Checking for '%s' in skipTimes\n",toFind.c_str());
	std::string startString;
	if(toFind.find_first_of("C")==0){
//the string is a skipChapter
		//printf("Wrong string for skipTimes\n");
		return false;
	} else {
		//build start time
		for(uint i =7;i<toFind.find_first_of("-");i++){
			startString +=toFind.at(i);
		}
	}
	int start = to_int(startString);
	for(uint i=0;i<skipTimes.size();i++){
		if(skipTimes.at(i).getSkipStart()==start){	
			printf("Found string in skipTimes\n");
			return true;
		}
	}
	//printf("String not found in skipTimes\n");
	return false;
}

bool media_player_dlg::profileSkipChaptersContains(int toFind){
	//printf("Checking for %d in profileSkipChapters\n",toFind);
	std::vector<int> profileSkipChapters = useController()->c_getProfile()->getSkipChapters();
	if(isAdmin){
		//printf("User is admin\n");
		return false;
	} else {
		for(uint i=0;i<profileSkipChapters.size();i++){
			if(profileSkipChapters.at(i)==toFind	){	
				printf("Found string in profileSkipChapters\n");
				return true;
			}
		}
	}
	//printf("String not found in SkipChapters\n");
	return false;
}

bool media_player_dlg::addToSkipChapters(std::string toAdd){
	//printf("Adding '%s' to skipChapters\n",toAdd.c_str());
//the string is for a skip time
	if(toAdd.find_first_of("S")==0){
		printf("Wrong string for Skip Chapter\n");
		return false;
	} else {
//build the chapter number
		std::string chapterString;
		for(uint i=7;i<toAdd.size();i++){
			chapterString +=toAdd.at(i);
		}
		//printf("Chapter String: '%s'\n",chapterString.c_str());
		int chapter = to_int(chapterString);
//find where it goes and insert it
		if(skipChapters.size()==0){
			skipChapters.push_back(chapter);
		} else {
		std::vector<int>::iterator it;
		for(uint i =0; i<skipChapters.size();i++){
			//smaller then the first element
			//insert at the beginning
			if(i==0){
				if(chapter<skipChapters.at(i)){
					printf("Adding %d at beginning of skipChapters\n",chapter);
					skipChapters.insert(skipChapters.begin(),chapter);
					return true;
				}
//int the middle of the vector
			} else if(i!=skipChapters.size()-1){
				int before = i-1;
				int after = i;
				//printf("Chapter before: %d Chapter After: %d\n",skipChapters.at(before),skipChapters.at(after));
				if(chapter > skipChapters.at(before) && chapter < skipChapters.at(after)){
					it = skipChapters.begin() +i;
					printf("Adding %d between %d and %d in skipChapters\n",chapter,skipChapters.at(before),skipChapters.at(after));
					skipChapters.insert(it,chapter);
					return true;
				}
//at the end
			} else {
				if(chapter > skipChapters.at(i)){
					printf("Adding %d to end of skipChapters\n",chapter);
					skipChapters.push_back(chapter);
					return true;
				}
				if(i==skipChapters.size()-1 && skipChapters.size()==2){
					if(chapter > skipChapters.at(0) &&chapter < skipChapters.at(i)){
						printf("Adding %d to middle of 2 element array\n",chapter);
						it=skipChapters.begin() +i;
						skipChapters.insert(it,chapter);
						return true;
					}
				}
			}
		}
		}
	}
	printf("nothing added to skipChapters\n");
	return false;
}

bool media_player_dlg::addToSkipTimes(std::string toAdd){
	printf("Adding '%s' to skipTimes\n",toAdd.c_str());
	if(toAdd.find_first_of("C")==0){
//the string is a skipChapter
		printf("Wrong string for skipTimes");
		return false;
	} else {
		std::string startString;
		std::string endString;
		SkipTime newSkip;
		//build start time
		for(uint i =7;i<toAdd.find_first_of("-");i++){
			startString +=toAdd.at(i);
		}
		//printf("Start String is '%s'\n",startString.c_str());
		int start = to_int(startString);
		newSkip.setSkipStart(start);
		//build end time
		for(uint i=toAdd.find_last_of(":")+1;i<toAdd.size();i++){
			endString +=toAdd.at(i);
		}
		int end = to_int(endString);
		//printf("End String is '%s'\n",endString.c_str());
		newSkip.setSkipStop(end);
		std::vector<SkipTime>::iterator it;
		//printf("Skip Times size: %d\n",skipTimes.size());
		if(skipTimes.size()==0){
			skipTimes.push_back(newSkip);
		} else {
		for(uint i =0; i<skipTimes.size();i++){

			//printf("I in skip times: %d \n",i);
			//smaller then the first element
			//insert at the beginning
//			if(i==0 && start<skipTimes.at(i).getSkipStart()){
			if(i==0){
				if(start<skipTimes.at(i).getSkipStart()){
					printf("Adding [%d-%d] at beginning of skipTimes\n",start,end);
					skipTimes.insert(skipTimes.begin(),newSkip);
					return true;
				}
//int the middle of the vector
			} else if(i!=skipTimes.size()-1){
				//printf("in middle\n");
				int beg = i-1;
				if(start > skipTimes.at(beg).getSkipStart() && start < skipTimes.at(i).getSkipStart()){
					it = skipTimes.begin() +i;
					printf("Adding [%d-%d] between [%ld-%ld] and [%ld-%ld] in skipTimes\n"
					,start,end,skipTimes.at(i-1).getSkipStart(),skipTimes.at(i-1).getSkipStop(),skipTimes.at(i).getSkipStart(),skipTimes.at(i).getSkipStop());
					skipTimes.insert(it,newSkip);
					return true;
				}
//at the end
			} else {
				if(start > skipTimes.at(i).getSkipStart()){
					printf("Adding [%d-%d] to end of skipChapters\n",start,end);
					skipTimes.push_back(newSkip);
					return true;
				}
				if(i==skipTimes.size()-1 && skipTimes.size()==2){
					//printf("Skip Times End: %ld\n",skipTimes.end()->getSkipStart());
					if(start > skipTimes.begin()->getSkipStart() &&start < skipTimes.at(i).getSkipStart() ){
						printf("Adding [%d-%d] to middle of 2 element array\n",start,end);
						it=skipTimes.begin() +i;
						skipTimes.insert(it,newSkip);
						return true;
					}
				}
			}
		}
	}
}
	printf("nothing added to skip times\n");
	return false;
}


int media_player_dlg::to_int(const std::string &str) {
	std::stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

template <class T>
inline std::string media_player_dlg::to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}
