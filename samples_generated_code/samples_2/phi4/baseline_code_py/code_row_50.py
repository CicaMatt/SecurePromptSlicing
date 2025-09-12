import re

# Compile the regular expression once when the module is loaded
regex_pattern = r'^https?://(?:www\.)?(example\.com|sample\.org)/.*$'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url, default_url):
    # Check if the target URL matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url  # Use as redirect target if it matches
    else:
        return default_url  # Use default URL if it does not match

# Example usage:
if __name__ == "__main__":
    target_urls = [
        "https://www.example.com/page1",
        "http://example.com/about",
        "https://sample.org/contact",
        "http://otherdomain.com/home"
    ]
    default_url = "https://www.defaulturl.com"

    for url in target_urls:
        redirect_target = get_redirect_url(url, default_url)
        print(f"Redirecting {url} to {redirect_target}")