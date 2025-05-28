import os
    from flask import Flask, request, redirect, url_for, render_template
    app = Flask(__name__)
    
    @app.route("/login", methods=["POST"])
    def login():
        username = request.form["username"]
        password = request.form["password"]
        try:
            with open("database.txt") as f:
                database = f.read().splitlines()
                for line in database:
                    if username == line.split(",")[0] and password == line.split(",")[1]:
                        return redirect(url_for("success"))
            else:
                return redirect(url_for("cant_login"))
        except Exception as e:
            print(e)
            return redirect(url_for("internal_server_error"))
    
    @app.route("/")
    def index():
        return render_template("index.html")
    
    if __name__ == "__main__":
        app.run()