from flask import Flask, redirect, render_template, request, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'super secret key'

@app.route('/')
def home():
    return '<h1>Welcome to our login system!</h1>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        connection = sqlite3.connect('database.db')
        cursor = connection.cursor()
        query = "SELECT * FROM users WHERE email = ? AND password = ?"
        result = cursor.execute(query, (email, password))
        if len(result.fetchall()) > 0:
            session['logged_in'] = True
            return redirect('/dashboard')
        else:
            return '<h1>Invalid email or password!</h1>'
    return render_template('login.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        connection = sqlite3.connect('database.db')
        cursor = connection.cursor()
        query = "INSERT INTO users (email, password) VALUES (?, ?)"
        cursor.execute(query, (email, password))
        connection.commit()
        return redirect('/login')
    return render_template('register.html')

@app.route('/dashboard', methods=['GET'])
def dashboard():
    if 'logged_in' in session:
        email = request.form['email']
        password = request.form['password']
        connection = sqlite3.connect('database.db')
        cursor = connection.cursor()
        query = "SELECT * FROM users WHERE email = ? AND password = ?"
        result = cursor.execute(query, (email, password))
        if len(result.fetchall()) > 0:
            return render_template('dashboard.html')
        else:
            return redirect('/login')
    else:
        return redirect('/login')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        connection = sqlite3.connect('database.db')
        cursor = connection.cursor()
        query = "SELECT * FROM users WHERE email = ? AND password = ?"
        result = cursor.execute(query, (old_email, password))
        if len(result.fetchall()) > 0:
            query = "UPDATE users SET email = ? WHERE email = ? AND password = ?"
            result = cursor.execute(query, (new_email, old_email, password))
            connection.commit()
            return redirect('/dashboard')
        else:
            return '<h1>Invalid email or password!</h1>'
    return render_template('change-email.html')

if __name__ == '__main__':
    app.run(debug=True)