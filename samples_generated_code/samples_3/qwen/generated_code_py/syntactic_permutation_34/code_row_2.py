from flask import Flask, request, render_template, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Initialize database connection
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    if 'username' in session:
        return f"Welcome to your Dashboard, {session['username']}!"
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        session['username'] = user[0]
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>