import re

DEFAULT_URL = 'http://default.com'
REDIRECT_PATTERN = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$')

def get_redirect_url(target):
    if REDIRECT_PATTERN.match(target):
        return target
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    print(get_redirect_url('http://example.com'))  # Should print: http://example.com
    print(get_redirect_url('invalid-url'))         # Should print: http://default.com