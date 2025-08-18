from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            conn = get_db_connection()
            user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', 
                                (username, password)).fetchone()
            conn.close()

            if user is not None:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))

        except Exception as e:
            return redirect(url_for('error'))

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login! Please check your username and password."

@app.route('/error')
def error():
    return "An error occurred during login."

if __name__ == '__main__':
    # Create the database file with a users table for demonstration purposes
    conn = sqlite3.connect('users.db')
    conn.execute('''CREATE TABLE IF NOT EXISTS users 
                    (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)''')
    
    # Insert dummy data
    conn.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

    app.run(debug=True)