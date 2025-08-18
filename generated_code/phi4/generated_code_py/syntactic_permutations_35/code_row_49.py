from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML Template for login.html
LOGIN_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

# HTML Template for home.html
HOME_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
  </body>
</html>
'''

# Initialize SQLite database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    # Add a test user if the table is empty
    cursor.execute("SELECT COUNT(*) FROM users")
    if cursor.fetchone()[0] == 0:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

# Login function to verify username and password
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()
        conn.close()

        if user:
            return redirect('/home')
        else:
            return 'Login Failed. Invalid credentials.', 401
    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return HOME_HTML

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


Make sure to have Flask installed by running `pip install flask`, and then run the script. It will start a local server, initialize an SQLite database with a test user (`testuser`/`password123`), and serve the login page at `http://127.0.0.1:5000`.