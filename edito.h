#ifndef EDITOR_H
#define EDITOR_H

/*** Includes  ***/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** Data ****/

struct editorConfig 
{
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

extern struct editorConfig E;

/*** Defines ***/

#define EDITO_VERSION "0.0.1"

#define CTRL_KEY(k) ((k) & 0x1f)

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
char editorReadKey();
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

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();

/*** Init ***/
void initEditor(); 

#endif