# Scrollsay
Generates an ASCII art scroll with a message in the terminal.

### Installation
Clone into a folder and run `make`.

Add path to `scrollsay` to your env if you'd like.

### Usage
`scrollsay [options] [file]`

Try `scrollsay --help` for more.

### Examples
Input from a file:

`scrollsay -i -w 30 input.txt`

Passing in a string:

`scrollsay -s hahdookin 'Here is some text!'`

Pipe in output from another command:

`fortune | scrollsay`
