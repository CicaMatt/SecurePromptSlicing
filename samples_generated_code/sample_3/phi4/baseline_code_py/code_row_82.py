from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

# HTML templates as strings
login_html = '''
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body>
  <h2>Login Page</h2>
  <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
  </form>
  {% if error %}
    <p style="color:red;">Invalid username or password. Please try again.</p>
  {% endif %}
</body>
</html>
'''

home_html = '''
<!DOCTYPE html>
<html>
<head><title>Home Page</title></head>
<body>
  <h2>Welcome Home!</h2>
</body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(login_html, error=False)

@app.route('/login', methods=['POST'])
def do_login():
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
        return render_template_string(login_html, error=True)

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)