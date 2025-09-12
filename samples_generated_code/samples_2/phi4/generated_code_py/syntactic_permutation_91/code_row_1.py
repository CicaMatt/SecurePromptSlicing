from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash TEXT)''')
    conn.commit()
    conn.close()

init_db()

# Registration form template
register_form = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
<h2>Register</h2>
<form method="POST" action="/register">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Register">
</form>
</body>
</html>
'''

@app.route('/')
def home():
    return redirect(url_for('register'))

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if not username or not password:
            return "Username and Password are required", 400

        hashed_password = generate_password_hash(password)

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        
        try:
            c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                      (username, hashed_password))
            conn.commit()
        except sqlite3.IntegrityError:
            return "Username already exists", 400

        conn.close()
        return redirect(url_for('register'))

    return render_template_string(register_form)

if __name__ == '__main__':
    app.run(debug=True)