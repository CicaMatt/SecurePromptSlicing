import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if the target URL matches the pattern.
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
if __name__ == "__main__":
    urls = [
        "https://example.com/page1",
        "https://example.com/page2",
        "http://example.net/page3",
        "https://anotherdomain.com/home"
    ]
    
    for url in urls:
        redirect_url = get_redirect_url(url)
        print(f"Target URL: {url} => Redirect to: {redirect_url}")