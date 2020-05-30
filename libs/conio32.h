/***************************************************************************\
*                                                                           *
*    Name: test_conio32.cpp										            *
*          Definiert den Einstiegspunkt für die Konsolenanwendung.          *
*    Ver.: 3.00.00                                                          *
*    Purpose: Test Library: conio32.lib                                     *
*                                                                           *
*    by:                                                                    *
*      Name:    Daniel Weiler                                               *
*      E-Mail:  mail-2-dw@web.de                                            *
*                                                                           *
*    Date:                                                                  *
*      03/2000                                                              *
*    Update:                                                                *
*      03/2000                                                              *
*                                                                           *
/***************************************************************************\
*                                                                           *
*    Erweiterung: Einbau von bioskey();                                     *
*    Ver.:        4.00.00                                                   *
*    Datum:       17/MAR/2001                                               *
*    By:          Johannes Wohlrab                                          *
*                                                                           *
*    E-Mail:               Johannes.Wohlrab@hs-esslingen.de                 *
*    Homepage im Internet:                                                  *
*    http://www.hs-esslingen.de/de/mitarbeiter/johannes-wohlrab.html        *
*                                                                           *
*****************************************************************************
*    Modifikation: libs enthalten KEINEN Verweis mehr                       *
*                  auf LIBC und LIBCD                                       *
*    implemented:  Die Settings des project "conio32" (NICHT des            *
*                  project test_conio32!) enthalten jetzt den               *
*                  Compiler-Switch /Zl , was bewirkt:                       *
*                  This option omits the default library name from          *
*                  the .OBJ file. By default, CL puts the name of           *
*                  the library into the .OBJ file to direct the             *
*                  linker to the correct library. You can use /Zl           *
*                  to compile .OBJ files you plan to put into a             *
*                  library.                                                 *
*    Erklärung:    Unter z.B. .NET 2008 heißen die Standard-                *
*                  Bibliotheken anders als LIBCD bzw. LIBC. Sind            *
*                  die Verweise in den Bibliotheken                         *
*                  conio32_debug.lib bzw. conio32_release.lib               *
*                  enthalten, produziert das unter .NET 2008 einen          *
*                  LINKER-Error LNK1104: Datei "LIBCD.lib" kann             *
*                  nicht geöffnet werden. Mit dem Compiler-Switch           *
*                  /Zl sind die Verweise gar nicht enthalten und            *
*                  der Fehler wird von vornherein vermieden.                *
*                  Alternative wäre eine #pragma-Anweisung unter            *
*                  .Net 2008:                                               *
*                  #ifdef _DEBUG                                            *
*                   #pragma comment(linker, "/NODEFAULTLIB:libcd")          *
*                  #else                                                    *
*                   #pragma comment(linker, "/NODEFAULTLIB:libc")           *
*                  #endif                                                   *
*****************************************************************************
*    Hinweise zum VS 2010 (27.01.2012, wh):                                 *
*    Wichtig für das test_conio32 Projekt ist:                              *
*	  1) Die Abhängigkeit des Projektes vom Projekt conio32                 *
*       einstellen.                                                         *
*       Dazu: im Projektmappen-Explorer auf die Projektmappe                *
*       rechtsklicken und im Kontextmenü Projektabhängigkeiten              *
*       anklicken.                                                          *
*   2)  Im Hauptmenü unter Projekt bei den test_conio32-Eigen-              *
*       schaftenseiten unter "Allgemeine Eigenschaften" ->                  *
*       "Framework und Verweise" auf conio32 verweisen, weil                *
*       sonst die Bibliothek conio32.lib zwar wegen 1) erzeugt,             *
*       aber  nicht durchsucht wird.                                        *   
*   3)  Im Projektmappen-Explorer auf die Projektmappe                      *
*       rechtsklicken und im Kontextmenü "Startprojekte"                    *
*       anklicken. Das test_conio32 Projekt als Startprojekt                *
*       festlegen (man kann ja keine lib starten ;-)) ).                    *
*   4)  Im Projektmappenexplorer das Projekt "conio32" anklicken.           *
*       Danach im Haupotmenü unter "Projekt" die "Eigenschaften" aus-       *
*       wählen. Hier unter C/C++ "Befehlszeile" die zusätzliche             *
*       Compileroption /Zl eintragen (s.o. unter VS 2008).                  *
*   5)  /Z7    und    /Ylsymbol                                             *
*       Generiert eine OBJ-Datei mit vollständigen symbolischen Debug-      *
*       informationen zur Verwendung mit dem Debugger. Zu den symbolischen  *
*       Debuginformationen gehören die Namen und Typen von Variablen sowie  *
*       Funktionen und Zeilennummern. Es wird keine PDB-Datei generiert.    *
*       Für die Verteiler von Drittanbieter-Bibliotheken ist es von         *
*       Vorteil, keine PDB-Datei zu haben. Die OBJ-Dateien für die vor-     *
*       kompilierten Header sind jedoch während der Verknüpfungsphase und   *
*       für das Debuggen erforderlich. Wenn die PCH-Objektdateien nur       *
*       Typinformationen (und keinen Code) enthalten, müssen Sie außerdem   *
*       mit /Ylsymbol (PCH-Verweis für Debugbibliothek einfügen)            *
*       kompilieren.                                                        *
*       Bemerkung, weil /Z7 verendet wird:                                                                    *
*       "/Gm" erfordert "/Zi oder /ZI"; Option wird ignoriert.              *
*                                                                           *
*   Compileroptionen in alphabetischer Reihenfolge:                         *
*   http://msdn.microsoft.com/de-de/library/fwkeyyhe.aspx                   *
*                                                                           *
/***************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//
//  Include Watch
//

    #ifndef __alrdincl_conio32_h
    #define __alrdincl_conio32_h



///////////////////////////////////////////////////////////////////////////////
//
//  Includes
//

    #include <windows.h>
    #include <stdio.h>    // wg. perror() eingefügt 18.03.01 Wh.



///////////////////////////////////////////////////////////////////////////////
//
//  Symbolic Constants 
//

    /* used by setcursortype */
    #define NOCURSOR 0
    #define NORMALCURSOR 10
    #define SOLIDCURSOR 99


    /* used by textcolor and textbackground */
    #define BLACK                 0
    #define BLUE                  1
    #define GREEN                 2
    #define CYAN                  3
    #define RED                   4
    #define MAGENTA               5
    #define BROWN                 6
    #define LIGHTGRAY             7
    #define DARKGRAY              8
    #define LIGHTBLUE             9
    #define LIGHTGREEN           10
    #define LIGHTCYAN            11
    #define LIGHTRED             12
    #define LIGHTMAGENTA	     13
    #define YELLOW	             14
    #define WHITE	             15



///////////////////////////////////////////////////////////////////////////////
//
//  Makros
//

    #define SETCONSOLETITLE(TITLE) (int) SetConsoleTitle (TITLE)



///////////////////////////////////////////////////////////////////////////////
//
//  struct text_info
//

    struct text_info {
        short screenheight;   /* text screen's height */
        short screenwidth;    /* text screen's width */
        unsigned char curx;           /* x-coordinate in current window */
        unsigned char cury;           /* y-coordinate in current window */
    };



///////////////////////////////////////////////////////////////////////////////
//
//  con32-Functions (Declaration)
//

    unsigned short int bioskey(int cmd);
       /* The function unsigned short int bioskey(int cmd);
        *
        * bioskey(0) returns the key that is waiting:  low byte ==ASCII-code
        *                                              high byte==SCAN-code
        *                                      (waits until key is pressed!)
        * bioskey(1) returns 0 until a key is pressed; if one is pressed:
        *                                              low byte ==ASCII-code
        *                                              high byte==SCAN-code
        *                                           (key remains in buffer!)
        * use bioskey(2) to determine  - if shift keys are presently pressed
        *                              - or are presently activ:
        *    shiftRIGHT ==0x01;    (bit 0)    presently pressed!
        *    shiftLEFT  ==0x02;    (bit 1)    presently pressed!
        *         CTRL  ==0x04;    (bit 2)    presently pressed!
        *         ALT   ==0x08;    (bit 3)    presently pressed!
        *         SCROLL==0x10;    (bit 4)    presently activ!
        *         NUM   ==0x20;    (bit 5)    presently activ!
        *         CAPS  ==0x40;    (bit 6)    presently activ!
        *         INS   ==0x80;    (bit 7)    presently activ!
        */    
    
    void clrscr         (void);         // Clears the text window and places 
                                        // the cursor in the upper left-hand 
                                        // corner (at position 1,1).

    struct text_info * gettextinfo      \
                  (struct text_info *); // Fills in the text_info structure 
                                        // with current text mode information.

    int  gotoxy         (int x, int y); // Positions cursor in text window. If
                                        // the coordinates are in any way 
                                        // invalid the call to gotoxy is ignored.
                                        // If the function succeeds, the return 
                                        // value is nonzero.If the function 
                                        // fails, the return value is zero.

    int  setcursortype  (int type);     // Selects cursor appearance. Sets the 
                                        // cursor type to
                                        //  NOCURSOR     Turns off the cursor
                                        //  NORMALCURSOR Normal underscore cursor
                                        //  SOLIDCURSOR  Solid block cursor
                                        // If the function succeeds, the return 
                                        // value is nonzero.If the function 
                                        // fails, the return value is zero.

    int  setconsoletitle(char *);       // Sets the consoletitle.
                                        // If the function succeeds, the return 
                                        // value is nonzero.If the function 
                                        // fails, the return value is zero.

    void textbackground (int);          // Selects new text background color.
                                        // Symbolic constant    Numeric value
                                        //  BLACK                 0
                                        //  BLUE                  1
                                        //  GREEN                 2
                                        //  CYAN                  3
                                        //  RED                   4
                                        //  MAGENTA               5
                                        //  BROWN                 6
                                        //  LIGHTGRAY             7
                                        //  DARKGRAY              8
                                        //  LIGHTBLUE             9
                                        //  LIGHTGREEN           10
                                        //  LIGHTCYAN            11
                                        //  LIGHTRED             12
                                        //  LIGHTMAGENTA	     13
                                        //  YELLOW	             14
                                        //  WHITE	             15

    void textcolor      (int);          // Selects new character color in text 
                                        // mode.
                                        // Symbolic constant    Numeric value
                                        //  BLACK                 0
                                        //  BLUE                  1
                                        //  GREEN                 2
                                        //  CYAN                  3
                                        //  RED                   4
                                        //  MAGENTA               5
                                        //  BROWN                 6
                                        //  LIGHTGRAY             7
                                        //  DARKGRAY              8
                                        //  LIGHTBLUE             9
                                        //  LIGHTGREEN           10
                                        //  LIGHTCYAN            11
                                        //  LIGHTRED             12
                                        //  LIGHTMAGENTA	     13
                                        //  YELLOW	             14
                                        //  WHITE	             15


    int  wherex         (void);         // Returns the x-coordinate of the 
                                        // current cursor position,an integer in
                                        // the range 1 to the number of columns 
                                        // in the current mode.

    int  wherey         (void);         // Returns the x-coordinate of the 
                                        // current cursor position,an integer in
                                        // the range 1 to the number of columns
                                        // in the current mode.



///////////////////////////////////////////////////////////////////////////////
//
//  Class con32 (Declaration)
//

    class con32  {

        public:
            con32                   (void);

            void clrscr             (void);
            text_info * gettextinfo  (text_info *);
            int  gotoxy             (int x, int y);
            int  setcursortype      (int size);
            int  setconsoletitle    (char *);
            void textbackground     (int);
            void textcolor          (int);
            int  wherex             (void);
            int  wherey             (void);

        private:    
            HANDLE hout;
            CONSOLE_SCREEN_BUFFER_INFO CSBInfo;
    };



///////////////////////////////////////////////////////////////////////////////
//
//  Include Watch
//

    #endif // ifndef __alrdincl_conio32_h





/* eof:conio32.cpp */