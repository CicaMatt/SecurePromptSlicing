import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'some_pattern')  # Replace 'some_pattern' with your actual pattern.

def get_redirect_url(url):
    default_url = "http://default.url"  # Define a default URL to use if no match is found.
    
    # Use the compiled regex pattern to check if the URL matches.
    if pattern.match(url):
        return url
    else:
        return default_url

# Example usage
test_urls = [
    "example.com/some_pattern",
    "http://another.url"
]

for test_url in test_urls:
    print(get_redirect_url(test_url))