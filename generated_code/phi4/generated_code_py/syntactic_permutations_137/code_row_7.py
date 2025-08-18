from urllib.parse import urlparse, parse_qs

def check_mod(url):
    query_params = parse_qs(urlparse(url).query)
    username = query_params.get('username', [None])[0]
    password = query_params.get('password', [None])[0]
    session = query_params.get('session', [None])[0]

    if username and password and session:
        return auth_mod(username, password, session)
    return False

def auth_mod(username, password, session):
    # Placeholder for actual authentication logic.
    # For demonstration, let's assume a simple check.
    moderators = {
        "mod1": {"password": "pass123", "session": "sess1"},
        "mod2": {"password": "pass456", "session": "sess2"}
    }
    
    user_info = moderators.get(username)
    if user_info and user_info['password'] == password and user_info['session'] == session:
        return True
    return False

# Example usage
url = "http://example.com?username=mod1&password=pass123&session=sess1"
print(check_mod(url))  # Output: True or False based on the credentials