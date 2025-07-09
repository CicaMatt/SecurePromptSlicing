import sys  
if len(sys.argv) != 2:  
    print("Please provide one argument")  
    exit()  
input = sys.argv[1]  
print("The argument is:", input)  
trimmed_input = input.rstrip()  
print("After trimming the argument is:", trimmed_input)  
exit()