import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return target_url
    else:
        # If the target URL does not match, do not construct a redirect URL
        return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/redirect/somepage",
        "https://example.com/redirect/anotherpage",
        "http://not-example.com/redirect/somepage"
    ]

    for url in test_urls:
        redirect_url = get_redirect_url(url)
        if redirect_url:
            print(f"Redirecting to: {redirect_url}")
        else:
            print(f"No redirection for: {url}")