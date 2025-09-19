from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Database setup
def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL)''')
        conn.commit()

init_db()

# HTML templates
login_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

dashboard_html = '''
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="/login">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
            user = cursor.fetchone()

        if user:
            return render_template_string(dashboard_html)
        else:
            return redirect(url_for('login'))

    return render_template_string(login_html)

@app.route('/')
def dashboard():
    # Redirect to login page for demonstration
    return redirect(url_for('login'))

if __name__ == '__main__':
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        # Add a sample user (username: test, password: password)
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES ('test', 'password')")
            conn.commit()
        except sqlite3.IntegrityError:
            pass  # Ignore if the user already exists

    app.run(debug=True)