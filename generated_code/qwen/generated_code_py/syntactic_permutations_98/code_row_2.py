from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

# Create SQLite database and table if not exists
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')
conn.commit()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        password_hash = hashlib.sha256(password.encode()).hexdigest()
        
        # Insert into database
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        
        return f"User {username} registered successfully!"
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)