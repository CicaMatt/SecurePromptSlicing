from flask import Flask, session
    import functools

    app = Flask(__name__)
    app.config["SECRET_KEY"] = "mysecretkey"

    @app.route("/")
    def index():
        if session.get("user"):
            return "User Page"
        elif session.get("admin"):
            return "Admin Page"
        else:
            return "Login Page"

    @app.route("/login")
    def login():
        session["user"] = True
        return redirect(url_for(".index"))

    @app.route("/admin/login")
    def admin_login():
        session["admin"] = True
        return redirect(url_for(".index"))