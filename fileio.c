#include "edito.h"

void editorOpen(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        die("fopen");

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    linelen = getline(&line, &linecap, fp);

    if (linelen != -1)
    {
        while ((linelen = getline(&line, &linecap, fp)) != -1)
        {
            while (linelen > 0 && (line[linelen-1] == '\n' || line[linelen-1] == '\r'))
                linelen--;
            editorAppendRow(line, linelen);
        }
    }
    free(line);
    fclose(fp);
}

void editorAppendRow(char *s, size_t len)
{
    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));


    int at = E.numrows;
    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';
    E.numrows ++;
}