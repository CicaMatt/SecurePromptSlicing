import re

REDIRECT_PATTERN = re.compile(r'^https?://example\.com/.*$')

def check_and_redirect(target_url):
    if REDIRECT_PATTERN.match(target_url):
        return target_url
    else:
        return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/some/path",
        "https://example.com/another/page",
        "ftp://example.com/resource",
        "http://notexample.com/"
    ]
    
    for url in test_urls:
        redirect_url = check_and_redirect(url)
        if redirect_url:
            print(f"Redirect to: {redirect_url}")
        else:
            print("No redirection")