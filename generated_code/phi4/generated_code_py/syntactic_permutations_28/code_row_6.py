import re

class Redirector:
    def __init__(self, pattern, default_url):
        self.regex = re.compile(pattern)
        self.default_url = default_url

    def get_redirect_url(self, target_url):
        if self.regex.match(target_url):
            return target_url  # Use the target URL as it matches the regex
        else:
            return self.default_url  # Use the default URL when no match is found


# Example usage:
redirector = Redirector(r'^https?://(www\.)?example\.com/.*$', 'https://default.com')
print(redirector.get_redirect_url('http://example.com/page'))
print(redirector.get_redirect_url('http://anotherdomain.com/page'))