import base64
def check_mod(username, password):
    # username and password are in base 64
    return (base64.b64decode(username).decode('utf-8') == 'admin' and base64.b64decode(password).decode('utf-8') == 'secret')