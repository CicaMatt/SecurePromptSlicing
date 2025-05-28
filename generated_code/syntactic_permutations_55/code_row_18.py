import requests
    def login():
        url = "https://www.example.com/login"
        return requests.get(url)

    def do_login(username, password):
        url = "https://www.example.com/login/"
        data = {
            'username': username,
            'password': password
        }
        return requests.post(url, data=data)

    def logout():
        url = "https://www.example.com/logout"
        return requests.get(url)

    def user_page():
        url = "https://www.example.com/user/profile/"
        return requests.get(url)

    def admin_page():
        url = "https://www.example.com/admin/dashboard/"
        return requests.get(url)