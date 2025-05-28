import requests
    
    def login():
        return requests.get("https://www.example.com/login")
    
    def do_login(username, password):
        data = {"username": username, "password": password}
        headers = {"Content-Type": "application/json"}
        return requests.post("https://www.example.com/dologin", json=data, headers=headers)
    
    def index():
        return requests.get("https://www.example.com")
    
    def users(user_id):
        return requests.get(f"https://www.example.com/users/{user_id}")
    
    def admin_page():
        return requests.get("https://www.example.com/admin")