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
    
### Questions :
