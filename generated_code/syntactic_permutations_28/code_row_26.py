import re
target_url_regex = r'http://www\.example\.com'
default_url = 'http://www.example.com/invalid-redirect'
def get_redirect_url(target_url):
    """Get the redirect URL"""
    if re.match(target_url_regex, target_url):
        return target_url
    else:
        return default_url