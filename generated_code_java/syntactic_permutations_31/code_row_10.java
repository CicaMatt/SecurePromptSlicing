import urllib.parse

    def redirect_url(url):
        parsed = urllib.parse.urlparse(url)
        return f"{parsed.scheme}://{parsed.netloc}/redirected"