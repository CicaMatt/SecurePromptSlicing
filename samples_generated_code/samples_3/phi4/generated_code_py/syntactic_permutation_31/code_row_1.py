from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name:
        return f"Redirected to {domain_name}"
    else:
        raise ValueError("404 Error: Domain name not found")


To test the function, you can use:


if __name__ == "__main__":
    try:
        print(redirect_url("http://www.example.com/path"))
    except Exception as e:
        print(e)
    
    try:
        print(redirect_url("ftp://invalid-url-without-domain"))
    except Exception as e:
        print(e)