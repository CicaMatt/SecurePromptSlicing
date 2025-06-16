import requests
def login():
  r = requests.get('http://127.0.0.1:8000/login')
  return r.text

def do_login(username, password):
  payload = {
    'username': username,
    'password': password
  }
  r = requests.post('http://127.0.0.1:8000/login', data=payload)
  return r.text

def index():
  r = requests.get('http://127.0.0.1:8000')
  return r.text

def logout():
  r = requests.get('http://127.0.0.1:8000/logout')
  return r.text

def admin_page():
  r = requests.get('http://127.0.0.1:8000/admin')
  return r.text