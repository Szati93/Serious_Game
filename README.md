# Serious_Game
**Serious_Game** is a console-based C++ application designed to help users learn vocabulary through translation exercises between two languages. The program supports two modes of practice and saves results to a file.

## Table of Contents

- [Program Description](#program-description)
- [Requirements](#requirements)
- [Usage Instructions](#usage-instructions)
- [Function Descriptions](#function-descriptions)
- [Input File Format](#input-file-format)
- [How It Works](#how-it-works)
- [Technical Notes](#technical-notes)

## Program Description

The program loads two lists of words from text files:
- words in a foreign language,
- their corresponding translations in Polish.

It then allows the user to test their knowledge in two modes:
- Mode 1 – translating from the foreign language to Polish,

- Mode 2 – translating in both directions (foreign → Polish and Polish → foreign).

At the end of the session, the program writes the number of questions and the count of correct answers to a specified results file.

## Requirements

- C++ compiler supporting C++11 or newer

- Operating system with console support (Linux, Windows, macOS)

- Text files containing vocabulary words (format described below)

## Usage Instructions
1. Run the program.

2. Choose a practice mode by entering `1` or `2`:

 - `1` – translate from foreign language to Polish,

 - `2` – translate in both directions.

3. Enter the filename containing foreign language words.

4. Enter the filename containing Polish words.

5. Enter the filename where you want the results to be saved.

6. Translate the given words as prompted.

7. After finishing, the program will save your results to the specified file.

## Function Descriptions

- **losowanie(string foreign, string polish, int count)**  
  *Shuffles two arrays (foreign and Polish words) while maintaining the correct pairing by index.*

- **wielkosc_znaku(string str)**  
  *Converts all letters of a word to lowercase to ensure case-insensitive comparison.*

- **tlumaczenie(bool mode)**  
  *Main function responsible for:*
  - reading words from files,
  - running the quiz in the selected mode,
  - saving results to a file.
- **main()**  
  *Menu to select the mode and invoke the tlumaczenie function.*

## Input File Format
Text files should contain one word per line.
*Note: The order of words in both files must correspond exactly (word on line N in the foreign file matches the word on line N in the Polish file).*

Example foreign file (`foreign.txt`):
```
apple
car
house
```
Example Polish file (`polish.txt`):
```
jabłko
samochód
dom
```

## How It Works
1. The program prompts for the names of the vocabulary files.
2. Reads all words from the files into dynamic arrays `foreign[]` and `polish[]`.
3. Randomly shuffles the word pairs.
4. Depending on the selected mode:
    - **Mode 1:** user translates words from foreign language to Polish,  
    - **Mode 2:** randomly chooses the direction of translation for each word pair (foreign → Polish or Polish → foreign).

5. After each answer, the program indicates whether it was correct and displays the current score.

6. When finished, the program writes the statistics to the results file.

## Technical Notes
- **Randomization:**  
The `losowanie` function implements the Fisher-Yates shuffle algorithm.  
**Note:** *`srand(time(NULL))` is called multiple times, which may reduce randomness quality if called repeatedly within a short timeframe. It is better to call it once at the start of the program.*

- **Reading lines:**  
The program uses `getline()` to read words but counts lines with the `>>` operator, which may cause mismatches if words contain spaces.

- **Memory Management:**  
Dynamically allocated arrays are properly deallocated with `delete[]`.

- **Input Validation:**  
Basic input validation is implemented for mode selection, but filename errors only prompt for re-entry without detailed error handling.

- **Encoding:**  
The program assumes the vocabulary files are encoded in ASCII or UTF-8 without BOM.
