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


### Some example hand-compiled arithemtic operations

**A. (1 * 2 + 3)**

```c
/////// main method in vm.c  /////////
// 1. Prepare chunk and constants
  Chunk chunk;
  Value const1 = 1.0;
  Value const2 = 2.0;
  Value const3 = 3.0;
  initChunk(&chunk);

  uint8_t const1Loc = addConstant(&chunk, const1);
  uint8_t const2Loc = addConstant(&chunk, const2);
  uint8_t const3Loc = addConstant(&chunk, const3);

  // 2. Write to chunk (1 * 2 + 3)
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const1Loc, 123);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const2Loc, 123);

  writeChunk(&chunk, OP_MULT, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const3Loc, 124);

  writeChunk(&chunk, OP_ADD, 124);

  writeChunk(&chunk, OP_RETURN, 124);

  // 3. Debug chunk
  disassembleChunk(&chunk, "Oh Chunk!");

  // 4. Run chunk
  interpret(&chunk);
```

**B. (1 + 2 * 3 - 4 / -5)**

equivelent to `1 + (2 * 3) - (4 / -5)`

```c
/////// main method in vm.c  /////////

// 1. Prepare chunk and constants
  Chunk chunk;
  Value const1 = 1.0;
  Value const2 = 2.0;
  Value const3 = 3.0;
  Value const4 = 4.0;
  Value const5 = 5.0;
  initChunk(&chunk);

  uint8_t const1Loc = addConstant(&chunk, const1);
  uint8_t const2Loc = addConstant(&chunk, const2);
  uint8_t const3Loc = addConstant(&chunk, const3);
  uint8_t const4Loc = addConstant(&chunk, const4);
  uint8_t const5Loc = addConstant(&chunk, const5);

  // 2. Write to chunk ( 1 + (2 * 3) - (4 / -5) )
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const5Loc, 123);

  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const4Loc, 123);

  writeChunk(&chunk, OP_DIVIDE, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const2Loc, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const3Loc, 124);

  writeChunk(&chunk, OP_MULT, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const1Loc, 124);

  writeChunk(&chunk, OP_ADD, 124);

  writeChunk(&chunk, OP_SUBTRACT, 124);

  writeChunk(&chunk, OP_RETURN, 124);

  // 3. Debug chunk
  disassembleChunk(&chunk, "Oh Chunk!");

  // 4. Run chunk
  interpret(&chunk);
```


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


