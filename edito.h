#ifndef EDITOR_H
#define EDITOR_H

/*** Includes  ***/

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <ctype.h>
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
    int size;
    int rsize;
    char *chars;
    char *render;
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
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct termios orig_termios;
};

extern struct editorConfig E;

/*** Defines ***/

#define EDITO_VERSION "0.0.1"
#define EDITO_TAB_STOP 8

#define CTRL_KEY(k) ((k) & 0x1f)

enum editorKey {
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

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();
void editorScroll();
void editorDrawStatusBar(struct abuf *ab);
void editorSetStatusMessage(const char *fmt, ...);
void editorDrawMessageBar(struct abuf *ab);

/*** File I/O ***/

void editorOpen();

/*** Row operations ****/

void editorAppendRow(char *s, size_t len);  
void editorUpdateRow(erow *row);
int editorRowCxToRx(erow *row, int cx);
void editorRowInsertChar(erow *row, int at, int c);

/*** Editor operations ****/
void editorInsertChar(int c);

/*** Init ***/

void initEditor(); 

#endif