# StripANSICodes
Strips ANSI codes out of a string using Boost Spirit X3 parser

To collaborate with Ciere consultine. 

GOAL: we want instead of simple "eating" the ANSI escape sequences and stripping them, we want to know where they
actually are in the actual parse stream...their start and finish positions in the original string.  

Example:

#define RESET_DEF					"\033[0m"
#define GREEN_DEF					"\033[32m"   

This string:
"this:\033[32m is green\033[0m"

prints "is green" in green. 

What we want to parse or capture is that:

First token (green_def) was at 0 to 7 abd that another token (reset_def) was at 17-22.


Would be great to also capture position of the actual string. 


We need to know/do this because many tools need to synchronize between the parsed AST and the original source file to perform intellisense and other operations. 



BONUS: there is also a section in the main .cpp wrapped by a #if 0.  It is all my rules but in a function scope. It will not compile because I can not get BOOST_SPIRIT_DEFINE or DECLARE to operate in a scope (which is understandable, templates can't be there) but what the alternative?  
