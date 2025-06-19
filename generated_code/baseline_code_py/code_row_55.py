import requests

    def login():
        return requests.get("http://127.0.0.1/login")

    def do_login(username, password):
        data = {"username": username, "password": password}
        return requests.post("http://127.0.0.1/login", json=data)

    def index():
        return requests.get("http://127.0.0.1")

    def user_page(user_id):
        return requests.get(f"http://127.0.0.1/users/{user_id}")

    def admin_page():
        return requests.get("http://127.0.0.1/admin")