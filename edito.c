/*** Includes  ***/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** Defines ***/
#define CTRL_KEY(k) ((k) & 0x1f) 


/*** Data  ***/

struct termios orig_termios;

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
char editorReadKey();       // wait for one key press then return it
void die(const char *s);    // Error handling 

/*** Input ****/

void editorProcessKeypress();   // wait for a key press, then handles it

/*** Output ****/

void editorRefreshScreen();
void editorDrawRows();
/*** init  ***/

int main()
{
    enableRawMode();

    while (1)
    {
		editorRefreshScreen();
    	editorProcessKeypress();
    }
    
    return 0;
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    {
        die("tcgetattr");
    }
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    // ICANON allows to turn off canonical mode --> read byte by byte
    // ICRNL I:input flag, CR: carriage return, NL: newline
    raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON); // Disable Ctrl-Q and Ctrl-S
    // ISIG: turn off Ctrl-C and Ctrl-Z signals
    // IEXTEN: turn off Ctrl-V
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);    
    // Output flags - Turn off output processing
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);

    // min num of bytes of input needed before read() return
    raw.c_cc[VMIN] = 0;
    // max time wait before read() returns
    raw.c_cc[VTIME] = 1; // ran in tenth of a second

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    {
        die("tcsetattr");
    }
}
void disableRawMode() 
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    {
        die("tcsetattr");
    }
}
void die(const char *s)
{
	write(STDIN_FILENO, "\x1b[2J", 4);
	write(STDIN_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

char editorReadKey() 
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }
    
    return c;
}

void editorProcessKeypress()
{
    char c = editorReadKey();

    switch (c) 
    {
        case CTRL_KEY('q'):
			write(STDIN_FILENO, "\x1b[2J", 4);
			write(STDIN_FILENO, "\x1b[H", 3);
	        exit(0);
            break;
    }
}

void editorRefreshScreen() 
{
    write(STDIN_FILENO, "\x1b[2J", 4);
	write(STDIN_FILENO, "\x1b[H", 3);

	editorDrawRows();

	write(STDIN_FILENO, "\x1b[H", 3);
}

void editorDrawRows() 
{
	// 30 is just some arbitrary number
	for (int i = 0; i < 30; i++)
	{
		write(STDIN_FILENO, "*\r\n", 3);
	}
}