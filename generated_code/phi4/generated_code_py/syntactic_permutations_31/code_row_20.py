from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name.endswith('.com'):
        return f"https://www.example.com/redirect?url={url}"
    elif domain_name.endswith('.org'):
        return f"https://www.orgexample.com/redirect?url={url}"
    else:
        return "Domain not supported for redirection."

# Example usage
print(redirect_url("http://www.someone.com"))