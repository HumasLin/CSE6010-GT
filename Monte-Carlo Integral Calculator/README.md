Author          : Haomin Lin
Created         : August 27, 2019
Last Modified   : August 27, 2019

Affiliation          : Georgia Institute of Technology


Description
-------------

This program is a integral calculator using Monte-Carlo method. User enters the the range of the integral, and inputs the times they want the experiment to run. Then the program will execute integral and return the value. If the range is reversed or the function in specific range has undefined points, the program will ask for another range or a modified function.

Installation
------------

To install, simply run:

    gcc main.c -std=c99 -o Calculate_Integral

in Terminal

Note: The -std=c99 flag is required on some C compilers
to allow variable declarations at arbitrary locations in
a function.

Execution
-----------

Assuming your executable is called "Calculate_Integral", run it in Terminal using:

    ./Calculate_Integral


