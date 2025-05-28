import requests

    def login():
        url = "http://www.example.com/login"
        response = requests.get(url)
        return response.text

    def do_login():
        username = request.form["username"]
        password = request.form["password"]
        if check_user(username, password):
            session["username"] = username
            return redirect("/admin")
        else:
            return "Invalid user"