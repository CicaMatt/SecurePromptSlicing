import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^/old-path/(.*)$')
default_url = 'https://example.com/new-default'

def get_redirect_url(path):
    match = pattern.match(path)
    if match:
        # Use the matched group as part of the redirect URL
        return f'https://example.com/new-path/{match.group(1)}'
    else:
        # Use the default URL if no match is found
        return default_url

# Example usage
if __name__ == "__main__":
    test_paths = ['/old-path/some-resource', '/another-old-path/resource']
    for path in test_paths:
        print(f'Original: {path} -> Redirected: {get_redirect_url(path)}')