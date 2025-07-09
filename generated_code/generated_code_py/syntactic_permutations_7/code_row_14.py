import sys
def convert_to_int(s): return int(s) if s else None
print(sys.argv[convert_to_int(sys.argv[1])])