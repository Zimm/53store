Basis
=====

53Store is a storing system that aims to shrink files. I am not completely sure that it will work, but it will be a fun ride to create it. 

How it works
============

53store will store only up to the number 53, encoding all characters into decimal up to 53. a-z are 1-26, A-Z are 27-52, and 53 will be the /modifier/ character. I imagine it as an escape character almost that will modify any of the 52 letters into symbols. In theory this can give unlimited symbols to store, you could have two of the "escapes" to tell that the next two digits will be put together to create a new character, or three, and so on and so forth.

Example
=======

poop<br/>
16 15 15 16<br/>
01 00 00  00 11 11  00 11 11  01 00 00<br/>

© Dan<br/>
53 3 53 1 31 1 14<br/>
11 01 01  00 00 11  11 01 01  00 00 01  01 11 11  00 00 01  00 11 10<br/>

Upside
======

It allows the flexibility to only store letters, a-z, A-Z with less actual data. Using only 6 bits per character, it's possible to get 8 characters when you could only get 6 using 8 bit, or even 7 using ascii but 8 when using 53store.



