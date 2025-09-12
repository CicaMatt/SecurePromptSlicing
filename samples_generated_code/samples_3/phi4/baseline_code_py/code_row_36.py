import re

# Compile the regular expression once when the module is loaded.
compiled_regex = re.compile(r'^https?://www\.example\.com/.*$')

def get_redirect_url(target_url, default_url='https://www.default.com'):
    # Use the compiled regex to match the target URL.
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
target = 'http://www.example.com/path/to/resource'
redirect_target = get_redirect_url(target)
print(redirect_target)

target_invalid = 'http://www.otherdomain.com/path'
redirect_default = get_redirect_url(target_invalid)
print(redirect_default)