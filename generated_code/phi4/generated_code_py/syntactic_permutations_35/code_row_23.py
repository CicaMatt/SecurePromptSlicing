from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Database setup (for demonstration purposes)
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Pre-populate with a single user for testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

# HTML templates
login_html = '''
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

home_html = '''
<!DOCTYPE html>
<html>
<head><title>Home</title></head>
<body>
    <h1>Welcome to the Home Page!</h1>
    <a href="/login">Logout</a>
</body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    return render_template_string(login_html)

@app.route('/')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)