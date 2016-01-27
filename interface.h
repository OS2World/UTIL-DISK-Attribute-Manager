//==========================================================================\
// interface.h : definizioni icone, bmp, menu e controlli dei vari dialoghi |
//==========================================================================/

#ifndef __ATTMAN_INTERFACE__
   #define  __ATTMAN_INTERFACE__

   #ifndef __ATTMAN_PREFERENCES__
      #include "preferences.h"
   #endif

   // nuovi controlli
   #define CC_HELPSBAR        "ACCHelpStatusBar"
   #define CC_HELPBTN         "ACCHelpButton"
   #define CC_MENULBOX        "ACCmenuLbox"
   #define CC_MENUSTXT        "ACCmenuStatic"
   #define CC_MENUMLE         "ACCmenuMLE"

   // ICONA APPLICAZIONE
   #define MAIN_ICON          1
   
   // icone listbox directory
   #define FLD_OPEN         100
   #define FLD_CLOSE        101
   
   // BITMAPS
   #define  BMP_BROWSE      100
   #define  BMP_BROWSE1     101
   #define  BMP_UP          102
   #define  BMP_DOWN        103
   #define  BMP_SAVE        104
   #define  BMP_IMPORT      105
   #define  BMP_REPORT      106
   #define  BMP_FIND        107
   #define  BMP_LOG         108
   #define  BMP_LOGO        600
   
   // DIALOGO PRINCIPALE
   #define DLG_MAIN         100
   #define TXT_DRIVE        101
   #define LB_DRIVE         102
   #define TXT_FOLDER       103
   #define LB_FOLDER        104
   #define TXT_FILE         105
   #define LB_FILE          106
   #define GRP_ORDATTR      107
   #define CBOX_A           108
   #define CBOX_S           109
   #define CBOX_H           110
   #define CBOX_R           111
   #define TXT_FSIZE        112
   #define TXT_EASIZE       113
   #define STB_WRITTEN      114
   #define STB_CREATED      115
   #define STB_ACCESSED     116
   #define TXT_SUBJ         117
   #define EF_SUBJ          118
   #define TXT_KEY          119 
   #define MLE_KEY          120 
   #define BTN_OPEN         121 
   #define BTN_CLOSE        122
   #define BTN_UP           123
   #define BTN_DOWN         124
   #define BTN_SAVE         125
   #define BTN_IMP          126
   #define BTN_REP          127
   #define BTN_FIND         128
   #define TXT_COMNT        129
   #define MLE_COMNT        130
   #define BTN_LOG          131
   #define SBARMSG          132
   
   // MENU PRINCIPALE
   #define MENU_MAIN        11100
   #define MN_BROWSE        11101
   #define MN_SEL_ALL       11102
   #define MN_DESEL_ALL     11103
   #define MN_MASK          11104
   #define MN_REFRESH       11105
   #define MN_SAVE          11106
   #define SUBMN_REPORT     11107
   #define MN_SELECTED      RADIO_SEL_FILES
   #define MN_ALL           RADIO_ALL_FILES
   #define MN_FTREE         RADIO_FULL_TREE 
   #define MN_FIND          11111  
   #define MN_EXIT          11112  
   #define MN_PREF          11113                            
   #define MN_FONT          11114                            
   #define MN_READ          11115                            
   #define MN_UNDO          11116                            
   #define MN_CUT           11117                            
   #define MN_COPY          11118  
   #define MN_PASTE         11119  
   #define MN_CLEAR         11120  
   #define SUBMN_IMPORT     11121                             
   #define MN_AUTO          RADIO_IMP_AUTO                            
   #define MN_4             RADIO_IMP_4                               
   #define MN_ID_DIZ        RADIO_FILE_ID_DIZ                               
   #define MN_ID_UDEF       RADIO_USER_DEF                               
   #define MN_OTHER         RADIO_IMP_OTHER                     
   #define MN_HLP_IDX       11127                   
   #define MN_HLP_GEN       11128                           
   #define MN_HLP_USE       11129                           
   #define MN_HLP_KEY       11130                           
   #define MN_HLP_PROD      11131                           
                                                          
   // menu editazione                                     
   #define MENU_EDIT        200                           
                                                          
   // ID controlli DIALOGO MONOSAVE                       
   #define SAVE_DLG         200                           
   #define TXT_FILESPEC     201                           
   #define ID_ICON          202
   #define TXT_MODIFIED     203
   #define BTN_2_SAVE       204
   #define BTN_2_DISCARD    205
   #define BTN_2_CANCEL     206
   
   // ID CONTROLLI DIALOGO EDIT DATE TIME
   #define EDITDATETIME_DLG 300
   #define TXT_HOUR         301
   #define SPIN_HOUR        302
   #define TXT_MIN          303
   #define SPIN_MIN         304
   #define TXT_SEC          305
   #define SPIN_SEC         306
   #define TXT_DAY          307
   #define SPIN_DAY         308
   #define TXT_MONTH        309
   #define SPIN_MONTH       310
   #define TXT_YEAR         311
   #define SPIN_YEAR        312
   #define BTN3_OK         313
   #define BTN3_CANC       314
   // ID CONTROLLI DIALOGO MULTISAVE
   #define MULT_SAVE_DLG    400
   #define GRP_MULT_SAVE    401
   #define GRP_ORD          402
   #define CKBOX_A          403
   #define CKBOX_H          404
   #define CKBOX_R          405
   #define CKBOX_S          406
   #define GRP_EAS          407
   #define CKBOX_SUBJ       408
   #define CKBOX_KEY        409
   #define CKBOX_CMNT       410
   #define GRP_LASTCHANGE   411
   #define CKBOX_CHTIME     412
   #define CKBOX_CHDATE     413
   #define GRP_LASTCREATE   414
   #define CKBOX_CRTIME     415
   #define CKBOX_CRDATE     416
   #define GRP_LASTACCESS   417
   #define CKBOX_ACTIME     418
   #define CKBOX_ACDATE     419
   #define BTN_4_OK         420
   #define BTN_4_DISCARD    421
   #define BTN_4_HELP       422
   // ID CONTROLLI DIALOGO PROGRESS
   #define WRITE_DLG        500
   #define WRITE_FILE       501
   #define PARTIAL          502
   #define TOTAL            503
   // ID DIALOGO LOGO
   #define LOGO_DLG         600
   #define BMP_CTRL         601
   #define TXT_VERSION      602
   #define LOGO_BTN         603
   // ID CONTROLLI DIALOGO MASK SELECTION
   #define MASKSEL_DLG      610
   #define COMBO_MASK       611
   #define MASK_STORE       612
   #define MASK_DEL         613
   #define MASK_OK          614
   #define MASK_CANC        615

#endif
