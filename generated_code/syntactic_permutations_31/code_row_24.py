def redirect_url(url):
    import urlparse
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == "example.com":
        return None