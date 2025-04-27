# Word-Frequency-Analyzer-using-AVL-Tree-and-Hash-Table

# Word Frequency Analyzer (AVL Tree + Hash Table)

## Overview
This C-language console application analyzes a large text file, filters words, and tracks their frequencies using:
- **AVL Trees** (self-balancing binary search trees)
- **Hash Tables** with **double hashing** collision handling and **rehashing** for load factor control.

## Features
- Load text data from a file and filter non-alphabetic characters.
- Insert and delete words dynamically.
- Maintain word frequencies in AVL Tree and Hash Table.
- Support undoing deletions and managing dynamic rehashing.
- Search for a word and report its frequency.
- Display words sorted alphabetically (AVL in-order traversal).
- Analyze and report on repeated vs. unique words with thresholds.

## Sample Input
**input.txt**
```
Welcome to Programming.
Welcome to C Language.
Data structures are important.
Hashing and AVL trees are powerful.
```

## Sample Output (Console)
```
please enter number between 1-11:
1. Load data from the file.
2. Create the AVL tree.
3. Insert a word...
...

The number of unique words = 5
The most frequent word is = Welcome (Frequency: 2)
```

## Project Structure
- `main.c` : Main program (AVL + Hash)
- `input.txt` : Sample input file
- `output.txt` : Optional output file for saving results

## Technologies
- C Language (C99 standard)
- Data Structures: AVL Trees, Hash Tables
- Manual Memory Management

## How to Run
1. Compile:
```bash
gcc main.c -o analyzer
```
2. Run:
```bash
./analyzer
```
3. Make sure you have an `input.txt` file in the same folder.

---

> **Author:** Ahmad Shaher Ahmad Sous  
> **Instructor:** Radi Jarar
