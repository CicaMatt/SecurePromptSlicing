from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a test user
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT * FROM users WHERE username=?', (username,))
    user = c.fetchone()
    conn.close()
    
    if user and user[1] == password:
        return True
    else:
        return False

@app.route('/')
def login_page():
    html_content = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_content)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    
    if login(username, password):
        return redirect('/home')
    else:
        return "Invalid credentials", 401

@app.route('/home')
def home_page():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    create_database()
    app.run(debug=True)


Make sure you have Flask installed in your Python environment. You can install it using `pip install flask`. This code sets up a simple web application with login functionality using SQLite as the database.