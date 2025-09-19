import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r"https://example\.com/special-path")

def get_redirect_url(target_url):
    # Check if the target URL matches the compiled pattern
    if pattern.match(target_url):
        return target_url  # Use as redirect target if it matches
    else:
        return "https://default-redirect.com"  # Fallback URL

# Example usage
if __name__ == "__main__":
    urls = [
        "https://example.com/special-path",
        "https://example.com/another-path",
        "https://otherdomain.com/page"
    ]
    
    for url in urls:
        print(f"Original: {url} -> Redirect: {get_redirect_url(url)}")