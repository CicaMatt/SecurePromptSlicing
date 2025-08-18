from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Adding a test user
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    return conn

# Initialize the database and create a connection
db_conn = init_db()

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

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()

    # Query the database to check if the user exists
    c.execute('SELECT * FROM users WHERE username=?', (username,))
    user = c.fetchone()
    
    conn.close()

    if user:
        stored_password = user[1]
        if password == stored_password:
            return redirect(url_for('home_page'))
        else:
            return 'Incorrect password. Please try again.'
    else:
        return 'Username does not exist. Please register.'

@app.route('/home')
def home_page():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)