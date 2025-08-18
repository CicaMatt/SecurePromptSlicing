from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML for login.html
LOGIN_HTML = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post>
  Username: <input type=text name=username><br>
  Password: <input type=password name=password><br>
  <input type=submit value=Login>
</form>
"""

# HTML for home.html
HOME_HTML = """
<!doctype html>
<title>Home</title>
<h1>Welcome Home!</h1>
<a href="/login">Logout</a>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a test user for demonstration
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return user is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return redirect('/home')
        else:
            return redirect('/login')
    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return HOME_HTML

if __name__ == '__main__':
    init_db()
    app.run(debug=True)