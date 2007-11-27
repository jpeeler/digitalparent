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
	frame4->hide();
		useController()->loadDisc();
	//returns c_disc_underscore_loaded
	//useController()->loadProfile();
	const Profile *aprofile = useController()->c_getProfile();
		useController()->loadProfile();
	
	//skipChapters = aprofile->getSkipChapters();
	skipChapters.clear();
	skipTimes.clear();
	skipTimes = aprofile->getSkipTimes();
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
skipChapters.push_back(chap);
			libvlc_playlist_add(inst, option.c_str(), name.c_str(), &excp);
		}
	} else {
		for(int i=1; i<useController()->c_getDisc()->getDiscChapterNum();i++){
			for(uint j=0;j<skipChapters.size();j++){
				if(skipChapters.at(j)!=i){
					option = "dvd:///dev/dvd@1:" + to_string(chap);
					name = "Chapter " + to_string(chap);
					libvlc_playlist_add(inst, option.c_str(), name.c_str(), &excp);
				}
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
	
	
	saveProfile->signal_clicked().connect(SigC::slot(*this, &media_player_dlg::on_save_button_clicked), false);
	slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));
	

}

void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_destroy(inst);
	skipTimes.clear();
	skipChapters.clear();
	firstTime = true;
	if(playlist_button->get_active()){
		playlist_button->set_active(false);
	}
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
			time_slider->set_value(newSkipTime(0));
		} else {
			if(newSkipTime(VLC_TimeGet(id))!=VLC_TimeGet(id)){
				time_slider->set_value(newSkipTime(VLC_TimeGet(id)));
				VLC_TimeSet(id,newSkipTime(VLC_TimeGet(id)),false);
			} else {
				time_slider->set_value(newSkipTime(VLC_TimeGet(id)));
			}
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
	
	VLC_TimeSet(id,newSkipTime((int)time_slider->get_value()),false);
	//VLC_TimeSet(id,(int)time_slider->get_value(),false);
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

void media_player_dlg::on_save_button_clicked()
{
	if(isAdmin){
		useController()->c_clearSkipVectors();
		printf("save button clicked\n");
		printf("&&&&& Skip Chapters Start &&&&&\n");
		for(uint i =0;i<skipChapters.size();i++){
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
				checkbutton = new class Gtk::CheckButton("Chapter" + to_string(chap));
				skipButtons.push_back(checkbutton);
				checkbutton->set_active();
				checkbutton->signal_toggled().connect(SigC::slot(*this, &media_player_dlg::on_playlist_clicked), false);				
				playlist_dlg->vbox4->pack_start(*checkbutton,Gtk::PACK_EXPAND_WIDGET,0);
			}
			for(uint i=0; i< skipTimes.size(); i++){
				checkbutton = new class Gtk::CheckButton();
				std::string start = "Start: ";
				std::string end = " - End: ";				
				checkbutton->set_label(start + to_string(skipTimes.at(i).getSkipStart())+end + to_string(skipTimes.at(i).getSkipStop()));
				checkbutton->set_active();
				skipButtons.push_back(checkbutton);
				checkbutton->signal_toggled().connect(SigC::slot(*this, &media_player_dlg::on_playlist_clicked), false);
				playlist_dlg->vbox4->pack_start(*checkbutton, Gtk::PACK_EXPAND_WIDGET, 0);
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
	//printf("size of old playlsit: %d\n",libvlc_playlist_items_count(inst,&excp));
	libvlc_playlist_delete_item(inst,12,&excp);
	for (uint i=0; i<skipButtons.size(); i++ )
	{
		printf("I:%d\n",i);
		//printf("active for %d is: %d\n" ,i,skipButtons.at(i)->property_active()==0);
		if(skipButtons.at(i)->property_active()==0){
			printf("Button not active was %s\n",skipButtons.at(i)->get_label().c_str());
			if(!eraseFromSkipChapters(skipButtons.at(i)->get_label())){
				eraseFromSkipTimes(skipButtons.at(i)->get_label());
			}
		} else {
			printf("Button active was %s\n",skipButtons.at(i)->get_label().c_str());
		//libvlc_playlist_add(inst, "dvd:///dev/dvd@1:" + to_string(i).c_str(), "Chapter " + to_string(i).c_str(), &excp);
			std::vector<int>::iterator it;
			//printf("Skip Chapters size: %d\n",skipChapters.size());
			std::string testString = "Chapter1";
			bool chapter1 = skipButtons.at(i)->get_label().c_str()==testString;
			bool chapter1Button= skipButtons.at(i)->property_active()==1;
			//printf("Button at(%d) label is: %s\n Active: %d\n",i,skipButtons.at(i)->get_label().c_str(),skipButtons.at(i)->property_active()==1);
			//printf("Chapter 1: %d\n Chapter1 active: %d\n",chapter1,chapter1Button);
			if(skipChapters.size()==0 && chapter1 && chapter1Button){
				//printf("Adding Chapter %d\n",useController()->c_getProfile()->getSkipChapters().at(0));
				printf("Adding Chapter 1\n");
				//skipChapters.push_back(useController()->c_getProfile()->getSkipChapters().at(0));
				skipChapters.push_back(1);
			} else {
printf("Checking Skip Chapters\n Size: %d\n",skipChapters.size());
printf("Number of Disc Chapters: %d\n",useController()->c_getDisc()->getDiscChapterNum());
				std::string label = skipButtons.at(i)->get_label();
				std::string tempLabel;
				for(uint p =7;p<label.size();p++){
					tempLabel +=label.at(p);
				}
				printf("tempLabel %s\n",tempLabel.c_str());
				for(uint j =1;j<=(unsigned)useController()->c_getDisc()->getDiscChapterNum();j++){

					if(!profileSkipChaptersContains(j)){
	
						if(j>=skipChapters.size() && !skipChaptersContains(tempLabel) && (signed)tempLabel.find_first_of("-")==-1){
							printf("J is %d greater then skipChapters.size()\n",j);
							printf("Adding: %d to skipChapters\n",j);
							skipChapters.push_back(j);
						//} else if(!skipChaptersContains(to_string(skipChapters.at(j)))){							
						} else if(!skipChaptersContains(tempLabel) && j==(unsigned)to_int(tempLabel)){
							printf("to_int(tempLabel): %d\n",to_int(tempLabel));
						it = skipChapters.begin() +(j-1);
						printf("Adding: %d to skipChapters\n",j);
						skipChapters.insert(it,j);
						}
					}
				}
			}
			std::vector<SkipTime>::iterator it2;
			std::string buttonLabel = skipButtons.at(i)->get_label();
			std::string toIntStart;
					std::string toIntEnd;
			if(skipTimes.size()==0 &&buttonLabel.at(0)=='S'){
				printf("SkipTimes size ==0\n");
				printf("buttonLabel at 6: %c at 7: %c\n",buttonLabel.at(6),buttonLabel.at(7));
				for(uint m =7;buttonLabel.at(m)!='-';m++){
							toIntStart+=buttonLabel.at(m);
					}
					printf("toIntStart Final: %s\n",toIntStart.c_str());
						
					for(uint n=buttonLabel.find_first_of("E")+4;n<buttonLabel.size();n++){
						toIntEnd+=buttonLabel.at(n);
					}
					printf("toIntEnd Final: %s\n",toIntEnd.c_str());
					SkipTime newSkip;
					newSkip.setSkipStart(to_int(toIntStart));
					newSkip.setSkipStop(to_int(toIntEnd));
					printf("Adding [%ld - %ld] to skipTimes\n",newSkip.getSkipStart(),newSkip.getSkipStop());
					skipTimes.push_back(newSkip);
					
			} else {
printf("Checking SkipTimes\n Size: %d\n",skipTimes.size());	
			for(uint m =7;buttonLabel.at(m)!='-'&&buttonLabel.at(0)=='S';m++){
				toIntStart+=buttonLabel.at(m);
			}
			printf("toIntStart Final: %s\n",toIntStart.c_str());
			
			for(uint k=0;k<skipTimes.size();k++){
				if(!skipTimesContains(to_string(skipTimes.at(k).getSkipStart()))){
				//if(!skipTimesContains(toIntStart)){
					it2 = skipTimes.begin() +k;
//printf("buttonLabel at 6: %c at 7: %c\n",buttonLabel.at(6),buttonLabel.at(7));
					
						
					for(uint n=buttonLabel.find_first_of("E")+4;n<buttonLabel.size();n++){
						toIntEnd+=buttonLabel.at(n);
					}
					printf("toIntEnd Final: %s\n",toIntEnd.c_str());
					
					//~ SkipTime newSkip;
					//~ //it2 = skipTimes.begin() + i;
					//~ newSkip.setSkipStart(to_int(toIntStart));
					//~ newSkip.setSkipStop(to_int(toIntEnd));
					//~ printf("Adding [%ld - %ld] to skipTimes\n",newSkip.getSkipStart(),newSkip.getSkipStop());
					//~ skipTimes.insert(it2+1,newSkip);
					
			
					SkipTime newSkip;
					//it2 = skipTimes.begin() + i;
					newSkip.setSkipStart(to_int(toIntStart));
					newSkip.setSkipStop(to_int(toIntEnd));
					printf("Adding [%ld - %ld] to skipTimes\n",newSkip.getSkipStart(),newSkip.getSkipStop());
					skipTimes.insert(it2+1,newSkip);
				}
			}
		}
		}
	}
	//printf("size of new playlsit: %d\n",libvlc_playlist_items_count(inst,&excp));
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
			bool temp = toCompare==toRemove;
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
	if(toRemove.size()<10){
		return false;
	}
	for(uint m =7;toRemove.at(m)!='E';m++){
		//printf("toRemove at[%d]: %c\n",m,toRemove.at(m));
		if(toRemove.at(m)!='-'){
			toRemoveString += toRemove[m];
			//printf("To remove[%d]: %s\n",m,toIntStart.c_str());
		}
	}
	//printf("toRemoveString Final: %s\n",toRemoveString.c_str());
	
	std::vector<SkipTime>::iterator it;
	for(uint i=0;i<skipTimes.size();i++){
		//printf("SkipTimes[%d]: [%ld - %ld]\n",i,skipTimes.at(i).getSkipStart(),skipTimes.at(i).getSkipStop());		
		std::string toString = to_string(skipTimes.at(i).getSkipStart());
		bool temp = toString.compare(toRemoveString);
		//printf("Skiptimes Start: %s\n",toString.c_str());
		//printf("Found String %d\n",temp);
		if(toString.compare(toRemoveString)){	
			it=skipTimes.begin()+i;			
			skipTimes.erase(it);
			printf("%s removed\n",toRemove.c_str());
			return true;
		}
	}
	return false;
}

bool media_player_dlg::skipChaptersContains(std::string toFind){
	//printf("Checking for %s in SkipChapters\n",toFind.c_str());
	for(uint i=0;i<skipChapters.size();i++){
		if(skipChapters.at(i)==to_int(toFind)){	
			//printf("Found string in SkipChapters\n");
			return true;
		}
	}
	//printf("String not found in SkipChapters\n");
	return false;
}

bool media_player_dlg::skipTimesContains(std::string toFind){
	//printf("Checking for '%s' in skipTimes\n",toFind.c_str());
	for(uint i=0;i<skipTimes.size();i++){
		if(skipTimes.at(i).getSkipStart()==to_int(toFind)){	
			//printf("Found string in skipTimes\n");
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
				//printf("Found string in profileSkipChapters\n");
				return true;
			}
		}
	}
	//printf("String not found in SkipChapters\n");
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
