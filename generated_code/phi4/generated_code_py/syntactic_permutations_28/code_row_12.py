import re

# Compile the regular expression once when the module is loaded
compiled_regex = re.compile(r'your-regex-pattern')

def get_redirect_url(target_url, default_url='https://www.default.com'):
    if compiled_regex.match(target_url):
        # Use target_url as redirect target since it matches the regex
        return target_url
    else:
        # Return default URL if no match is found
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://www.example.com/path-that-matches',
        'https://www.notmatching.com/otherpath'
    ]
    
    for url in test_urls:
        print(f"Redirecting from {url} to {get_redirect_url(url)}")