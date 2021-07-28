# File-recovery
Implement a program that recovers JPEGs from a forensic image, per the below.

$ ./recover card.raw

Background

In anticipation of this problem, we spent the past several days taking photos of people we know, all of which were saved on a digital camera as JPEGs on a memory card. (Okay, it’s possible we actually spent the past several days on Facebook instead.) Unfortunately, we somehow deleted them all! Thankfully, in the computer world, “deleted” tends not to mean “deleted” so much as “forgotten.” Even though the camera insists that the card is now blank, we’re pretty sure that’s not quite true. Indeed, we’re hoping (er, expecting!) you can write a program that recovers the photos for us!

Implement a program called recover that recovers JPEGs from a forensic image.

    Implement your program in a file called recover.c in a directory called recover.
    Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
    If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
    If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    Your program, if it uses malloc, must not leak any memory.
Usage

Your program should behave per the examples below.

$ ./recover
Usage: ./recover image

$ ./recover card.raw

