from flask import Flask, request, redirect
    app = Flask(__name__)
    
    @app.route("/")
    def index():
        return "Login to change your email!"
    
    @app.route("/login", methods=["POST"])
    def login():
        old_email = request.form.get("old_email")
        password = request.form.get("password")
        if old_email == "admin@example.com" and password == "password123":
            return redirect("/change-email")
        else:
            return "Incorrect email or password!"
    
    @app.route("/change-email", methods=["POST"])
    def change_email():
        new_email = request.form.get("new_email")
        if new_email != "":
            return f"Email changed to {new_email}!"
        else:
            return "Invalid email address!"