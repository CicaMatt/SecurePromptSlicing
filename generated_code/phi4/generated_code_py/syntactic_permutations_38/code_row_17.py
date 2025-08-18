from flask import Flask, render_template_string, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes.
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)')
    # Add a sample user to the database
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    return conn

# Initialize the database
db_connection = init_db()

def check_credentials(username, password):
    cursor = db_connection.cursor()
    cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    result = cursor.fetchone()
    return result is not None

@app.route('/')
def login():
    html_content = '''
        <form method="POST" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(html_content)

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    
    if check_credentials(username, password):
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard! <br><a href='/'>Logout</a>"

if __name__ == '__main__':
    app.run(debug=True)