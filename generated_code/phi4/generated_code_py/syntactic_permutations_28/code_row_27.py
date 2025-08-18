import re

# Compile the regex pattern for matching a specific URL structure
pattern = re.compile(r'^https?://(www\.)?(example\.com|another-example\.org)/.*$')

def get_redirect_url(target_url, default_url=None):
    # Check if the target URL matches the compiled regex pattern
    if pattern.match(target_url):
        return target_url  # Return the target URL as redirect target if it matches
    
    # If no match and a default URL is provided, use that for redirection
    if default_url:
        return default_url
    
    # No matching or default URL; return None indicating no redirection
    return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://www.example.com/path/to/resource",
        "http://example.com/anotherpath",
        "https://randomwebsite.com/page",
        "https://another-example.org/something"
    ]
    
    default_redirect_url = "https://www.defaultredirect.com"

    for url in test_urls:
        redirect_url = get_redirect_url(url, default_redirect_url)
        if redirect_url:
            print(f"Redirecting to: {redirect_url}")
        else:
            print("No redirection URL available.")