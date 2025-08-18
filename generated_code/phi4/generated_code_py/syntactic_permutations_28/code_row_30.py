import re

# Compile the regular expression once when the module is loaded.
regex_pattern = r'^https?://(?:www\.)?example\.com/.*$'
compiled_regex = re.compile(regex_pattern)

def get_redirect_target(target_url, default_url='https://default.example.com'):
    # Use the compiled regex to match the target URL
    if compiled_regex.match(target_url):
        return target_url  # Redirect to the target URL if it matches
    else:
        return default_url  # Use a default URL if no match

# Example usage
if __name__ == "__main__":
    urls = [
        'https://www.example.com/page1',
        'http://example.com/page2',
        'https://anotherdomain.com/page3'
    ]
    
    for url in urls:
        print(f"Original: {url} -> Redirected to: {get_redirect_target(url)}")