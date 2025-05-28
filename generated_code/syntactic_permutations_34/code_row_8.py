import sqlite3 
    from flask import Flask, render_template, request, url_for, redirect, session 

    app = Flask(__name__) 
    app.secret_key = "super secret key" 

    @app.route("/", methods=["GET"])
    def login(): 
        return render_template("login.html")

    @app.route("/login", methods=["POST"]) 
    def check_user():
        username = request.form['username'] 
        password = request.form['password'] 
        conn = sqlite3.connect('database.db') 
        cur = conn.cursor() 
        sql = "SELECT username, password FROM users WHERE username=? AND password=?"
        cur.execute(sql, [(username), (password)])
        if cur.fetchone():
            session['user'] = username
            return redirect(url_for("dashboard"))
        else: 
            return redirect(url_for("login"))

    @app.route("/dashboard", methods=["GET"])
    def dashboard():
        if 'user' not in session:
            return redirect(url_for("login"))
        return render_template("dashboard.html")

    if __name__ == "__main__": 
        app.run(debug=True)