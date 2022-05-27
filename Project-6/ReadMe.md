# Project: uShell
## Overview
Build a micro-shell for executing command-line programs.
### Objectives
- Understand processes and job control
- Learn to interface with more advanced system calls
- Increase familiarity with operating system functionality
## Description
### Introduction
A shell is an interactive command-line interpreter that runs programs on behalf of the user.
A shell repeatedly prints a prompt, waits for a command line on stdin, and then carries out some action, as directed by the contents of the command line.

The command line is a sequence of ASCII text words delimited by whitespace.
The first word in the command line is either the name of a built-in command or the pathname of an executable file.
The remaining words are command-line arguments.

If the first word is a built-in command, the shell immediately executes the command in the current process.
Otherwise, the word is assumed to be the pathname of an executable program.
In this case, the shell forks a child process, then loads and runs the program in the context of the child.

The child processes created as a result of interpreting a single command line are known collectively as a job.
In general, a job can consist of multiple child processes connected by Unix pipes.

If the command line ends with an ampersand "&", then the job runs in the background, which means that the shell does not wait for the job to terminate before printing the prompt and awaiting the next command line.
Otherwise, the job runs in the foreground, which means that the shell waits for the job to terminate before awaiting the next command line.
Thus, at any point in time, at most one job can be running in the foreground.
However, an arbitrary number of jobs can run in the background.

Unix shells support the notion of job control, which allows users to move jobs back and forth between background and foreground, and to change the process state (running, stopped, or terminated) of the processes in a job.
### What to do
Looking at the msh.c file, complete the remaining empty functions listed below.
- eval: Main routine tat parses and interprets the command line.
- builtin_cmd: Recognizes and interprets the build-in commands: quit, fg, bg, and jobs.
- do_bgfg: Implements the bg and fg built-in commands.
- waitfg: Waits for a foreground job to complete.
- sigchld_handler: Catches SIGCHILD signals.
- sigint_handler: Catches SIGINT (ctrl-c) signals.
- sigtstp_handler: Cataches SIGTSTP (ctrl-z) signmals.
### The msh Specification
The msh shell should have the following features
- The prompt should be the string "msh> "
- The command line typed by the user should consist of a name and zero or more arguments, all separated by one or more spaces.
- Need not support pipes (|) of I/O redirection (&lt; and &gt;)
- Typing ctrl-c should cause a SIGINT signal to be sent to the current foreground job, as well as any descendents of that job.
- Typing ctrl-z should cause a SIGTSTP signal to be sent to the current foreground job, as well as any descendents of that job.
- If the command line ends with an ampersand &, then msh should run the job in the background.
- Each job can be identified by either a process ID (PID) or a job ID (JID), which is a positive integer assigned by msh.
- msh should support the following built-in commands:
   * The quit command terminates the shell.
   * The jobs command lists all background jobs.
   * The bj &lt;job&gt; command restarts &lt;job&gt; by sending it a SIGCONT signal, and then runs it in the background.
   * The fg &lt;job&gt; command restarts &lt;job&gt; by sending it a SIGCONT signal, and then runs it in the foreground.
- msh should reap all of its zombie children.
