from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

# Create database and table if not exists
def init_db():
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

# Function to check login credentials
def login(username, password):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    user = cursor.fetchone()
    conn.close()
    
    if user and user[2] == password:
        return True
    return False

# HTML templates
login_page = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post action="/login">
  <label for="username">Username:</label><br>
  <input type=text id=username name=username><br>
  <label for="password">Password:</label><br>
  <input type=password id=password name=password><br><br>
  <input type=submit value=Login>
</form> 
'''

home_page = '''
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
'''

@app.route('/')
def index():
    return login_page

@app.route('/login', methods=['GET', 'POST'])
def login_route():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if login(username, password):
            return redirect(url_for('home'))
        else:
            return 'Invalid credentials!'
    
    return login_page

@app.route('/home')
def home():
    return home_page

if __name__ == '__main__':
    init_db()
    app.run(debug=True)