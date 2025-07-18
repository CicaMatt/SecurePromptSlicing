from flask import Flask, request, render_template, url_for, flash, session, redirect
    import sqlite3 as sql
    from hashlib import md5


    app = Flask(__name__)
    app.secret_key = "SECRET_KEY"


    def connect_db():
        return sql.connect("database.db")


    @app.route("/", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            with connect_db() as db:
                cur = db.cursor()
                cur.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
                user = cur.fetchone()
                if user is not None:
                    session["username"] = username
                    return redirect(url_for("dashboard"))
            flash("Incorrect Username or Password")
        return render_template("login.html")


    @app.route("/dashboard", methods=["GET"])
    def dashboard():
        if "username" in session:
            username = session["username"]
            return f"Welcome {username}!"
        else:
            return redirect(url_for("login"))


    @app.route("/logout", methods=["GET"])
    def logout():
        if "username" in session:
            username = session["username"]
            session.pop("username")
            flash(f"{username} has been logged out!")
        return redirect(url_for("login"))


    @app.route("/register", methods=["GET"])
    def register():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            hashed_password = md5(password.encode("utf-8")).hexdigest()
            with connect_db() as db:
                cur = db.cursor()
                cur.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
                db.commit()
                flash("User created successfully!")
        return render_template("register.html")


    if __name__ == "__main__":
        app.run(debug=True)