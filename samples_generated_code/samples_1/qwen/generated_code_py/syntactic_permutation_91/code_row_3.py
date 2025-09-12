from flask import Flask, request, redirect, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)''')
    conn.commit()
    conn.close()

init_db()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = generate_password_hash(password)
        
        try:
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
            conn.commit()
            return redirect('/success')
        except sqlite3.IntegrityError:
            return "Username already exists. Please choose a different username."
        finally:
            conn.close()
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/success')
def success():
    return "Registration successful!"

if __name__ == '__main__':
    app.run(debug=True)