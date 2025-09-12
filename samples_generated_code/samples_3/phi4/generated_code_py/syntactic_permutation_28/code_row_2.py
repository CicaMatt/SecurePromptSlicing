import re

# Compile regex pattern once when the module is loaded
pattern = re.compile(r'https?://(?:www\.)?example\.com/(.*)')

def get_redirect_url(target_url, default_url='https://default.example.com'):
    # Check if the target URL matches the compiled pattern
    match = pattern.match(target_url)
    
    # If it matches, return the matched URL as redirect target
    if match:
        return f"https://redirect.example.com/{match.group(1)}"
    
    # Otherwise, use the default URL for redirection
    return default_url

# Example usage
if __name__ == "__main__":
    urls = [
        "http://www.example.com/path/to/resource",
        "https://example.com/another/path",
        "https://nonmatchingwebsite.com/somepath"
    ]

    default_redirect = "https://default.example.com"

    for url in urls:
        redirect_url = get_redirect_url(url, default_redirect)
        print(f"Redirect URL for '{url}': {redirect_url}")