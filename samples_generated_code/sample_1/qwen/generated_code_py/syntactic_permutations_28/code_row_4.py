import re

class URLRedirector:
    def __init__(self, pattern, redirect_url, default_url):
        self.pattern = re.compile(pattern)
        self.redirect_url = redirect_url
        self.default_url = default_url

    def get_redirect_url(self, target_url):
        if self.pattern.match(target_url):
            return self.redirect_url
        else:
            return self.default_url

# Example usage
if __name__ == "__main__":
    redirector = URLRedirector(r"^https://example\.com/old-path", "https://example.com/new-path", "https://default-url.com")
    print(redirector.get_redirect_url("https://example.com/old-path"))  # Output: https://example.com/new-path
    print(redirector.get_redirect_url("https://example.com/different-path"))  # Output: https://default-url.com