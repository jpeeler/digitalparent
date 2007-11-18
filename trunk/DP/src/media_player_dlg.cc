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
std::vector<std::string> playTimes;
int item;
int id;
bool firstTime = true;
playlist_dlg *playlist_dlg;
media_chooser_dlg *media_chooser;
bool audioSkipped=false;
Gtk::CheckButton * checkbutton;
bool isAdmin;
long startTime;
long endTime;
int dvdLength;
int vlcSpeed;


extern Controller* useController();



void media_player_dlg::init()
{
	/*
	buildPlaylist();
	
	
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
	item = libvlc_playlist_add(inst, filename.c_str(), "Root Menu", &excp);
	//!!!!!!! need to change chap limit to disc->getChapterNum() once the
	//disc info is loaded
	for(chap = 1; chap <= 20; chap++) {
		option = "dvd:///dev/dvd@1:" + to_string(chap);
		name = "Chapter " + to_string(chap);
		libvlc_playlist_add(inst, option.c_str(), name.c_str(), &excp);
	}
	
	libvlc_playlist_play(inst, 0, 0, NULL, &excp);
	vlcSpeed=0;
	
	useController()->loadDisc();
	
	currentUser->set_text("User: " +useController()->c_getUserLoggedIn()->getUser());
	media->set_text(useController()->c_getDisc()->getDiscName());
	if(!isAdmin){
		cut_video->hide();
	}
	
	playlist_dlg = new class playlist_dlg();
	playlist_dlg->hide();						//hide the dlg
	
	volume_slider->set_value(libvlc_audio_get_volume(inst,&excp));
	time_slider->set_range(0,(useController()->c_getDisc()->getDiscLength())/1000);
	
	
	slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));
	

}

void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_destroy(inst);
	playTimes.clear();
	printf("size of cleared playtimes %d\n",playTimes.size());
	firstTime = true;
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
	VLC_TimeSet(id,(int)time_slider->get_value()-10,false);
	
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
	
		if(startTime < endTime){
			useController()->c_addSkipTiming(startTime,endTime);
			printf("Added skip time\tStart time: %ld\tEnd time: %ld\n",startTime, endTime);
		} else if(startTime!=-20) {
			useController()->c_addSkipTiming(startTime,(long)dvdLength);
			printf("Length: %d\n",VLC_LengthGet(id));
			printf("Start time not smaller then end time\n");
			printf("Added skip time\tStart time: %ld\tEnd time: %d\n",startTime,dvdLength);
		}
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

bool media_player_dlg::update_slider()
{
	if(libvlc_playlist_isplaying(inst,&excp)){
		if(VLC_TimeGet(id)<0){
			time_slider->set_value(0);
		} else {
			time_slider->set_value(VLC_TimeGet(id));
		}
	}
	
	return true;
}

void media_player_dlg::on_time_slider_value_changed()
{  
	//time_slider->set_range(0,VLC_LengthGet(id));	
	//VLC_TimeSet(id,(int)time_slider->get_value(),false);
}

void media_player_dlg::on_time_slider_button_move_event() {
	VLC_TimeSet(id,(int)time_slider->get_value(),false);
	usleep(50);
}

bool media_player_dlg::on_time_slider_button_press(GdkEventButton *ev)
{  
       slider_signal.disconnect();
	   //slider_signal = Glib::signal_timeout().connect(SigC::slot(*this, &media_player_dlg::on_time_slider_button_move_event), 500);
	   slider_signal = time_slider->signal_value_changed().connect(SigC::slot(*this, &media_player_dlg::on_time_slider_button_move_event), 500);

       return 0;
}

bool media_player_dlg::on_time_slider_button_release_event(GdkEventButton *ev)
{
	   slider_signal.disconnect();
	   //VLC_TimeSet(id,(int)time_slider->get_value(),false);
       slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));

       return 0;
}


void media_player_dlg::on_playlist_button_toggled()
{
	if(playlist_button->get_active()){
		if(firstTime){
			firstTime=false;
			for(uint i=0; i< playTimes.size(); i++){
				if(i%2==0){
				checkbutton = new class Gtk::CheckButton(playTimes[i]);
				} else {
					checkbutton->set_label(checkbutton->get_label() +" , " + playTimes[i]);
				}
				checkbutton->set_active();
				//checkbutton->show();
				playlist_dlg->vbox4->pack_start(*checkbutton, Gtk::PACK_EXPAND_WIDGET, 0);
			}
		}
		//playlist_dlg->vbox4->show();
		//playlist_dlg->show();
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
	playTimes.clear();
	firstTime=true;
	if(isAdmin){		
		hide();
	} else {
		useController()->dp_state=DP_LOGIN;
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
}


bool media_player_dlg::on_delete_event(GdkEventAny * event){
	//libvlc_destroy(inst);
	on_Logout_clicked();
	return true;
}



void media_player_dlg::buildPlaylist(){
	const Profile *aprofile = useController()->c_getProfile();
	const std::vector<SkipTime>& skipTimes = aprofile->getSkipTimes();
	//~ std::vector<SkipTime> skipTimes;
 	//~ SkipTime askiptime0;
 	//~ askiptime0.setSkipStart(0);
 	//~ askiptime0.setSkipStop(10);
 	//~ skipTimes.push_back(askiptime0);
 	//~ SkipTime askiptime1;
 	//~ askiptime1.setSkipStart(30);
	//~ askiptime1.setSkipStop(60);
	//~ skipTimes.push_back(askiptime1);
	//~ SkipTime askiptime2;
 	//~ askiptime2.setSkipStart(90);
	//~ askiptime2.setSkipStop(100);
	//~ skipTimes.push_back(askiptime2);
	//~ SkipTime askiptime3;
	//~ askiptime3.setSkipStart(110);
 	//~ askiptime3.setSkipStop(200);
	//~ skipTimes.push_back(askiptime3);
 

	
	printf("Correct Skip Times\n");
	for (std::vector<SkipTime>::const_iterator it = skipTimes.begin();
		it!=skipTimes.end(); ++it)
	{
		printf("[%ld-%ld] ",it->getSkipStart(), it->getSkipStop());
	}
	puts("");
	//std::vector<std::string> tempPlayTimes;
	std::string start = ":start-Time=";
	std::string stop = ":stop-Time=";
	for (uint i =0;i<skipTimes.size();i++){
		if(skipTimes.at(0).getSkipStart()!=0 && i==0){
			playTimes.push_back(start + "0");			
		} else if (skipTimes.at(0).getSkipStart()==0 && i==0){
			playTimes.push_back(start + to_string(skipTimes.at(0).getSkipStop()));
			i++;
		}
		playTimes.push_back(stop + to_string(skipTimes.at(i).getSkipStart()));
		playTimes.push_back(start + to_string(skipTimes.at(i).getSkipStop()));
	}

}

template <class T>
inline std::string media_player_dlg::to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}
