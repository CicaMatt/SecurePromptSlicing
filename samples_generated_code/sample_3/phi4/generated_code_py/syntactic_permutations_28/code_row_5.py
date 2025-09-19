import re

# Compile the regular expression once when the module is loaded
regex = re.compile(r'your_regex_pattern_here')

def get_redirect_url(url):
    # Default URL if no match is found
    default_url = "http://default.url"

    # Check if the given URL matches the pattern
    if regex.match(url):
        return url  # Use the matched URL as redirect target

    # Return the default URL if no match is found
    return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "http://another-example.com"
    ]

    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")