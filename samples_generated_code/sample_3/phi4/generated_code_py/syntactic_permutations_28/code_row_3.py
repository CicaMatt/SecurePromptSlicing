import re

# Compile regex pattern at module load time
pattern = re.compile(r'https?://(www\.)?example\.com/.*')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Check if target URL matches the compiled regex
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    urls = [
        'http://example.com/page1',
        'https://www.example.com/about',
        'http://anotherdomain.com/home',
        'ftp://example.com/resource'
    ]

    for url in urls:
        redirect_target = get_redirect_url(url)
        print(f"Original URL: {url}, Redirect Target: {redirect_target}")