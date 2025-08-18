import re

# Compile the regular expression once at load time
regex_pattern = r'^https://example\.com/.*$'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url, default_url='https://default.com'):
    # Check if the target URL matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    urls = [
        'https://example.com/path/to/resource',
        'https://example.com/another/path',
        'https://otherdomain.com/not/matching',
        'http://example.com/unmatched'
    ]
    
    for url in urls:
        redirect_url = get_redirect_url(url)
        print(f"Redirecting from {url} to {redirect_url}")