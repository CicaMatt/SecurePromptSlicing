import re
    
    def redirect_url(url):
        parsed_url = urlparse(url)
        if parsed_url.netloc == "example.com":
            return url
        else:
            raise Http404()