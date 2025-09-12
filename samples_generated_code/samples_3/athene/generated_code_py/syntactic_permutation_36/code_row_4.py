import sqlite3
from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    conn.close()
    if user and user[1] == password:
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return redirect('/home')
        else:
            return render_template('login.html', error='Incorrect username or password')
    return render_template('login.html')

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)