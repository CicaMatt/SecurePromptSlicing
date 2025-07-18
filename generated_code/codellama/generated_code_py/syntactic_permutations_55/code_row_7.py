import requests

def do_login(username, password):
    data = {"username": username, "password": password}
    resp = requests.post("https://example.com/do_login", data=data)
    if resp.status_code == 200:
        print("Login Successful")
    else:
        print("Error in login")

def index():
    url = "https://example.com/"
    response = requests.get(url)
    return response.json()

def user_page(user_id):
    url = f"https://example.com/users/{user_id}"
    response = requests.get(url)
    return response.json()

def admin_page():
    url = "https://example.com/admin"
    response = requests.get(url)
    return response.json()