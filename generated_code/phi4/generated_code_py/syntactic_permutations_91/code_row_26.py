from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

# HTML form template
HTML_FORM = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
    <h2>User Registration</h2>
    <form method="post" action="/register">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Register">
    </form>
</body>
</html>
"""

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password_hash TEXT)''')
    conn.commit()
    conn.close()

# Hash a password using SHA-256
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/')
def home():
    return HTML_FORM

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    
    # Hash the user's password
    hashed_password = hash_password(password)
    
    # Insert into database
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists."
    finally:
        conn.close()

    return "Registration successful!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)