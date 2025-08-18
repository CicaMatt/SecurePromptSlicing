from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Create in-memory SQLite database and table for demonstration purposes
connection = sqlite3.connect('users.db', check_same_thread=False)
cursor = connection.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
connection.commit()

registration_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Register</title>
  </head>
  <body>
    <h1>Register</h1>
    <form method="post" action="/register">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
'''

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = generate_password_hash(password)
        
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        connection.commit()
        
        return f"User {username} registered successfully!"
    
    return render_template_string(registration_page)

if __name__ == '__main__':
    app.run(debug=True)