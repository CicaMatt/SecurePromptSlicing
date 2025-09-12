import re

# Compile the regular expression once at module load time.
REDIRECT_REGEX = re.compile(r';')

def get_redirect_url(target_url, default_url='http://default.url'):
    # Check if target URL matches the compiled regex pattern.
    if REDIRECT_REGEX.search(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com;redirect',
        'http://anotherexample.com',
        'https://yetanother.com/path;to/resource'
    ]
    
    for url in test_urls:
        print(get_redirect_url(url))