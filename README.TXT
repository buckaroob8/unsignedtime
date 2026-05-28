This header is a drop in replacement for the C time functions in the 
Microsoft compiler that extends the 2038 Unix time epoch signed overflow 
to 2106 by treating 32 bit time variables as unsigned and using the 64 bit 
time functions to generate the output. Any structure use or file storage 
of the 32 bit sized variables will continue to work for an extra 64 years. 

To use the library, simply replace any #include "time.h" lines in your code 
with #include "unsigned_time.h". It includes the original time library and
uses defines to overwrite the time header function names with static 
functions. It's not the most elegant of solutions as it creates copies of 
the static functions for each file, but it requires no additional code 
changes or linked libraries.

