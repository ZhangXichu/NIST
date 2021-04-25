*************************************************************************
*        Alternative (faster) implementation of the NIST STS tests      *
*                                                                       *
*            NIST STS Version 2.1.2 - Alt Version F (v6)                *
*************************************************************************
*                                                                       *
*   Please write your bug reports, questions and comments to:           *
*                        zriha@mail.muni.cz                             *
*                        syso@mail.muni.cz                              *
*                                                                       *
*************************************************************************
*                                                                       *
*                         I N S T A L L                                 *
*                                                                       *
*************************************************************************

Just type 'make' (unix-like systems) or use NIST.sln (Visual Studio).
Result is a single executable file. For the Non-overlapping Template 
Matching Test a subdirectory "template" with the template files must be
available. For saving the results the "experiments" subtree must exist.

If you want to use the FFTW library for the FFT tests then install the
library and in stat_fncs.h define DiscreteFourierTransform_v2 as
DiscreteFourierTransform3 or DiscreteFourierTransform4.

Compilation tested on recent Linux (gcc 4.4.7), cygwin64 (gcc 4.9.3) and 
mingw64 (gcc 5.2.0). Tested on Visual Studio 2015 (also works with previous
versions).

*************************************************************************
*                                                                       *
*                           U S A G E                                   *
*                                                                       *
*************************************************************************

This is an alternative implementation of the NIST statistical randomness
tests. The source codes include both the original and the new alternative
improved variant/variants of tests. You can also compare performance of 
both implementations and correctness of the new implementation. Also 
Kolmogorov-Smirnov test is added to check uniformity (additional test 
to Chi^2 test).

Each test can be used in two versions v1, v2 (for instance Frequency_v1 
and Frequency_v2),  where v1 (Frequency_v1) defines original implementation
of the test and v2 (Frequency_v2) defines a new implementation. 
 
You can add new implementation of the arbitrary test as follows: 
	1.Add the new function (Frequency_new(int n){...}) to file frequency.h.
	2.Add its prototype (Frequency_new(int n);) to stat-fncs.h
	3.Change #define Frequency_v2 Frequency3 
	  to #define Frequency_v2 Frequency_new
 
*************************************************************************
*                                                                       *
*                           Randomness testing                          *
*                                                                       *
*************************************************************************
1. In config.h set the following:
    //#define VERIFY_RESULTS 1
    //#define SPEED 1
     #define FILE_OUTPUT 1 
    //define KS 1 
    if you want to test randomness.
    
    //#define FILE_OUTPUT 1 
    define KS 1 
    if you want also to test uniformity using Kolmogorov-Smirnov test.
    KS can compute p-value greater than 1 since it computes accurate 
    p-values only for small p-values. 
    
 
2. Usage: assess <stream length> [-fast] 
   <stream length> is the length of the individual bit stream(s) to be processed
   -fast           use the faster alternative implementation (version 2) of tests
   (set Command arguments: 10000 -fast if you want to test 10 000 bits with faster version of NIST tests)

*************************************************************************
*                                                                       *
*                           Performance testing                         *
*                                                                       *
*************************************************************************
1. In config.h set the following:
    //#define VERIFY_RESULTS 1
    #define SPEED 1
    //#define FILE_OUTPUT 1
    //define KS 1 
2. Usage: assess scale repeat test_from test_to (for instance 0 10 1 2)
	scale      - 0 (one fixed bit size = 20MB) or 1 (bitsizes are increases in steps)
	repeat     - is number of times( 10) each test is executed (minimum time is taken as the result)
	test_from test_to  - which tests are measured ( 1 - 2 = Freqency and BlockFrequency) 

You can also compare speed of your implementation with our implemenation.
If you want to compare speed of our Frequency2 and your Frequency_your function
it suffices to change defines to:
    1. #define Frequency_v1 Frequency2
    2. #define Frequency_v2 Frequency_your

*************************************************************************
*                                                                       *
*                           Correctness testing                         *
*                                                                       *
*************************************************************************
1. In config.h set the following:
    #define VERIFY_RESULTS 1
    //#define SPEED 1
    //#define FILE_OUTPUT 1
    //define KS 1 
2. Usage: assess test
	test - which test to verify (e.g. 1 = Frequency) 

*************************************************************************
*                                                                       *
*              Introduce support for m>25 (and m<=32)                   *
*              in Serial and Overlapping Template Matching tests        *
*                                                                       *
*************************************************************************

If you feel limited with the maximum value of m (m <=25) in the Serial
and Overlapping Template Matching tests then simply replace the calls
of get_nth_block4() with the calls of get_nth_block_effect() in the 
relevant parts of the source code. For the serial test search for function 
Serial4() in serial.c. For the Overlapping Template Matching test search for
the funtion OverlappingTemplateMatchings2() in overlappingTemplateMatchings.c



*************************************************************************
*                                                                       *
*               Performance testing of FFT libraries                    *
*                        Xichu Zhang                                    *
*                                                                       *
*************************************************************************
*                                                                       *
*                         Overview                                      *
*                                                                       *
*************************************************************************
Some libraries implementing FFT libraries are chosen to compare the performance.
Extra code is added to the NIST STS project to test the libraries' performance 
for transforming random bit sequence. All implementations of the libraries are 
in the directory fft_benchmark.c.

*************************************************************************
*                                                                       *
*                        Testing data                                   *
*                                                                       *
*************************************************************************
The testing data are chosen between the range of 2 and 2²⁶, which can be 
found in test_data.h. 
The tests are run using the random bit sequence generated by the RNG in 
NIST STS, and the resulting p-values are used to verify whether the 
transform is correct. 
Those p-values are precalculated and also stored in the test_data.h file.

*************************************************************************
*                                                                       *
*                        Run the tests                                  *
*                                                                       *
*************************************************************************
Do not build the system by directly running the makefile because some of 
the macros are not defined. Use the test.sh script to build the project 
instead. 
All the tests are automated using the test.sh script, which means after 
running this script, all the tests will be run sequentially. It is also 
possible to comment out some of the tests in the verify/test function 
to omit them or modify the functions' arguments for testing each library.
In order to test randomness, different versions of FFT using different
libraries can be switched in stat_fncs.h via macro DiscreteFourierTransform_v2.

*************************************************************************
*                                                                       *
*                           Arguments                                   *
*                                                                       *
*************************************************************************
The functions in test.sh are divided into two groups, namely verify and 
test. The functions called in verify are used to check whether the 
implementation gives corect result of Discrete Fourier Transform. And the 
functions called in test measure the time needed to perform the transform.
The first few arguments in the functions for testing each library define 
the following macros:

Pow2: transform of input length being power of 2

PRIME: input length is prime

SMALL_FACTOR: input length consists of small factors

P_VALUE: check whether the p-value is corrcet to verify the correctness 
of the transform

DiscreteFourierTransform_v2: the library to test

Apart from defining the macros, there is one more integer argument to each 
verify/test function, the second last argument.
This argument sets the number of inputs of the transform to be truncated. 
For example, while testing the DFT of length, which is a power of 2, if 
this integer is set to 1, then the very last input 2²⁶ is omitted. Setting 
this argument avoids inputs, which are very large and will take 
unrealistically a lot of time to compute.
The last argument is a string that defines the name of the output file.

*************************************************************************
*                                                                       *
*                              Plots                                    *
*                                                                       *
*************************************************************************
The scripts used to make graphs are in the directory scripts. 
File plot_ampli.py plots a sample transformed bit sequence and shows the 
corresponding threshold of peak height.
File plot_result.py plots the performance of each library with different
inputs. The tests can be switched in main function.
