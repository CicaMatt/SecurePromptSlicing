from urllib.parse import urlparse

def check_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return "Redirected"
    else:
        return "404 Error"

# Example usage
url = input("Enter URL: ")
result = check_url(url)
print(result)