[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description

## Running Instructions
``make `` \
``./a.out``

## 1. Display Requirement
> files being used:\
    `main, prompt`

The prompt shows the username and system name. 
If the current working directory is the home directory, it will show ~. \
If the current working directory is a subdirectory of the home directory, it will show the path relative to the home directory. \
If the current working directory is not a subdirectory of the home directory, it will show the absolute path. 

## 2. Input Requirements
> files being used:\
    `main, callfunction`

The shell accounts for random spaces and tabs while taking input. \
A `\n` character implies that the command is complete. \
A `;` separates two commands. \
A `&` implies that all the commands before that are to be run in the background. \
Command after `&` will be run in the foreground.

## 3. Warp
> files being used:\
    `main, warp `

The `.`, `..`, `-`, `~` flags are implemented. \
Absolute and relative paths can both be used. \
Absolute paths start with a `/`. \

## 4. Peek
> files being used:\
    `main, peek`

This looks into folder for files and other directories. \
The flags `-l` `-a` can be used along with a combination. \
`-l` displays extra information. \
`-a` shows hidden files as well. \

## 5. Pastevents
> files being used:\
    `main, pastevents`

This prints old commands. \
It stores 15 commands and prints them in order of last used to newest. \
For pastevents execute, execute 1 executes the latest command. \
Pastevents purge clears the file and all saved commands. \
It only stores commands if they are not the exact same as the previous one. \

## 6. System Commands
> files being used:\
    `main, checkbgprocess`

This runs system commands like echo, sleep. \
This runs the background and foreground processes. \
It shows exit messages when the process is completed.

## 7. Proclore
> files being used:\
    `main, proclore`

This prints
1. pid
2. Process Status
3. Process group
4. Virtual Memory
5. Executable path of process 

If the process is not specified, it takes the shell pid and works with that

## 8. Seek
> files being used:\
    `main, seek`

This finds files/directories based on the file name entered. \
`-d` and `-f` flag cannot be used at the same time. \
`-e` flag works if only one file/directory is found. \
No flags specified finds both files and directories.

# Assumptions

- The maximum size of file paths or commands is 1000
- if any command with - is done at the beginning it will use the home directory as -
- If a command like `sleep 2; sleep 3` is given, the next promp will be dependent on whether the last command takes more than 2 seconds to execute
- If command is erroneous, default errors will be printed if it is a system command/if it does not exist in the list of commands that we have implemented.
- If a command such as `warp .. abc` is given, the current working folder will change according to the `..`. However, for `abc`, if the directory does not exist it will show up as invalid directory. 
- `warp` followed by nothing goes to the `~` directory.
- `peek` does not find hidden files.
-  Extra flags in peek show up as invalid flags and the command does not execute.
- If `pastevents execute x` is out of bounds, it will show an error message.
- `echo 1;` and `echo 1` are different commands.
- The command `vim` does not work, but it does not work in my terminal either.
- If the file `peek.c` needs to be found, the word `peek` needs to be specified, giving `peek.c` will not find it.




