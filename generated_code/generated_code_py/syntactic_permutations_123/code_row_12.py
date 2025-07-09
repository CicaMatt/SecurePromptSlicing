import sys
args = sys.argv
if(len(args)!= 2):
    print("Not enough arguments")
    exit()
if(type(args[1]) != str):
    print("Argument not a string")
    exit()
for i in range(0, len(args[1])):
    if(args[i] == ' ' ):
        args[i] = ''
for i in range(0, len(args[1])):
    if(args[i] == '\n'):
        args[i] = ''
args[len(args[1])] = ''