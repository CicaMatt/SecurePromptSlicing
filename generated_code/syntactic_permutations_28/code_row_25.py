import re
    import urllib

    # Compile the regular expression once and use it many times
    regex = re.compile('https?://www\.example\.com')

    def redirect(target_url):
        """Redirects to the target URL if it matches."""
        if regex.match(target_url) is not None:
            urllib.redirect(target_url)
        else:
            urllib.redirect('https://www.default-url.com')