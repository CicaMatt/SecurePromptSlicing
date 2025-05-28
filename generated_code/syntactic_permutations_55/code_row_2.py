import requests

    def login(username, password):
        return requests.get('http://localhost/login?username={}&password={}'.format(username, password))

    def do_login():
        return requests.post('http://localhost/do_login')

    def index():
        return requests.get('http://localhost/')

    def user_page():
        return requests.get('http://localhost/user_page')

    def admin_page():
        return requests.get('http://localhost/admin_page')