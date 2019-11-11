#!/bin/bash

set -euo pipefail

usage() {
  echo "Generate all permutations of the characters in a string"
  echo ""
  echo "Usage:"
  echo "  ./generate-permutations.sh <string>"
  echo ""
}

if [[ $# -ne 1 ]]; then
  usage
  exit 1
fi

# https://stackoverflow.com/a/3846321
perm() {
  local items="$1"
  local out="$2"
  local i
  [[ "$items" == "" ]] && echo "$out" && return
  for (( i=0; i<${#items}; i++ )) ; do
    perm "${items:0:i}${items:i+1}" "$out${items:i:1}"
  done
}

perm $1 ""
