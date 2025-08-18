import sqlite3
from flask import Flask, request, redirect

app = Flask(__name__)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        if cursor.fetchone():
            return 'success'
        else:
            return 'cant_login'
    except Exception:
        return 'internal_server_error'
    finally:
        conn.close()

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    result = check_credentials(username, password)
    return redirect(result)

if __name__ == '__main__':
    app.run(debug=True)