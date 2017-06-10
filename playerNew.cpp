#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <gst/gst.h>
#include <glib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sstream>
#include <gdk-pixbuf/gdk-pixbuf.h>

using namespace std;
	
	GtkWidget *window,*entry, *entry1, *entry2, *entryNameSong,*entryTimeSong,*entryaddressSong,*entryCostSong;
	GMainLoop *loop;
	GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink, *filter;
	GstElement *convert1, *convert2, *resample;
	GstStateChangeReturn ret;
  	GstBus *bus;
	static int entry_num,timeSong,costSong;
	static string name = "",password,nameSong,kindSong,addressSong,state;
	fstream File;
    static vector<string> names(0);
    static vector<string> passwords(0);
    static vector<double> bankAcount(0);
    vector<string> nameMusicUser(0);
    vector<string> namePop(0);
    vector<string> nameClassic(0);
    vector<string> nameOthers(0);
    static int whichOne = 0;
	char argv[2][1000];
	bool played = false,customer = false;
class Player
{
public:
    Player();
    ~Player();
    static void Salesperson();
    static void Customer();
    static void Register();
    static void Login();
    bool CheckExistOfNames();
    void play();
    void ShowListOfSongs();
    static int Playingogg(GtkWidget* ,char*);
    static int PlayingMp3(GtkWidget *,char*);
    bool ErrOfRegister();
    bool ErrOfLogin();
    static void listenMusic();
    static void rmMusic();
    int media_window();
    int entry_window();
    int msg(string, string);
    int msg_ask(string);
    static int window_register_option();
    static int window_Login_option();
    static void yes() { entry_num = 1; gtk_widget_destroy(window);}
    static void no() { entry_num = 2;	gtk_widget_destroy(window);}
    static int show_question(string);
    int window_kind_name_time_address_music();
    static void Pause() { state = "Pause"; }
    static void Stop() { state = "Stop"; }
	
};
//______________________________________ entry_window  ________________________________________

static void enter_callback_name_password( GtkWidget *widget)
{
	name = (char*)gtk_entry_get_text (GTK_ENTRY (entry1));
	password = (char*)gtk_entry_get_text (GTK_ENTRY (entry2));
}

static void entry_toggle_visibility( GtkWidget *checkbutton )
{
	gtk_entry_set_visibility (GTK_ENTRY (entry2),GTK_TOGGLE_BUTTON (checkbutton)->active);
}

int Player::entry_window()
{
	GtkWidget *vbox, *hbox;					
	GtkWidget *button1,*button2, *button3;
	GtkWidget *check;					
	GtkWidget *fixed;

	gtk_init (NULL, NULL);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request (GTK_WIDGET (window), 420, 200);
	gtk_window_set_title (GTK_WINDOW (window), "   Entry  ");
	g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	entry1 = gtk_entry_new ();
	entry2 = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry1), 20);
	gtk_entry_set_max_length (GTK_ENTRY (entry2), 20);

	gtk_entry_set_text (GTK_ENTRY (entry1), "enter your name");
	gtk_entry_set_text (GTK_ENTRY (entry2), "enter your password");
	gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (vbox), hbox);
		                          
	check = gtk_check_button_new_with_label ("visible password");
	gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
	g_signal_connect (check, "toggled", G_CALLBACK (entry_toggle_visibility), entry2);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
		                               
	fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(vbox),fixed,TRUE,TRUE,0);

	button1 = gtk_button_new_with_label("Register");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 140, 40);
	gtk_widget_set_size_request(button1, 120, 35);

	button2 = gtk_button_new_with_label("Login");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 7, 40);
	gtk_widget_set_size_request(button2, 120, 35);

	button3 = gtk_button_new_with_label("Quit");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 273, 40);
	gtk_widget_set_size_request(button3, 120, 35);

	g_signal_connect (G_OBJECT(button1), "clicked", G_CALLBACK(Register), NULL);
	g_signal_connect (G_OBJECT(button2), "clicked", G_CALLBACK(Login),NULL);
	g_signal_connect (G_OBJECT(button3), "clicked",G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
//___________________________  kinds of msg dialog ______________________________
//__________________________ window_register_option _____________________________

int Player::window_register_option()
{
	gtk_widget_destroy(window);// destroy befor window
	GtkWidget *fixed;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *label;
	GtkWidget *hseparator;
	GtkWidget *vbox;

	gtk_init(NULL, NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Options :");
	gtk_window_set_default_size(GTK_WINDOW(window),300, 60);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();

	label = gtk_label_new("what do you want to do ? ");

	vbox = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hseparator = gtk_hseparator_new();

	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, TRUE, 0);

	gtk_container_set_border_width(GTK_CONTAINER(window), 30);

	button1 = gtk_button_new_with_label("buying music");
	gtk_fixed_put(GTK_FIXED(fixed), button1,10, 20);
	gtk_widget_set_size_request(button1, 120, 35);

	button2 = gtk_button_new_with_label("selling music");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 160, 20);
	gtk_widget_set_size_request(button2, 120, 35);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Customer), NULL);

	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(Salesperson),NULL);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}

//_____________________________ window_kind_name_time_address_music()  ___________________

static void Pop()
{ 
	Player p;
	kindSong = "Pop"; 
	p.ShowListOfSongs();
}
static void Classic() 
{
	Player p;
	kindSong = "Classic";
	p.ShowListOfSongs();
}
static void Others() 
{
	Player p;
	kindSong = "Others"; 
	p.ShowListOfSongs(); 
}
static void entry_callback_song()
{
	nameSong = (char*)gtk_entry_get_text (GTK_ENTRY (entryNameSong));
	timeSong = atoi((char*)gtk_entry_get_text (GTK_ENTRY (entryTimeSong)));
	addressSong = (char*)gtk_entry_get_text (GTK_ENTRY (entryaddressSong));
	costSong = atoi((char*)gtk_entry_get_text (GTK_ENTRY (entryCostSong)));
}

int Player::window_kind_name_time_address_music()
{
	GtkWidget *button;
	GtkWidget *check1,*check2,*check3;
	GtkWidget *label1,*label2,*label3,*label4,*label5;
	GtkWidget *vbox,*hbox;

	gtk_init(NULL, NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"some questions:");
	gtk_window_set_default_size(GTK_WINDOW(window), 400,600);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	label1 = gtk_label_new("Enter the kind of song ? ");
	label2 = gtk_label_new("Enter the name of song ?");
	label3 = gtk_label_new("(for customer):\nHow much of song would you like to listen ?");
	label4 = gtk_label_new("(for salesperson):\nEnter the address of song ?");
	label5 = gtk_label_new("(for salesperson):\nEnter the cost of song ?");
	
	entryNameSong = gtk_entry_new();
	entryTimeSong = gtk_entry_new();
	entryaddressSong = gtk_entry_new();
	entryCostSong = gtk_entry_new();
	
	vbox = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	hbox = gtk_hbox_new(TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
	
	check1 = gtk_check_button_new_with_label ("POP");
	gtk_box_pack_start (GTK_BOX (hbox), check1, TRUE, TRUE, 0);
	g_signal_connect (check1, "toggled", G_CALLBACK (Pop), NULL);
	
	check2 = gtk_check_button_new_with_label ("CLASSIC");
	gtk_box_pack_start (GTK_BOX (hbox), check2, TRUE, TRUE, 0);
	g_signal_connect (check2, "toggled", G_CALLBACK (Classic), NULL);
	
	check3 = gtk_check_button_new_with_label ("OTHERS");
	gtk_box_pack_start (GTK_BOX (hbox), check3, TRUE, TRUE, 0);
	g_signal_connect (check3, "toggled", G_CALLBACK (Others), NULL);

	gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, TRUE, 0);	
	gtk_box_pack_start (GTK_BOX (vbox), entryNameSong, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, TRUE, 0);	
	gtk_box_pack_start (GTK_BOX (vbox), entryTimeSong, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox), label4, FALSE, TRUE, 0);	
	gtk_box_pack_start (GTK_BOX (vbox), entryaddressSong, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox), label5, FALSE, TRUE, 0);	
	gtk_box_pack_start (GTK_BOX (vbox), entryCostSong, TRUE, TRUE, 0);
	
	button = gtk_button_new_with_label("Apply");
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, TRUE, 0);
	gtk_widget_set_size_request(button, 120, 35);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(entry_callback_song), NULL);
	g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

//___________________________________ window_Login_option ______________________________

int Player::window_Login_option()
{
	gtk_widget_destroy(window);
	gtk_main_quit();
	
	GtkWidget *fixed;
	GtkWidget *button1,*button2,*button3,*button4;
	GtkWidget *label;
	GtkWidget *hseparator;
	GtkWidget *vbox;


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Options :");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();

	label = gtk_label_new("what do you want to do ? ");

	vbox = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hseparator = gtk_hseparator_new();

	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, TRUE, 10);

	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, TRUE, 0);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	button1 = gtk_button_new_with_label("buying music");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 10, 20);
	gtk_widget_set_size_request(button1, 120, 35);

	button2 = gtk_button_new_with_label("selling music");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 160, 20);
	gtk_widget_set_size_request(button2, 120, 35);

	button3 = gtk_button_new_with_label("removing music");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 10, 56);
	gtk_widget_set_size_request(button3, 120, 35);

	button4 = gtk_button_new_with_label("listening music");
	gtk_fixed_put(GTK_FIXED(fixed), button4, 160, 56);
	gtk_widget_set_size_request(button4, 120, 35);

	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Customer), NULL);
	  
	g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(Salesperson),NULL);
		
	g_signal_connect(G_OBJECT(button3), "clicked",G_CALLBACK(rmMusic),NULL);
		
	g_signal_connect(G_OBJECT(button4), "clicked",G_CALLBACK(listenMusic),NULL);
	  
	g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}

//_________________________________ msg_ask  ____________________________

static void entry_callback()
{
	nameSong = (char*)gtk_entry_get_text (GTK_ENTRY (entry));
	timeSong = atoi((char*)gtk_entry_get_text (GTK_ENTRY (entry)));
}

int Player::msg_ask(string messege)
{
	gtk_widget_destroy(window);
	GtkWidget *window; 
	GtkWidget *vbox, *hbox;
	GtkWidget *button;

	gtk_init (NULL, NULL);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (GTK_WIDGET (window), 400, 150);
	gtk_window_set_title (GTK_WINDOW (window), "Entry Msg :");
	g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	entry = gtk_entry_new ();
	gtk_widget_set_size_request (GTK_WIDGET (entry), 400, 50);

	gtk_entry_set_text (GTK_ENTRY (entry), messege.c_str());
	gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (vbox), hbox);
		                      
	button = gtk_button_new_with_label("Apply");

	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(entry_callback),NULL);
	g_signal_connect_swapped (button, "clicked",G_CALLBACK (gtk_widget_destroy), window);

	gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

	gtk_widget_set_size_request (GTK_WIDGET (button), 200, 30);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	gtk_widget_show_all (window);

	gtk_main();

	return 0;
}

//_____________________________  msg just show _________________________________

int Player::msg(string title, string messege)
{
	GtkWidget *fixed;
	GtkWidget *button;
	GtkWidget *table;
	GtkWidget *frame;
	GtkWidget *label;

	gtk_init(NULL,NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Msg :");

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);  
		
	table = gtk_table_new(2, 2, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 10);
	gtk_table_set_col_spacings(GTK_TABLE(table), 10);
	gtk_fixed_put(GTK_FIXED(fixed),table,25,20);

	button = gtk_button_new_with_label("OK");

	gtk_widget_set_size_request(button, 85, 35);
	gtk_fixed_put(GTK_FIXED(fixed), button, 200, 200);

	frame = gtk_frame_new(title.c_str());
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);

	gtk_table_attach_defaults(GTK_TABLE(table), frame, 0, 2, 0, 2);

	label = gtk_label_new(messege.c_str());

	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_container_add(GTK_CONTAINER(frame), label);
	
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

//_______________________________ other msg   ________________________________________________

void show_err(string err)
{
	GtkWidget *dialog;
	//(GtkWindow *parent,GtkDialogFlags flags,GtkMessageType type,GtkButtonsType buttons,const gchar *message_format,...)
	dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,(gchar*)err.c_str());
	gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
}

int Player::show_question(string ask)
{
	gtk_widget_destroy(window);
	
	GtkWidget *fixed;
	GtkWidget *button1, *button2;
	GtkWidget *label;
	GtkWidget *hseparator;
	GtkWidget *vbox;

	gtk_init(NULL, NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Question :");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 75);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();

	label = gtk_label_new(ask.c_str());

	vbox = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hseparator = gtk_hseparator_new();

	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, TRUE, 10);

	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, TRUE, 0);

	gtk_container_set_border_width(GTK_CONTAINER(window), 5);

	button1 = gtk_button_new_with_label("YES");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 150, 15);
	gtk_widget_set_size_request(button1, 80, 35);

	button2 = gtk_button_new_with_label("NO");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 55, 15);
	gtk_widget_set_size_request(button2, 80, 35);

	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(yes), NULL);
	  
	g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(no),NULL);
	  
	g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}

//_________________________________  exit msg  ______________________________________

//_________________________________   media window _________________________________

GdkPixbuf *load_pixbuf_from_file (const char *filename)
{
	GError *error = NULL;
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (filename, &error);//(const char *filename,GError **error:Return location for an error)

	if (pixbuf == NULL)
	{
		g_print ("Error loading file: %d : %s\n", error->code, error->message);
		g_error_free (error);
		exit (1);
	}
	return pixbuf;
}

int Player::media_window()
{
	GdkPixbuf *image;
	GdkPixmap *background;
	GtkStyle *style;
	GtkWidget *vbox;
	GtkWidget *button1,*button2,*button3,*button4,*button5;

	gtk_init (NULL,NULL);
	image = load_pixbuf_from_file ("/home/sepideh/Desktop/green.jpg");
	gdk_pixbuf_render_pixmap_and_mask (image, &background, NULL, 0);//(GdkPixbuf *pixbuf,GdkPixmap **pixmap_return:Location to store a pointer to the created pixmap, ,GdkBitmap 				**mask_return:Location to store a pointer to the created mask ,int alpha_threshold:Threshold value for opacity values.)
	style = gtk_style_new ();
	style->bg_pixmap [0] = background;/*style "tooltip"{bg_pixmap[NORMAL], bg_pixmap[PRELIGHT] ,bg_pixmap[ACTIVE],bg_pixmap[INSENSITIVE]="<none>"}  assigns an image to the background of 		the widget,*/
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Media Player");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
	gtk_widget_set_style (GTK_WIDGET(window), GTK_STYLE (style));
	gtk_window_set_transient_for (GTK_WINDOW (window), NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	vbox = gtk_vbox_new (0, FALSE);
	gtk_container_add (GTK_CONTAINER(window), vbox);

	button1 = gtk_button_new_with_label ("PLAY OGG");
	button2 = gtk_button_new_with_label ("PLAY MP3");
	button3 = gtk_button_new_with_label ("STOP");
	button4 = gtk_button_new_with_label ("PAUSE");
	button5 = gtk_button_new_with_label ("CLOSE");
	gtk_box_pack_end (GTK_BOX (vbox), button5, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (vbox), button4, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (vbox), button3, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (vbox), button2, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (vbox), button1, FALSE, FALSE, 0);

	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Playingogg),argv[1]);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(PlayingMp3),argv[1]);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(Stop), NULL);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(Pause),NULL);
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	  
	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}

//____________________________________  playing the song  _________________________________

static gboolean cb_print_position (GstElement *pipeline)
{
	gint64 pos, len;
	GstFormat fmt = GST_FORMAT_TIME;
	char *rev = (char*)fmt;
	if (gst_element_query_position (pipeline, &fmt, &pos) && gst_element_query_duration (pipeline, &fmt, &len))//(GstElement *element,GstFormat *format,gint64 *cur)
	{
		if(state=="Pause")	gst_element_set_state (pipeline, GST_STATE_PAUSED);
		if(state=="Play")	gst_element_set_state (pipeline, GST_STATE_PLAYING);
		if(state=="Stop" || pos > timeSong*1e9L) {
			gst_element_set_state (pipeline, GST_STATE_NULL);
			played = false;g_main_loop_quit(loop);return FALSE;
		}
	
		g_print ("Time: %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
		GST_TIME_ARGS (pos), GST_TIME_ARGS (len));
	}
	return TRUE;
}


static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
	GMainLoop *loop = (GMainLoop *) data;

	switch(GST_MESSAGE_TYPE(msg))
	{
		case GST_MESSAGE_EOS:
		{
			g_print ("End of stream\n");
			g_main_loop_quit (loop);
			break;
		}
		case GST_MESSAGE_ERROR: 
		{
			gchar  *debug;
			GError *error;

			gst_message_parse_error (msg, &error, &debug);
			g_free (debug);

			g_printerr ("Error: %s\n", error->message);
			g_error_free (error);

			g_main_loop_quit (loop);
			break;
		}
		default:
			break;
	}
	return TRUE;
}

static void on_pad_added (GstElement *element, GstPad *pad, gpointer data)
{
	GstPad *sinkpad;
	GstElement *decoder = (GstElement *) data;

	g_print ("Dynamic pad created, linking demuxer/decoder\n");

	sinkpad = gst_element_get_static_pad (decoder, "sink");

	gst_pad_link (pad, sinkpad);

	gst_object_unref (sinkpad);
}

 //__________________________________ main playing ogg song  _____________________________
 
int Player::Playingogg(GtkWidget *widget,char* argv)		
{
	state = "Play";
	
	if(played)	return 0;
	
	gst_init (NULL, NULL);// initial gst lib

	loop = g_main_loop_new (NULL, FALSE);

	/* Create gstreamer elements */
	pipeline = gst_pipeline_new ("audio-player");
	source   = gst_element_factory_make ("filesrc",       "file-source");
	demuxer  = gst_element_factory_make ("oggdemux",      "ogg-demuxer");
	decoder  = gst_element_factory_make ("vorbisdec",     "vorbis-decoder");
	conv     = gst_element_factory_make ("audioconvert",  "converter");
	sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

	if (!pipeline || !source || !demuxer || !decoder || !conv || !sink) 
	{
		g_printerr ("One element could not be created. Exiting.\n");
		return -1;
	}
	g_object_set (G_OBJECT (source), "location", argv, NULL);
	
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);

	gst_bin_add_many (GST_BIN (pipeline),
	source, demuxer, decoder, conv, sink, NULL);

	gst_element_link (source, demuxer);
	gst_element_link_many (decoder, conv, sink, NULL);
	g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);

	g_print ("Now playing: %s\n", argv);
	gst_element_set_state (pipeline, GST_STATE_PLAYING);

	g_print ("Running...\n");
	
	g_timeout_add (200, (GSourceFunc) cb_print_position, pipeline);
	
	played = true;
	
	g_main_loop_run (loop);

	g_print ("Returned, stopping playback\n");
	gst_element_set_state (pipeline, GST_STATE_NULL);

	g_print ("Deleting pipeline\n");
	gst_object_unref (GST_OBJECT (pipeline));

	return 0;
}

//_____________________________________ main playing mp3 song ________________________________________

int Player::PlayingMp3 (GtkWidget *widget,char* argv)
{
	state = "Play";

	if(played)	return 0;
	
	gst_init (NULL,NULL);
	loop = g_main_loop_new (NULL, FALSE);
	
	pipeline = gst_pipeline_new ("mp3 player");
	source = gst_element_factory_make ("filesrc", "file reader");
	filter = gst_element_factory_make ("mad", "MP3 decoder");
	sink = gst_element_factory_make ("alsasink", "ALSA output");
	
	g_object_set (G_OBJECT (source), "location", argv, NULL);
	
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);
	
  if (!filter) {
		g_print ("the reason why it is not being loaded.");
		return -1;
	}

	gst_bin_add_many (GST_BIN (pipeline), source, filter,sink, NULL);
	gst_element_link_many(source,filter,sink,NULL);

	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	
	g_timeout_add (200, (GSourceFunc) cb_print_position, pipeline);
	
	played = true;
	
	g_main_loop_run (loop);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT(pipeline));

	return 0;
}
//________________________________________  exit playing song ______________________________________

//_______________________________________        others       ______________________________________

string itostr(int x)
{
	stringstream s;
	s << x;
	return s.str();
}
bool exist(vector<string> vec, string str)
{
	for(int i=0 ; i<vec.size() ; i++)
		if(str == vec[i])	return true;
	return false;
}
Player::Player()
{
	if(name!="")
	{
		File.open(name.c_str(),ios::in);
		while(!File.eof())
		{
		    string rev;
		    File >> rev;
		    if(rev!="" && !exist(nameMusicUser,rev))	nameMusicUser.push_back(rev);
		}
		File.close();
    }
    
    File.open("doc.txt",ios::in);
    while(!File.eof())
    {
        string rev1,rev2,rev3;
        File >> rev1 >> rev2 >> rev3;
        if(rev1!="" && !exist(names,rev1))	{ 
        	names.push_back(rev1); passwords.push_back(rev2); 
        	bankAcount.push_back(atoi(rev3.c_str())); 
        }
    }
    File.close();
    
    File.open("namePop.txt",ios::in);
    while(!File.eof())
    {
    	string ret;
    	File >> ret;
    	if(ret!="" && !exist(namePop,ret))	namePop.push_back(ret);
    }
    File.close();
    
    File.open("nameClassic.txt",ios::in);
    while(!File.eof())
    {
    	string ret;
    	File >> ret;
    	if(ret!="" && !exist(nameClassic,ret))	nameClassic.push_back(ret);
    }
    File.close();
    
    File.open("nameOthers.txt",ios::in);
    while(!File.eof())
    {
    	string ret;
    	File >> ret;
    	if(ret!="" && !exist(nameOthers,ret))	nameOthers.push_back(ret);
    }
    File.close();
}
Player::~Player()
{
	File.close();
	File.open(name.c_str(),ios::out);
    for(int i=0 ; i<nameMusicUser.size() ; i++)
        File << nameMusicUser[i] <<endl;
    File.close();
    
	File.close();
	File.open("doc.txt",ios::out);
    for(int i=0 ; i<names.size() ; i++)
        File << names[i] <<' '<< passwords[i]<<' '<< bankAcount[i]<<endl;
    File.close();
    
    File.close();
	File.open("nameClassic.txt",ios::out);
    for(int i=0 ; i<nameClassic.size() ; i++)
        File << nameClassic[i]<<endl;
    File.close();
    
    File.close();
	File.open("namePop.txt",ios::out);
    for(int i=0 ; i<namePop.size() ; i++)
        File << namePop[i]<<endl;
    File.close();
    
    File.close();
	File.open("nameOthers.txt",ios::out);
    for(int i=0 ; i<nameOthers.size() ; i++)
        File << nameOthers[i]<<endl;
    File.close();
}
void Player::Register()
{
	enter_callback_name_password(NULL);
	Player p;
    while(p.ErrOfRegister()) {
		gtk_widget_destroy(window);
		p.entry_window();
    }

    names.push_back(name);
    passwords.push_back(password);
    bankAcount.push_back(10);
    whichOne = names.size()-1;
    
    File.close();
	File.open("doc.txt",ios::app);
    File << name << ' '<< password << ' '<< 10 <<endl;
    File.close();
    
    system(("cp /home/sepideh/Desktop/Desktop/project/New  /home/sepideh/Desktop/Desktop/project/"+name).c_str());
    
   	window_register_option();
}
void Player::Login()
{
	enter_callback_name_password(NULL);
	Player p;
    while(p.ErrOfLogin()) { 
    	gtk_widget_destroy(window);
    	gtk_main_quit();p.entry_window(); 
    }
    
    window_Login_option();
}
bool Player::ErrOfRegister()
{
    for(int i=0 ; i<names.size() ; i++)
        if(names[i]==name)
        {
            show_err("your entered name was existed, try again.");
            return true;
        }
    return false;
}
bool Player::ErrOfLogin()
{
    bool exist = false;
    for(int i=0 ; i<names.size() ; i++)
        if(names[i]==name)
        {
            if(passwords[i]==password)	{ whichOne = i;return false; }
            exist = true;
            if(passwords[i]!=password)	{ show_err("you entered a wrong password, try again.");return true; }
        }
    if(!exist) { show_err("you entered a wrong name, try again.");return true; }
    return false;
}

void Player::ShowListOfSongs()
{
	if(!customer)	return;
	string messege = "\n",title;
	if(kindSong=="Pop")
	{
		title = "list of pop songs :";
		for(int i=0 ; i<namePop.size() ; i++)
			messege+=(namePop[i] +"\n");
	}
	else if(kindSong=="Classic")
	{		
		messege+=("list of classic songs : \n");
		for(int i=0 ; i<nameClassic.size() ; i++)
			messege+=(nameClassic[i] +"\n");
	}
	else
	{
		messege+=("list of others songs : \n");
		for(int i=0 ; i<nameOthers.size() ; i++)
			messege+=(nameOthers[i] +"\n");
	}
	msg(title, messege);
}
void Player::play()
{
    window_kind_name_time_address_music();
    
    string rev = "/home/sepideh/Desktop/Desktop/project/"+kindSong+"/"+nameSong;
    strcpy(argv[0],nameSong.c_str());
    strcpy(argv[1],rev.c_str());

   	media_window();
}
void Player::Customer()
{
	customer = true;
	gtk_widget_destroy(window);
	gtk_main_quit();
	
	Player p;p.play();
	
    show_question("Would you like the song ?");
    if(entry_num==1)
    {
        if(bankAcount[whichOne]>=2)
        {
            p.msg("information :\n","\n\ntwo dolar were taken from your bank acount .");
            bankAcount[whichOne] -= 2;
            
			nameMusicUser.push_back(kindSong); nameMusicUser.push_back(nameSong);
        }
        else
            show_err("you don't have enough money .");
    }
    else
    {
        while(entry_num==2)
        {
            show_question("whould you like try another song ?");
            if(entry_num==2)  { return; gtk_main_quit(); }
            
            p.play();
           	show_question("Would you like the song ?");
            if(entry_num==1)
			{
				if(bankAcount[whichOne]>=2)
				{
					p.msg("information :","\n\ntwo dolar were taken from your bank acount .");
					bankAcount[whichOne] -= 2;
					
					nameMusicUser.push_back(kindSong); nameMusicUser.push_back(nameSong);
				}
				else
					show_err("you don't have enough money .");
			}
        }
    }
}
void Player::Salesperson()
{
	gtk_main_quit();
	Player p;
	
	p.window_kind_name_time_address_music();
	
    p.msg("information :","\n\n"+itostr(costSong) +" $ is added in your bank acount .");
    bankAcount[whichOne] += entry_num;
    
    if(kindSong=="Pop")	namePop.push_back(nameSong);	else if(kindSong=="Classic")	nameClassic.push_back(nameSong);	else	nameOthers.push_back(nameSong);
    
    system(("cp "+addressSong+"  /home/sepideh/Desktop/Desktop/project/"+kindSong+"/"+nameSong).c_str());
}

void Player::listenMusic()
{
	gtk_main_quit();
	Player p;
	int idx;
	if(nameMusicUser.size()==0)	{ show_err("you don't have any music.");return; }
	
	string messege = "\n", title;
	title = "list of your music :";
	for(int i=1 ; i<nameMusicUser.size() ; i+=2)
		messege += nameMusicUser[i]+"\n";
	p.msg(title, messege);	
	
	p.msg_ask("which one you want to listen ?");
	
	for(int i=1 ; i<nameMusicUser.size() ; i+=2)
		if(nameMusicUser[i]==nameSong)	idx = i-1;
	
    string rev = "/home/sepideh/Desktop/Desktop/project/"+nameMusicUser[idx]+"/"+nameSong;
    strcpy(argv[0],nameSong.c_str());
    strcpy(argv[1],rev.c_str());
    
    p.msg_ask("How much of song would you like to listen ?");
    p.media_window();
}
void Player::rmMusic()
{
	gtk_main_quit();
	Player p;
	int idx;
	if(nameMusicUser.size()==0)	{ show_err("you don't have any music.");return; }
	
	string messege = "\n",title;
	title = "list of your music :";
	for(int i=1 ; i<nameMusicUser.size() ; i+=2)
		messege += nameMusicUser[i]+"\n";
	p.msg(title, messege);	
	
	p.msg_ask("which one do you want to remove ?");
	
	for(int i=1 ; i<nameMusicUser.size() ; i+=2)
		if(nameMusicUser[i]==nameSong)	idx = i;
		
	nameMusicUser.erase(nameMusicUser.begin()+idx);
	nameMusicUser.erase(nameMusicUser.begin()+idx-1);
	    
    bankAcount[whichOne] += 1.4;
    p.msg("information :", "\n\n"+nameSong +" was deleted and 70% of the money has returned to your bank acount. \n your bank acount now is : "+itostr(bankAcount[whichOne]));
}
int main()
{
	Player P;
	P.entry_window();
}
