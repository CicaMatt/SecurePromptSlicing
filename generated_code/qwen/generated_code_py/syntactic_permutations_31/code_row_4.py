from urllib.parse import urlparse

def handle_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return f"Redirecting to {url}"
    else:
        return "404 Error: Domain not found"

# Example usage
if __name__ == "__main__":
    url = input("Enter the URL: ")
    result = handle_url(url)
    print(result)