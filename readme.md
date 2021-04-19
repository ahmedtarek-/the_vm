# Writing my first VM

A stack based VM that reads a limited set of bytecode (TBD) and executes it in C.

## Compononets of a VM

### The instruction set

- OP_RETURN
- OP_NO_RETURN
- OP_CONSTANT
- OP_NEGATE
- OP_ADD
- OP_SUBTRACT
- OP_MULT
- OP_DIVIDE


## The run method

This is the heart of the VM (you can find it in `vm.c`).


### The stack and how VM traverses the syntax tree


## To run the MOFO

`gcc -o main main.c chunk.c memory.c debug.c value.c vm.c`


## Resources

### Effecient bytecode dispatching

**Direct Call Threading**
In Direct call threading, the opcode of the virtual instruction represents the address of a C function which executes this operation (addition for example). The PC (or IP)
needs to be incremented by this function call.

A dispatch loop is still needed to go over the instruction set.

http://www.cs.toronto.edu/~matz/dissertation/matzDissertation-latex2html/node6.html


**Direct Threading**
Only one function contains the implementation for every possible instruction. This function is organised as 'labels', one per each instruction implementation. This allows the programm to JUMP after finishing execution to the next instruction (using the PC, which is an address of the label of that instruction).

Bytecode is "loaded" into Direct Threading Table (DTT) which is a table holding one operation or operand per row. Again, the instruction value in this table is the address of the label of that operation

NO Dispatch loop is needed in this case, and most common C compilers support these features which make it quite portable as well

http://www.cs.toronto.edu/~matz/dissertation/matzDissertation-latex2html/node6.html


**Computed Go-To**

https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables


