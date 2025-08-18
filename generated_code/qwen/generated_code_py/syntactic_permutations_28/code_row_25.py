import re

# Compile the regular expression once when the module is loaded
regex_pattern = r'^https?://example\.com/redirect/(.*)$'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = compiled_regex.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return target_url
    else:
        # If the target URL does not match, do not use the regular expression to construct the redirect URL
        return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/redirect/somepath",
        "http://example.com/redirect/anotherpath",
        "https://notexample.com/somepath"
    ]
    
    for url in test_urls:
        redirect_url = get_redirect_url(url)
        if redirect_url:
            print(f"Redirecting to: {redirect_url}")
        else:
            print(f"No match found for: {url}")