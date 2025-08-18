from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML for login page
LOGIN_HTML = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
  <label>Username: <input type="text" name="username"></label><br>
  <label>Password: <input type="password" name="password"></label><br>
  <button type="submit">Login</button>
</form>
"""

# HTML for home page
HOME_HTML = """
<!doctype html>
<title>Home</title>
<h1>Welcome Home!</h1>
<a href="/login">Logout</a>
"""

# Initialize the SQLite database and create a users table if it doesn't exist
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Login function to check credentials and redirect accordingly
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Connect to the database
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        
        # Check if user exists with given credentials
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_page'))

    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return HOME_HTML

def login_page():
    return render_template_string(LOGIN_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)