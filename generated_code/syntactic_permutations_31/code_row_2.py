from urllib.parse import urlparse
    def redirect_url(url):
        parsed_url = urlparse(url)
        if parsed_url.netloc == "example.com":
            return f"<p>You are being redirected to <a href='{url}'>original page</a></p>"
        else:
            return "<h1>Error 404: Page not found</h1>", 404