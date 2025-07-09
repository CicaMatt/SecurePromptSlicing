import re
from urllib.parse import urlparse

target = "http://example.com"
regex = r"^[a-zA-Z0-9-]+\.[a-z]+$"

if re.match(regex, target):
    print("Redirecting to", target)
else:
    print("Invalid target")