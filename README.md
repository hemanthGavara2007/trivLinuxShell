# TrivShell Beta 0.1v
## What is it ?
It is a **Sandboxed mini-Linux Shell implemented using C and Makefile**. The commands implemented are either coded by me or with help of special libraries.This README file is a comprehensive manual to all the commands I implemented in the shell

## What makes it special ?

Yep there are many factors which make it special and try-worthy

- ### SandBoxed Environment
  - The whole shell is made on restricted access principles, implying that whatever you run using this shell does not affect the whole disk or system and everything lies inside the folder you cloned
- ### 100% AI Free
  - Might look a bit over-promising and before you contradict this let me explain what I meant by this.
    - The Shell has been coded without the use of any AI tools , literally any 
      - No Vibe Coding
      - No Usage of ChatGPT, Gemini etc , not even for debugging
      - I had to disable Google AI Overview to train myself to write better code
      - except for git add and push, I blocked github website because many people have already made similar ones
    <br><br>
    - The sources I used :
      - [Stack Overflow](http://stackoverflow.com/)
      - [Geeks for Geeks](https://www.geeksforgeeks.org/)
      - [Youtube](https://www.youtube.com/)
      - [Unix & Linux Stack Exchange](https://unix.stackexchange.com/)
      - [Tutorials Point](https://www.tutorialspoint.com/)
- ### Commands done without the use of exec()
  - Might sound vague but this is simplest way for running of commands which cannot be called by C. I made sure I wont use it in this project to improve my resource gathering and debugging ability
- ### Better Organization and Commentation of the Project
  - This project is a very good starting point for learners and tech enthusiasts for either implementing their own shell or learning how linux shell works in the background(not all features have been implemented yet)
# What commands have been implemented
- ls
- cd
- pwd
- sleep
- Redirections(> and >>)
- Pipes(|)
- quit
- Signals
- Shell Variables(Global has to be implemented)
- which
- Conditionals(&& and ||)

Still many others are in development and will be finished soon

