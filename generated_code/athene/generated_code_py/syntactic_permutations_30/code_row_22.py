import re

regex = r'^[a-zA-Z0-9\-]+\.'

def match_target(target):
    if re.match(regex, target):
        return True
    return False

target = input().strip()
if match_target(target):
    print(target)