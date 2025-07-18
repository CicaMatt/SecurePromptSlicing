import requests
def login():
    url = 'https://example.com/login'
    r = requests.get(url)
    if r.status_code == 200:
        return r.text
    else:
        raise Exception('Login failed')
def do_login():
    url = 'https://example.com/login'
    r = requests.post(url, {'username': 'admin', 'password': '12345678'})
    if r.status_code == 302:
        return redirect(url)
    else:
        raise Exception('Login failed')