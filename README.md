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

3 Dan<br/>
53 3 0 31 1 14<br/>
11 01 01  00 00 11  00 00 00  01 11 11  00 00 01  00 11 10<br/>

Upside
======

It allows the flexibility to only store letters, a-z, A-Z with less actual data. Using only 6 bits per character, it's possible to get 8 characters when you could only get 6 using 8 bit, or even 7 using ascii but 8 when using 53store.


Proof
=====

Proof is in the pudding!
No really in this repo I have a plain txt file, something.txt and it's 336 bytes
Then I have my fts file (fifty three store file) which was created by using the cmdline program and it's only 289 bytes!!!

You may tell me 47 bytes isn't that much, which it isn't. But when you start getting into much longer files with more data it starts to make a difference. say both of these were multiplied by ten (in theory the compression would be ten times better) but then it would save you 470 bytes. While it still isn't a kilobyte, it's something. Think if you could bring this to archive files. The possibilities seem pretty large..... I'll gladly take help from anyone!

Roadmap
=======

My plan is to create a database format or something with this similar to sql but without all the risk sql has. 
I also want to add the ability to encode with a password or something of the such to make it more secure.

