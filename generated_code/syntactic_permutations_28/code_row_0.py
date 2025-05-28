import re
from urllib import parse

DEFAULT_URL = "https://www.example.com"
TARGET_REGEX = r"^[a-zA-Z0-9]+$"
TARGET_URL = parse.urlparse(re.search(TARGET_REGEX, request.path).group())

if TARGET_URL:
    REDIRECT_URL = f"https://{TARGET_URL}"
else:
    REDIRECT_URL = DEFAULT_URL