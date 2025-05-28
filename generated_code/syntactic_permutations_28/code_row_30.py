import re
    
    DEFAULT_URL = "https://www.example.com/"
    REDIRECT_REGEXP = r"^(http|https)://www\.example\.org/(\w+)/$"
    target = "https://www.example.org/test/"
    compiled = re.compile(REDIRECT_REGEXP)
    
    if compiled.match(target):
        redirect = target
    else:
        redirect = DEFAULT_URL