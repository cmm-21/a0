# Assignement 0

This assignment has two purposes:

1. match your github username to your student ID
2. make sure you can build and run the starter code

## Part 1: match github to student ID

1. Insert your student id (Legi Nummer) in the file `student-id.txt`. Example: Your student id is 12-345-678. The contens of `student-id.txt` should be: 
    ```
    12-345-678
    ```

2. Commit and push the changes to `student-id.txt`. For example:

   ```
   git add student-id.txt
   git commit -m "added my student id number"
   git push
   ```
   

3. Verify that your changes were uploaded to github.com by checking github.com/cmm-21/a0-YOUR_GITHUB_NAME

## Part 2: build and run starter code

This assignement is to make sure your computer and you are both set up for the next three assignements. You do not have to hand-in anything. However, you can already play around with the code, and commit and push changes to your repository. For future assignements, you will have to commit and push your solutions to github. Commits (or rather pushes) after the deadline will be disregarded. So make sure you are ready and test out things with this assignement.

### Prerequisites
Make sure you install the following:

- Git (https://git-scm.com)
    + Windows: download installer from website
    + Linux: e.g. `sudo apt install git`
    + MacOS: e.g. `brew install git`
- CMake (https://cmake.org/)
    + Windows: download installer from website
    + Linux: e.g. `sudo apt install cmake`
    + MacOS: e.g. `brew install cmake`

### Building the code

On Windows, you can use Git Bash to perform the steps mentioned below.

1. Run CMake to create project files
    ```
    cd comp-fab-a0-XXX
    mkdir build && cd build
    cmake ..
    ```
3. Compile code and run executable
    - for MacOS and Linux:
        ```
        make
        ./src/app/app
        ```
    - for Windows: 
        * open `assignement0.sln` in Visual Studio
        * in the project explorer, right-click target "app" and set as startup app.
        * Hit F5!


### Some comments

- If you are new to git, there are many tutorials online, e.g. http://rogerdudler.github.io/git-guide/.

- You will not have to edit any CMake file, so no real understanding of CMake is required. You might however want to generate build files for your favorite editor/IDE: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
