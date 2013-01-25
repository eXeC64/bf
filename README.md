bf
==

This is a quick and dirty brainfuck interpreter I wrote in C. It was written in about an hour during a compilers lecture when I felt inspired, and then polished for about another hour.

I was just having fun with C when I wrote this, and decided to try and make the code as compact as I could. Hence some of the weird stylistic choices, such as using an array of function pointers instead of a switch statement.

I'm tempted to refine it futher by removing all conditional branching from the main execution loop by using another array of function pointers for the [ and ] loops. But that'd make the code *too* unreadable.

Harry.
