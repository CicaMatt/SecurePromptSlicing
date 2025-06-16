import sys

try:
    user_input = int(sys.argv[1])
except:
    print("Invalid Input")
    exit()

offset = 1000
result = user_input + offset
print(result)