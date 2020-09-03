# Roman_numerals
Avarko code challenge. Program that takes roman numerals as parameter and converts them to arabic numbers.

### Features
- Roman numeral math
- Validation of input

### Value guide
- **M** = 1000
- **D** = 500
- **C** = 100
- **L** = 50
- **X** = 10
- **V** = 5
- **I** = 1

### Math
This was the easy part. Assignment only asked to support I, V, X, L, C, D and M numerals so I only had to deal with addition and subtraction. The basic idea is as follows: we have positive total and negative total, if next value in the list is larger than current one, I know the operation is subtraction and I can add the current value to the negative total. If the next value is equal or smaller than current value, I add the value to the positive total. Once all values have been added to their respective totals, simply subtracting the negative total from positive total gives the correct total value.

### Validation
The hard part. There are various rules with roman numerals and implementing them was a pain. The rules are as follows:
1. Characters must be part of "MDCLXVI"
2. There can't be more than 3 of same value in row.
3. There can't be more than 1 of DLV (500/50/5) value in row.
4. All the numerals must be in order from largest to smallest "MDCLXVI" -order. Except when there is subtracting value.
5. DLV values (500/50/5) may not be used for subtraction.
6. Subtracting value must be large enough. 10 x subtrahend == minuend (subtrahend is smaller value, subtracted from minuend, which is larger value).
7. Same subtraction may not happen more than once, for example IXIX is invalid.
8. Subtraction must be in last position for current values, for example: MCMM is incorrect, because CM == 1000-100 is not in last position, correct is MMCM.
9. After subtraction, subtrahend may not be used for addition, for example: MXCX is incorrect, it would be 1000+100-10+10, correct is just MC.
10. After lowest subtraction IX/IV, there may not be any numerals.

### Note
Project has a makefile. Simply write "make" in command line to compile.
Usage: ./romans MDCKXVI
