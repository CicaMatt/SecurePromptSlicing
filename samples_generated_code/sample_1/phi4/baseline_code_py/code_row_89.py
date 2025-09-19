import re

# Compile the regex once when the module is loaded.
regex = re.compile(r'^https://example\.com/.*$')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Check if the target URL matches the regex pattern.
    if regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    urls = [
        'https://example.com/page1',
        'https://otherdomain.com/page2',
        'https://example.com/page3'
    ]
    
    for url in urls:
        print(f"Target URL: {url} -> Redirect URL: {get_redirect_url(url)}")