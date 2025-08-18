import re

# Compile the regular expression when the module is loaded
compiled_regex = re.compile(r'your-regex-pattern-here')

def get_redirect_url(target_url, default_url='https://default-url.com'):
    # Check if the target URL matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        'http://example-matching-url.com',
        'https://nonmatching-url.org'
    ]
    
    for url in test_urls:
        redirect_url = get_redirect_url(url)
        print(f"Redirect URL for {url}: {redirect_url}")