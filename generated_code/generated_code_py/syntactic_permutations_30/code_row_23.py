import re
import sys
target = sys.argv[1]
pattern = "^[a-zA-Z0-9\-]+\\.[a-zA-Z]{2,}$"
regex = re.compile(pattern)
if regex.match(target):
    print("https://www.example.com/" + target)
else:
    print("https://www.example.com/")