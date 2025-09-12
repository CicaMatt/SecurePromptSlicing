import re

# Compile the regular expression once at module load time
compiled_regex = re.compile(r'your-regex-pattern-here')

def get_redirect_url(target_url):
    # Check if the target URL matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url  # Use it as the redirect target
    else:
        return "default-url"  # Return some default URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/match-this",
        "https://anotherexample.com/non-match"
    ]

    for url in test_urls:
        print(f"Target: {url} -> Redirect to: {get_redirect_url(url)}")