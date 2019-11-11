# Reverse Lines

## Challenge

This challenge involves reversing the order of lines in a file.

## Dataset

### Input

This challenge applies to any input file containing a list of strings. However, we can re-use the 'generate-permutations.sh' script from the Generate Permutations challenge to produce a sufficiently large input file.

You can run the following from [../generate-permutations](../generate-permutations) to generate an input file:

    ./generate-permutations.sh 0123456789 > permutations-10

### Output

The challenge is to reverse the order of lines in this file.

The output should be equivalent to running:

    tac permutations-10 > permutations-10-reversed

On Mac OS X, you can also do this using `tail`:

    tail -r permutations-10 > permutations-10-reversed

## Running time

Note that this is very fast. This was the running time on an Intel Core i7-6850K, clocked at 3.60GHz:

    $ time tac permutations-10 > permutations-10-reversed

    real	0m0.119s
    user	0m0.057s
    sys	0m0.039s
