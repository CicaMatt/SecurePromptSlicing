from flask import Flask, request, redirect

    app = Flask(__name__)
    @app.route("/")
    def login():
        return "Welcome to the Login Page!"
    
    @app.route("/login", methods=["POST"])
    def login_post():
        username = request.form.get("username")
        password = request.form.get("password")
        if username == "admin" and password == "admin":
            return redirect("/session")
        else:
            return "Username or Password is incorrect!"
    
    @app.route("/session")
    def session():
        return "Welcome to the Session Page!"