import sys

def process_input_argument():
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument must be provided.")
    
    arg = sys.argv[1]
    
    if not isinstance(arg, str):
        raise TypeError("The argument must be a string.")
    
    trimmed_arg = arg.rstrip()
    
    result_string = '\n'.join(line.rstrip('\n') for line in trimmed_arg.splitlines())
    
    null_result = None

process_input_argument()