# EDITO --- A Simple Text Editor in Command Line
## Description:
Edito is a simple text editor that can be used to view and edit text files in the terminal. It is written in C and uses only the standard library with no dependencies. It uses fairly standard VT100(and similar terminals) escape sequences.<br>

It implements all the **basic features you would expect in a minimal text editor**. Other features include:
- Syntax highlighting for C and C++.
- A search feature.
- Many more features to come...

**This project is heavily inspired by [kilo editor](https://github.com/antirez/kilo) and [Paige Ruten](https://viewsourcecode.org/snaptoken/kilo/).**

## Video Demo:  <URL HERE>
## Prerequisites:
To run the program, you need to have the following installed on your system:
- **A C compiler** (gcc, clang, etc.) for compiling the source code.
- **make** utility for building the project.
- A terminal to run the program.
- A git client to clone the repository.
## Installation:
(**Note:** The following instructions are for Linux systems. The program should work on Windows and MacOS as well, but the installation process may vary.)
Make sure you have the git client installed by using the following command:
```bash
$ git --version
```
If your terminal prints out the version of git, you have it installed. If not, you can install it using the following command:
```bash
$ sudo apt install git
```
1. Clone the repository:
```bash
$ git clone https://github.com/Bao-Trinh-Quoc/cs50-final-project.git
```
2. Change the directory to the project directory:
```bash
$ cd cs50-final-project
```
3. Build the project using the make utility:
```bash
$ make edito
```
If done correctly, you will see a binary file named `Edito` in the project directory.
## Usage:
To run the program, use the following command:
```bash
$ ./edito <filename>
```
Replace `<filename>` with the name of the file you want to open. If the filename is not provided, the program will open a new empty file.

Keys | Description
--- | ---
Ctrl-s | Save the file.
Ctrl-q | Quit the editor.
Ctrl-f | Search for a string in the file

## Implementation Details:
Not using any external libraries made me implement everything from scratch. <r>
First, I had to set up the terminal to raw mode to read input character by character. Then, I had to handle the cursor movement, scrolling, and screen refresh. <br>
The document and The instruction are very clear and easy to follow. I had to read the document multiple times to understand the code and implement it in my way. <br>