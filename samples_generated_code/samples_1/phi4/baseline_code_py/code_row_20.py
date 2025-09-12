from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_table():
    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
        conn.commit()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        with sqlite3.connect('users.db') as conn:
            c = conn.cursor()
            c.execute('SELECT * FROM users WHERE username=?', (username,))
            user = c.fetchone()
            if user and user[1] == password:
                return redirect(url_for('home'))
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
    create_table()
    app.run(debug=True)