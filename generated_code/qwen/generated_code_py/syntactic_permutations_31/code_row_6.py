from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return "Redirected to example.com"
    else:
        return "404 Not Found"

# Example usage
if __name__ == "__main__":
    print(redirect_url("http://example.com/somepage"))
    print(redirect_url("http://anotherdomain.com"))