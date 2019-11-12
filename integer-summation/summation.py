#!/usr/bin/env python3

import random

random.seed(1)

# A list tuples of problem sizes.
#
# Each tuple contains a sequence of integers that denote the digit length of
# each paramter.
digits = [ 
    (1, 1), (1, 1), (1, 1), (1, 1),
    (1, 2), (1, 2), (1, 2), (1, 2),
    (2, 1), (2, 1), (2, 1), (2, 1),
    (3, 5), (3, 5),
    (5, 4),
    (9, 7),
    (5,),
    (20, 20),
    (30, 40),
    (40, 30),
    (80, 80),
    (200, 200), (200, 200), (200, 200),

    (1, 1, 1), (1, 1, 1), (1, 1, 1),
    (2, 2, 2), (2, 2, 2), (2, 2, 2), 
    (4, 4, 4), (4, 4, 4),

    (200, 200, 200, 200, 200),

    (5,) * 10,
    (5,) * 100,
    (5,) * 1000,
]

# Generate a random number consisting of `digits` count of random digits.
#
# Note: if the leading digit is zero the result is indistinguishable from a
# request for `digits-1` digits.
def generate(digits: int) -> int:
    out = int(0)
    for i in range(digits):
        out = out * 10 + random.randint(0, 9)
    return out

import subprocess
import argparse
import sys

parser = argparse.ArgumentParser()
parser.add_argument("executable", type=str)
args = parser.parse_args()

successes = 0

# Test each set of problems.
for (index, instance) in zip(range(len(digits)), digits):
    vals = [ generate(d) for d in instance ]

    # Run the supplied executable with the values from the problem instance as arguments
    cmd = [ args.executable, *(str(i) for i in vals) ]
    res = subprocess.run(cmd, capture_output=True)
    
    # Test that the output matches our expectaction   
    output = res.stdout.decode().strip()
    if output == str(sum(vals)):
        message = 'success'
        successes += 1
    else:
        message = 'fail'

    print(index, message)

# Exit with success if we've pass all the problems
sys.exit(0 if successes == len(digits) else 1)
