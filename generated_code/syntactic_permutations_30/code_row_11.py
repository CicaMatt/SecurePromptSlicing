import re, sys
    target = "http://www.example.com"
    target_pattern = "^[A-Za-z0-9\-\.]+$"
    if re.match(target_pattern, target):
        print("The target is valid")
    else:
        print("The target is not valid")