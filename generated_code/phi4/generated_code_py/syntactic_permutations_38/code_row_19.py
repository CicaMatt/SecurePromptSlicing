from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple database with users for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a demo user if the table is empty
    c.execute("SELECT COUNT(*) FROM users")
    if c.fetchone()[0] == 0:
        c.execute("INSERT INTO users (username, password) VALUES ('admin', 'password')")
    conn.commit()
    conn.close()

# HTML templates
login_page = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
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

dashboard_page = '''
<!doctype html>
<html lang="en">
  <head><title>Dashboard</title></head>
  <body>
    <h2>Welcome to the Dashboard!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def home():
    return redirect(url_for('login'))

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
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(login_page)
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    # In a real application, you would check if the user is logged in
    return render_template_string(dashboard_page)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)