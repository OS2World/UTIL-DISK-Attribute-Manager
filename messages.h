//==========================================================================\
// messages.h : stringhe usate da programma                                 |
//==========================================================================/

#ifndef __ATTMAN_MESSAGES__
   #define __ATTMAN_MESSAGES__

   #define UK                         // definizione del linguaggio
   // define IT
   

   #ifdef UK
      // messaggi fly over help
      #define BTN_OPEN_FLYHLP  "Open browse mode"
      #define BTN_CLOSE_FLYHLP "Close browse mode"
      #define BTN_UP_FLYHLP    "Select previous file"
      #define BTN_DOWN_FLYHLP  "Select next file"
      #define BTN_SAVE_FLYHLP  "Save attributes"
      #define BTN_IMP_FLYHLP   "Import"
      #define BTN_REP_FLYHLP   "Report"
      #define BTN_FIND_FLYHLP  "Find..."
      #define BTN_LOG_FLYHELP  "Open log window"
      #define SZ_CLICKTOEDIT   "Click to edit date/time"

      // messaggi di errore e vari
      #define SZ_CCREGISTRATIONFAILURE "Unable to register enhanced window classes"
      #define ERR_TMP_DIR      "Unable to create temporary path!"
      #define DRIVE_NOT_READY  "The selected drive is not ready!"
      #define ERR_EA_BUFFER    "Data will be truncated to 32 KB length!"
      #define CANNOT_REFRESH   "Drive not ready! Cannot update listbox content!"
      #define PSZ_EXPIRED  "This version of Attribute Manager has expired! Please "\
                           "get the new release."
      #define PSZ_INVARGS  "Attribute Manager V. 0.76.51\n"\
                           "Use:\n"\
                           "ATTMAN [-pProfile] [filespec]\n"
      #define ERR_ALLOC_SWPARRAY \
                           "Allocation for control position structures failed!"
      #define ERR_ALLOC_SELFILES \
                           "Allocation for array of selected files failed!"
      #define ERR_ALLOC_MASK_DATA \
                           "Allocation for mask selection data failed!" \
                           " The mask selection list has not been updated."
      #define ERR_ALLOC_MASK_BUFFER \
                           "Allocation for mask selection buffer failed!"
      #define ERR_INIFILE_CORRUPTED \
                           "Profile corrupted! Delete attman.ini"
      #define ERR_ALLOC_WRITE_ATTR "Allocation for EAs writing failed!"
      #define ERR_ALLOC_READ_ATTR "Allocation for EAs reading failed!"
      #define ERR_ACCESS_4DOSFILE \
              "Unable to acces 4 Dos - OS/2 description file!"
      #define ERR_ALLOC_READ_DESCRIPTION \
              "Allocation for reading 4DOS - OS/2 description file failed!"
      #define ERR_ALLOC_UNARC_DBASE \
              "Allocation for the unarchivers data base failed!"
      #define ERR_ALLOC_UPDATE_UNARC_DBASE \
              "Allocation failure! Can't update the unarchiver database"
      #define ERR_INV_PARMS     "Invalid parameters string: "
      #define ERR_UNSUPPORTED \
              "No program available for this file format!"
      #define ERR_UNOPEN_FIDIZ \
              "Unable to open description file from archive!"
      #define ERR_OPEN_UDEF \
              "Unable to open file created by the user defined program!"
      #define ERR_OPEN_OTHER \
              "Unable to open file!"
      #define ERR_ALLOC_FIDIZ \
              "Allocation for reading description from archive failed!"
      #define ERR_ALLOC_UDEF \
              "Allocation for reading user defined file failed!"
      #define ERR_ALLOC_OTHER \
              "Alocation for file reading failed!"
      #define ERR_UNARC_PRG \
              "Unarchiver program failure!"
      #define ERR_UDEF_PRG \
              "User defined program failure!"
      // dialogo salvataggio singolo
      #define SZ_SAVE_                "Save..."
      #define SZ_SOME_ATTR_BEEN_MOD   "Some attribute has been modified..."
      #define SZ_SAVE                 "~Save"
      #define SZ_DISCARD              "~Discard"
      #define SZ_CANCEL               "~Cancel"

      // dialogo salvataggio multiplo
      #define SZ_MULTI_FILE_SAVE      "Multiple file save"
      #define SZ_SET_ALL_SELFILES     "Set all selected files:"
      #define SZ_ORD_ATTRS            "Ordinary attributes:"
      #define SZ_LASTCHANGE           "Last changed date & time:"
      #define SZ_LASTCREATE           "Creation date & time:"
      #define SZ_LASTACCESS           "Last access date & time:"
      #define SZ_EXT_ATTRS            "Extended attributes:"
      #define SZ_SUBJECT              "Subject"
      #define SZ_KEYPHRASES           "Key Phrases"
      #define SZ_COMMENTS             "Comments"
      #define SZ_OK                   "~OK"
      #define SZ_HELP                 "~Help"

      // dialogo progresso
      #define SZ_SAVING               "Saving attribute:"

      // dialogo mask selection       
      #define SZ_MASK_SEL             "Mask selection"
      #define SZ_STORE                "~Store"
      #define SZ_DEL                  "~Delete"

      // dialogo logo.dlg
      #define LOGO_TITLE              "Product Information"
      #define PROG_VERSION            "Version 0.76.51"
      // stringhe blocco preferenze
      #define PREFERENCE_TITLE        "Attribute manager: preferences"

      // dialogo editazione data/ora file
      #define SZ_HOUR                 "~hour:"
      #define SZ_MIN                  "mi~n.:"
      #define SZ_SEC                  "~sec.:"
      #define SZ_DAY                  "~day:"
      #define SZ_MONTH                "~month:"
      #define SZ_YEAR                 "~year:"
   #endif
#endif
