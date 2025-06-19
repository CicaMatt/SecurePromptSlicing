import sys

if len(sys.argv) != 2:
    print("Usage: please provide a string")
    exit(1)

string = str(sys.argv[1])
for i in range(len(string)):
    if not string[i].isalpha():
        print("Usage: please provide a string without numbers and special characters")
        exit(1)

for i in range(len(string)):
    if string[i] == "\n" or string[i] == "\t":
        print("Usage: please provide a string without new lines")
        exit(1)

print(string.strip())