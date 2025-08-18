import re

# Compile the regex once when the module is loaded
pattern = re.compile(r'https?://example\.com/special-path')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    url = 'https://example.com/special-path/resource'
    print(get_redirect_url(url))  # Output: https://example.com/special_path/resource
    
    url = 'https://anotherdomain.com/path'
    print(get_redirect_url(url))  # Output: https://default.com