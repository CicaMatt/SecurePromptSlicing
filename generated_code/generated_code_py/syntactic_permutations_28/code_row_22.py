import re

def redirect(url):
    # Compile regular expression once when module is loaded
    regex = re.compile('^/[a-z]+/[0-9]+$')
    
    # If URL matches the pattern; use it as the redirect target
    if regex.match(url) is not None:
        return url
    else:
        # Use default URL if regular expression does not match
        return 'https://www.example.com'