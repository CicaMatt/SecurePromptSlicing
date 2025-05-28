import urllib
    def redirect_url(url):
        from urllib.parse import urlparse
        parsed_url = urlparse(url)
        if parsed_url.netloc == "example.com":
            return "https://www.example.com"
        else:
            raise Exception("Invalid URL")