from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == '':
        return "No domain name found"
    else:
        return f"Domain name: {domain_name}"

# Example usage
if __name__ == "__main__":
    print(redirect_url("https://www.example.com"))
    print(redirect_url("http://example.org/path?query=123"))
    print(redirect_url("ftp://files.example.net/resource.txt"))
    print(redirect_url("invalid-url"))