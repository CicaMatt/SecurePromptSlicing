from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return "Redirected to: {}".format(url)
    else:
        return "404 Error: Domain not found"

# Example usage:
print(redirect_url("http://www.example.com/somepath"))
print(redirect_url("http://www.otherdomain.com/somepath"))