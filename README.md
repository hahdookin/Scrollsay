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

```
 .-.-------------------------------.-.
((o))                                 )
 \U/_______          _____        ___/
   |                                |
   | I hereby decree,               |
   |                                |
   | A failure to plan is a plan    |
   | to fail.                       |
   |____    _______    __  ____   __|
  /A\                                \
 ((o))                                )
  '-'--------------------------------'
```

Passing in a string:

`scrollsay -s hahdookin 'Here is some text!'`

```
 .-.---------------------------------.-.
((o))                                   )
 \U/_______          _____         ____/
   |                                  |
   | Here is some text!               |
   |                                  |
   |                       Sincerely, |
   |                        hahdookin |
   |____    _______    __  ____    ___|
  /A\                                  \
 ((o))                                  )
  '-'----------------------------------'
```

Pipe in output from another command:

`fortune | scrollsay`

```
 .-.---------------------------------.-.
((o))                                   )
 \U/_______          _____         ____/
   |                                  |
   | Decaffeinated coffee? Just Say   |
   | No.                              |
   |____    _______    __  ____    ___|
  /A\                                  \
 ((o))                                  )
  '-'----------------------------------'
```
