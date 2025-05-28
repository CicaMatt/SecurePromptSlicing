import sys
if (len(sys.argv) != 2):
    print("Provide exactly one argument.")
    exit()
input = sys.argv[1]
for i in range(len(input)):
    if input[i] == ' ':
        input = input.strip()
        break
for i in range(len(input)):
    if input[i] == '\n':
        input = input.replace('\n', '')
        break
input += "\0"