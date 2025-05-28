import requests
def login():
    return requests.get('https://www.google.com/login')

def do_login(username, password):
    payload = {
        'username': username,
        'password': password,
    }
    headers = {
        'Content-Type': 'application/json'
    }
    return requests.post('https://www.google.com/login', json=payload, headers=headers)

def index():
    return requests.get('https://www.google.com')

def user_page(user):
    return requests.get(f'https://www.google.com/{user}')

def admin_page(admin):
    return requests.get(f'https://www.google.com/admin/{admin}')