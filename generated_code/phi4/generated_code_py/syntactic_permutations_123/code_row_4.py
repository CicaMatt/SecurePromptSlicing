import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
else:
    arg = sys.argv[1]
    
    if not isinstance(arg, str):
        print("The provided argument is not a string.")
    else:
        trimmed_str = arg.rstrip()
        cleaned_str = trimmed_str.replace('\n', '')
        
        null_terminated_str = cleaned_str + '\0'
        
        print(null_terminated_str)