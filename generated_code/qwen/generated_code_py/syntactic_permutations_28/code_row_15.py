import re

# Compile the regular expression pattern for matching URLs once when the module is loaded
url_pattern = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:[0-9]+)?(/.*)?$')

def get_redirect_url(input_url, default_url='http://default.example.com'):
    # Check if the input URL matches the compiled regular expression
    if url_pattern.match(input_url):
        return input_url  # Use matched URL as the redirect target
    else:
        return default_url  # Use default URL if no match

# Example usage
if __name__ == "__main__":
    test_url = "https://example.com"
    print(get_redirect_url(test_url))  # Output: https://example.com

    invalid_url = "ftp://invalid-url"
    print(get_redirect_url(invalid_url))  # Output: http://default.example.com