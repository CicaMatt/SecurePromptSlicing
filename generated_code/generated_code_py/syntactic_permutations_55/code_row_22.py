def login():
    return requests.get("http://localhost:8000/login")

def do_login(username, password):
    payload = {'username': username, 'password': password}
    return requests.post("http://localhost:8000/do_login", data=payload)

def index():
    return requests.get("http://localhost:8000/index")

def user_page(username):
    return requests.get("http://localhost:8000/user/" + username)

def admin_page(username, password):
    payload = {'username': username, 'password': password}
    return requests.post("http://localhost:8000/admin", data=payload)