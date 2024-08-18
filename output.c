#include "edito.h"

void editorRefreshScreen()
{
    struct abuf ab = ABUF_INIT;

    // Hide the cursor when repaiting the screen
    abAppend(&ab, "\x1b[?25L", 6);
    // Clear the screen
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);
    // Reposition the cursor
    abAppend(&ab, "\x1b[H", 3);
    abAppend(&ab, "\x1b[?25H", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void editorDrawRows(struct abuf *ab)
{
    for (int i = 0; i < E.screenrows; i++)
    {   
        // Why E.screenrows / 3?
        if (i == E.screenrows / 3) 
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

        abAppend(ab, "\x1b[K]", 3);

        if (i < E.screenrows - 1)
        {
            abAppend(ab, "\r\n", 2);
        }
    }
}