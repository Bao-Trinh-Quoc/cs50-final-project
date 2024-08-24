#include "edito.h"



int main(int argc, char *argv[])
{
    enableRawMode();
    initEditor();

    if (argc >= 2)
    {
        editorOpen(argv[1]);
    }

    editorSetStatusMessage("Quit: Ctrl-q | Save: Ctrl-s");

    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
