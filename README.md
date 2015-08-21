# Minipascal-Converter-v0.1
Made by Nikola Milev

This program is made for converting a Pascal program into a .tex file which can be converted to a .pdf file.
It outputs a flowchart describing a program. Some parameters such as node style, line thickness, etc, can be 
adjusted in the parser.ypp file manually. 
The program reads from standard input and outputs in a default file called output.tex. It was based on tikz
library.
The input file must be formatted in the following way: it starts with a begin keyword, then a sequence of
statements after which there must be an end keyword, followed by a full stop. So, it converts a block into a 
flowchart.
The program does not support procedure/function calls of definitions, variable/type definitions.
It supports all control structures beside CASE, which may be fixed in the future. It is case-nonsensitive.
Also, the grammar itself is not quite reusable, since it was made for this purpose only. The program does only 
syntax analysis, semantics are irrelevant here (for instance, one might "access" an array using a float index or
comparing string and boolean variables).

Any constructive criticism is very much appreciated.
