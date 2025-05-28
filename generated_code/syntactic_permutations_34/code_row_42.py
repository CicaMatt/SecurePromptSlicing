import sys
    import os
    import mysql.connector as mydb
    from flask import Flask, request, render_template, session, redirect
    app = Flask(__name__)
    app.secret_key = "SuperSecretKey"

    def logInUser(username, password):
        conn = mydb.connect(host='localhost', user='root', password='password', database='login')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
        result = cursor.fetchall()
        if len(result) > 0:
            return True
        return False

    @app.route("/", methods=["GET", "POST"])
    def index():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if logInUser(username, password):
                session['logged_in'] = True
                return redirect('/dashboard')
            else:
                return "Invalid Credentials"
        return render_template('index.html')

    @app.route("/dashboard")
    def dashboard():
        if 'logged_in' in session:
            return render_template('dashboard.html')
        else:
            return redirect('/')

    if __name__ == "__main__":
        app.run(debug=True)