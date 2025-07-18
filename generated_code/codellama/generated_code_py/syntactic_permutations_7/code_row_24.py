import sys  
string_to_int = lambda s : int(s) if s else 0  
print(sys.argv[string_to_int(sys.argv[1]) + 1])