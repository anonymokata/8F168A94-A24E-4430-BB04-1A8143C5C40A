# Roman Numeral Calculator

For this programming exercise, you will be creating a library which will allow the addition and subtraction of Roman numerals. Once your solution is complete, please provide your solution as a Git repository (publicly available via Github or Bitbucket). Please include within your repository, all source and test code.

The solution will be reviewed for:

* coverage

* Driven Development

* Algorithm Usage

* Code structure

* Use of source control

* Completeness of the overall solution

The environment for this programming exercise ​must​ utilize:

* Ubuntu Linux 14.04

* The C programming language

* GNU GCC compiler tool chain

* GNU Make

* Check unit testing framework ( https://libcheck.github.io/check/ )

* git

Roman Numeral rules:

* Roman numerals consist of the following letters: I, V, X, L, C, D, and M which mean one, five, ten, fifty, hundred, five hundred and one thousand respectively.

* An example would be "XIV" + "LX" = "LXXIV"

* Numerals can be concatenated to form a larger numeral ("XX" + "II" = "XXII").

* If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger ("IV" means four, "CM" means ninehundred).

* If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).

* If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)

* The maximum roman numeral is 3999 (MMMCMXCIX)

# Stories

## User Story: Addition

As a Roman bookkeeper, I want to be able to add two numbers together. So that I can do my work faster with fewer mathematical errors.

## User Story: Subtraction

As a Roman bookkeeper, I want to be able to subtract one number from another. So that I can do my work faster and with fewer mathematical errors.

> This exercise is based on the Roman Numeral Calculator Kata at http://bit.ly/1VfHqlj
> Please submit your test­driven solution via a public Git repository (github/bitbucket).

- - - 

# Notes from the author

* used Docker container to create a development environment

	* mounted my home directory on my Mac at /home/rich in the Docker machine

* build check from source

* added splint to check validity of code (static analysis)

	* splint reports a memory issue (but I disagree)

* used gcov for coverage information

	* 100% except default cases of some switch statements

* still concerned that I'm using a lot of memory with 5 100 byte buffers

	* need to find the optimal size for those buffers at a minimum

* added a CLI (untested) for entertainment/demo purposes.

	* I might try to test drive this later



