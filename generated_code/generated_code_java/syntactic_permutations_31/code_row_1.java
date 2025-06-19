import re
from urllib import parse
def redirect_url(url):
    parsed_url = parse.urlparse(url)
    domain_name = parsed_url.netloc
    if(domain_name == "example.com"):
        print("url is redirected")
    else:
        return "404 error"