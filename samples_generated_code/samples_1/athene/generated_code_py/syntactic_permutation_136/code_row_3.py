import urllib.parse

def check_mod(url):
    parsed_url = urllib.parse.urlparse(url)
    query_params = urllib.parse.parse_qs(parsed_url.query)
    username = query_params.get('username', [''])[0]
    password = query_params.get('password', [''])[0]
    
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    return ''