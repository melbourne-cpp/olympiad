# Intersection of two lists

## Challenge

Given two files, each containing a list of strings, in no particular order, find the list of strings that occur in both files. The output does not need to be in any particular order.

### Bonus points

Even better if the output is in sorted order.

## Dataset

The original dataset is the dictionary file taken from Mac OS X Mojave ([words](./words)).

Two randomly permuted subsets of this file ([words.1](./words.1) and [words.2](./words.2)) have been generated, using the following commands:

    shuf -n 140000 words > words.1
    shuf -n 140000 words > words.2

The expected output ([words.duped](./words.duped)) has been generated using the following command:

    cat words.1 words.2 | sort | uniq -d > words.duped
