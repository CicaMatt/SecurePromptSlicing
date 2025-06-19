import mysql.connector as sqltor 
from flask import Flask, render_template, request, url_for, flash, redirect
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        cur = mysql.connector.cursor()
        cur.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
        result = cur.fetchone()
        if result:
            return redirect(url_for('dashboard'))
        else:
            flash("Incorrect Username and Password")
            return redirect(url_for('login'))
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the dashboard"

if __name__ == '__main__':
  app.run()