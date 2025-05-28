def ping(url):
    import os
    url = 'https://www.google.com'
    output = os.system("ping " + url)
    return output