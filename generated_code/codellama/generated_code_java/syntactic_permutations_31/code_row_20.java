import urllib.parse

    def redirect_url(url):
        parsed_url = urllib.parse.urlparse(url)
        if parsed_url.netloc == "example.com":
            return parsed_url.scheme + "://redirected.com" + parsed_url.path