from flask import Flask, request, redirect, url_for, render_template_string

import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT
        )
    ''')
    # Add a sample user for testing purposes
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def check_credentials(username, password):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    user = cursor.fetchone()
    conn.close()
    return user is not None

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return redirect(url_for('dashboard'))
        else:
            error_message = "Invalid username or password"
    else:
        error_message = None
    login_page = '''
    <html>
      <head><title>Login</title></head>
      <body>
        <h2>Login Page</h2>
        <form method="post">
          Username: <input type="text" name="username"><br>
          Password: <input type="password" name="password"><br>
          <input type="submit" value="Login">
        </form>
        {% if error_message %}
            <p style="color:red;">{{ error_message }}</p>
        {% endif %}
      </body>
    </html>
    '''
    return render_template_string(login_page, error_message=error_message)

@app.route('/dashboard')
def dashboard():
    return "<h2>Welcome to the Dashboard</h2>"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)