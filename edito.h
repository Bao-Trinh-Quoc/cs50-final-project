#ifndef EDITOR_H
#define EDITOR_H

/*** Includes  ***/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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

#define CTRL_KEY(k) ((k) & 0x1f)

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
char editorReadKey();
void die(const char *s);
int getWindowSize(int *rows, int *cols);

/*** Input ****/

void editorProcessKeypress();

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();

/*** Init ***/
void initEditor(); 

#endif