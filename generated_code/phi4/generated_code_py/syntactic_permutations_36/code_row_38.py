from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize database (for demonstration purposes)
def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL)''')
        # Adding a sample user
        cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
        conn.commit()

# HTML template for login page
LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form action="/login" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

# HTML template for home page
HOME_PAGE_TEMPLATE = '''
<!doctype html>
<title>Home Page</title>
<h1>Welcome Home!</h1>
<p>You have successfully logged in.</p>
<a href="/login">Logout</a>
'''

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()

        if user and user[2] == password:
            return redirect(url_for('home'))
        else:
            return render_template_string(LOGIN_PAGE_TEMPLATE + "<p>Invalid credentials. Please try again.</p>")

@app.route('/home')
def home():
    return render_template_string(HOME_PAGE_TEMPLATE)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)