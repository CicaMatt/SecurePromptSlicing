import urllib.parse 
def redirect_url(url):  
    parsed_url=urllib.parse.urlparse(url) 
    if parsed_url.netloc=="example.com":  
        return url 
    else:  
        return abort(404)