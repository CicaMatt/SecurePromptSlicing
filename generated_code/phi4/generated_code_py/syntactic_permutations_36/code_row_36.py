from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def connect_db():
    conn = sqlite3.connect('users.db')
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = connect_db()
        cursor = conn.cursor()

        # Query to check if the user exists
        cursor.execute('SELECT * FROM users WHERE username=?', (username,))
        user = cursor.fetchone()

        if user:
            stored_password = user[1]  # Assuming password is at index 1 in the DB

            if password == stored_password:
                return redirect(url_for('home'))  # Redirect to home page on successful login
            else:
                return 'Incorrect password'
        
        return 'Username does not exist'

    return '''
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    # Ensure database and table exist
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)')
    conn.commit()
    conn.close()

    app.run(debug=True)