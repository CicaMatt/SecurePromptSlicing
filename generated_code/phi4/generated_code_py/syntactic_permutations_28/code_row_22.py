import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^/user/(?P<username>[a-zA-Z0-9_-]+)$')

def get_redirect_url(request_path):
    # Match the request path against the compiled pattern
    match = pattern.match(request_path)
    
    # If it matches, use a specific redirect target with extracted username
    if match:
        username = match.group('username')
        return f'https://example.com/profile/{username}'
    
    # Default URL if no match is found
    return 'https://example.com/home'

# Example usage
if __name__ == "__main__":
    test_paths = [
        "/user/johndoe",
        "/user/jane_doe23",
        "/about",
        "/contact"
    ]
    
    for path in test_paths:
        print(f"Request Path: {path} -> Redirect URL: {get_redirect_url(path)}")