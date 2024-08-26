#ifndef EDITOR_H
#define EDITOR_H

/*** Includes  ***/

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/*** Data ****/

typedef struct erow 
{
    int idx;
    int size;
    int rsize;
    char *chars;
    char *render;
    unsigned char *hl;
    int hl_open_comment;
} erow;

struct editorConfig 
{
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    int dirty;
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct editorSyntax *syntax;
    struct termios orig_termios;
};

extern struct editorConfig E;

struct editorSyntax {
    char *filetype;
    char **filematch;
    char **keywords;
    char *singleline_comment_start;
    char *multiline_comment_start;
    char *multiline_comment_end;
    int flags;
};


/*** Defines ***/

#define EDITO_VERSION "1.0.0"
#define EDITO_TAB_STOP 8
#define EDITO_QUIT_TIMES 1
#define CTRL_KEY(k) ((k) & 0x1f)
#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

enum editorKey {
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

enum editorHighlight 
{
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING, 
    HL_NUMBER,
    HL_MATCH
};

/*** filetypes ****/

extern char *C_HL_extensions[];
extern struct editorSyntax HLDB[];

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
int editorReadKey();
void die(const char *s);
int getWindowSize(int *rows, int *cols);
int getCursorPosition(int *row, int *cols);

/***  append buffer****/
struct abuf
{
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);

/*** Input ****/

void editorProcessKeypress();
void editorMoveCursor(int key);   
char *editorPrompt(char *prompt, void(*callback)(char *, int));

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();
void editorScroll();
void editorDrawStatusBar(struct abuf *ab);
void editorSetStatusMessage(const char *fmt, ...);
void editorDrawMessageBar(struct abuf *ab);

/*** File I/O ***/

void editorOpen();
char *editorRowsToString(int *buflen);
void editorSave();

/*** Row operations ****/

void editorInsertRow(int at, char *s, size_t len);  
void editorUpdateRow(erow *row);
int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowDelChar(erow *row, int at);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowAppendString(erow *row, char *s, size_t len);

/*** Editor operations ****/

void editorInsertChar(int c);
void editorDelChar();
void editorInsertNewline();

/*** Find ***/

void editorFind();
void editorFindCallback(char *query, int key);

/*** Syntax highlighting ***/

void editorUpdateSyntax(erow *row);
int editorSyntaxToColor(int hl);
int is_separator(int c);
void editorSelectSyntaxHighlight();

/*** Init ***/

void initEditor(); 

#endif