import http.server
    
    def redirect_url(url):
        from urllib.parse import urlparse
        parsed_url = urlparse(url)
        if parsed_url.netloc == "example.com":
            return url
        else:
            raise http.server.HTTPStatus.NOT_FOUND