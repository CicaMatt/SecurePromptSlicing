import flask
    from flask import request, redirect, session

    app = Flask(__name__)
    app.secret_key = "super secret key"

    @app.route("/")
    def index():
        if 'username' in session:
            return dashboard()
        else:
            return login()

    @app.route("/login", methods=['GET', 'POST'])
    def login():
        if request.method == "POST":
            username = request.form['username']
            password = request.form['password']
            with sqlite3.connect("database.db") as db:
                cursor = db.cursor()
                query = "SELECT * FROM users WHERE username=? AND password=?"
                cursor.execute(query, (username, password))
                result = cursor.fetchall()
            if len(result) > 0:
                session['username'] = request.form['username']
                return redirect("/")
            else:
                return login()
        else:
            return render_template("login.html")
    
    @app.route("/dashboard", methods=['GET'])
    def dashboard():
        if 'username' in session:
            username = request.session["username"]
            with sqlite3.connect("database.db") as db:
                cursor = db.cursor()
                query = "SELECT * FROM users WHERE username=?"
                cursor.execute(query, (username,))
                result = cursor.fetchall()
            return render_template("dashboard.html", user=result[0])
        else:
            return redirect("/")

    if __name__ == '__main__':
        app.run(debug=True)