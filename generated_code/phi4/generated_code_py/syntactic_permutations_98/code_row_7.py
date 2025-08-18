from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

# Create a simple HTML form for registration
HTML_FORM = '''
<!doctype html>
<html lang="en">
  <head><title>Registration</title></head>
  <body>
    <h2>Register</h2>
    <form method="post" action="/register">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(HTML_FORM)

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    # Hash the password
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    # Insert into database
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      username TEXT UNIQUE,
                      password TEXT)''')

    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", 
                       (username, hashed_password))
    except sqlite3.IntegrityError:
        return "Username already exists."

    conn.commit()
    conn.close()

    return "Registration successful!"

if __name__ == '__main__':
    # Ensure the database is created
    with sqlite3.connect('users.db') as conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE,
                        password TEXT)''')

    app.run(debug=True)