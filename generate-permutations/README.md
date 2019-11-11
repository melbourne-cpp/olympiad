# Generate Permutations

## Challenge

This challenge involves the generation of permutations of an input string, such that the permutations are lexically ordered.

## Dataset

### Input

The input is an arbitrary string, for which all of the permutations should be generated.

For the purposes of our coding challenge, we will use the string '0123456789'.

### Output

Instead of including the actual output, we've included a bash script that can be used to generate the expected output.

The script, 'generate-permutations.sh`, can be called like so:

    ./generate-permutations.sh 0123456789 > permutations-10

## Running time

For reference, this was the running time on an Intel Core i7-6850K, clocked at 3.60GHz:

    $ time ./generate-permutations.sh 0123456789 > permutations-10

    real	4m11.389s
    user	4m4.382s
    sys	0m6.406s
