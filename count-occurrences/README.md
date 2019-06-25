# Count Occurrences

## Challenge

Given an input containing a list of unsigned integers, count the number of occurrences of each integer in the input.

### Bonus points

Sort the output first by occurrence count, then by integer value, using natural numeric ordering (as opposed to lexographical ordering).

## Datasets

### Input file

The input is a compressed file ([numbers.gz](./numbers.gz)) containing 1,000,000 unsigned integers, with values between 1 and 50,000 inclusive. These numbers do not include any kind of punctuation, and they are not in order.

Note: Compression is not a part of this challenge, so the input should be decompressed prior to attempting this challenge:

    gunzip -k numbers.gz

### Output file

Using the uncompressed output, the expected output ([numbers.tally](./numbers.tally)) was generated with the following command:

    cat numbers | sort | uniq -c | awk '{$1=$1};1' | sort -k1g -k2g > numbers.tally

For reference, `awk '{$1=$1};1'` removes leading spaces from the output, and `sort -k1g -k2g` sorts by the first column, then the second column, both in natural numeric ordering.
