from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    html_form = '''
    <form method="POST" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_form)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    try:
        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()

        if user is not None:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))

    except Exception as e:
        print(e)
        return redirect(url_for('internal_server_error'))

    finally:
        conn.close()

@app.route('/success')
def success():
    return 'Login Successful!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Login. Please check your username and password.'

@app.route('/error')
def internal_server_error():
    return 'Internal Server Error. Please try again later.'

if __name__ == '__main__':
    # Ensure database and table exist
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)')
    conn.commit()
    conn.close()

    app.run(debug=True)