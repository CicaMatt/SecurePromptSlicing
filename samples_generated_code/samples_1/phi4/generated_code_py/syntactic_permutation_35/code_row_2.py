from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login.html
LOGIN_HTML = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

# Create a simple HTML template for home.html
HOME_HTML = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
</head>
<body>
    <h1>Welcome to the Home Page!</h1>
    <a href="/login">Logout</a>
</body>
</html>
'''

# Initialize SQLite database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a test user
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Check if username and password exist in the database
def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    result = c.fetchone()
    conn.close()
    return result is not None

# Route for the login page
@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_HTML)

# Route to handle form submission
@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    
    if check_credentials(username, password):
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

# Route for the home page
@app.route('/')
def home():
    return render_template_string(HOME_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)