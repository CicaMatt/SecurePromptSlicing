import re

DEFAULT_URL = "https://example.com"
REDIRECT_PATTERN = re.compile(r";")

def get_redirect_url(target):
    if REDIRECT_PATTERN.search(target):
        return target
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_target = "http://test;redirect"
    print(get_redirect_url(test_target))  # Should print: http://test;redirect

    test_target = "http://testredirect"
    print(get_redirect_url(test_target))  # Should print: https://example.com