def login():
    return "GET /login HTTP/1.0\\nHost: www.example.com\n\n"

def do_login():
    return "POST /login HTTP/1.0\nHost: www.example.com\nContent-Length: 27\nContent-Type: application/x-www-form-urlencoded\n\nusername=foo&password=bar"

def index():
    return "GET /index HTTP/1.0\\nHost: www.example.com\n\n"

def user_page():
    return "GET /user_page HTTP/1.0\\nHost: www.example.com\n\n"

def do_something():
    return "GET /do_something HTTP/1.0\\nHost: www.example.com\n\n"