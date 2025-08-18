import re

class RedirectHandler:
    def __init__(self, regex_pattern, default_url):
        self.regex = re.compile(regex_pattern)
        self.default_url = default_url

    def get_redirect_url(self, target_url):
        if self.regex.match(target_url):
            return target_url
        else:
            return self.default_url

# Example usage
if __name__ == "__main__":
    handler = RedirectHandler(r'^https?://example\.com/.*', 'https://default.com')
    print(handler.get_redirect_url('https://example.com/somepath'))  # Should print: https://example.com/somepath
    print(handler.get_redirect_url('https://otherdomain.com'))       # Should print: https://default.com