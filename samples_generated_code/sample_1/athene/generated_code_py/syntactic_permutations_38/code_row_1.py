import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Initialize database
conn = sqlite3.connect(':memory:', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE users (username TEXT, password TEXT)''')
c.execute("INSERT INTO users VALUES ('admin', 'password123')")
conn.commit()

def authenticate(username, password):
    c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    return c.fetchone() is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if authenticate(username, password):
            return redirect('/dashboard')
        else:
            return render_template_string('<p>Invalid credentials</p><form action="/login" method="post"><input name="username" type="text"/><input name="password" type="password"/><button type="submit">Login</button></form>')
    return render_template_string('<form action="/login" method="post"><input name="username" type="text"/><input name="password" type="password"/><button type="submit">Login</button></form>')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)