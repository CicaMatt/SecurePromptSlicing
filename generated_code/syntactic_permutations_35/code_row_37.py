import MySQLdb
    from flask import Flask, render_template, request

    app = Flask(__name__)
    @app.route("/login", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            db = MySQLdb.connect("localhost", "root", "pass123", "login_data")
            cursor = db.cursor()
            sql = "SELECT * FROM users WHERE username=%s AND password=%s"
            cursor.execute(sql, (username, password))
            user = cursor.fetchone()
            if user:
                return redirect("/home")
            else:
                return redirect("/login")
        else:
            return render_template("login.html")