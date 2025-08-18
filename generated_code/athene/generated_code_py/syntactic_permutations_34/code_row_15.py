import sqlite3
from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Sample user for testing
    if not list(c.execute("SELECT * FROM users WHERE username='testuser'")):
        c.execute("INSERT INTO users VALUES ('testuser', 'testpass')")
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    user = list(c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password)))
    conn.close()

    if user:
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)


<!-- login.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>