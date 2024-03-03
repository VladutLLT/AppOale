#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <xlsxwriter.h>
#include <time.h>

	//OALE GLOBAL PARAMETERS
	int nr_oale=0;
	struct oala* oale;
	int sarj_init[30];
	
	//MAIN TAB WIDGETS
	GtkBuilder *main_builder;
    GtkWidget *Main_window;
    GtkWidget *Main_fixed;
    GtkWidget *Info_label;
    GtkWidget *Main_textview;
    GtkWidget *Nume_label;
    GtkWidget *Nrsarje_label;
    GtkWidget *Observ_label;
    GtkWidget *Nume_entry;
    GtkWidget *Nrsarje_entry;
    GtkWidget *Observ_entry;
    GtkWidget *Mtextviewinfo_label;
    GtkWidget *MColumn1;
    GtkWidget *MColumn2;
    GtkWidget *MColumn3;
    GtkWidget *Input_button;
    GtkWidget *Organize_button;
    GtkWidget *Map_button;
    GtkWidget *Nrsapt_entry;
    GtkWidget *Nrsapt_label;
    GtkWidget *Clear_button;
    GtkWidget *Main_textview_scrolledwindow;
    
    //ORGANIZE TAB WIDGETS
    GtkWidget *Second_window;
	GtkWidget *Second_fixed;
	GtkWidget *Second_textview;
	GtkWidget *Info2_label;
	GtkWidget *SColumn1;
	GtkWidget *SColumn2;
	GtkWidget *SColumn3;
	GtkWidget *Second_textview_scrolledwindow;
    
    // MAP TAB WIDGETS
	GtkWidget *Map_window;
	GtkWidget *Map_fixed;
	GtkWidget *Nrsapt_entry;
	GtkWidget *Nrsapt_label;
	GtkWidget *Crtexcel_button;
	GtkWidget *Crtmap_button;
	GtkWidget *Harta_textview;
	GtkWidget *Harta_scrolledwindow;
	GtkWidget *Pred_scrolledwindow;
	GtkWidget *Pred_textview;
	GtkWidget *Nroalefol_entry;
	GtkWidget *Data_entry;
	GtkWidget *Nroalefol_label;
	GtkWidget *Data_label;
	GtkWidget *Pred_label;
	GtkWidget *Harta_label;

//OALE STRUCT AND FUNCTIONS

struct oala
{
	char* nume;
	int sarje;
	char* obsv;
};
void incarcare_vector(struct oala* oale, int pozitie, char* nume_text, char* sarje_text, char* obsv_text)
{
		int v;
		oale[pozitie].nume=(char*)malloc(20*sizeof(char));
		oale[pozitie].obsv=(char*)malloc(100*sizeof(char));
		strcpy(oale[pozitie].nume, nume_text);
		strcpy(oale[pozitie].obsv, obsv_text);
		oale[pozitie].sarje=atoi(sarje_text);
}
void afisare_vector(struct oala* oale, int nr_oale)
{
	for(int i=0;i<nr_oale;i++)
	{
		printf("%s %d ", oale[i].nume, oale[i].sarje);
	}

}
void ordonare_dupa_nr_sarje(struct oala* oale, int nr_oale)
{
	struct oala placeholder;
	
	for(int i=0;i<nr_oale;i++)
		for(int j=0;j<nr_oale-i-1;j++)
		{
			if(oale[j].sarje<oale[j+1].sarje)
			{
				placeholder=oale[j];
				oale[j]=oale[j+1];
				oale[j+1]=placeholder;
			}
		}
	
}
	void increment()
{
	nr_oale++;
}

	//INCREMENT DATE FUNCTION
char *incrementDate(const char *inputDate) {
    char day[3], month[3], year[5];
    sscanf(inputDate, "%2s.%2s.%4s", day, month, year);

    int d = atoi(day);
    int m = atoi(month);
    int y = atoi(year);

    // Check for valid date
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 0) {
    
        return NULL;  // Invalid date
    }

    // Check for end of month
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) {
        daysInMonth[2] = 29;  // Leap year
    }

    if (d == daysInMonth[m]) {
        d = 1;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    } else {
        d++;
    }

    // Create and format the incremented date
    char *resultDate = g_strdup_printf("%02d.%02d.%04d", d, m, y);

    return resultDate;
}


	//INPUT BUTTON CLICK IN MAIN TAB + ORGANIZE BUTTON ACTIVATION
void on_Input_button_clicked(GtkWidget *widget, gpointer data) {
    GtkTextView *textview = GTK_TEXT_VIEW(data);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	
	
	
    gchar *Nume_entry_text = gtk_entry_get_text(GTK_ENTRY(Nume_entry));
    
    gchar *Nrsarje_entry_text = gtk_entry_get_text(GTK_ENTRY(Nrsarje_entry));
     
	gchar *Observ_entry_text = gtk_entry_get_text(GTK_ENTRY(Observ_entry));
	
	gchar *buff_txt = g_strdup_printf("%s    ////    %s    ////    %s    ////\n", Nume_entry_text, Nrsarje_entry_text, Observ_entry_text);
	
	
	const gchar *entry_text = buff_txt;
    
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, entry_text, -1);
    
    incarcare_vector(oale, nr_oale, Nume_entry_text, Nrsarje_entry_text, Observ_entry_text);
    
    
    strcpy(buff_txt,"");
    
    gtk_entry_set_text(GTK_ENTRY(Nume_entry), "");
    gtk_entry_set_text(GTK_ENTRY(Nrsarje_entry), "");
    gtk_entry_set_text(GTK_ENTRY(Observ_entry), "");
    
    
	g_free(buff_txt);
    increment();
    
    gtk_widget_set_sensitive(Organize_button, TRUE);
    gtk_widget_set_sensitive(Map_button, TRUE);
    
}

	//ORGANIZE BUTTON CLICK IN MAIN TAB + ORGANIZE TAB ACTIVATION
void on_Organize_button_clicked(GtkWidget *widget, gpointer data) {
	ordonare_dupa_nr_sarje(oale, nr_oale);
	GtkBuilder *second_builder = gtk_builder_new_from_file("SecondWindow.glade");
	
	
	Second_window = GTK_WIDGET(gtk_builder_get_object(second_builder, "Second_window"));
	Second_textview = GTK_WIDGET(gtk_builder_get_object(second_builder, "Second_textview"));
	Second_textview_scrolledwindow = GTK_WIDGET(gtk_builder_get_object(second_builder, "Second_textview_scrolledwindow"));
	Second_fixed= GTK_WIDGET(gtk_builder_get_object(second_builder, "Second_fixed"));
	Info2_label= GTK_WIDGET(gtk_builder_get_object(second_builder, "Info2_label"));
	SColumn1= GTK_WIDGET(gtk_builder_get_object(second_builder, "SColumn1"));
	SColumn2= GTK_WIDGET(gtk_builder_get_object(second_builder, "SColumn2"));
	SColumn3= GTK_WIDGET(gtk_builder_get_object(second_builder, "SColumn3"));
	
	
	
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Second_textview));
    
    gchar* buff_txt;
    
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    for(int i=0;i<nr_oale;i++)
    {
    	buff_txt= g_strdup_printf("%s    ////    %d    ////    %s    ////\n", oale[i].nume, oale[i].sarje, oale[i].obsv);
    	const gchar* entry_text=buff_txt;
    	gtk_text_buffer_insert(buffer, &end, entry_text, -1);
	}
	
	
	gtk_widget_show_all(Second_window);
	
	g_object_unref(second_builder);
}

	//CLEAR BUTTON CLICK IN MAIN TAB
void on_Clear_button_clicked(GtkWidget *widget, gpointer data)
{
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Main_textview));
    gtk_text_buffer_set_text(buffer, "", -1);
    nr_oale=0;
    gtk_widget_set_sensitive(Organize_button, FALSE);
    gtk_widget_set_sensitive(Map_button, FALSE);
    
}

	//INPUT BUTTON ACTIVATION
void on_Input_entries_changed(GtkEditable *editable, gpointer data)
{
	GList *entries = (GList *)data;
    GtkWidget *button = g_list_last(entries)->data;

    gboolean all_entries_populated = TRUE;

   for (GList *node = entries; node != NULL; node = node->next) {
        if (node->data == button) {
            continue; // Skip the button
        }
        
        GtkWidget *entry = GTK_WIDGET(node->data);
        const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
        
        if (entry_text == NULL || entry_text[0] == '\0') {
            all_entries_populated = FALSE;
            break;
        }
    }

    gtk_widget_set_sensitive(button, all_entries_populated);
}

	//CRTEXCEL BUTTON CLICK IN MAP TAB
void on_Crtexcel_button_clicked(GtkWidget *widget, gpointer data)
{
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Harta_textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
	
	lxw_workbook *workbook = workbook_new("~Harta.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
	
	gchar **lines = g_strsplit(text, "\n", -1);
    int row = 0;

    for (int i = 0; lines[i]; i++) {
        gchar **tokens = g_strsplit(lines[i], ":", -1);
        if (tokens[0] && tokens[1]) {
            gchar **date_tokens = g_strsplit(tokens[0], " ", -1);
            if (date_tokens[0]) {
                // Write date in the first column
                worksheet_write_string(worksheet, row, 0, date_tokens[0], NULL);

                // Get the day of the week and write it in the second column
                if (date_tokens[1]) {
                    worksheet_write_string(worksheet, row, 1, date_tokens[1], NULL);
                } else {
                    worksheet_write_blank(worksheet, row, 1, NULL);
                }

                gchar **values_tokens = g_strsplit(tokens[1], " ", -1);
                int col = 2; // Start writing in the third column

                // Write values in separate columns
                for (int j = 0; values_tokens[j]; j++) {
                    worksheet_write_string(worksheet, row, col++, values_tokens[j], NULL);
                }

                row++;
                g_strfreev(values_tokens);
            }
            g_strfreev(date_tokens);
        }
        g_strfreev(tokens);
    }
    
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Pred_textview));
    GtkTextIter start2, end2;
    gtk_text_buffer_get_start_iter(buffer2, &start2);
    gtk_text_buffer_get_end_iter(buffer2, &end2);
    char *text2 = gtk_text_buffer_get_text(buffer2, &start2, &end2, FALSE);
    
    worksheet_set_column(worksheet, 14, 14, 40, NULL);
    for(int i = 0; i<=13; i++)
    worksheet_set_column(worksheet, i, i, 15, NULL);
    
	
	lxw_format *red = workbook_add_format(workbook);
    format_set_bg_color(red, LXW_COLOR_RED);
    
    lxw_format *yellow = workbook_add_format(workbook);
    format_set_bg_color(yellow, LXW_COLOR_YELLOW);
    
    
    // Split the text into lines
    gchar **lines2 = g_strsplit(text2, "\n", -1);
    row = 0;

    for (int i = 0; lines2[i]; i++) {
        // Write each line into the 18th column
        worksheet_write_string(worksheet, row, 14, lines2[i], red);
        row++;
    }
	
	
    // Close the workbook to save the changes
    workbook_close(workbook);
    

    g_free(text);
    
    g_free(text2);
	
	// Confirmation dialog
	GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    
    dialog = gtk_message_dialog_new(GTK_WINDOW(data), flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Aveti grija sa inchideti fisierul ~Harta.xlsx inainte de a apasa acest buton, daca fisierul nu este inchis, acesta nu se va modifica.");
    
    gtk_window_set_title(GTK_WINDOW(dialog), "Informatie");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
    
}

 	// CRTMAP BUTTON CLICK IN MAP_TAB

void on_Crtmap_button_clicked(GtkWidget *widget, gpointer data)
{
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Harta_textview));
	gtk_text_buffer_set_text(buffer, "", -1);
	
	GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Pred_textview));
	gtk_text_buffer_set_text(buffer2, "", -1);
	
	
	const gchar *entrytxt_sapt = gtk_entry_get_text(GTK_ENTRY(Nrsapt_entry));
	const gchar *entrytxt_nro = gtk_entry_get_text(GTK_ENTRY(Nroalefol_entry));
	const gchar *entrytxt_data = gtk_entry_get_text(GTK_ENTRY(Data_entry));
	
	int sapt=atoi(entrytxt_sapt);
	int nro =atoi(entrytxt_nro);
	
	
	//WHEN WRONG DATE INPUT
	char day[3], month[3], year[5];
    sscanf(entrytxt_data, "%2s.%2s.%4s", day, month, year);

    int d = atoi(day);
    int m = atoi(month);
    int ye = atoi(year);
    
    int ok = 0, afk=0;

	if (strlen(entrytxt_data) != 10 || entrytxt_data[2] != '.' || entrytxt_data[5] != '.') {
    	ok = 1;
		} 
		else if (d < 1 || d > 31 || m < 1 || m > 12 || ye < 0) 
			{
   			 ok = 1;
			}
			

if (ok) {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_message_dialog_new(GTK_WINDOW(Map_window), flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "DATA INCEPERE INVALIDA!");
    gtk_window_set_title(GTK_WINDOW(dialog), "GRESEALA!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    afk=1;
		}
    
    
    //Harta textview stuff
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    //Pred textview stuff
    GtkTextIter end2;
    gtk_text_buffer_get_end_iter(buffer2, &end2);
    

    //initializare cu valori initiale
    for(int c=0;c<nr_oale;c++)
    oale[c].sarje=sarj_init[c];
    

	int i=0, zile, j=0, loop_ct=0, y;
	gchar* t_txt, bfr[4];
	char *buff;
	
	if(afk==0)
	for(int x=0;x<sapt;x++)
	{
		zile=0;
		while(zile<7)
		{
		if(i>=nr_oale)
		i=0;
		switch(zile)
		{
			case 0:
			
		    
		    buff = (gchar*)malloc(30* sizeof(gchar));
		    oale[i].sarje++;
		    if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...LUNI: %s \n", entrytxt_data, buff);
			
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 1:
				
		    buff = (gchar*)malloc(30* sizeof(gchar));
		    oale[i].sarje++;
		    if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...MARTI: %s \n", entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 2:
				
			buff = (gchar*)malloc(30* sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...MIERCURI: %s \n",entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 3:
				
			buff = (gchar*)malloc(30* sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...JOI: %s \n", entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 4:
				
		    
			buff = (gchar*)malloc(30* sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...VINERI: %s \n",entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 5:
			
		    	
			buff = (gchar*)malloc(30* sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...SAMBATA: %s \n", entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			
			zile++;
			entrytxt_data=incrementDate(entrytxt_data);
			break;
			
			case 6:
				
			buff = (gchar*)malloc(30* sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
			strcpy(buff, oale[i].nume);
			strcat(buff, "(");
			itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
			strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
		    for(y=1;y<nro;y++)
		    {
		    	
			buff = (gchar*)realloc(buff, (strlen(buff) + strlen(oale[i].nume) + strlen(bfr) + 13) * sizeof(gchar));
			oale[i].sarje++;
			if(oale[i].sarje==170)
			{
				gtk_text_buffer_insert(buffer2, &end2, oale[i].nume, -1);
				gtk_text_buffer_insert(buffer2, &end2, " atinge 170 de sarje in data: ",-1);
				gtk_text_buffer_insert(buffer2, &end2, entrytxt_data, -1);
				gtk_text_buffer_insert(buffer2, &end2, "\n", -1);
			}
		    strcat(buff, oale[i].nume);
		    strcat(buff, "(");
		    itoa(oale[i].sarje, bfr, 10);
			strcat(buff, bfr);
		    strcat(buff, ") ");
			i++;
			if(i>=nr_oale)
			i=0;
			}
			t_txt = g_strdup_printf("%s ...DUMINICA: %s \n\n",entrytxt_data, buff);
			gtk_text_buffer_insert(buffer, &end, t_txt, -1);
			
			free(buff);
			zile++;
			
			entrytxt_data=incrementDate(entrytxt_data);
			break;		
			}
		
		}	
	}
}

	//CRTEXCEL CRTMAP ACTIVATION IN MAP TAB
void on_Map_entries_changed(GtkWidget *widget, gpointer data)
{
	GList *entries = (GList *)data;
    GtkWidget *button1 = g_list_last(entries)->data;
    GtkWidget *button2 = GTK_WIDGET(Crtexcel_button);

    gboolean all_entries_populated = TRUE;

   for (GList *node = entries; node != NULL; node = node->next) {
        if (node->data == button1) {
            continue;
        }
        
        GtkWidget *entry = GTK_WIDGET(node->data);
        const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
        
        if (entry_text == NULL || entry_text[0] == '\0') {
            all_entries_populated = FALSE;
            break;
        }
    }

    gtk_widget_set_sensitive(button1, all_entries_populated);
    gtk_widget_set_sensitive(button2, all_entries_populated);
}

	//MAP BUTTON CLICK IN MAIN TAB + MAP TAB ACTIVATION
void on_Map_button_clicked(GtkWidget *widget, gpointer data)
{
	GtkBuilder *map_builder = gtk_builder_new_from_file("MapWindow.glade");
	
	
	Map_window = GTK_WIDGET(gtk_builder_get_object(map_builder, "Map_window"));
	Map_fixed= GTK_WIDGET(gtk_builder_get_object(map_builder, "Map_fixed"));
	Nrsapt_entry = GTK_WIDGET(gtk_builder_get_object(map_builder, "Nrsapt_entry"));
	Nrsapt_label = GTK_WIDGET(gtk_builder_get_object(map_builder, "Nrsapt_label"));
	Crtexcel_button = GTK_WIDGET(gtk_builder_get_object(map_builder, "Crtexcel_button"));
	Crtmap_button = GTK_WIDGET(gtk_builder_get_object(map_builder, "Crtmap_button"));
	Harta_textview = GTK_WIDGET(gtk_builder_get_object(map_builder, "Harta_textview"));
	Harta_scrolledwindow = GTK_WIDGET(gtk_builder_get_object(map_builder, "Harta_scrolledwindow"));
	Pred_scrolledwindow = GTK_WIDGET(gtk_builder_get_object(map_builder, "Pred_scrolledwindow"));
	Pred_textview = GTK_WIDGET(gtk_builder_get_object(map_builder, "Pred_textview"));
	Nroalefol_entry = GTK_WIDGET(gtk_builder_get_object(map_builder, "Nroalefol_entry"));
	Data_entry = GTK_WIDGET(gtk_builder_get_object(map_builder, "Data_entry"));
	Nroalefol_label = GTK_WIDGET(gtk_builder_get_object(map_builder, "Nroalefol_label"));
	Data_label = GTK_WIDGET(gtk_builder_get_object(map_builder, "Data_label"));
	Pred_label = GTK_WIDGET(gtk_builder_get_object(map_builder, "Pred_label"));
	Harta_label = GTK_WIDGET(gtk_builder_get_object(map_builder, "Harta_label"));
	
	GList *entries = NULL;
    entries = g_list_append(entries, Nrsapt_entry);
    entries = g_list_append(entries, Nroalefol_entry);
    entries = g_list_append(entries, Data_entry);
    entries = g_list_append(entries, Crtmap_button);
    
    
	for (GList *node = entries; node != NULL; node = node->next) {
        GtkWidget *entry = GTK_WIDGET(node->data);
            if (entry != Crtmap_button) {
            g_signal_connect(entry, "changed", G_CALLBACK(on_Map_entries_changed), entries);
        }
        }
	
	
    g_signal_connect(Crtexcel_button, "clicked", G_CALLBACK(on_Crtexcel_button_clicked), NULL);
    
    g_signal_connect(Crtmap_button, "clicked", G_CALLBACK(on_Crtmap_button_clicked), Harta_textview);
    
    //VECTOR SORT ON MAP BUTTON PRESS
    ordonare_dupa_nr_sarje(oale, nr_oale);
    
    for(int c=0;c<nr_oale;c++)
    {
    	sarj_init[c]=oale[c].sarje;
	}
    
   	
	gtk_widget_show_all(Map_window);
	
	g_object_unref(map_builder);
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    oale=(struct oala*)malloc(20*sizeof(struct oala));
    
	main_builder = gtk_builder_new_from_file("MainWindow.glade");

    Main_window = GTK_WIDGET(gtk_builder_get_object(main_builder, "Main_window"));
    
    g_signal_connect(Main_window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    
     
	
	Main_fixed = GTK_WIDGET(gtk_builder_get_object(main_builder, "Main_fixed"));
	Info_label = GTK_WIDGET(gtk_builder_get_object(main_builder, "Info_label"));
	Main_textview = GTK_WIDGET(gtk_builder_get_object(main_builder, "Main_textview"));
	Main_textview_scrolledwindow = GTK_WIDGET(gtk_builder_get_object(main_builder, "Main_textview_scrolledwindow"));
	Nume_label = GTK_WIDGET(gtk_builder_get_object(main_builder, "Nume_label"));
	Nrsarje_label = GTK_WIDGET(gtk_builder_get_object(main_builder, "Nrsarje_label"));
	Observ_label = GTK_WIDGET(gtk_builder_get_object(main_builder, "Observ_label"));
	Nume_entry = GTK_WIDGET(gtk_builder_get_object(main_builder, "Nume_entry"));
	Nrsarje_entry = GTK_WIDGET(gtk_builder_get_object(main_builder, "Nrsarje_entry"));
	Observ_entry = GTK_WIDGET(gtk_builder_get_object(main_builder, "Observ_entry"));
	Mtextviewinfo_label = GTK_WIDGET(gtk_builder_get_object(main_builder, "Mtextviewinfo_label"));
	MColumn1 = GTK_WIDGET(gtk_builder_get_object(main_builder, "MColumn1"));
	MColumn2 = GTK_WIDGET(gtk_builder_get_object(main_builder, "MColumn2"));
	MColumn3 = GTK_WIDGET(gtk_builder_get_object(main_builder, "MColumn3"));
	Input_button = GTK_WIDGET(gtk_builder_get_object(main_builder, "Input_button"));
	Organize_button = GTK_WIDGET(gtk_builder_get_object(main_builder, "Organize_button"));
	Map_button = GTK_WIDGET(gtk_builder_get_object(main_builder, "Map_button"));
	Clear_button = GTK_WIDGET(gtk_builder_get_object(main_builder, "Clear_button"));
	
	
	//Input entries signals for input button activation
	GList *entries = NULL;
    entries = g_list_append(entries, Nume_entry);
    entries = g_list_append(entries, Nrsarje_entry);
    entries = g_list_append(entries, Input_button);
    
    
	for (GList *node = entries; node != NULL; node = node->next) {
        GtkWidget *entry = GTK_WIDGET(node->data);
            if (entry != Input_button) {
            g_signal_connect(entry, "changed", G_CALLBACK(on_Input_entries_changed), entries);
        }
        }
	
	//input_button click signal
    g_signal_connect(Input_button, "clicked", G_CALLBACK(on_Input_button_clicked), Main_textview);
    
    //organize button click signal
    g_signal_connect(Organize_button, "clicked", G_CALLBACK(on_Organize_button_clicked), NULL);
    
    //map button click signal
    g_signal_connect(Map_button, "clicked", G_CALLBACK(on_Map_button_clicked), NULL);
    
    //clear button click signal
    g_signal_connect(Clear_button, "clicked", G_CALLBACK(on_Clear_button_clicked), NULL);
    

	gtk_builder_connect_signals(main_builder, NULL);
	
    gtk_widget_show_all(Main_window);

    gtk_main();
    
    return 0;
}


