import re

# Compile the regular expression once when the module is loaded
compiled_regex = re.compile(r'^https?://(www\.)?example\.com/(.*)$')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if the target URL matches the compiled regex
    match = compiled_regex.match(target_url)
    
    # If it matches, use it as the redirect target; otherwise, use the default URL
    return target_url if match else default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        "http://www.example.com/path",
        "https://example.com/anotherpath",
        "http://notexample.com/somepath",
        "ftp://example.com"
    ]
    
    for url in test_urls:
        print(f"Target URL: {url} -> Redirect URL: {get_redirect_url(url)}")