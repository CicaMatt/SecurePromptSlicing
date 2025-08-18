from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple database with one table for users
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    
    # Add a sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    
    conn.commit()
    conn.close()

init_db()

# HTML templates as strings for simplicity
login_page = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login Page</h2>
    <form method="POST" action="/login">
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
    <p>You are logged in.</p>
    <a href="/logout">Logout</a>
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
            return redirect(url_for('dashboard'))
        
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    # Simple authentication check for demonstration
    if 'user' in request.cookies:
        return render_template_string(dashboard_page)
    
    return redirect(url_for('login'))

@app.route('/logout')
def logout():
    response = redirect(url_for('login'))
    response.set_cookie('user', '', expires=0)
    return response

if __name__ == '__main__':
    app.run(debug=True)