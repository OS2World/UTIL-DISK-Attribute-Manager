// preferences.h : definizioni per il blocco impostazioni

#ifndef __ATTMAN_PREFERENCES__
   #define __ATTMAN_PREFERENCES__

   // dialogo principale
   #define DLG_PREFERENCES     2000
   #define PREF_NOTEBOOK       2001
   
   // prima pagina : General
   #define PREF_GENERAL        2010
   #define CBOX_NOLOGO         2011
   #define CBOX_BUBBLE         2012
   #define GRP_SUBJ_LEN        2013
   #define CBOX_DEF_LEN        2014
   #define TXT_SUBJ_CHARS      2015
   #define SPIN_SUBJ_LEN       2016
   #define CBOX_READ_ONLY      2017
   #define CBOX_SV_LASTPATH    2018
   #define BTN_FONT            2019
   #define TXT_FONT            2020
   
   // seconda pagina : Selection
   #define PREF_SEL            2100
   #define CBOX_EXT_SEL        2101
   #define CBOX_SEL_ALL_INDIR  2102
   #define CBOX_MOUSE_SINGLE   2103
   #define CBOX_FILE_WIN       2104
   #define CBOX_ONLY_DIR       2105
   
   // terza pagina : Import (1)
   #define PREF_IMPORT_1       2200
   #define CBOX_ENABLE_AIMP    2201
   #define CBOX_VIEW_ONLY      2202
   #define GRP_IMPORT_TO       2203
   #define RADIO_TO_SUBJ       2204
   #define RADIO_TO_CMNT       2205
   #define RADIO_TO_AUTO       2206
   #define GRP_DEF_IMPORT      2207
   #define RADIO_IMP_AUTO      2208
   #define RADIO_IMP_4         2209
   #define RADIO_FILE_ID_DIZ   2210
   #define RADIO_USER_DEF      2211
   #define RADIO_IMP_OTHER     2212
   #define TXT_DESCRIPTION     2213
   #define EF_DESCRIPTION      2214
   #define GRP_IMP_UDEF        2215

   // quarta pagina: import (2)
   #define PREF_IMPORT_2       2300                
   #define GRP_IMP_FARCH       2301                
   #define GRP_ATYPE           2302                
   #define LB_ATYPE            2303                
   #define BTN_REPLACE         2304                
   #define BTN_ADD             2305                
   #define BTN_REMOVE          2306                
   #define TXT_NEWTYPE         2307                
   #define TXT_F_TOIMP         2308                
   #define TXT_IMP_PROG        2309                
   #define TXT_IMP_PARMS       2310                
   #define EF_ATYPE            2311                
   #define EF_F_TOIMP          2312                
   #define EF_IMP_PROG         2313                
   #define EF_IMP_PARMS        2314                

   // quinta pagina : report (1)
   #define PREF_REPORT_1       2500
   #define GRP_MODE            2501                         
   #define CBOX_AUTO_REP       2502                         
   #define CBOX_ONLY_DIR_REP   2503                         
   #define RADIO_SHOW          2504                         
   #define RADIO_HIDE          2505                         
   #define RADIO_SHOW_ONLYREP  2506                         
   #define GRP_DEF_REP         2507
   #define RADIO_SEL_FILES     2508
   #define RADIO_ALL_FILES     2509               
   #define RADIO_FULL_TREE     2510               
                                                  
   // sesta pagina : report (2)
   #define PREF_REPORT_2       2600
   #define CBOX_FORMAT         2601
   #define GRP_IMP_FORMAT      2602
   #define CBOX_AUTOSAVE       2603
   #define GRP_AUTOSAVE        2604
   #define TXT_SAVEAS          2605
   #define EF_SAVEAS           2606

   // settima pagina : find
   #define PREF_FIND           2700
   #define CBOX_FIND           2701
   #define GRP_FIND            2702
   
   // pulsanti comuni a tutte le pagine del notebook
   #define BTTN_UNDO            100
   #define BTTN_DEFAULT         101
   #define BTTN_HELP            102            
                                               
#endif                                         
                                               
