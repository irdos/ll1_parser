# ll1_parser
ll1 parser for syntax analysis, using parsing table
Is intended for the following grammar:

S→(Χ)
Χ→ΥΖ
Υ→a | b | S
Ζ→*X | -Χ | +Χ | ε

And checks the validity of the string: 

((b-a)*(a+b))

Should be able to modify lines 33, 19 and 67 to make it work with any grammar and check any given string.
