# Two_Character_Challenge_in_C
Coding challenge response for the hackerrank challenge "Two Characters" by nabila_ahmed, completed in C

Please go to hackerrank to get the actual problem in the same manner that it was presented to me.
The official link to this challenge can be found here:
https://www.hackerrank.com/challenges/two-characters/problem

This problem could have been solved easily in Python using sets, however, I could only use Java or C. Because I used Java on previous problems for the same challenge group, I chose C, figuring this was a chance to show my ability to take a step by step approach to show understanding of the problem and core software design ideas. The result was pretty lengthy, as I tried to do as much as I could using the bare minimum provided in C language and design as I would for embedded software in the automotive industry.

There are certainly multiple ways to code this. I ended up having functions return pointers to strings to stay organized. This felt a bit foul since I had to account for large strings, dynamic memory allocated to the heap had to be freed in a different function then the one it was orginally allocated in. I normally would try to avoid this, but I cringe at modifying a global pointer between multiple functions. A global variable might read better for some, but this strategy seems to manage the location of the pointer distinctly. 
