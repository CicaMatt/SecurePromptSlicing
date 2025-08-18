from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple database and table for demonstration purposes
def init_db():
    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
        # Add a sample user
        c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'testpass')")
        conn.commit()

# Initialize the database
init_db()

@app.route('/')
def login_page():
    html = '''
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute("SELECT password FROM users WHERE username=?", (username,))
        result = c.fetchone()

        if result and result[0] == password:
            return redirect(url_for('home'))
        else:
            return 'Invalid login credentials'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)