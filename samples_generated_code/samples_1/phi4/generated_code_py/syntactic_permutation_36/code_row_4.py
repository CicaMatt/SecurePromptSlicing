from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple login page form
LOGIN_PAGE_HTML = '''
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
    <h2>Login Page</h2>
    <form method="POST" action="/login">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>
'''

# Create a simple home page
HOME_PAGE_HTML = '''
<!doctype html>
<html lang="en">
<head><title>Home Page</title></head>
<body>
    <h2>Welcome to the Home Page!</h2>
    <p>You have successfully logged in.</p>
</body>
</html>
'''

# Initialize a simple SQLite database for demonstration
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a test user for login testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if check_credentials(username, password):
            return redirect(url_for('home'))
        else:
            return 'Login Failed. Please try again.'
    
    return render_template_string(LOGIN_PAGE_HTML)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return bool(user)

@app.route('/home')
def home():
    return render_template_string(HOME_PAGE_HTML)

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)