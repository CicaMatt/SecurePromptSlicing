import re
target = parameter
if re.match("^[a-zA-Z0-9-]+\.", target):
    pass # redirect to target
else:
    target = "/"
    pass # redirect to root of site