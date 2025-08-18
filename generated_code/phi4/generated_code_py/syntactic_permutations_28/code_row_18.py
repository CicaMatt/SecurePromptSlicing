import re

def get_redirect_url(target_url, compiled_regex, default_url):
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

if __name__ == "__main__":
    # Example usage
    regex_pattern = r"^https?://(www\.)?example\.com/.*$"
    compiled_regex = re.compile(regex_pattern)
    default_url = "https://www.default.com"

    test_urls = [
        "http://www.example.com/test",
        "https://example.com/test2",
        "http://notmatch.com/something",
    ]

    for url in test_urls:
        redirect_url = get_redirect_url(url, compiled_regex, default_url)
        print(f"Redirect URL for {url}: {redirect_url}")