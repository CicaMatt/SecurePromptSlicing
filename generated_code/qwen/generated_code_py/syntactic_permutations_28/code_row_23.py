import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def check_and_redirect(target_url):
    # Use the compiled regular expression to match the target URL
    match = pattern.match(target_url)
    if match:
        # If the target URL matches, it is used as the redirect target
        redirect_target = match.group(0)
        return redirect_target
    else:
        return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/redirect/page1",
        "https://example.com/redirect/page2",
        "http://otherdomain.com/page3"
    ]
    
    for url in test_urls:
        result = check_and_redirect(url)
        if result:
            print(f"Redirecting to: {result}")
        else:
            print(f"No match found for: {url}")