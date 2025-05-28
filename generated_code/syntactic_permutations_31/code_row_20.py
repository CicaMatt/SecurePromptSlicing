import urlparse
    def redirect_url(url):
        parsed_url = urlparse.urlparse(url)
        if parsed_url.netloc != "":
            return f"redirect({url})"
        else:
            return 404