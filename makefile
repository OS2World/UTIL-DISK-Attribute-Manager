# makefile
# Creato dal MakeMake del WorkFrame/2 IBM alle 9:49:00 del 31 Dicembre 1997
#
# Le azioni incluse in questo file Make sono:
#  Compile::Resource Compiler
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind

.SUFFIXES: .c .obj .rc .res 

.all: \
    .\attman.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

{F:\dev\prj\AttMan\AM07650}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /V"Attribute Manager V. 0.76.51 * (c) 1997 * Alessandro Cantatore * Team OS/2 Italy" /Oc /G5 /Gu /C %s

{F:\dev\prj\AttMan\AM07650}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /V"Attribute Manager V. 0.76.51 * (c) 1997 * Alessandro Cantatore * Team OS/2 Italy" /Oc /G5 /Gu /C %s

.\attman.exe: \
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
     /B" /exepack:2 /pmtype:pm /packd /align:4 /optfunc /nologo"
     /Feattman.exe 
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
    rc.exe -x2 .\attman.res attman.exe

.\attman.res: \
    F:\dev\prj\AttMan\AM07650\attman.rc \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}datetime.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}masksel.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}logo.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}preferences.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}prefMessages.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}progress.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}multisave.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}monosave.dlg \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}main.DLG \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}fldclose.ico \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}fldopen.ico \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}attman.ico \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE)}messages.h

.\utils.obj: \
    F:\dev\prj\AttMan\AM07650\utils.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\sstring.obj: \
    F:\dev\prj\AttMan\AM07650\sstring.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h

.\PROFILE.obj: \
    F:\dev\prj\AttMan\AM07650\PROFILE.C \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\prefsel.obj: \
    F:\dev\prj\AttMan\AM07650\prefsel.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\prefrep_2.obj: \
    F:\dev\prj\AttMan\AM07650\prefrep_2.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\prefrep_1.obj: \
    F:\dev\prj\AttMan\AM07650\prefrep_1.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\prefimp_2.obj: \
    F:\dev\prj\AttMan\AM07650\prefimp_2.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\prefimp_1.obj: \
    F:\dev\prj\AttMan\AM07650\prefimp_1.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\prefgen.obj: \
    F:\dev\prj\AttMan\AM07650\prefgen.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\preffind.obj: \
    F:\dev\prj\AttMan\AM07650\preffind.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\preferences.obj: \
    F:\dev\prj\AttMan\AM07650\preferences.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\ordattrs.obj: \
    F:\dev\prj\AttMan\AM07650\ordattrs.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h

.\mask.obj: \
    F:\dev\prj\AttMan\AM07650\mask.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\mainaux.obj: \
    F:\dev\prj\AttMan\AM07650\mainaux.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\init.obj: \
    F:\dev\prj\AttMan\AM07650\init.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\impudef.obj: \
    F:\dev\prj\AttMan\AM07650\impudef.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}efdlg.h

.\impother.obj: \
    F:\dev\prj\AttMan\AM07650\impother.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\import.obj: \
    F:\dev\prj\AttMan\AM07650\import.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\impfileiddiz.obj: \
    F:\dev\prj\AttMan\AM07650\impfileiddiz.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\imp4dos.obj: \
    F:\dev\prj\AttMan\AM07650\imp4dos.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\font.obj: \
    F:\dev\prj\AttMan\AM07650\font.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}prefmessages.h

.\folder.obj: \
    F:\dev\prj\AttMan\AM07650\folder.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h

.\file.obj: \
    F:\dev\prj\AttMan\AM07650\file.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\eas.obj: \
    F:\dev\prj\AttMan\AM07650\eas.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h

.\drop.obj: \
    F:\dev\prj\AttMan\AM07650\drop.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h

.\drive.obj: \
    F:\dev\prj\AttMan\AM07650\drive.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\datetime.obj: \
    F:\dev\prj\AttMan\AM07650\datetime.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\commands.obj: \
    F:\dev\prj\AttMan\AM07650\commands.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\AuxDlgs.obj: \
    F:\dev\prj\AttMan\AM07650\AuxDlgs.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h

.\attribute.obj: \
    F:\dev\prj\AttMan\AM07650\attribute.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\attman.obj: \
    F:\dev\prj\AttMan\AM07650\attman.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}messages.h

.\window.obj: \
    F:\dev\prj\AttMan\AM07650\window.c \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}attman.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}definitions.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}funzioni.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}interface.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}debug.h \
    {F:\dev\prj\AttMan\AM07650;$(INCLUDE);}preferences.h
