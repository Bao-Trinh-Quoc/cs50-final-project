/*** Includes  ***/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** Data  ***/

struct termios orig_termios;

/*** Terminal  ***/

void enableRawMode();
void disableRawMode();
void die(const char *s); // Error handling 

/*** init  ***/

int main()
{
    enableRawMode();

    while (1)
    {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
        {
            die("read");
        }
        if (iscntrl(c)) 
        {
            printf("%d\r\n", c);
        }
        else 
        {
            printf("%d ('%c')\r\n", c, c);
        }
        // type q to quit
        if (c == 'q')
        {
            break;
        }
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
    perror(s);
    exit(1);
}
