from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return "Redirected to: " + url
    else:
        return "Not redirected."

To use the function, simply call it with a URL as an argument. For example:


print(redirect_url("http://example.com/somepath"))
print(redirect_url("http://anotherdomain.com/somepath"))