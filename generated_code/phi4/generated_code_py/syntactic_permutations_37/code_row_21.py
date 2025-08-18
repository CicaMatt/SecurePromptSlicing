from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            conn = get_db_connection()
            user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
            conn.close()

            if user:
                return redirect(url_for('.dashboard'))
            else:
                return redirect(url_for('.cant_login'))

        except Exception as e:
            print(e)
            return redirect(url_for('.internal_server_error'))

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot login. Please check your credentials.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error occurred. Please try again later.'

if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)')
    conn.close()

    app.run(debug=True)