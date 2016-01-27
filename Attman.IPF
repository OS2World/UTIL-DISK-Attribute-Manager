:userdoc.
:title.Attribute Manager V. 0.76.50 beta
:docprof  toc=123456 .
:h1 id=ID@1.Attribute Manager V. 0.76.50
:p.
:p.
:p.
:color fc=darkgreen bc=default.:font facename=Helv size=30x20.:hp2.
.ce Attribute Manager V. 0.76.50 beta
:ehp2.
:p.
:p.
:font facename=Helv size=23x20.
.ce (c) 1997-98 Alessandro Cantatore - Team OS&slash.2 Italy
:color fc='Default' bc='Default'.
:font facename=default size=0x0.

.****************** Disclaimer *******************
:h1 id=ID@2.Disclaimer
:p.
Under no circumstances the author is liable for any loss or damage. The use of
the program implies acceptance of the conditions stated above.

.****************** License Agreement *******************
:h1 id=ID@3.License Agreement 
:p.
After :color fc='Red' bc='default'.1998&slash.12&slash.31 
:color fc='Default' bc='Default'.the program will cease to work, but a new 
version will be available before the expire date&per.
:p.
You are free to use this version of the program on as many machines as you like
until the next version will be released&per.
:link reftype=hd refid=ID@29.Send me an email 
:elink.to get a message about the relase of any new version&per.
:p.
You are free to distribute the program on BBSs, FTP sites, CD ROMs, etc,
provided that you enclose all the files in the archive without any modification&per.
.br
You are not allowed to sell the program, but can charge a reasonable amount to
cover the cost of the distribution media&per.

.****************** System Requirements *******************
:h1 id=ID@4.System Requirements
:p.
OS&slash.2 Warp 3 or 4, about 200 KB of free diskspace&per.
:p.
The program executables have been packed in a format not compatible with OS&slash.2 v&per.
2&per.X&per. You can use 
:hp1.LXLITE  :ehp1.to unpack the executable or can 
:link reftype=hd refid=ID@29.email me:elink. to receive the OS&slash.2 2&per.X compatible format version&per.
:nt.
:hp1.LXLITE  :ehp1.is a free utility by Andrew Zabolotny&per.
You can download it from&colon.
:color fc='Red' bc='default'.ftp&colon.&slash.&slash.nmsu.edu&slash.pub&slash.os2&slash.util&slash.archiver&slash.lxlt121&per.zip
:color fc='Default' bc='Default'.&per.
:ent.

.****************** Introduction *******************
:h1 id=ID@5.Introduction
:p.
Attribute Manager allows to easily add, edit or delete the 
:hp1.&per.SUBJECT, &per.COMMENTS  :ehp1.
and 
:hp1.&per.KEYPHRASES  :ehp1.
extended attributes, ordinary attributes and time&slash.date stamps of one or more
files&per.
:p.
:color fc='Red' bc='default'.Don't miss the following features&colon. 
:color fc='Default' bc='Default'.
:ul.
:li.you can start the program from the commandline, dropping a file on it or
just double clicking on its icon&per. 
:li.to edit a new file or directory attributes just drag it on the titlebar of
the :link reftype=hd refid=ID@10.:hp2.Attribute Manager:ehp2. window:elink.!!!
:li.click with mouse button 2 on the program window to get the contextual menu
and to open the preferences notebook!
:li.you can show&slash.hide drive&slash.directory&slash.file selection controls&per.
:li.you can drop a font on the program (drop it on an empty area or on the
window border) to permanently change the font (controls will be resized
according to the font size)&per.
:li.you can permanently resize the drive&slash.directory&slash.file selection listboxes with
the mouse (move the mouse over the space between two listboxes)&per.
:li.you can optionally set different drive&slash.directory&slash.file with one mouse click&per.
:eul.
:p.I have a lot of archived files I downloaded from the internet and often
cannot remember their content or cannot find a particular file&per. 
:hp1.Attribute manager  :ehp1.
allows to add a small description (it can be as long as about 32 KB in this
release) and some 
:hp1.Key Phrases  :ehp1.
you can use when searching files&per.
:p.Even if the 
:hp1.Find  :ehp1.
button is not yet operative in this release, the OS&slash.2 built-in Find utility
allows file search based on the content of the 
:hp1.Key Phrases  :ehp1.
extended attribute&per.
:p.Suppose you run a BBS and have archives of various kind of applications for
different operating system, you could use various key phrases describing for
example&colon.
:ol compact.
:li.the author of the application
:li.the operating system it is designed for
:li.kind of application (file manager, game, etc.)
:li.your evaluation (good application, useful, etc)
:li.anything else
:eol.
:p.
This way, through the 
:hp1.object find  :ehp1.
utility, you could automatically create folders containing all your "OS&slash.2 text
mode file managers", or all applications of your favourite software author and
so on&per.&per.&per.
:p.

.****************** What is new *******************
:h1 id=ID@6.What is new
:p.
:ul.
:li.The data displayed was not updated when changing folder or drive while the
first file in the listbox was selected&per. Now it works fine!
:li.Better detection of attribute modification&per. Now it should avoid wrong 
:hp1.Some attribute have been modified :ehp1.
messages&per.
:li.File and EA size are now displayed together with 
:hp2.last write:ehp2., :hp2.creation:ehp2. and :hp2.last access date and time:ehp2.&per.
To edit date and time click with mouse button1 on the text&per.
:li.Date and number format follows the national settings format, so it will
display year&slash.month&slash.day, day&slash.month&slash.year or month&slash.day&slash.year and separate thousands
by "," or "&per." etc&per. according to your national settings&per.
:li.All controls are resized according to the size of the font used by the main
dialog&per.
Width is based on the font average width so some kind of proportional (not
monospaced) font will be displayed uncorrectly&per.
:li.All listbox can be resized and their width will be saved in 
:hp2.attman&per.ini:ehp2.&per.
When the mouse moves on the space
between two list boxes its shape changes: press mouse button 1 down and move the
mouse to resize the listbox width&per.
:li.
:hp2.Select previous&slash.next:ehp2.
file buttons added, to browse through all files in the current directory without
opening the upper part of the window&per.
:li.Buttons help is displayed in a statusbar&per.
:li.Improved 
:hp2.single click:ehp2.
file selection routine&per.
:eul.
:p.

.****************** Installation/deinstallation *******************
:h1 id=ID@7.Installation&slash.deinstallation
:p.
Unzip the archive in any directory&per. It would be better if you keep only the
program files in the directory so if you want to uninstall the program you can
just drag the directory on the shredder&per.
:p.
The files the programs needs to work are&colon.
:dl tsize=15 compact.
:dt.ATTMAN&per.EXE
:dd.the program itself&per.
:dt.3DCTLS&per.DLL
:dd.contains some controls used by the program and that will be used in the
preferences notebook too in a next version&per.
:dt.ATTMAN&per.INF
:dd.this file&per.
:dt.ATTMAN&per.INI
:dd.will be created as soon as you run the program&per.
:edl.
:p.
The :hp1.LIBPATH  :ehp1.statement in your 
:hp1.CONFIG.SYS  :ehp1.
file must include the "&per." (current directory) path!
:p.
All the informations needed by the program will be stored in its own INI file
(ATTMAN&per.INI)&per. Nothing will be added to OS2&per.INI or OS2SYS&per.INI&per.
If you want to use a different INI file, you can pass its name as argument using
the "P" option&per. The option is case insensitive and can be
introduced either by "&slash." or by "-"&per.
So if you want to store your program preferences in 
:font facename=Courier size=12x12.D&colon.\PROGRAMS\MYINIFILE&per.INI 
:font facename=default size=0x0. and open the program with the
attributes of 
:font facename=Courier size=12x12.C&colon.\OS2\BITMAPS\*&per.GIF
:font facename=default size=0x0.you must type&colon.
:xmp.
:font facename=Courier size=12x12.
ATTMAN -pD&colon.\PROGRAMS\MYINIFILE&per.INI C&colon.\OS2\BITMAPS\*&per.GIF
:exmp.
.br
:font facename=default size=0x0.
The arguments can have any order&colon. the profile name can be specified either
before or after the file name&per. You can create different program objects using
different INI files&per. Just type in the object settings "Parameters" entry
field&colon.
:xmp.
:font facename=Courier size=12x12.
-pD&colon.\PROGRAMS\MYINIFILE&per.INI %*
:exmp.
.br
:font facename=default size=0x0.(change :font facename=Courier size=12x12.D&colon.\PROGRAMS\MYINIFILE&per.INI
:font facename=default size=0x0.to the path\name of the INI file
you want to use)&per.
:p.
To deinstall just delete all the above mentioned files and ATTMAN&per.INI&per.
:p.

.****************** Starting the program *******************
:h1 id=ID@8.Starting the program
:p.
You can start it from the command line, doubleclick on its icon, or just drag a
file&slash.directory on its icon&per. In future I shall add the option to start it by the
contetextual menu of file objects&per.
:p.
You can select files or directories in the 
:link reftype=hd refid=ID@10.:hp1.Browse window  :ehp1.:elink.(click
on the first button in the tool bar or select 
:link reftype=hd refid=ID@21.:hp1.File->Select->Browse  :ehp1.:elink.from
the pop-up menu) or by opening folders on your desktop and dragging
files or directories on the application title bar&per.

.****************** Help *******************
:h1 id=ID@9.Help
:p.
At the moment there is no on line help&per.
To tell the truth there are still a lot of not yet implemented features so do
not wonder if some menu option or button doesn't work&per.
:p.
If you move your mouse over a toolbar button you'll get some explanation about
that button&per.
:p.
:hp1.Report 
:artwork  runin name='F:\WORKDESK\Progetti\AttMan\AM07650\report.BMP'.:ehp1.
, 
:hp1.Find 
:artwork  runin name='F:\WORKDESK\Progetti\AttMan\AM07650\find.BMP'.  :ehp1.
and 
:hp1.Open log window 
:artwork  runin name='F:\WORKDESK\Progetti\AttMan\AM07650\log.BMP'.  :ehp1.
buttons still do not work&per.
:p.

.****************** How it works *******************
:h1 id=ID@10.How it works
:p.
It is like a file dialog box&colon. just select a file and edit the attributes&per.
:p.
:artwork  align=center name='F:\Grafica\Images\attman.bmp'.
:p.
:p.If you have changed some attribute and select a new file or directory a
dialog box will ask you if you want to save or discard what you modified&per. Click
on the Save button to avoid that&per.
:p.
:p.If you chosed to work with the 
:link reftype=hd refid=ID@14.Extended selection option 
:elink.you can select one or more files in the same way you do that with other
WPS objects&colon. 
:ul compact.
:li.swiping the mouse pointer on the 
:hp1.File&colon. :ehp1.
list box while pressing down mouse button one&per.
:li.clicking with mouse button one while keeping the 
:hp2.Ctrl :ehp2.
key pressed down for selecting not-contiguous files&per.
:li.clicking with mouse button one while keeping the 
:hp2.Shift :ehp2.
key pressed down for selecting all files betwen the previous selection and the
current selection&per.
:eul.
:p.
If you didn't check the 
:link reftype=hd refid=ID@14.Single mouse click option 
:elink.in the selection page, when selecting more than one file, remember to
double click (press the 
:hp2.Ctrl :ehp2.
key in order to avoid to deselect previously selected files) on the last file
selected to force the program update its internal list of selected files!
:p.
The file specifics and attributes showed concern the topmost selected file&per.
If you want to set the same attribute for all selected files you must click on
the 
:hp1.Save :ehp1.
:artwork  runin name='F:\WORKDESK\Progetti\AttMan\AM07650\save.BMP'.
button in the main window&per. The 
:link reftype=hd refid=ID@26.Multiple File Save dialog 
:elink.will then be displayed to allow you to choose which attributes to set for
all the selected files&per.
For instance if the selected files have different 
:hp1.comments  :ehp1.
and you want them to share the same 
:hp1.key phrases  :ehp1.
without affecting 
:hp1.comments  :ehp1.
or any other attribute, you must select only the 
:hp1.Key phrases :ehp1.
check box in the 
:link reftype=hd refid=ID@26.Multiple File Save dialog
:elink..
:p.
The first button on the left 
:artwork  runin name='F:\WORKDESK\Progetti\AttMan\AM07650\browse0.BMP'.allows
to 
:hp1.show&slash.hide :ehp1.
(browse&slash.nobrowse mode) the drive&slash.path&slash.file selection window&per. For the same
purpose you can use the menu by clicking with mouse button 2 almost anywhere in
the window and selecting&colon. 
:link reftype=hd refid=ID@21.File->Select->Browse
:elink.&per.
:p.

.****************** Features and Settings *******************
:h1 id=ID@11.Features and Settings
:p.
To open the preferences notebook select from the menu&colon. 
:link reftype=hd refid=ID@22.Options->General Preferences
:elink.&per.
(New options or just enabled options are hilited in
:color fc='Red' bc='default'.red color:color fc='Default' bc='Default'., modified options are hilited in
:color fc='Pink' bc='default'.pink color:color fc='Default' bc='Default'.)&per.
:ul compact.
:li.
:link reftype=hd refid=ID@12.Common buttons 
:elink.
:li.
:link reftype=hd refid=ID@13.General Page 
:elink.
:li.
:link reftype=hd refid=ID@14.Selection page 
:elink.
:li.
:link reftype=hd refid=ID@15.Import page 1 of 2 
:elink.
:li.
:link reftype=hd refid=ID@16.Import page 2 of 2 
:elink.
:li.
:link reftype=hd refid=ID@17.Report page 1 of 2 
:elink.
:li.
:link reftype=hd refid=ID@18.Report page 2 of 2 
:elink.
:li.
:link reftype=hd refid=ID@19.Find page 
:elink.
:eul.
:p.

.****************** Common buttons *******************
:h2 id=ID@12.Common buttons
:dl.
:dt.Undo&colon. 
:dd.It reverts the various buttons, entry fields, etc&per., in the current page, to
their previous state&per.
:dt.Default&colon. 
:dd.It reverts the various buttons, entry fields, etc&per., in the current page, to
the default state&per.
:dt.Help&colon. 
:dd.Not yet implemented&per.
:edl.

.****************** General page *******************
:h2 id=ID@13.General page
:p.
:artwork  align=center name='F:\Grafica\Images\attman1.bmp'.
:p.
:dl tsize=35.
:dt.Disable logo&colon. 
:dd.allows to hide&slash.display the startup logo&per.
:dt.:color fc='Pink' bc='default'.Enable toolbar bubble help 
:color fc='Default' bc='Default'.&colon. 
:dd.when the mouse moves over a button a small description of the button
function is showed in the status bar&per.
:dt.Subject length&colon. 
:dd.unchecking the 
:hp1.Default check box :ehp1.
you'll be able to specify a non default lenght (the default is 40 characters and
the maximum is 255).
:dt.Read only mode&colon. 
:dd.If this is checked you can read the attributes, but cannot modify them&per.
:dt.Save last path&colon. 
:dd.It will save last selected path when you close the application and start it
from there if you double click on the application icon&per. If you start the
application by dragging a file on its icon, it will started in the file path
rather than the previous one&per.
:dt.Font&colon. 
:dd.The button displays the font dialog&per. To set a new font you can as well drag
it on a free region of the main window or on the window border from the font
palette&per.
:edl.
:p.

.****************** Selection page *******************
:h2 id=ID@14.Selection page
:p.
:artwork  align=center name='F:\Grafica\Images\attman2.bmp'.
:p.
:dl tsize=40.
:dt.Extended file selection&colon. 
:dd.Allows to select multiple files&per.
:dt.Select all files in directory&colon. 
:dd.If the program is opened by passing it a directory name as argument, if the 
:hp1.Extended file selection check box :ehp1.
is enabled, all files contained in the directory will be selected&per.
:dt.Single mouse click&colon. 
:dd.Allows to select drive&slash.directory&slash.file with one mouse click rather than with
a double click&per.
:dt.Show file selection window&colon. 
:dd.If checked the window is displayed in its full size&per. When it is unchecked
only the attributes of the current file are diaplayed&per.
:dt.Only directory&colon. 
:dd.If the previous checkbox is enabled the window will be displayed in its full
size only when the argument of the program is a directory&per.
:edl.
:p.

.****************** Import page 1 of 2 *******************
:h2 id=ID@15.Import page 1 of 2
:p.
:artwork  align=center name='F:\Grafica\Images\prefimp1.bmp'.
:p.
:p.The following options haven't yet been fully tested&per.
:dl tsize=35.
:dt.Auto import&colon. 
:dd.If the currently selected file, or the first of the selected files, doesn't
have any 
:hp1.Subject  :ehp1.
or 
:hp1.Comment  :ehp1.
description the program will look for a 
:hp2.description.ion :ehp2.
file, for 
:hp2.file_id.diz :ehp2.
if the current file is an archive of known format, or for a different kind of
description which could be extracted by the 
:hp2.user defined :ehp2.
options importing it into the field specified in the 
:hp1.Import to :ehp1.
box&per.
:nt.
This works only for one file even if more than one file are selected&per. 
:ent.
The description is automatically saved in the EAs unless 
:hp1.View only :ehp1.
(see next option) or 
:link reftype=hd refid=ID@13.Read only mode 
:elink.are checked&per.
:dt.View only&colon. 
:dd.The imported descriptions are shown in the Subject or Comment fields, but
aren't automatically saved in the EAs. If the application is not in 
:link reftype=hd refid=ID@13.Read only mode 
:elink.you can save the imported description in the EAs by clicking on the 
:link reftype=hd refid=ID@10.Save 
:artwork  runin name='F:\Grafica\Images\save.BMP'.
:elink. button in the toolbar or by selecting 
:link reftype=hd refid=ID@21.File->Save attributes 
:elink.from the pop-up menu&per.
:dt.Import to&colon. 
:dd.Sets the default field where imported descriptions are displayed (and
saved). You can override this by selecting a different import target by its
contextual menu&colon. i.e. if you select 
:link reftype=hd refid=ID@23.Edit->Import 
:elink.from the 
:hp1.Subject entry field :ehp1.
pop-up menu descriptions will be imported there&per. 
:hp1.Auto select :ehp1.
lets the program look for the most suitable field&colon. if the description is
longer than the 
:link reftype=hd refid=ID@13.maximum Subject length 
:elink.it will be imported in the 
:hp1.Comment field. :ehp1.
(In the next release it will check for line feed chars too)&per.
:dt.Default import mode&colon. 
:dd.Sets the default source of file descriptions&per.
.br
When :hp1.Automatic :ehp1.it will check for :hp2.4 DOS - 4 OS&slash.2 description
files:ehp2., if it fails, will check if the file is a known archive type and if a suitable
description is in the archive, last if you defined your own import program it
will try to get a description through it&per.
.br
:hp1.Other :ehp1.displays an :hp1.Open file :ehp1.dialog in order to allow you to import any text file&per.
:dt.4 DOS - OS&slash.2 description file&colon. 
:dd.you must specify here the name used by the 
:hp2.4 DOS - 4 OS&slash.2 :ehp2.
for file descriptions&per.
:dt.User defined&colon. 
:dd.If you need to import descriptions from a particular file you could write a
REXX script (I will include some sample in the future releases) or use a
suitable program&per. The description will be imported from a file generated by the
program you defined&per.
:dl tsize=17.
:dt.File to import&colon.
:dd.is the name of the output file created by the user defined program&per.
:dt.Program&colon.
:dd.is the executable name and must include the full path unless the program is
in 
:font facename='Courier' size=12x7.%PATH% 
:font facename=default size=0x0.as defined in CONFIG.SYS
:dt.Parameters&colon.
:dd.specify the parameters you need to pass to the program you defined. Some
special characters are used&colon.
:dl tsize=5 compact.
:dt.%d
:dd.means a temporary directory created by the application. The output file, as
defined in 
:hp1.File to import&colon. :ehp1.
must be generated here unless you specify its full path&per.
:dt.%f
:dd.means the current file including the full path (as displayed in the
application title bar)&per.
:dt.%i
:dd.means
:hp1.File to import&colon.&per.
:ehp1.
:dt.%p
:dd.means the full path of the current file&per.
:dt.%%
:dd.means the percent ("%") char&per.
:edl.
:note.Chars following "%" are case insensitive so "%D" has the same meaning of
"%d"&per.
:edl.
:edl.
:p.

.****************** Import page 2 of 2 *******************
:h2 id=ID@16.Import page 2 of 2
:p.
:artwork  align=center name='F:\Grafica\Images\prefimp2.bmp'.
:p.
:dl tsize=21.
:dt.Archive type&colon. 
:dd.In this box are listed all the archive extensions used by the program to
tell if a file is a 
:hp1.known archive :ehp1.
You can add or remove extensions or edit the respective fields&per. The 
:hp1.Update :ehp1.
, 
:hp1.Add :ehp1.
and 
:hp1.Remove :ehp1.
buttons are enabled as suitable to avoid incorrect user operations&per.
:dt.Update button&colon. 
:dd.Will be enabled as soon as you select an item from the 
:hp1.Archive type list box&per. :ehp1.
It allows you to edit the settings relative to an already listed file extension&per.
:dt.Add button&colon. 
:dd.Allows to add data for a new type of archive file. It is disabled if some
field is empty or the text in 
:hp1.New type&colon. :ehp1.
is already listed.
:dt.Remove button&colon. 
:dd.Will be enabled as soon as you select an item from the 
:hp1.Archive type list box&per. :ehp1.
It allows you to remove an 
:hp1.archive type :ehp1.
from the list&per.
:dt.New type&colon. 
:dd.In this field you must specify the extension of an archive file (for
instance ":font facename='Courier' size=12x7.*&per.rar:font facename=default size=0x0."
or ":font facename='Courier' size=12x7.*&per.arj:font facename=default size=0x0.", etc&per.)&per.
:dt.File to import&colon.
:dd.In this field you must specify the name of the file that will be extracted
from the archive and imported as a file description&per. It should usually be 
:hp2.FILE_ID&per.DIZ:ehp2.
:dt.Program&colon. 
:dd.You should specify here the unarchiver program to use with files whose
extension is specified in 
:hp1.New type&colon.. :ehp1.
You must specify the executable full path unless it is in a directory mentioned
in the CONFIG.SYS  %PATH% statement&per.
:dt.Parameters&colon. 
:dd.These are the parameters needed by the program you specified to extract 
:hp1.File to import&colon. :ehp1.
files from file of type 
:hp1.New type&colon.. :ehp1.
See 
:link reftype=hd refid=ID@15.Import page 1 of 2 
:elink.for conventions about parameters&per.
:edl.
:p.

.****************** Report page 1 of 2 *******************
:h2 id=ID@17.Report page 1 of 2
:p.
:p.
:artwork  align=center name='F:\Grafica\Images\prefrep1.bmp'.
:p.
:p.
:hp2.The following options haven't yet been implemented!
:ehp2.
:dl tsize=25.
:dt.Auto report&colon. 
:dd.Allows to generate a report with all file data and attributes&per. The report
will be showed in a separate window&per. It will be possible to print it and save it
to file&per. If this checkbox is selected, usually, both the main program window and
the report window will be displayed&per. If this checkbox is unchecked it will
always be possible to generate a Report by selecting the button in the toolbar
of the main window or by selecting from the menu
:link reftype=hd refid=ID@21.File->Report:elink.&per.
:dt.Only directory&colon.
:dd.The report will be generated only if the argument is a directory&per.
:dt.Show&colon. 
:dd.The report window will be shown besides the application main window&per.
:dt.Hide&colon. 
:dd.The report will be generated but won't be visible&per.
:dt.Show only report&colon. 
:dd.Only the report window will be visible. It will be possible to generate
directory&slash.file report by dragging file and directories on the report window
title bar&per.
:dt.Selected files&colon. 
:dd.Only the selected files will be included in the report&per.
:dt.All files&colon. 
:dd.All files in the current directory will be included in the report&per.
:dt.Full Tree&colon. 
:dd.All files in the current directory and, recursively, in all its
subdirectories will be included in the report&per.
:edl.
:p.

.****************** Report page 2 of 2 *******************
:h2 id=ID@18.Report page 2 of 2
:p.
:artwork  align=center name='F:\Grafica\Images\prefrep2.bmp'.
:p.
:p.
:hp2.The following options haven't yet been implemented!
:ehp2.
:dl tsize=15.
:dt.Format&colon. 
:dd.he report will be formatted by the program you specify here (it could just
be a 
:hp2.REXX :ehp2.
script). This way you could easily create 
:hp2.DESCRIPT&per.ION :ehp2.
or 
:hp2.FILE&per.BBS :ehp2.
files from subjects and comments EAs&per.
:dt.Auto save&colon. 
:dd.Generated (and formatted) reports will be saved automatically in a file you
specify in the current directory or any other specified directory&per.
:edl.
:p.

.****************** Find page *******************
:h2 id=ID@19.Find page
:p.
:artwork  align=center name='F:\Grafica\Images\preffind.bmp'.
:p.
:p.It (
:hp2.doesn't work yet!:ehp2.) will allow to specify an external program for the find function&per.
:p.

.****************** Menu *******************
:h1 id=ID@20.Menu
:p.
There are two pop-up menus&per. Clicking with mouse button 2 on the edit
controls (:hp1.Subject entryfield :ehp1.and :hp1.Keys&slash.Comments fields :ehp1.)
you will get the most complete menu&per. The menu you'll get by clicking elsewhere
will not have the Edit submenu&per.
:ul compact.
:li.
:link reftype=hd refid=ID@21.Submenu File
:elink.
:li.
:link reftype=hd refid=ID@22.Submenu Options
:elink.
:li.
:link reftype=hd refid=ID@23.Submenu Edit
:elink.
:li.
:link reftype=hd refid=ID@24.Submenu Help
:elink.
:eul.

.****************** Submenu File *******************
:h2 id=ID@21.Submenu File
:p.
:artwork  align=center name='F:\Grafica\Images\menufile.bmp'.
:p.
:dl tsize=22.
:dt.Select&colon. 
:dd.
:dl tsize=14 compact.
:dt.Browse&colon. 
:dd.Show&slash.hide drive&slash.directory&slash.file selection window&per.
:dt.Select all&colon. 
:dd.Selects all files in the current directory&per.
:dt.Deselect all&colon. 
:dd.Deselect all files&per.
:dt.Mask&colon.
:dd.Allows to specify a selection mask throuh the Mask selection dialog&per. See
Mask selection section for more details&per.
:edl.
:dt.Refresh&colon. 
:dd.Refresh the contents of the drive&slash.directory&slash.file selection window&per.
:dt.Save attributes&colon. 
:dd.Saves the current attributes&per.
:dt.Report&colon. 
:dd.See 
:link reftype=hd refid=ID@17.Report page 1 of 2 
:elink.and 
:link reftype=hd refid=ID@18.page 2 of 2:elink.&per.
:dt.Find&colon. 
:dd.Not yet implemented&per.
:dt.Exit&colon. 
:dd.Terminate the application&per.
:edl.

.****************** Submenu Options *******************
:h2 id=ID@22.Submenu Options
:p.
:artwork  align=center name='F:\Grafica\Images\menuopt.bmp'.
:p.
:dl tsize=27.
:dt.General Preferences&colon. 
:dd.see 
:link reftype=hd refid=ID@11.Features and settings&per.
:elink.
:dt.Font&colon. 
:dd.see Features ans settings - 
:link reftype=hd refid=ID@13.General page&per.
:elink.
:dt.Read only mode&colon. 
:dd.see Features ans settings - 
:link reftype=hd refid=ID@13.General page&per.
:elink.
:edl.

.****************** Submenu Edit *******************
:h2 id=ID@23.Submenu Edit
:p.
:artwork  align=center name='F:\Grafica\Images\menuedit.bmp'.
:p.
:dl tsize=22.
:dt.Undo&colon. 
:dd.work as usual (the second Undo works like Redo)&per. 
:dt.Cut-Copy-Paste&colon. 
:dd.work as usual. 
:dt.Clear&colon. 
:dd.delete selected text&per. 
:dt.Import&colon. 
:dd.will import file description from the selected source to the target that
originated the pop-up menu&per. If there are multiple file selected and the
application is not in 
:link reftype=hd refid=ID@13.Read only 
:elink.or 
:link reftype=hd refid=ID@15.View only mode
:elink., file descriptions will automatically be saved in the EAs of all
selected files&per.
.br
For instance, if you have a directory with archived files you
downloaded from internet, you can automatically import all 
:hp2.file_id&per.diz :ehp2.
descriptions (if available) in the archives EAs by selecting all files (from the
pop-up menu&colon. 
:link reftype=hd refid=ID@21.File->Select->Select all 
:elink.) and then selecting 
:hp1.Edit->Import->File_id&per.diz :ehp1.
from the 
:hp1.Subject  :ehp1.
or 
:hp1.Comment  :ehp1.
pop-up menu&per. 
:edl.
:p.

.****************** Submenu Help *******************
:h2 id=ID@24.Submenu Help
:p.
:p.
:hp2.not yet implemented!
:ehp2.

.****************** Mask selection dialog *******************
:h1 id=ID@25.Mask selection dialog
:p.
:artwork  align=center name='F:\Grafica\Images\masksel.bmp'.
:p.
:p.You can select multiple files by this dialog&per. You can either enter the file
name in the entryfield part of the combo box or select from the list box the
file specifics that suits your need&per.
:p.
Items can be added or deleted to the list box through the :hp1.Store :ehp1.
and :hp1.Delete :ehp1.buttons&per. Data are stored in the application INI file&per.
:p.Clicking on OK will confirm the file selection&per. Clicking on Cancel or closing
the dialog won't perform any action in the file list box&per.
:p.

.****************** Multiple File Save dialog *******************
:h1 id=ID@26.Multiple File Save dialog
:p.
:artwork  align=center name='F:\Grafica\Images\multisave.bmp'.
:p.
:p.This dialog is shown when a 
:hp1.save attributes :ehp1.
action is performed on multiple files&per.
:p.The dialog shows the data of the first file selected in the list box and
allows to select which attributes must be set for all the selected files&per.
:p.For instance, by checking 
:hp1.Archive :ehp1.
, 
:hp1.Hidden :ehp1.
, 
:hp1.Subject :ehp1.
and date in the 
:hp1.Last changed date time group box :ehp1.
you will set all the selected files attributes to the displayed values, while
the remaining attributes will be unchanged&per.
:p.

.****************** Known problems and limitations *******************
:h1 id=ID@27.Known problems and limitations
:p.
:ol.
:li.I've used standard list box controls so there could be problems if you have
large amounts of files in your folders (32765 files with OS&slash.2 Warp 3 or 4 - I'm
not sure about OS&slash.2 2&per.x)&per.
:li.The program still does all work in a unique thread, so some operation like
modifying attributes of a large number of file, will not allow you to interact
with the system until the end of it&per.
:li.The program has been packed in a format not compatible with OS&slash.2 V&per. 2&per.x, if
you need it on an OS&slash.2 2&per.x machine :link reftype=hd refid=ID@29.send me an email 
:elink.or unpack it with LXLITE&per.
.br
LXLITE is a free utility by Andrew Zabolotny&per.
.br
You can download it from&colon.
ftp&colon.&slash.&slash.hobbes&per.nmsu&per.edu&slash.pub&slash.os2&slash.util&slash.archiver&slash.lxlt121&per.zip&per.
:li.Some controls are not resized correctly when you use a proportional font&per.
Use a monospaced font like System VIO or courier!
:li.The status bar doesn't work yet for displaying the result of attribute
saving, importing, etc&per. operations&per. So does the 
:hp1.Open log window 
:artwork  runin name='F:\Grafica\Images\log.BMP'. :ehp1.
button&per.
:eol.
:p.

.****************** Future releases *******************
:h1 id=ID@28.Future releases
:p.The next release will be fully multithreaded and I'll try to add an 
:hp1.Attribute  :ehp1.
item to the contextual menu of every file object&per.
:p.
I will implement the still missing features as soon as possible&per.

.****************** About the author *******************
:h1 id=ID@29.About the author
:p.
For any suggestion or bug report write to me&colon.
:p.
Alessandro Cantatore
:ul.
:li.email
:ul compact.
:li.alexcant@tin.it
:li.alex.cant@iol.it
:eul.
:li.fidonet&colon.  2&colon.335&colon.705&slash.2
:eul.
:euserdoc.