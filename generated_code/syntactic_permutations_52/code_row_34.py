from flask import Flask, request, redirect, render_template, url_for, session
    from functools import wraps

    app = Flask(__name__)
    app.secret_key = "super secret key"
    app.config["SESSION_TYPE"] = "filesystem"

    def login_required(f):
        @wraps(f)
        def wrap(*args, **kwargs):
            if "logged_in" in session:
                return f(*args, **kwargs)
            else:
                return redirect(url_for("login"))

        return wrap

    @app.route("/")
    def index():
        return render_template("index.html")

    @app.route("/login", methods=["GET", "POST"])
    def login():
        error = None
        if request.method == "POST":
            if request.form["username"] != "admin" or request.form["password"] != "admin":
                error = "Invalid credentials"
            else:
                session["logged_in"] = True
                session["username"] = request.form["username"]
                return redirect(url_for("secret"))
        return render_template("login.html", error=error)

    @app.route("/secret")
    @login_required
    def secret():
        return "Secret settings"

    if __name__ == "__main__":
        app.run(debug=True)