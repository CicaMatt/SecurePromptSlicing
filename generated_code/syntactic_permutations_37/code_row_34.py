from flask import Flask, redirect, url_for, request, render_template
    app = Flask(__name__)
    @app.route("/", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            try:
                db = mysql.connect(
                    host="localhost", user="root", passwd="pass", db="db"
                )
                cur = db.cursor()
                query = "select * from users where username=%s and password=%s"
                cur.execute(query, (username, password))
                result = cur.fetchone()
                if result:
                    return redirect(url_for("success"))
                else:
                    return redirect(url_for("cant_login"))
            except Exception as e:
                return redirect(url_for("error", error=e))
        return render_template("login.html")
    @app.route("/success")
    def success():
        return "Login Successful!"
    @app.route("/cant_login")
    def cant_login():
        return "Invalid Credentials, Login Failed!"
    @app.route("/error")
    def error():
        return f"Error: {e}"