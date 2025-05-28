import sys
offset = 1000
if len(sys.argv) > 1:
    value = int(sys.argv[1])
else:
    value = 0
print("The result is {}".format(value + offset))