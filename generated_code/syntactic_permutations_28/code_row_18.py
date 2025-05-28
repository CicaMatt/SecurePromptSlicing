import re
    
    target_url = 'https://www.example.com/news'
    default_url = 'https://www.example.com/'
    
    regex = r'^/[a-z]+/?$'
    
    if re.match(regex, target_url):
        redirect_url = target_url
    else:
        redirect_url = default_url