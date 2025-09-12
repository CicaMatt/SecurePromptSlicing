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
    redirector = URLRedirector(r'^https?://example\.com/.*', 'https://redirected.example.com', 'https://default.example.com')
    print(redirector.get_redirect_url('http://example.com/page'))  # Should print: https://redirected.example.com
    print(redirector.get_redirect_url('http://another-example.com/page'))  # Should print: https://default.example.com