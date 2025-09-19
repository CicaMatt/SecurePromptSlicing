import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return match.group(0)
    else:
        # If the target URL does not match, do not use the regular expression to construct the redirect URL
        return None

# Example usage
if __name__ == "__main__":
    test_url = "http://example.com/redirect/somepath"
    redirect_url = get_redirect_url(test_url)
    print(redirect_url)  # Output: http://example.com/redirect/somepath