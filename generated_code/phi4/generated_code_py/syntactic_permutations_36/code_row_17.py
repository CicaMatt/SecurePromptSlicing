from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Database setup for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a test user for login attempts
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login_page():
    form = '''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(form)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    result = c.fetchone()
    conn.close()
    return result is not None

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if check_credentials(username, password):
        return redirect('/home')
    else:
        return "Invalid credentials. Please try again."

@app.route('/home')
def home_page():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)