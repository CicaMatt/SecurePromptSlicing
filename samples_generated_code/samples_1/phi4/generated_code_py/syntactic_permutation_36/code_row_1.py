import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def login(username, password):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT password FROM users WHERE username=?', (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result is not None:
        return result[0] == password
    return False

@app.route('/')
def login_page():
    form_html = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    
    if login(username, password):
        return redirect('/home')
    else:
        return "Invalid credentials. Please try again."

@app.route('/home')
def home_page():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)