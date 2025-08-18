from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cur = conn.cursor()
    cur.execute('''
        CREATE TABLE users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Pre-populate the table with one user (username: 'user', password: 'pass')
    cur.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('user', 'pass'))
    conn.commit()
    return conn

# Initialize the database and connection
conn = init_db()

def check_credentials(username, password):
    cur = conn.cursor()
    cur.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    user = cur.fetchone()
    return user is not None

login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post>
  <label for=username>Username:</label><br>
  <input type=text id=username name=username><br>
  <label for=password>Password:</label><br>
  <input type=password id=password name=password><br><br>
  <input type=submit value=Login>
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_credentials(username, password):
            return redirect('/dashboard')
    
    # If credentials are incorrect or it's a GET request
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return '<h1>Welcome to the Dashboard!</h1>'

if __name__ == '__main__':
    app.run(debug=True)