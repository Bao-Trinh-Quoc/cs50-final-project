#include "edito.h"

void editorRefreshScreen()
{
    write(STDIN_FILENO, "\x1b[2J", 4);
    write(STDIN_FILENO, "\x1b[H", 3);

    editorDrawRows();

    write(STDIN_FILENO, "\x1b[H", 3);
}

void editorDrawRows()
{
    for (int i = 0; i < E.screenrows; i++)
    {
        write(STDIN_FILENO, "*\r\n", 3);
    }
}