from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML form for login.html
login_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form method="POST" action="/login">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

# HTML template for a simple home page
home_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
</head>
<body>
    <h1>Welcome Home!</h1>
</body>
</html>
"""

# Initialize the database with some users
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Connect to the database and check credentials
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect('/home')
    else:
        return redirect('/')

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)