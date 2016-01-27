!if $(DEBUG) == 1
COMPILE="icc /C /Ss /W3 /Ti+ /Tm+ /O- /Q+"
LINK="ilink /NOFREE /DEbug /PM:PM"
!else
COMPILE="icc /C /Ss /W3 /Q+"
LINK="ilink /NOFREE /PM:PM"
!endif


all:attman.exe


!if $(DEBUG) == 1
attman.exe : attman.obj attribute.obj auxdlgs.obj commands.obj drive.obj \
             drop.obj eas.obj file.obj folder.obj font.obj imp4dos.obj \
             impfileiddiz.obj import.obj impother.obj impudef.obj init.obj \
             mainaux.obj mask.obj ordattrs.obj preferences.obj preffind.obj \
             prefgen.obj prefimp_1.obj prefimp_2.obj prefrep_1.obj \
             prefrep_2.obj prefsel.obj profile.obj sstring.obj \
             utils.obj window.obj datetime.obj printf.obj attman.def \
             attman.res
    $(LINK)  attman attribute auxdlgs commands drive drop eas file folder \
             font imp4dos impfileiddiz import impother impudef init mainaux \
             mask ordattrs preferences preffind prefgen prefimp_1 prefimp_2 \
             prefrep_1 prefrep_2 prefsel profile sstring utils window \
             datetime printf , , , ,attman.def;
!else
attman.exe : attman.obj attribute.obj auxdlgs.obj commands.obj drive.obj \
             drop.obj eas.obj file.obj folder.obj font.obj imp4dos.obj \
             impfileiddiz.obj import.obj impother.obj impudef.obj init.obj \
             mainaux.obj mask.obj ordattrs.obj preferences.obj preffind.obj \
             prefgen.obj prefimp_1.obj prefimp_2.obj prefrep_1.obj \
             prefrep_2.obj prefsel.obj profile.obj sstring.obj \
             utils.obj window.obj datetime.obj attman.def attman.res
    $(LINK)  attman attribute auxdlgs commands drive drop eas file folder \
             font imp4dos impfileiddiz import impother impudef init mainaux \
             mask ordattrs preferences preffind prefgen prefimp_1 prefimp_2 \
             prefrep_1 prefrep_2 prefsel profile sstring utils window\
             datetime, , , , attman.def;
!endif

    rc attman.res

attman.res : attman.rc browse0.bmp browse1.bmp find.bmp import.bmp report.bmp\
             save.bmp attman.ico fldclose.ico fldopen.ico attman.h\
             definitions.h interface.h messages.h preferences.h\
             prefmessages.h main.dlg monosave.dlg multisave.dlg\
             progress.dlg preferences.dlg logo.dlg logo.bmp masksel.dlg \
             datetime.dlg up.bmp down.bmp
    rc -r attman.rc

attman.obj : attman.c attman.h definitions.h funzioni.h
    $(COMPILE) $*.c

attribute.obj: attribute.c attman.h definitions.h funzioni.h interface.h\
               messages.h
    $(COMPILE) $*.c

auxdlgs.obj : auxdlgs.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

datetime.obj: datetime.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

commands.obj: commands.c attman.h definitions.h funzioni.h interface.h\
              messages.h preferences.h
    $(COMPILE) $*.c

drive.obj : drive.c attman.h definitions.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

drop.obj: drop.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

eas.obj : eas.c attman.h definitions.h funzioni.h
    $(COMPILE) $*.c

file.obj: file.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

folder.obj: folder.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

font.obj: font.c attman.h funzioni.h preferences.h prefmessages.h
    $(COMPILE) $*.c

imp4dos.obj: imp4dos.c attman.h definitions.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

impfileiddiz.obj: impfileiddiz.c attman.h definitions.h funzioni.h \
                  interface.h messages.h
    $(COMPILE) $*.c

impother.obj  impother.c attman.h definitions.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

impudef.obj: impudef.c attman.h definitions.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

import.obj: import.c attman.h definitions.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

init.obj: init.c attman.h definitions.h interface.h funzioni.h
    $(COMPILE) $*.c

mainaux.obj: MainAux.c attman.h funzioni.h interface.h messages.h
    $(COMPILE) $*.c

mask.obj: mask.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

ordattrs.obj: ordattrs.c attman.h definitions.h funzioni.h interface.h
    $(COMPILE) $*.c

preferences.obj: preferences.c attman.h definitions.h funzioni.h\
                 preferences.h prefmessages.h
    $(COMPILE) $*.c

preffind.obj: preffind.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefgen.obj: prefgen.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefimp_1.obj: prefimp_1.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefimp_2.obj: prefimp_2.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefrep_1.obj: prefrep_1.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefrep_2.obj: prefrep_2.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

prefsel.obj: prefsel.c attman.h preferences.h prefmessages.h funzioni.h
    $(COMPILE) $*.c

profile.obj : profile.c attman.h funzioni.h messages.h preferences.h\
              interface.h
    $(COMPILE) $*.c

sstring.obj: sstring.c funzioni.h
    $(COMPILE) $*.c

utils.obj: utils.c attman.h interface.h funzioni.h
    $(COMPILE) $*.c

window.obj: window.c attman.h funzioni.h interface.h
    $(COMPILE) $*.c

!if $(DEBUG) == 1
printf.obj : printf.c debug.h
    $(COMPILE) $*.c
!endif

