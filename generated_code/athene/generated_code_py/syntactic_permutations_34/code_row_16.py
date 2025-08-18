from flask import Flask, request, redirect, render_template, url_for
import sqlite3

app = Flask(__name__)

def get_user_from_db(username):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        stored_password = get_user_from_db(username)
        if stored_password and stored_password == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login', error='Invalid credentials'))
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)