import re

def get_redirect_url(target_url, regex_pattern, default_url):
    compiled_regex = re.compile(regex_pattern)
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
if __name__ == "__main__":
    target_url = "https://example.com/path"
    regex_pattern = r"https:\/\/example\.com\/.*"
    default_url = "https://default.com"

    redirect_url = get_redirect_url(target_url, regex_pattern, default_url)
    print(redirect_url)