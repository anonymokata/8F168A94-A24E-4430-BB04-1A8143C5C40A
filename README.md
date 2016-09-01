# Roman Numeral Calculator

# What?

This is a programming exercise. It creates a command line calculator that does addition and subtraction with roman numerals. It does this by manipulating the string rather than using normal arithmatic. 

# Why?

Everyone loves a challenge


# How?

In order to build the code you will need to run make. Below there are some notes about about my experience. But here are the high level instructions;

* Assume check is installed in the traditional location /usr/local/lib

* Assume make, gcc, splint, gcov, and checkmk are all installed as well

* Assume pkg-config is installed too!

```bash
#from the root folder
make; make cli
```

You should see output similar to this;

```bash
splint +unixlib -compdef -mayaliasunique -I src src/./adjust_roman.c src/./calculator.c src/./convert_roman.c src/./validate.c | tee all.splint
Splint 3.1.2 --- 03 May 2009

Finished checking --- no warnings
if [ -e /usr/local/lib/libcheck.a ]; then echo "libcheck.a ok!"; else echo "libcheck.a is not in /usr/local/lib as expected"; exit 1; fi;
libcheck.a ok!
checkmk test/./_all_tests.check test/./addition.check test/./convert_roman_char_to_dec.check test/./subtraction.check test/./validate.check > test/all_tests.c
gcc -Wall `pkg-config --cflags check` -o all_tests src/./adjust_roman.c src/./calculator.c src/./convert_roman.c src/./validate.c test/./all_tests.c -lcheck `pkg-config --libs --static check` -I src
LD_LIBRARY_PATH=/usr/local/lib ./all_tests
Running suite(s): Core
100%: Checks: 80, Failures: 0, Errors: 0
gcc -Wall `pkg-config --cflags check` -fprofile-arcs -ftest-coverage -o all_tests_gcov src/./adjust_roman.c src/./calculator.c src/./convert_roman.c src/./validate.c test/./all_tests.c -lcheck `pkg-config --libs --static check` -I src
LD_LIBRARY_PATH=/usr/local/lib ./all_tests_gcov
Running suite(s): Core
100%: Checks: 80, Failures: 0, Errors: 0
gcov calculator.c
File 'src/calculator.c'
Lines executed:100.00% of 28
Creating 'calculator.c.gcov'

gcov convert_roman.c
File 'src/convert_roman.c'
Lines executed:98.00% of 50
Creating 'convert_roman.c.gcov'

gcov validate.c
File 'src/validate.c'
Lines executed:100.00% of 23
Creating 'validate.c.gcov'

gcov adjust_roman.c
File 'src/adjust_roman.c'
Lines executed:100.00% of 25
Creating 'adjust_roman.c.gcov'

gcc -Wall -o romani src/./adjust_roman.c src/./calculator.c src/./convert_roman.c src/./validate.c demo/main.c  -I src
```

As you can see from the output, 

* make first checks to see if the check library is installed, if it isn't the build stops.

* splint is run against the source code to detect issues with security, memory leaks, etc.

* checkmk is run to create a test runner. This is done by mashing all the check files into one .c file, simple but effective

* gcc is invoked to build the unit-test suite. This requires linking in check

* the test suite is executed, if it fails the build will stop

* gcc is invoked again to build the unit-test suite with gcov active, this generates coverage meta-data

* gcov is invoked on the meta data to get coverage data for each of the .c files. 

	* note, main.c from the demo folder is not included as that code is not part of the exercise

* gcc is invoked a final time (if you ran make cli) to create the command line interface (romani)

	* romani is for demo purposes only, the code is not test driven or checked by static analysis (thought it could have been)

	* romani accepts input in pre-fix, in-fix, and post fix notation, for example

```bash
		% ./romani + VI CCXI
		CCXVII
		
```

	* I added romani just so I could do exploratory testing. It actually revealed bugs in my validator, causing a rewrite.

## Other notes

* Used docker to get an Ubuntu 14.04 machine, setup is in the docker folder

* Added a setup.sh file to install all the tooling and build check from source.

	* docker would not cooperate on saving this state, so each time I started the conainter I had to re-run that

	* setup.sh needs you to be root in order to install check

---------------------------------------

# Assigned Exercise

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

------------------------

# Notes from the author

* used Docker container to create a development environment

	* mounted my home directory on my Mac at /home/rich in the Docker machine

* build check from source

* added splint to check validity of code (static analysis)

* used gcov for coverage information

	* 100% except default cases of some switch statements

* added a CLI (untested) for entertainment/demo purposes.

	* I might test drive this later, I just built it for exploratory testing

* assume check is installed in /usr/local/lib

	* this is really just so we can run the test suite automatically

	* makefile uses pkg-config for compilations

