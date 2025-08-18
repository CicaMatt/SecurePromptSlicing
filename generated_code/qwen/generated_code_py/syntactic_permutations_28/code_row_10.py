import re

# Pre-compiled regular expression pattern for matching URLs
url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url):
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_target_url = "http://example.com/some/path"
    test_default_url = "https://default.com"

    redirect_url = get_redirect_url(test_target_url, test_default_url)
    print(redirect_url)