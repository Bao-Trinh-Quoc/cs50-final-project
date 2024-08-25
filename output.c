#include "edito.h"

void editorRefreshScreen()
{
    struct abuf ab = ABUF_INIT;

    // Hide the cursor when repaiting the screen
    abAppend(&ab, "\x1b[?25L", 6);
    // Clear the screen
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);
    editorDrawStatusBar(&ab);
    editorDrawMessageBar(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowoff) + 1, (E.rx - E.coloff) + 1);
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25H", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void editorDrawRows(struct abuf *ab)
{
    editorScroll();

    for (int i = 0; i < E.screenrows; i++)
    {   
        int filerow = i + E.rowoff;
        if (filerow >= E.numrows)
        {
            // Why E.screenrows / 3?
            if (i == E.screenrows / 3 && E.numrows == 0) 
            {
                char welcome[80];
                int welcomelen = snprintf(welcome, sizeof(welcome), "Edito editor -- version %s by Cloudy ~_~", EDITO_VERSION);
                if (welcomelen > E.screencols)
                {
                    welcomelen = E.screencols;
                }
                int padding = (E.screencols - welcomelen) / 2;
                if (padding)
                {
                    abAppend(ab, "*", 1);
                    padding--;
                }
                while (padding--)
                {
                    abAppend(ab, " ", 1);
                }
                abAppend(ab, welcome, welcomelen);
            }
            else
            {
                abAppend(ab, "*", 1);
            }
        } 
        else
        {
            int len = E.row[filerow].rsize - E.coloff;
            if (len < 0) len = 0;
            if (len > E.screencols) len = E.screencols;
            char *c = &E.row[filerow].render[E.coloff];
            int j;
            for (j = 0; j < len; j++)
            {
                if (isdigit(c[j]))
                {
                    abAppend(ab, "\x1b[93m", 5);
                    abAppend(ab, &c[j], 1);
                    abAppend(ab, "\x1b[39m", 5);
                }
                else 
                {
                    abAppend(ab, &c[j], 1);
                }
            }
        }
    
        abAppend(ab, "\x1b[K]", 3);
        abAppend(ab, "\r\n", 2);
    }
}

void editorScroll()
{
    E.rx = 0;
    if (E.cy < E.numrows)
    {
        E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
    }

    if (E.cy < E.rowoff)
    {
        E.rowoff = E.cy;
    }

    if (E.cy >= E.rowoff + E.screenrows)
    {
        E.rowoff = E.cy - E.screenrows + 1;
    }

    if (E.rx < E.coloff) 
    {
        E.coloff = E.rx;
    }

    if (E.rx >= E.coloff + E.screencols) 
    {
        E.coloff = E.rx - E.screencols + 1;
    }
}

void editorDrawStatusBar(struct abuf *ab)
{
    abAppend(ab, "\x1b[7m", 4);
    char status[80], rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines %s", 
    E.filename ? E.filename : "<No Name>", E.numrows,
    E.dirty ? "<modified>" : "");
    int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", E.cy+1, E.numrows);
    if (len > E.screencols)
        len = E.screencols;
    abAppend(ab, status, len);
    while (len < E.screencols)
    {
        if (E.screencols - len == rlen)
        {
            abAppend(ab, rstatus, rlen);
            break;
        }
        else 
        {
            abAppend(ab, " ", 1);
            len++;
        }
    }
    abAppend(ab, "\x1b[m", 3);
    abAppend(ab, "\r\n", 2);
}

void editorSetStatusMessage(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
    va_end(ap);
    E.statusmsg_time = time(NULL);
}

void editorDrawMessageBar(struct abuf *ab)
{
    abAppend(ab, "\x1b[K", 3);
    int msglen = strlen(E.statusmsg);
    if (msglen > E.screencols) 
        msglen = E.screencols;
    if (msglen && time(NULL) - E.statusmsg_time < 5)
        abAppend(ab, E.statusmsg, msglen);
}