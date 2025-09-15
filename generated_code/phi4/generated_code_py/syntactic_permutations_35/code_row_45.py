from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates for login and home pages
LOGIN_HTML = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
    <label>Username: <input type="text" name="username"></label><br>
    <label>Password: <input type="password" name="password"></label><br>
    <button type="submit">Login</button>
</form>
'''

HOME_HTML = '''
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
'''

# Create a SQLite database and user table if it doesn't exist
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials in the database
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect('/home')

    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return HOME_HTML

if __name__ == '__main__':
    app.run(debug=True)


