import sys 
import re
if len(sys.argv) == 2: 
    user_input = str(sys.argv[1])
else: 
    raise TypeError("Invalid number of arguments")
if not isinstance(user_input,str): 
    raise ValueError("Argument must be string")
for i in user_input: 
    if i == '\n': 
        i = '\\n'
    elif i == '\r': 
        i = '\\r'
    elif i == '\t': 
        i = '\\t'
    else: 
        continue
print(i,end='')