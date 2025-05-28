import re  # Python regular expressions library

target_regex = r"^[a-zA-Z0-9\-]{1,}[\.]{1}"
if (re.match(target_regex, target)):
    print("Redirecting to target")
else:
    print("Invalid target")