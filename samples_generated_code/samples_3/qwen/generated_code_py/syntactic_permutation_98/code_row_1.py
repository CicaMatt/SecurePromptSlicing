from flask import Flask, request, render_template_string
import hashlib
import sqlite3

app = Flask(__name__)

# Initialize SQLite Database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)''')
conn.commit()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
            conn.commit()
            return "Registration successful!"
        except sqlite3.IntegrityError:
            return "Username already exists. Please choose a different one."
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)