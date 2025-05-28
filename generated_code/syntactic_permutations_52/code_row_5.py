from flask import Flask, request, session, redirect, url_for
    
    app = Flask(__name__)
    app.config["SECRET_KEY"] = "mysecretkey"
    
    @app.route("/login", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form.get("username")
            password = request.form.get("password")
            if username == "admin" and password == "secret":
                session["user"] = username
                return redirect(url_for("secret"))
        return """
        <form action="" method="post">
            <p><input type=text name=username>
            <p><input type=password name=password>
            <p><input type=submit value=Login>
        </form>"""
    
    @app.route("/secret")
    def secret():
        if "user" not in session:
            return redirect(url_for("login"))
        return "<h1>Secret Settings</h1>"
    
    if __name__ == "__main__":
        app.run()