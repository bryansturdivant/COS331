COS 331, Homework 1
Bryan Sturdivant

This is a short program that runs on an infinite loop, creating a child process that asks the user for the name of a program.
If the program exists, the child executes it. If the program does not exist, an error message is printed and the child process exits.

I struggled a bit with certain things that I just didn't understand enough. I didn't realize that the exit() command is supposed to only exit the process it's currently in(in this case, the child). I kept trying to fix it, and wondering why the program kept executing - because I created an infinite loop and it was working how it was supposed to. Once I googled the exit() command I realized that I was actually doing it correctly.

I mostly got help by reviewing lecture slides and doing some googling. My biggest struggle is that I haven't done anything in C since my first year of college. I do wish more classes used C because I think it's an interesting programming language.
