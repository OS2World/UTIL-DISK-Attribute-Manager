//==========================================================================\
// funzioni.h : dichiarazione delle funzioni usate nei vari moduli          |
//==========================================================================/

#ifndef __ATTMAN_FUNCTIONS__
   #define __ATTMAN_FUNCTIONS__

   #ifndef INCL_WIN
      #define INCL_WIN
   #endif

   #ifndef INCL_WINSTDDRAG
      #define INCL_WINSTDDRAG
   #endif

   #ifndef __OS2_H__
      #include <os2.h>
   #endif

   #ifndef __ATTMAN_STRUCTS__
      #include "attman.h"
   #endif

   // attman.c : modulo principale
   int main(int argc, char** argv);
   MRESULT EXPENTRY MyDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY NewTitleWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ACCMMLEWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY NewEFWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ACCMSTextWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ACCMLBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ACCHBtnWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ACCHSBarWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY FileBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

   // attribute.c : funzioni generiche lettura scrittura attributi
   LONG GetAttr(HWND hwnd, PFILESPECS pfsp);
   BOOL WriteNewAttr(HWND hwnd, PATTMAN pam);
   BOOL WriteSubject(HWND hwnd, PSZ pszFile, PVOID buffer);
   BOOL WriteKeyPhrases(HWND hwnd, PSZ pszFile, PVOID buffer);
   BOOL WriteComments(HWND hwnd, PSZ pszFile, PVOID buffer);
   VOID ReadMle(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData);
   VOID ShowAttr(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData);
   
   // AuxDlgs.c : procedure messaggi finestre dialogo ausiliarie
   MRESULT EXPENTRY SaveMultiDlgProc(HWND hwnd, ULONG msg,
                                     MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY ProgDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT EXPENTRY LogoDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

   // controls.c : Š divisa tra drive.c, folder.c e file.c
   
   // commands.c : elaborazione dei vari WM_COMMAND
   MRESULT ProcessButtonOpen(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonClose(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonSave(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonImport(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonReport(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonFind(void);
   MRESULT ProcessButtonUp(HWND hwnd, PATTMAN pam);
   MRESULT ProcessButtonDown(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuBrowse(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuSelAll(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuDeselAll(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuMask(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuRefresh(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuSelected(HWND hwnd);
   MRESULT ProcessMenuAll(HWND hwnd);
   MRESULT ProcessMenuFullTree(HWND hwnd);
   MRESULT ProcessMenuFind(HWND hwnd);
   MRESULT ProcessMenuPreferences(HWND hwnd, PATTMAN pam, PAM_PRO ppref);
   MRESULT ProcessMenuFont(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuReadOnly(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuUndo(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuCut(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuCopy(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuPaste(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuClear(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuImpAuto(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenu4Dos(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuID_DIZ(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuImpUdef(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuOther(HWND hwnd, PATTMAN pam);
   MRESULT ProcessMenuHelpIDX(void);
   MRESULT ProcessMenuHelpGeneral(void);
   MRESULT ProcessMenuHelpUse(void);
   MRESULT ProcessMenuHelpKey(void);
   MRESULT ProcessMenuHelpProduct(HWND hwnd);

   // datetime.c
   MRESULT OpenEditDateTimeDlg(HWND hwnd, PATTMAN pam, ULONG id);
   MRESULT EXPENTRY DateTimeDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT InitDateTimeDlg(HWND hwnd, PEDITDATETIME pedt);
   VOID SetDateTimeSpins(HWND hwnd, PEDITDATETIME pedt);
   VOID SetDateTimeLimits(HWND hwnd, PEDITDATETIME pedt);
   VOID GetDateTimePref(PFILESPECS pfs);
   
   // drive.c : funzioni gestione listbox drive, cambio partizione, ecc.
   BOOL SetDisk(HWND hwnd, BYTE newDisk, PBOOL phpfs);
   VOID FillDriveList(HWND hwnd, PATTMAN pam);
   VOID ProcessDriveSelection(HWND hwnd, MPARAM mp1, PATTMAN pam);
   BOOL isHPFS(UCHAR uchDrive);

   // drop.c eleborazione messaggi drag&drop
   MRESULT ProcessDragOver(HWND hwnd, PDRAGINFO pdinfo);
   MRESULT ProcessDrop(HWND hwnd, PDRAGINFO pdinfo);
   
   // eas.c : funzioni relative alla gestione degli attributi estesi
   ULONG PutEa(CHAR *pszFile, CHAR *pszAttName, USHORT cbAttName,
               CHAR *AttValue, ULONG *cbValue);
   ULONG GetEa(CHAR *file, CHAR *attName, USHORT cbAttName,
               CHAR *attVal, ULONG *cbValue);
   USHORT Attr2Text(CHAR *buffer, ULONG cbAttr, BOOL mode);
   VOID Text2Attr(CHAR *buffer, ULONG *cbData);
   
   // file.c : funzioni relative alla gestione listbox file, titolo finestra, ecc
   VOID ProcessFileSelection(HWND hwnd, PATTMAN pam);
   BOOL isChanged(HWND hwnd, PATTMAN pam);
   VOID SetWinTitle(HWND hwnd, PATTMAN pam);
   VOID DeselectAllFiles(HWND hwnd, PATTMAN pam);
   VOID UpdateSelFilesArray(HWND hwnd, PATTMAN pam);

   // Find.c : funzioni per la ricerca di file
   // folder.c : funzioni listbox folder, cambio directory, ecc.
   int SetPath(PFILESPECS pfsp);
   VOID FillDirList(HWND hwnd, PATTMAN pam);
   VOID QueryCurrentPath(PSZ pszPath, PSZ pszFile);
   VOID ProcessFolderSelection(HWND hwnd, MPARAM mp1, PATTMAN pam);
   BOOL SetTempPath(PSZ pszTmpPath);

   // font.c
   BOOL ShowFontDlg(HWND hwnd, PSZ pszFont);
   VOID BreakFontAttrs(PSZ pszFont, PSZ pszName, PULONG pulStyle, PFIXED pfix);
   VOID JoinFontAttrs(PSZ pszFont, PSZ pszName, ULONG ulStyle, FIXED fix);
   MRESULT EXPENTRY NewFontDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

   // imp4dos.c
   BOOL Show4Dos(HWND hwnd, PATTMAN pam);
   BOOL ReadDescriptionList(PATTMAN pam, PPSZ buffer);
   ULONG Find4DosFileDescription(PATTMAN pam, PPSZ ppszCur);
   MRESULT Import4Dos(HWND hwnd, PATTMAN pam);

   // impfileiddiz.c
   BOOL ShowFileIdDiz(HWND hwnd, PATTMAN pam);
   BOOL ExtractFileIdDiz(HWND hwnd, PATTMAN pam, int i);
   BOOL ReadFileIdDiz(HWND hwnd, PATTMAN pam, MPARAM mp2);
   int FindExt(PATTMAN pam);
   MRESULT ImportFileIdDiz(HWND hwnd, PATTMAN pam);

   // import.c : funzioni per l'importazione di commenti esterni
   BOOL ImportFileData(HWND hwnd, PATTMAN pam);
   BOOL DisplayImportedData(HWND hwnd, PATTMAN pam, PSZ pszData, ULONG ulSize);
   MRESULT ProcessReady(HWND hwnd, MPARAM mp1, MPARAM mp2);

   // impother.c
   BOOL ShowOther(HWND hwnd, PATTMAN pam);

   // impudef.c
   BOOL ShowUserDef(HWND hwnd, PATTMAN pam);
   BOOL ReadUserDef(HWND hwnd, PATTMAN pam, MPARAM mp2);
   MRESULT ImportUserDef(HWND hwnd, PATTMAN pam);

   // init.c : analisi argomenti inizializzazione dialogo
   int ParseArgs(int argc, char** argv, PATTMAN pam);
   MRESULT InitDlg(HWND hwnd, PATTMAN pam);

   // mainaux.c : funzioni di interfaccia elaborazione msg finestra principale
   MRESULT MinMaxFrame(HWND hwnd, PSWP pswp);
   MRESULT ProcessMeasureItem(HWND hwnd);
   MRESULT AdjustWindowPos(HWND hwnd, PSWP pswp);
   MRESULT DrawListBoxItem(HWND hwnd, POWNERITEM poi);
   MRESULT ProcessContextMenu(HWND hwnd, ULONG idCtl);
   MRESULT ProcessBubbleHelp(HWND hwnd, HWND hFrom);
   MRESULT ProcessControl(HWND hwnd, MPARAM mp1);
   MRESULT ProcessPresParmsChanged(HWND hwnd, LONG flag);
   MRESULT ProcessCommand(HWND hwnd, MPARAM mp1, PAM_PRO ppref);
   MRESULT ProcessTermination(HWND hwnd, BOOL flag);
   MRESULT ProcessChildAppEnd(HWND hwnd, MPARAM mp1, MPARAM mp2);
   MRESULT ProcessMouseMove (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT ProcessMotionStart (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT ProcessMotionEnd (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   MRESULT ProcessTimer(HWND hwnd, ULONG ulid);
   MRESULT ProcessLBoxBtnUp(HWND hwnd, LONG lId, MPARAM mp2);

   // mask.c
   MRESULT EXPENTRY MaskDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID ProcMaskDlgExit(HWND hwnd, PMASKSEL pmask);
   VOID SaveMaskDlgPos(HWND hwnd, PMASKSEL pmask);

   // MenuEdit.c : funzioni per la gestione menu editazione
   
   // OrdAttrs.c : funzioni relative alla gestione degli attributi ordinari e
   //              data e ora dei file
   VOID GetOrdAttrs(HWND hwnd, PFILESPECS pfsp);
   VOID ShowFileFlags(HWND hwnd, PFILESPECS pfsp);
   VOID ShowDateTime(HWND hwnd, PFILESPECS pfsp);
   VOID ReadNewOrdAttrs(HWND hwnd, PFILESPECS pfsp);
   BOOL isOrdAttrChanged(HWND hwnd, PFILESPECS pfsp);
   VOID UpdateOrdAttr(HWND hwnd, PFILESTATUS3 pfs, PFILESPECS pfsp, ULONG mask);
   
   // preferences.c : funzioni per la gestione notebook impostazioni
   MRESULT EXPENTRY PrefDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID ReadNewSettings(HWND hwnd, PHWND pHpages, PAM_PRO ppref);
   MRESULT UpdateSettings(HWND hwnd, PAM_PRO ppnew);
   
   // prefgen.c
   MRESULT EXPENTRY GenDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitGeneralPage(HWND hwnd, PPREF_GEN pgen);
   VOID SetGeneralDefault(HWND hwnd, PPREF_GEN pgen);

   // prefsel.c
   MRESULT EXPENTRY SelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);   
   VOID InitSelectionPage(HWND hwnd, PPREF_SEL psel);   
   VOID SetSelectionDefault(HWND hwnd);

   // prefimp_1.c
   MRESULT EXPENTRY Imp1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitImport1Page(HWND hwnd, PPREF_IMPORT pimp, PULONG pulPrev);
   VOID SetImport1Default(HWND hwnd);

   // prefimp_2.c
   MRESULT EXPENTRY Imp2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitImport2Page(HWND hwnd, PPREF_IMPORT pimp, PUNARCDATA punarcNew,
                     BOOL flag);
   VOID ProcPrefImp2WMCtl(HWND hwnd, MPARAM mp1, PUNARCDATA punNew);
   BOOL ReplaceUnarcItem(HWND hwnd, PUNARCDATA puNew);
   BOOL AddUnarcItem(HWND hwnd, PUNARCDATA puNew);
   BOOL RemUnarcItem(HWND hwnd, PUNARCDATA puNew);
   VOID CleanUnarcEntries(HWND hwnd);
   BOOL SetImport2Default(HWND hwnd, PUNARCDATA puNew);
   VOID EnableImp2Entries(HWND hwnd, BOOL flag);

   // prefrep_1.c
   MRESULT EXPENTRY Rep1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitReport1Page(HWND hwnd, PPREF_REPORT prep);
   VOID EnableAutoReport(HWND hwnd, BOOL flag);
   VOID SetReport1Default(HWND hwnd);

   // prefrep_2.c
   MRESULT EXPENTRY Rep2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitReport2Page(HWND hwnd, PPREF_REPORT prep);
   VOID EnableReportFormat(HWND hwnd, BOOL flag);
   VOID EnableReportAutosave(HWND hwnd, BOOL flag);
   VOID SetReport2Default(HWND hwnd);

   // preffind.c
   MRESULT EXPENTRY FindDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
   VOID InitFindPage(HWND hwnd, PPREF_FIND pfind);
   VOID EnableFind(HWND hwnd, BOOL flag);
   VOID SetFindDefault(HWND hwnd);

   // profile.c : funzioni di interfacciamento con il file di inizializzazione
   VOID GetDefaultProfile(PSZ pszExe, PSZ pszProfile);
   BOOL ParseProfile(HAB hab, PSZ pszProfile, PAM_PRO ppro);
   VOID WriteAMSettings(HWND hwnd, PSZ pszProfile, PAM_PRO ppref);

   // report.c : funzioni per la creazione dei report
   // sstring.c
   char* sstrcpy(char* target, char *source);
   ULONG sstrlen(const char* s);
   PSZ sstrcat(char* out, const char* in);
   int sstrcmp(const char* s1, const char* s2);
   int sstrncmp(char* s1, const char* s2, unsigned int c);
   int sstrnicmp(char* s1, const char* s2, unsigned int n);
   int sstricmp(const char* s1, const char* s2);
   
   // Utils.c : varie funzioni di utilit…
   BOOL WildCmp(char* mask, char* cmp);
   BOOL isWildCh(PSZ pszFile);
   LONG GetMaxDay(USHORT month, USHORT year);
   PSZ i2str(int i, PSZ psz);
   SHORT isInListBox(HWND hwnd, PSZ pszFile, ULONG ID);
   PSZ GetParms(HWND hwnd, PSZ pszOut, PATTMAN pam, PSZ pszImp, PSZ pszParms);
   BOOL Subclass(HWND hwnd, USHORT usID, PFNWP newProc);
   BOOL SubclassFileList(HWND hwnd ,PATTMAN pam, PFNWP newProc);
   int Terminate(HAB hab, HMQ hmq, int rc);
   PSZ i2fstr(int i, PSZ psz, CHAR ch);
   BOOL RegisterCustomControls(HAB hab);
   BOOL Superclass(HAB hab, PSZ pszClass, PSZ pszNewClass, PFNWP pfnwpNew,
                   PFNWP *pfnwpDefault, BOOL flag);
   VOID FormatDate(PFDATE pfd, PFFDATE pffd, ULONG ulFrm);
                                                   
   // Window.c : funzioni per il ridimensionamento finestra e controllo vari
   //            parametri di presentazione
   VOID ResizeControls(HWND hwnd, SHORT cxOld, SHORT cxNew, SHORT cyNew,
                       PATTMAN pam);
   VOID SetSubjectLimit(HWND hwnd, LONG length);
   VOID EnableBrowsing(HWND hwnd, PATTMAN pam, BOOL flag);
   VOID SwitchBrowserVisibility(HWND hwnd, BOOL flag);
   VOID SetDialogFont(HWND hwnd, PPREF_GEN pGen, BOOL flag);
   MRESULT ShowContextMenu(HWND hwnd, HWND hMenu);
   VOID SwitchSelectionMode(HWND hwnd, BOOL flag);
   VOID SwitchEditMode(HWND hwnd, BOOL flag, PATTMAN pam);
   VOID SwitchCheckBoxStyle(HWND hwnd, BOOL flag);
   VOID Iconize(HWND hwnd, BOOL flag, BOOL hpfs);
   VOID SetMenuCondCascadeStyle(HWND hMenu, SHORT sSubMenuID);
   VOID SetMenuDefaults(HWND hMenu, SHORT sSubMenu,
                        SHORT sUnchkID, SHORT sCheckID);
   VOID InitEditMenu(HWND hwnd, HWND hMenu, PATTMAN pam);
   VOID EnableImportMenuItems(HWND hwnd, PATTMAN pam, PAM_PRO ppref);

#endif
