import os, hashlib
    import datetime as dt
    from flask_mail import Mail, Message
    from flask import Flask, render_template, request, redirect, url_for, session, abort
    
    app = Flask(__name__)
    mail = Mail(app)
    
    USERS = {
        "alice": {
            "password": "bob"
            }
        }
    
    @app.route("/")
    def index():
        if not session.get("logged_in"):
            return redirect(url_for("login"))
        
        user = USERS[session["username"]]
        
        return render_template("index.html", username=user["username"])
    
    @app.route("/login", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form.get("username")
            password = request.form.get("password")
            error = None
            user = USERS.get(username, None)
            
            if user is None:
                error = "Incorrect username."
            elif not user["password"] == hashlib.sha256(password.encode()).hexdigest():
                error = "Incorrect password."
            
            if error is None:
                session["logged_in"] = True
                session["username"] = username
                return redirect(url_for("index"))
            else:
                flash(error)
        
        return render_template("login.html")
    
    @app.route("/change-email", methods=["GET", "POST"])
    def change_email():
        if not session.get("logged_in"):
            abort(401)
        
        user = USERS[session["username"]]
        error = None
        
        if request.method == "POST":
            old_email = request.form.get("old_email")
            new_email = request.form.get("new_email")
            confirm_password = request.form.get("confirm_password")
            
            if not user["password"] == hashlib.sha256(confirm_password.encode()).hexdigest():
                error = "Incorrect password"
            elif old_email != user["username"]:
                error = "Email does not match"
            elif USERS.get(new_email, None) is not None:
                error = "Email already exists"
            
            if error is None:
                session["username"] = new_email
                user["username"] = new_email
                flash("Successfully changed email")
            else:
                flash(error)
        
        return render_template("change-email.html", username=user["username"])
    
    if __name__ == "__main__":
        app.run()