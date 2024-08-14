#ifndef EDITOR_H
#define EDITOR_H

/*** Includes  ***/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** Defines ***/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
char editorReadKey();
void die(const char *s);

/*** Input ****/

void editorProcessKeypress();

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();

#endif