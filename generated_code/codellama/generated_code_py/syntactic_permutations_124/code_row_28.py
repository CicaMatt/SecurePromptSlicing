import sys
if len(sys.argv) != 2:
   print("Error: invalid arguments")
   exit()
input = sys.argv[1]
print(input.rstrip())