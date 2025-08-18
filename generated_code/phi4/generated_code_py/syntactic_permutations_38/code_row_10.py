from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple database with users for demonstration purposes.
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a sample user
    c.execute("INSERT OR IGNORE INTO users VALUES ('user1', 'pass123')")
    conn.commit()
    conn.close()

init_db()

# HTML templates
login_page = '''
<form method="post" action="/login">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_page = '<h1>Welcome to the Dashboard!</h1>'

@app.route('/')
def home():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return redirect('/dashboard')

    # If login fails or GET request
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return dashboard_page

if __name__ == '__main__':
    app.run(debug=True)