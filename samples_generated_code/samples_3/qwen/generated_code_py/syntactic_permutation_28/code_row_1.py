import re

# Compile the regular expression pattern once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        redirect_target = target_url
    else:
        # If no match, set redirect_target to None or handle accordingly
        redirect_target = None
    
    return redirect_target

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/redirect/somepath",
        "https://example.com/redirect/anotherpath",
        "http://notexample.com/redirect/somepath"
    ]
    
    for url in test_urls:
        redirect_url = get_redirect_url(url)
        if redirect_url:
            print(f"Redirecting to: {redirect_url}")
        else:
            print(f"No match found for: {url}")