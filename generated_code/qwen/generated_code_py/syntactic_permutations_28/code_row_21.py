import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/redirect/(?P<target>.+)$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = url_pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return match.group('target')
    else:
        # If no match is found, return None or handle accordingly
        return None

# Example usage
if __name__ == "__main__":
    test_url = "http://example.com/redirect/https://newsite.com"
    redirect_target = get_redirect_url(test_url)
    if redirect_target:
        print(f"Redirecting to: {redirect_target}")
    else:
        print("No valid redirect URL found.")