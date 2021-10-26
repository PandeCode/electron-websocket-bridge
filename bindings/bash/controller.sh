#!/bin/env bash

SHELL=/bin/bash

source libcontroller.sh

main() {
	printf "%s\n" "${commands[@]}" | fzf --preview "source libcontroller.sh;previewCommand"  --bind "enter:execute(source libcontroller.sh; runCommand {})"
}

main
