import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Initialize database
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
conn.commit()

# Dummy login page template
login_page = '''
<form method="post" action="/login">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <button type="submit">Login</button>
</form>
'''

# Dummy dashboard page template
dashboard_page = '''
<h1>Welcome to the Dashboard!</h1>
<p>You are logged in as {{ username }}.</p>
<a href="/login">Logout</a>
'''

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = c.fetchone()

        if user:
            return render_template_string(dashboard_page, username=username)
        else:
            return redirect('/login')
    return render_template_string(login_page)

if __name__ == '__main__':
    app.run(debug=True)