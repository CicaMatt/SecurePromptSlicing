import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r"your-regex-pattern-here")

def get_redirect_url(target_url, default_url):
    """
    Returns a redirected URL based on whether the target URL matches a pattern.

    :param target_url: The target URL to check against the regex pattern.
    :param default_url: The default URL to use if no match is found.
    :return: A string representing the redirect URL.
    """
    # Check if the target URL matches the compiled regular expression.
    if pattern.match(target_url):
        # If it matches, use the target URL as the redirect target.
        return target_url
    else:
        # If it doesn't match, use the default URL instead.
        return default_url

# Example usage of the function
if __name__ == "__main__":
    target = "example-target-url"
    default = "http://default-redirect.com"
    redirect_url = get_redirect_url(target, default)
    print(redirect_url)