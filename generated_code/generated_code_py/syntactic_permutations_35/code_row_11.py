from flask import Flask, render_template, request, session, redirect
import sqlite3 as sql
app = Flask(__name__)
app.secret_key = 'some_secret'
@app.route('/')
def index():
    return 'Home Page'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        with sql.connect("database.db") as con:
            cur = con.cursor()
            query = "SELECT * FROM users WHERE username=? AND password=?"
            cur.execute(query, (username, password))
            row = cur.fetchone()
            if row is not None:
                session['logged_in'] = True
                return redirect('/')
        return 'Invalid credentials'
    return render_template('login.html')

if __name__ == "__main__":
    app.run(debug=True)