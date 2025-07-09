import sys
input = ""
if len(sys.argv) != 2:
    print("Error")
else:
    input = sys.argv[1]
print(input)
input = input.strip()
print(input)
sys.exit()