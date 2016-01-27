# debug.mak
# Creato dal MakeMake del WorkFrame/2 IBM alle 18:18:01 del 29 Dicembre 1997
#
# Le azioni incluse in questo file Make sono:
#  Compile::Resource Compiler
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind

.SUFFIXES: .c .obj .rc .res 

.all: \
    .\debug.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

{C:\Workdesk\Progetti\AttMan\AM07600}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /V"* (c) 1997 * Alessandro Cantatore * Team OS/2 Italy" /Ti /G5 /Gu /C %s

{C:\Workdesk\Progetti\AttMan\AM07600}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /V"* (c) 1997 * Alessandro Cantatore * Team OS/2 Italy" /Ti /G5 /Gu /C %s

.\debug.exe: \
    .\utils.obj \
    .\window.obj \
    .\attman.obj \
    .\attribute.obj \
    .\AuxDlgs.obj \
    .\commands.obj \
    .\datetime.obj \
    .\drive.obj \
    .\drop.obj \
    .\eas.obj \
    .\file.obj \
    .\folder.obj \
    .\font.obj \
    .\imp4dos.obj \
    .\impfileiddiz.obj \
    .\import.obj \
    .\impother.obj \
    .\impudef.obj \
    .\init.obj \
    .\mainaux.obj \
    .\mask.obj \
    .\ordattrs.obj \
    .\preferences.obj \
    .\preffind.obj \
    .\prefgen.obj \
    .\prefimp_1.obj \
    .\prefimp_2.obj \
    .\prefrep_1.obj \
    .\prefrep_2.obj \
    .\prefsel.obj \
    .\PROFILE.obj \
    .\sstring.obj \
    .\attman.res \
    {$(LIB)}3dctls.lib
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /de /exepack:2 /pmtype:pm /packd /optfunc /nologo"
     /Fedebug.exe 
     3dctls.lib 
     .\utils.obj
     .\window.obj
     .\attman.obj
     .\attribute.obj
     .\AuxDlgs.obj
     .\commands.obj
     .\datetime.obj
     .\drive.obj
     .\drop.obj
     .\eas.obj
     .\file.obj
     .\folder.obj
     .\font.obj
     .\imp4dos.obj
     .\impfileiddiz.obj
     .\import.obj
     .\impother.obj
     .\impudef.obj
     .\init.obj
     .\mainaux.obj
     .\mask.obj
     .\ordattrs.obj
     .\preferences.obj
     .\preffind.obj
     .\prefgen.obj
     .\prefimp_1.obj
     .\prefimp_2.obj
     .\prefrep_1.obj
     .\prefrep_2.obj
     .\prefsel.obj
     .\PROFILE.obj
     .\sstring.obj
<<
    rc.exe -x2 .\attman.res debug.exe

.\attman.res: \
    C:\Workdesk\Progetti\AttMan\AM07600\attman.rc \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}datetime.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}masksel.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}logo.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}preferences.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}prefMessages.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}progress.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}multisave.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}monosave.dlg \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}main.DLG \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}fldclose.ico \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}fldopen.ico \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}attman.ico \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE)}messages.h

.\utils.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\utils.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\sstring.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\sstring.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h

.\PROFILE.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\PROFILE.C \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\prefsel.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefsel.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\prefrep_2.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefrep_2.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\prefrep_1.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefrep_1.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\prefimp_2.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefimp_2.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\prefimp_1.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefimp_1.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\prefgen.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\prefgen.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\preffind.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\preffind.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\preferences.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\preferences.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\ordattrs.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\ordattrs.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h

.\mask.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\mask.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\mainaux.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\mainaux.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\init.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\init.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\impudef.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\impudef.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}efdlg.h

.\impother.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\impother.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\import.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\import.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\impfileiddiz.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\impfileiddiz.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\imp4dos.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\imp4dos.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\font.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\font.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}prefmessages.h

.\folder.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\folder.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h

.\file.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\file.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\eas.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\eas.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h

.\drop.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\drop.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h

.\drive.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\drive.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\datetime.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\datetime.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\commands.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\commands.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\AuxDlgs.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\AuxDlgs.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h

.\attribute.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\attribute.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\attman.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\attman.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}messages.h

.\window.obj: \
    C:\Workdesk\Progetti\AttMan\AM07600\window.c \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}attman.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}definitions.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}funzioni.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}interface.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}debug.h \
    {C:\Workdesk\Progetti\AttMan\AM07600;$(INCLUDE);}preferences.h
