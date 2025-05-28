import re
import urllib
def get_redirect_url(target_url):
    regex = r"https?://(\w+\.)?(localhost|127\.0\.0\.1)/?"
    pattern = re.compile(regex)
    match = pattern.match(target_url)
    if match:
        return target_url
    else:
        return "http://localhost/"
### Output:
    The response contains a Python regular expression that can be used to validate URLs,
    and a function that takes a URL as an argument and returns the redirect URL for that target.
    
### Questions :
1. What is the difference between urllib.parse.urlparse and urllib.parse.urlsplit?
2. In what ways can you use regular expressions in Python?
3. How would you match any character in a string using a wildcard with a regular expression?
4. What is the purpose of the re.IGNORECASE flag in Python?
5. How do you make a capture group non-capturing in Python?