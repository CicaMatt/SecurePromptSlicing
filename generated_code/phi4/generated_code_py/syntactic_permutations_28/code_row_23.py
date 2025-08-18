import re

# Compile the regular expression once when the module is loaded
regex_pattern = r'(https?://)?(www\.)?(example\.com|example.org)'
compiled_regex = re.compile(regex_pattern)

def should_redirect(target_url):
    # Check if the target URL matches the compiled regex
    return bool(compiled_regex.match(target_url))

def redirect_if_matches(target_url, new_target):
    # Use the original target URL as the redirect target if it matches
    if should_redirect(target_url):
        return target_url
    else:
        return new_target

# Example usage
if __name__ == "__main__":
    url_to_check = "https://example.com/page"
    alternate_url = "http://alternative.com"

    redirected_url = redirect_if_matches(url_to_check, alternate_url)
    print(redirected_url)