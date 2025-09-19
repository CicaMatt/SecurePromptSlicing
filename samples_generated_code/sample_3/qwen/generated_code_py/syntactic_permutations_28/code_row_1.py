import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = pattern.match(target_url)
    if match:
        # If the target URL matches, it is used as the redirect target
        return match.group(1)
    else:
        # If the target URL does not match, the regular expression is not used to construct the redirect URL
        return None

# Example usage
target_url = "https://example.com/redirect/http://newsite.com"
redirect_url = get_redirect_url(target_url)
print(redirect_url)  # Output: http://newsite.com