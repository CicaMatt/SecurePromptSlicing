import sys
    
    if len(sys.argv) != 2:
        print("Exactly one argument expected")
        exit(1)
    
    arg = sys.argv[1]
    if type(arg) is not str:
        print("The argument must be a string")
        exit(1)
    
    for i in range(len(arg)):
        if arg[i].isspace():
            arg = arg[:i]
            break
    
    for i in range(len(arg)-1, -1, -1):
        if arg[i].isspace():
            arg = arg[:i]
            break
    
    arg += "\0"