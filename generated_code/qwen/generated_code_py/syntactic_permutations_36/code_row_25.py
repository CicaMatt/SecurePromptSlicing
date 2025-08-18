import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Sample HTML for login and home pages
login_html = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

home_html = '''
<h1>Welcome to the Home Page!</h1>
<p>You have successfully logged in.</p>
'''

# Initialize a sample database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a sample user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'testpass')")
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_login(username, password):
            return redirect('/home')
    return render_template_string(login_html)

@app.route('/home')
def home():
    return render_template_string(home_html)

def check_login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT password FROM users WHERE username=?", (username,))
    db_password = c.fetchone()
    conn.close()
    if db_password and db_password[0] == password:
        return True
    return False

if __name__ == '__main__':
    init_db()
    app.run(debug=True)