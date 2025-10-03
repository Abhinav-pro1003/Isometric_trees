
In this lab, we will be diving deeper into trees through red black trees.
The first part is pretty straightforward -> Implement the insert operation into red black trees

Details:
- All the functions have been declared in the header file which you MUST NOT change.
- Implementations for inorder and printRBT have been provided. 
- Implement the functions `insert` , `fixup` , `leftrotate` and `rightrotate`.
- Please handle the various cases as mentioned in the slides carefully.
- Remember to design your OWN testcases to test out the various possible cases.
- Keys will be distinct for insertion
Read the comments next to each function to understand what each function is supposed to do.


Instructions to Run the Code 
1. Run make to run your code.
# Make Commands

```
make             # Build and Run Tests
make build       # Build
make runtests    # Run Tests
make clean       # Clean Temporary Files
```
Please read Makefile to understand the above commands!

# VS Code interface

You can open this folder in VS Code. The problem folder is configured 
to enable debugging.

After opening the folder, click on Run > Start Debugging or press F5.
This will run your program on input ./test/test1/input.txt.
You may place breakpoints to pause the program at any desired location.

You can modify "./.vscode/launch.json" to run any test of your choice.

In some labs, there may be multiple binaries, and you may need to modify 
the binary name in the ./.vscode/settings.json file.

```
    "problem": "<binary>",
```

# General Instructions

- Read all .h and .cpp files before starting.
- Do not include any additional header files.
- Do not modify files other than the specified files. Any other changes 
  will not be considered during evaluation.
- You are expected to submit an efficient implementation. Inefficient 
  solutions will lose marks.

