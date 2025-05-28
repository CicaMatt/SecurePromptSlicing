import re
REDIRECT_TARGET = re.compile(r"^/(?P<target>[a-f0-9]{32})$")
DEFAULT_URL = "https://www.example.com/"
def get_redirect_url(path):
    match = REDIRECT_TARGET.match(path)
    if not match:
        return DEFAULT_URL
    return f"https://{match['target']}.example.com/"