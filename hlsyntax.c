#include "edito.h"

/*** filetypes ****/

char *C_HL_extensions[] = { ".c", ".h", ".cpp", NULL };
struct editorSyntax HLDB[] = {
  {
    "c",
    C_HL_extensions,
    HL_HIGHLIGHT_NUMBERS
  },
};

void editorUpdateSyntax(erow *row)
{
    row->hl = realloc(row->hl, row->rsize);
    memset(row->hl, HL_NORMAL, row->rsize);

    if (E.syntax == NULL)
        return;

    int prev_sep = 1;

    int i = 0;
    while (i < row->rsize)  
    {
        char c = row->render[i];
        unsigned char prev_hl = (i > 0) ? row->hl[i-1] : HL_NORMAL;
        
        if (E.syntax->flags & HL_HIGHLIGHT_NUMBERS) {
        if ((isdigit(c) && (prev_sep || prev_hl == HL_NUMBER)) ||
            (c == '.' && prev_hl == HL_NUMBER)) {
            row->hl[i] = HL_NUMBER;
            i++;
            prev_sep = 0;
            continue;
        }
        }
        
        prev_sep = is_separator(c);
        i++;
    }
}

int editorSyntaxToColor(int hl)
{
    switch(hl)
    {
        case HL_NUMBER: return 91;
        case HL_MATCH: return 93;
        default: return 37;
    }
}

int is_separator(int c) {
  return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != NULL;
}

void editorSelectSyntaxHighlight() {
    E.syntax = NULL;
    if (E.filename == NULL) return;
    char *ext = strrchr(E.filename, '.');
    for (unsigned int j = 0; j < HLDB_ENTRIES; j++) 
    {
        struct editorSyntax *s = &HLDB[j];
        unsigned int i = 0;
        while (s->filematch[i]) 
        {
        int is_ext = (s->filematch[i][0] == '.');
        if ((is_ext && ext && !strcmp(ext, s->filematch[i])) ||
            (!is_ext && strstr(E.filename, s->filematch[i]))) 
        {
            E.syntax = s;
            int filerow;
            for (filerow = 0; filerow < E.numrows; filerow++) {
            editorUpdateSyntax(&E.row[filerow]);
            }
    
            return;
        }
            i++;
        }
    }
}