//==========================================================================\
// prefMessages.h : stringhe usate nel dialogo preferenze                   |
//==========================================================================/

#ifndef __ATTMAN_PREFMESSAGES__
   #define __ATTMAN_PREFMESSAGES__ 

   #define UK                         // definizione del linguaggio
   // #define IT
   
   // messaggi di errore e vari
   #ifdef UK
      #define PREF_TITLE         "Attribute manager: preferences"
      // pagina 1: General
      #define DISAB_LOGO         "Disable logo"
      #define SUBJ_LEN           "Subject length"
      #define DEFAULT            "Default"
      #define CHARS              "chars:"
      #define RDONLY_MODE        "Read only mode"
      #define SZ_BUBBLEHELP      "Enable toolbar bubble help"
      #define SZ_SVLASTPATH      "Save last path"
      #define SZ_DATEFRMT        "Date format"
      #define SZ_DMY             "day/month/year"
      #define SZ_MDY             "month/day/year"
      #define SZ_YMD             "year/month/day"
      #define FONT_              "Font..."
      // pagina 2: Selection
      #define EXT_FILE_SEL       "Extended file selection"
      #define SEL_ALL_FILES      "Select all files in directory"
      #define MOU_SNGL_CLICK     "Single mouse click"
      #define SHOW_FIL_SEL_WIN   "Show file selection window"
      #define ONLY_DIR           "Only directory"
      // pagina 3: Import (1)
      #define AUTO_IMP           "Auto import"
      #define ENABLE             "Enable"
      #define VIEW_ONLY          "View only"
      #define IMP_TO             "Import to"
      #define SZ_SUBJ            "Subject"
      #define SZ_CMNT            "Comment"
      #define AUTO_SEL           "Auto select"
      #define DEF_IMP_MODE       "Default import mode"
      #define SZ_4DOS_OS_2       "4 DOS - OS/2"
      #define F_ID_DIZ           "file_id.diz"
      #define USER_DEF           "User defined"
      #define OTHER              "Other"
      #define SZ_AUTO            "Automatic"
      #define SZ_4_DESC_FILE     "4 DOS - OS/2 description file:"
      #define DESCRIPT_ION       "DESCRIPT.ION"
      // pagina 4: Import (2)
      #define SZ_IMP_FARCH       "Import from archive"
      #define SZ_ATYPE           "Archive type"
      #define SZ_NEWTYPE         "New type:"
      #define SZ_REPLACE         "<< U~pdate"
      #define SZ_ADD             "<< ~Add"
      #define SZ_REMOVE          ">> ~Remove"
      #define SZ_F_TOIMP         "File to import:"
      #define SZ_PROG            "Program:"
      #define SZ_PARMS           "Parameters:"
      // pagina 5: Import (3)
      #define SZ_EXTRACT         "Extract:"
      #define SZ_FORMAT          "Format:"
      // pagina 6: Report (1)
      #define AUTO_REP           "Auto report"
      #define REP_ONLY_DIR       "Only directory"
      #define SZ_SHOW            "Show"
      #define SZ_HIDE            "Hide"
      #define SHOW_REP_ONLY      "Show only report"
      #define SZ_DEF_REPORT      "Default report:"
      #define REP_SEL_FILE       "Selected files"
      #define REP_ALL_FILE       "All files"
      #define REP_TREE           "Full tree"
      // pagina 7: report (2)
      #define SZ_AUTOSAVE        "Auto save"
      #define SZ_SAVEAS          "Save as:"
      // pagina 8: Find
      #define SZ_FIND            "Find"
      // pulsanti comuni blocco impostazioni
      #define _SZ_UNDO           "~Undo"
      #define _SZ_DEFAULT        "~Default"
      #define _SZ_HELP           "Help"
      // Testo Tabs:
      #define _SZ_GENERAL        "~General"
      #define _SZ_SELECTION      "~Selection"
      #define _SZ_IMPORT         "~Import"
      #define _SZ_REPORT         "~Report"
      #define _SZ_FIND           "~Find"
      // Testo status line:
      //#define PG1OF3             "Page 1 of 3"
      //#define PG2OF3             "Page 2 of 3"
      //#define PG3OF3             "Page 3 of 3"
      #define PG1OF2             "Page 1 of 2"
      #define PG2OF2             "Page 2 of 2"
   #endif
#endif
