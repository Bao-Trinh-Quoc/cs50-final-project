#include "edito.h"

void editorProcessKeypress()
{
    int c = editorReadKey();

    switch (c)
    {
        case CTRL_KEY('q'):
            write(STDIN_FILENO, "\x1b[2J", 4);
            write(STDIN_FILENO, "\x1b[H", 3);
            exit(0);
            break;
        // Make the cursor to the left of the screen
        case HOME_KEY:
            E.cx = 0;
            break;
        // Make the cursor to the right of the screen
        case END_KEY:
            E.cx = E.screencols - 1;
            break;
        // move the cursor to top or bottom of the screen when pressing page up or page down
        case PAGE_UP:
        case PAGE_DOWN:
            {
                int times = E.screenrows;   
                while (times--)
                    editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;  
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorMoveCursor(c);
            break;
    }
}

void editorMoveCursor(int key)
{
    switch (key)
    {
        case ARROW_UP:
            if (E.cy != 0)
                E.cy--;
            break;
        case ARROW_DOWN:
            if (E.cy != E.screenrows -1)
                E.cy++;
            break;
        case ARROW_LEFT:
            if (E.cx != 0)
                E.cx--;
            break;
        case ARROW_RIGHT:
            if (E.cx != E.screencols - 1)
                E.cx++;
            break;
    }
}