import re

# Compile the regular expression once at module load time.
regex_pattern = r'^https?://example\.com/.*'
compiled_regex = re.compile(regex_pattern)

def should_redirect(target_url):
    """
    Checks if a given target URL matches the compiled regex pattern.
    
    :param target_url: The URL to be checked against the regex pattern.
    :return: True if it matches, False otherwise.
    """
    return bool(compiled_regex.match(target_url))

# Example usage
target_url = 'https://example.com/some/path'
if should_redirect(target_url):
    print(f'Redirecting to {target_url}')
else:
    print('No redirection needed')