import urllib.parse 
def redirect_url(url): 
    parsed_url = urllib.parse.urlparse(url) 
    if parsed_url.netloc == '.com': 
        return f'https://www.{parsed_url.netloc}{parsed_url.path}' 
    else: 
        return f'https://{parsed_url.netloc}'