# EDITO --- A Simple Text Editor in Command Line
## Description:
Edito is a simple text editor that can be used to view and edit text files in the terminal. It is written in C and uses only the standard library with no dependencies. It uses fairly standard VT100(and similar terminals) escape sequences.<br>

It implements all the **basic features you would expect in a minimal text editor**. Other features include:
- Syntax highlighting for C and C++.
- A search feature.
- Many more features to come...

**This project is heavily inspired by [kilo editor](https://github.com/antirez/kilo) and [Paige Ruten](https://viewsourcecode.org/snaptoken/kilo/).**

## Video Demo: 
https://youtu.be/Yeeiu1onIaw
## Prerequisites:
To run the program, you need to have the following installed on your system:
- **A C compiler** (gcc, clang, etc.) for compiling the source code.
- **make** utility for building the project.
- A terminal to run the program.
- A git client to clone the repository.
## Installation:
 >[!NOTE]
 >The following instructions are for Linux systems. The program should work on Windows and MacOS as well, but the installation process may vary.
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

## Development Process:
Since I didn't use any external libraries, I had to build everything from the ground up. First, I set the terminal to raw mode so I could read input one character at a time. Then, I worked on managing the cursor movement, scrolling, and refreshing the screen. <br>
I went through the document several times to grasp the code and implement it properly. Luckily, there are plenty of online resources available to help me understand the code better, especially the work by [Paige Ruten](https://viewsourcecode.org/snaptoken/kilo/). 

After finishing the text viewer, I added features for a text editor, including inserting, deleting, and saving text. Working on this project has been a lot of fun, and I've learned a great deal about terminal programming and text editors in general.

Next, I implemented syntax highlighting for C and C++ code. I created a simple structure to store the syntax highlighting information for each character in the file. I also added a search feature that highlights all occurrences of a search string within the file. This feature was easier to implement thanks to the resources provided by Paige Ruten.

More information about the development process can be found in the [development log](log.txt).

## Future Features To Add:
- **Line numbers**: Display line numbers on the left side of the screen. This will make it easier to navigate through the file. I plan to implement this feature by storing the line number information in a separate buffer and updating it whenever the file is modified.
- **Copy and paste**: This text editor is missing a crucial feature: copy and paste. I plan to implement this feature by adding a copy buffer that stores the selected text and a paste buffer that stores the copied text. I will then add key bindings to copy and paste text.
- **Undo/redo**: Implement undo and redo functionality to allow users to revert changes made to the file. This feature will require storing the state of the file before each change and implementing key bindings to undo and redo changes. <-- This is pretty hard tho.

## Contributing:
If you would like to contribute to this project, feel free to fork the repository and submit a pull request. You can also open an issue if you have any suggestions or feedback.

## License:
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements:
Special thanks to the following resources for helping me complete this project:
- [kilo editor](https://github.com/antirez/kilo)
- Paige Ruten's [tutorial](https://viewsourcecode.org/snaptoken/kilo/)
- CS50 course by Harvard University
- And a big thank to CS50 community for providing me with the knowledge and resources to complete this project.
