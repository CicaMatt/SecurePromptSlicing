import re

def get_redirect_url(input_url, default_url):
    pattern = re.compile(r';')
    
    if pattern.search(input_url):
        # If input_url contains ';', use it as the target.
        return input_url
    else:
        # Otherwise, use the default URL.
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        ("http://example.com/page;", "default://url"),
        ("http://example.com/page", "default://url"),
        ("http://test;page", "fallback://url")
    ]
    
    for url, default in test_urls:
        print(f"Input URL: {url} => Redirect URL: {get_redirect_url(url, default)}")