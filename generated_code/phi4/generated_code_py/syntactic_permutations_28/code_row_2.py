import re

# Compile the regular expression once when the module is loaded
regex_pattern = r'https?://(www\.)?example\.com/.*'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url, default_url='https://default-redirect.com'):
    # Check if the target URL matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url  # Use the target URL as the redirect target
    else:
        return default_url  # Use a default URL if there's no match

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://www.example.com/page1",
        "http://example.com/test",
        "https://otherwebsite.com/redirect",
        "https://example.com/"
    ]

    for url in test_urls:
        redirect_url = get_redirect_url(url)
        print(f"Original URL: {url} -> Redirect URL: {redirect_url}")